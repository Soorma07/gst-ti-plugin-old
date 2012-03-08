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

static void
gst_ce_h264_encoder_class_init (GstCEH264EncoderClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  GST_DEBUG_CATEGORY_INIT (gst_ce_h264_encoder_debug, "ceenc_h264", 0,
      "CodecEngine h264 encoder");

  gobject_class->set_property = gst_ce_h264_encoder_set_property;
  gobject_class->get_property = gst_ce_h264_encoder_get_property;

  g_object_class_install_property (gobject_class, PROP_D,
      g_param_spec_boolean ("testd", "Test D", "Testing D", FALSE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


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

  static const GTypeInfo object_info = {
    sizeof (GstCEH264EncoderClass),
    (GBaseInitFunc) gst_ce_h264_encoder_base_init,
    (GBaseFinalizeFunc) gst_ce_h264_encoder_base_finalize,
    (GClassInitFunc) gst_ce_h264_encoder_class_init,
    NULL,
    NULL,
    sizeof (GstCEH264Encoder),
    0,
    NULL,
    NULL
  };

  object_type = g_type_register_static (GST_TYPE_CE_VIDENC1,
      "GstCEH264Encoder", &object_info, (GTypeFlags) 0);

  return object_type;
};