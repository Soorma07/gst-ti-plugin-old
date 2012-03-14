/*
 * Authors:
 *   Diego Dompe <ddompe@gmail.com>
 *   Luis Arce <luis.arce@rigerun.com>
 *
 * Copyright (C) 2012 RidgeRun	
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation version 2.1 of the License.
 *
 * This program is distributed #as is# WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */


#include <gst/gst.h>
#include <gstceh264encoder.h>

#define GST_CAT_DEFAULT gst_ce_h264_encoder_debug
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);

static GstStaticPadTemplate CEH264Encoder_sink_factory =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

static GstStaticPadTemplate CEH264Encoder_src_factory =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

static GstCaps *ce_h264_encoder_src_caps;

enum
{
  PROP_0,
  PROP_D
};

static void
gst_ce_h264_encoder_base_init (GstCEH264EncoderClass * klass)
{
  /* Initialize dynamic data */
}

static void
gst_ce_h264_encoder_base_finalize (GstCEH264EncoderClass * klass)
{
}

static void
gst_ce_h264_encoder_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  
   g_print("set_property h264\n");
  /* Set h264 encoder params */
  switch (prop_id) {
    default:
      break;
  }

}

static void
gst_ce_h264_encoder_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{

  /* Get h264 encoder params */
  switch (prop_id) {
    default:
      break;
  }
}

static gboolean
gst_ce_h264_encoder_sink_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  //GstBaseCEEnc *enc;
  //ogg_packet op;
  //gboolean res = TRUE;

  /* Obtain the instance of the class */	
  //enc = GST_BASECEENC (parent);

  return TRUE;
}

/* Obtain the caps of the element, for validation of the link with others elements */
static GstCaps *
gst_ce_h264_encoder_sink_getcaps (GstPad * pad, GstCaps * filter)
{
	
  GstCEH264Encoder *h264_encoder;
  GstPad *peer;
  GstCaps *caps;

  /* If we already have caps return them */
  if ((caps = gst_pad_get_current_caps (pad)) != NULL) {
	  return caps;
  }
  
  h264_encoder = GST_CE_H264_ENCODER (gst_pad_get_parent (pad));
  GstCEBaseEncoder *base_encoder = GST_CE_BASE_ENCODER(h264_encoder);
  /* If not exist the encoder instance, return a new empty cap */ 
  if (!h264_encoder) {
	  return gst_caps_new_empty ();
  }
    
  /* Obtain the peer of the pad */
  peer = gst_pad_get_peer (base_encoder->src_pad);
  if (peer) {
	
    const GstCaps *templ_caps;
    GstCaps *peer_caps, *tmp_caps;
    GstStructure *s;
    guint i, n;
	
	/* Obtain the caps of the peer pad */
    peer_caps = gst_pad_query_caps (peer, NULL);

    /* Translate peer caps to YUV */
    peer_caps = gst_caps_make_writable (peer_caps);
    n = gst_caps_get_size (peer_caps);
    for (i = 0; i < n; i++) {
      s = gst_caps_get_structure (peer_caps, i);

      gst_structure_set_name (s, "video/x-raw-yuv");
      gst_structure_remove_field (s, "streamheader");
    }
	
	  /* Obtain the template caps of the pad */
    templ_caps = gst_pad_get_pad_template_caps (pad);
	
	  /* Calculate the formats intersection between peer_caps and own caps */
    tmp_caps = gst_caps_intersect (peer_caps, templ_caps);
    caps = gst_caps_intersect (tmp_caps, ce_h264_encoder_src_caps);
    gst_caps_unref (tmp_caps);
    gst_caps_unref (peer_caps);
    gst_object_unref (peer);
    peer = NULL;
  } else {
	/* Obtain caps from a arbitrary way */
    caps = gst_caps_ref (ce_h264_encoder_src_caps);
  }
  gst_object_unref (h264_encoder);
	
  /* Filter the formats for the result */
  if (filter) {
    GstCaps *intersection;
	
	/* Calculate the formats intersection between caps provider and own caps */
    intersection =
        gst_caps_intersect_full (filter, caps, GST_CAPS_INTERSECT_FIRST);
   
    gst_caps_unref (caps);
    caps = intersection;
  }

  return caps;
}


