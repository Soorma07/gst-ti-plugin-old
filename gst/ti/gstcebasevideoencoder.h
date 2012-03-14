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

#ifndef ___GST_CE_BASE_VIDEO_ENCODER_H__
#define ___GST_CE_BASE_VIDEO_ENCODER_H__

#include <gst/gst.h>
#include <gstcebaseencoder.h>

G_BEGIN_DECLS
#define GST_TYPE_CE_BASE_VIDEO_ENCODER \
  (gst_ce_base_video_encoder_get_type())
#define GST_CE_BASE_VIDEO_ENCODER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_CE_BASE_VIDEO_ENCODER,GstCEBaseVideoEncoder))
#define GST_CE_BASE_VIDEO_ENCODER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_CE_BASE_VIDEO_ENCODER,GstCEBaseVideoEncoderClass))
#define GST_IS_CE_BASE_VIDEO_ENCODER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_CE_BASE_VIDEO_ENCODER))
#define GST_IS_CE_BASE_VIDEO_ENCODER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_CE_BASE_VIDEO_ENCODER))
#define CE_BASE_VIDEO_ENCODER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_CE_BASE_VIDEO_ENCODER, GstCEBaseVideoEncoderClass))

typedef struct _GstCEBaseVideoEncoder GstCEBaseVideoEncoder;
typedef struct _GstCEBaseVideoEncoderClass GstCEBaseVideoEncoderClass;

/**
 * This is the base class for the CodecEngine based video encoders
 * @extends _GstCEBaseEncoder
 */
struct _GstCEBaseVideoEncoder
{
  GstCEBaseEncoder base_encoder;
};

struct _GstCEBaseVideoEncoderClass
{
  GstCEBaseEncoderClass parent_class;
  
  GstFlowReturn (*encoder_chain) (GstPad * pad, GstObject * parent,
    GstBuffer * buffer);
  void (*set_caps) (GstPad * pad, GstObject * parent, GstQuery * query);
};

GType gst_ce_base_video_encoder_get_type (void);
static GstFlowReturn gst_ce_base_video_encoder_chain (GstPad * pad, GstObject * parent,
                                                      GstBuffer * buffer);
/*------------------*/
/* Public Functions */
/*------------------*/
/** 
 * @memberof _GstCEBaseVideoEncoder
 * @fn void gst_ce_base_video_encoder_set_caps(_GstCEBaseVideoEncoder *base_encoder, GstPad *pad, GstObject *parent, GstQuery *query)
 * @brief Set the caps that correspond to video encoder in general.
 * @details This function generalizes the set caps for any format of video encoder 
 * @param base_encoder a pointer to a _GstCEBaseVideoEncoder object
 * @param pad a pointer to a GstPad object that will be set
 * @param parent a pointer to a GstObject object parent of the pad
 * @param query a pointer to a GstQuery object 
 */
#define gst_ce_base_video_encoder_set_caps(obj, pad, parent, query) \
  CE_BASE_VIDEO_ENCODER_GET_CLASS(obj)->set_caps(pad, parent, query)


/* Abstract Functions */

G_END_DECLS
#endif /* ___GST_BASE_CE_VIDEO_ENCODER_H__ */
