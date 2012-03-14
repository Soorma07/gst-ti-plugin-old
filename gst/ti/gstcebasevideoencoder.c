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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gstcebasevideoencoder.h>

#define GST_CAT_DEFAULT gst_ce_base_video_encoder_debug
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);

enum
{
  PROP_0,
  PROP_B
};


static void
gst_ce_base_video_encoder_base_init (GstCEBaseVideoEncoderClass * klass)
{
  /* Initialize dynamic data */
}

static void
gst_ce_base_video_encoder_base_finalize (GstCEBaseVideoEncoderClass * klass)
{
}

static void
gst_ce_base_video_encoder_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  
  g_print("set_property base video encoder\n");
  /* Set video encoder params */
  switch (prop_id) {
    default:
      break;
  }

}

static void
gst_ce_base_video_encoder_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{

  /* Get video encoder params */
  switch (prop_id) {
    default:
      break;
  }
}

static GstFlowReturn
gst_ce_base_video_encoder_default_chain (GstPad * pad, GstObject * parent,
    GstBuffer * buffer)
{
  
  GstCEBaseEncoder *base_encoder = GST_CE_BASE_ENCODER (parent);
  GST_DEBUG_OBJECT(base_encoder,"Entry to default chain");
  
  
  GST_DEBUG_OBJECT(base_encoder,"Leave default chain");
  return gst_pad_push (base_encoder->src_pad, buffer);
}

static void
gst_ce_base_video_encoder_class_init (GstCEBaseVideoEncoderClass * base_video_encoder_class)
{
  GObjectClass *gobject_class = (GObjectClass *) base_video_encoder_class;
  GstCEBaseEncoderClass *base_encoder_class = GST_CE_BASE_ENCODER_CLASS(base_video_encoder_class);
  
  /* Init debug instance */
  GST_DEBUG_CATEGORY_INIT (gst_ce_base_video_encoder_debug,
      "cebasevideoencoder", 0, "CodecEngine base video encoder Class");
  
  /* Override inheritance methods */
  gobject_class->set_property = gst_ce_base_video_encoder_set_property;
  gobject_class->get_property = gst_ce_base_video_encoder_get_property;
  base_video_encoder_class->encoder_chain = gst_ce_base_video_encoder_default_chain;
  
  
  /* Install properties for the class */
  g_object_class_install_property (gobject_class, PROP_B,
      g_param_spec_boolean ("testb", "Test B", "Testing B", FALSE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


}

static void
gst_ce_base_video_encoder_class_finalize (GstCEBaseVideoEncoderClass * klass,
    gpointer * class_data)
{
}

/* Obtain and register the type of the class */
GType
gst_ce_base_video_encoder_get_type (void)
{
  g_print("Registro Base Video Encoder\n");
  static GType object_type = 0;
  
  if (object_type == 0) {
    static const GTypeInfo object_info = {
      sizeof (GstCEBaseVideoEncoderClass),
      (GBaseInitFunc) gst_ce_base_video_encoder_base_init,
      (GBaseFinalizeFunc) gst_ce_base_video_encoder_base_finalize,
      (GClassInitFunc) gst_ce_base_video_encoder_class_init,
      NULL,
      NULL,
      sizeof (GstCEBaseVideoEncoder),
      0,
      NULL,
      NULL
    };
    
    object_type = g_type_register_static (GST_TYPE_CE_BASE_ENCODER,
        "GstCEBaseVideoEncoder", &object_info, (GTypeFlags) 0);
  }
  return object_type;
};