static gboolean
gst_ce_h264_encoder_sink_query (GstPad * pad, GstObject * parent, GstQuery * query)
{	
  gboolean res = FALSE;
  
  g_print("Inicio _sink_query h264\n\n");
  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_CAPS:
    {
      GstCaps *filter, *caps;
      
      /* Fill the filter cap */
      gst_query_parse_caps (query, &filter);
      
      /* Get the caps */
      caps = gst_ce_h264_encoder_sink_getcaps (pad, filter);
      
      /* Set the caps */
      gst_query_set_caps_result (query, caps);
      
      gst_caps_unref (caps);
      res = TRUE;
      
      break;
    }
    default:
	  /* Sent the query to all pads internally linked to "pad". */	
      res = gst_pad_query_default (pad, parent, query);
      break;
  }
  g_print("Final _sink_query h264\n\n");
  return res;
}

static void gst_ce_h264_encoder_init (GstCEH264Encoder *h264_encoder) {
  
  g_print("Inicio _init h264\n\n");
  GstCEH264EncoderClass *h264_encoder_class = CE_H264_ENCODER_GET_CLASS(h264_encoder);
  
  /* Obtain base class and instance */
  GstCEBaseEncoderClass *base_encoder_class = GST_CE_BASE_ENCODER_CLASS(h264_encoder_class);
  GstCEBaseEncoder *base_encoder = GST_CE_BASE_ENCODER(h264_encoder);
  
  /* Obtain base video class */
  GstCEBaseVideoEncoderClass *base_video_encoder_class = GST_CE_BASE_VIDEO_ENCODER_CLASS(h264_encoder_class);
  
  
  /* Process the sinkpad */
  base_encoder->sink_pad =
      gst_pad_new_from_static_template (&CEH264Encoder_sink_factory, "sink");
  gst_pad_set_chain_function (base_encoder->sink_pad, base_video_encoder_class->encoder_chain);
  gst_pad_set_event_function (base_encoder->sink_pad, gst_ce_h264_encoder_sink_event);
  gst_pad_set_query_function (base_encoder->sink_pad, gst_ce_h264_encoder_sink_query);
  gst_element_add_pad (GST_ELEMENT (base_encoder), base_encoder->sink_pad);
  
  /* process the src pad */
  base_encoder->src_pad =
      gst_pad_new_from_static_template (&CEH264Encoder_src_factory, "src");
  //gst_pad_set_event_function (h264_encoder->srcpad, BaseCEEnc_src_event);
  gst_pad_use_fixed_caps (base_encoder->src_pad);
  gst_element_add_pad (GST_ELEMENT (base_encoder), base_encoder->src_pad);
  g_print("Final _init h264\n\n");
  
}

static void
gst_ce_h264_encoder_class_init  (GstCEH264EncoderClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (klass);
  
  GST_DEBUG_CATEGORY_INIT (gst_ce_h264_encoder_debug, "ceenc_h264", 0,
      "CodecEngine h264 encoder");

  gobject_class->set_property = gst_ce_h264_encoder_set_property;
  gobject_class->get_property = gst_ce_h264_encoder_get_property;
  
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&CEH264Encoder_src_factory));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&CEH264Encoder_src_factory));
  
  g_object_class_install_property (gobject_class, PROP_D,
      g_param_spec_boolean ("testd", "Test D", "Testing D", FALSE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  
  /* Caps can't do null */
  gchar *caps_string = g_strdup_printf ("ANY");
  ce_h264_encoder_src_caps = gst_caps_from_string (caps_string);
  g_free (caps_string);

}

static void
gst_ce_h264_encoder_class_finalize (GstCEH264EncoderClass * klass,
    gpointer * class_data)
{
}

/* Obtain the type of the class */
GType
gst_ce_h264_encoder_get_type (void)
{
  static GType object_type = 0;
  if (object_type == 0) {
    static const GTypeInfo object_info = {
      sizeof (GstCEH264EncoderClass),
      (GBaseInitFunc) gst_ce_h264_encoder_base_init,
      (GBaseFinalizeFunc) gst_ce_h264_encoder_base_finalize,
      (GClassInitFunc) gst_ce_h264_encoder_class_init,
      NULL,
      NULL,
      sizeof (GstCEH264Encoder),
      0,
      (GInstanceInitFunc) gst_ce_h264_encoder_init,
      NULL
    };

    object_type = g_type_register_static (GST_TYPE_CE_VIDENC1,
        "GstCEH264Encoder", &object_info, (GTypeFlags) 0);
  }
  return object_type;
};
