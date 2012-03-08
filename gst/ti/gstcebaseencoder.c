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

#include <gstcebaseencoder.h>
#include <string.h>
#include <stdlib.h>

#define GST_CAT_DEFAULT gst_ce_base_encoder_debug
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);

enum
{
  PROP_0,
  PROP_A
};

static void
gst_ce_base_encoder_base_init (GstCEBaseEncoderClass * klass)
{
  /* Initialize dynamic data */
}

static void
gst_ce_base_encoder_base_finalize (GstCEBaseEncoderClass * klass)
{
}

static void
gst_ce_base_encoder_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{

  /* Set base params */
  switch (prop_id) {
    default:
      break;
  }

}

static void
gst_ce_base_encoder_finalize (GObject * object)
{
}

static void
gst_ce_base_encoder_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{

  /* Get base params */
  switch (prop_id) {
    default:
      break;
  }
}

static void
gst_ce_base_encoder_class_init (GstCEBaseEncoderClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  GST_DEBUG_CATEGORY_INIT (gst_ce_base_encoder_debug, "cebaseencoder", 0,
      "CodecEngine base encoder class");

  gobject_class->set_property = gst_ce_base_encoder_set_property;
  gobject_class->get_property = gst_ce_base_encoder_get_property;
  gobject_class->finalize = gst_ce_base_encoder_finalize;

  g_object_class_install_property (gobject_class, PROP_A,
      g_param_spec_boolean ("testa", "Test A", "Testing A", FALSE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
}

void
gst_ce_base_encoder_class_finalize (GstCEBaseEncoderClass * klass,
    gpointer * class_data)
{
}

static void
gst_ce_base_encoder_init (GstCEBaseEncoder * base_encoder)
{
}

/* Obtain and register the type of the class */
GType
gst_ce_base_encoder_get_type (void)
{
  static GType object_type = 0;

  if (object_type == 0) {

    static const GTypeInfo object_info = {
      sizeof (GstCEBaseEncoderClass),
      (GBaseInitFunc) gst_ce_base_encoder_base_init,
      (GBaseFinalizeFunc) gst_ce_base_encoder_base_finalize,
      (GClassInitFunc) gst_ce_base_encoder_class_init,
      NULL,
      NULL,
      sizeof (GstCEBaseEncoder),
      0,
      NULL,
    };

    object_type = g_type_register_static (GST_TYPE_ELEMENT,
        "GstCEBaseEncoder", &object_info, 0);
  }

  return object_type;
};

/** gst_ce_base_encoder_get_output_buffer
 * @base_encoder : a #GstCEBaseEncoder object
 * @size : size for the buffer
 *
 * Returns: a #GstBuffer 
 */
GstBuffer *
gst_ce_base_encoder_get_output_buffer (GstCEBaseEncoder * base_encoder,
    gsize size)
{
  return NULL;
}

/* Reconfig the output buffer size of the encoder */
void
gst_ce_base_encoder_shrink_output_buffer (GstCEBaseEncoder * base_encoder,
    GstBuffer * buffer, gsize new_size)
{
}

/* Process the encode algorithm */
void
gst_ce_base_encoder_encode (GstCEBaseEncoder * base_encoder,
    GstBuffer * input_buffer, GstBuffer * output_buffer)
{
}
