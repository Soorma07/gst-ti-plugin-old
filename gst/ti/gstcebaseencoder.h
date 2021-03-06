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

#ifndef _GST_CE_BASE_ENCODER_H_
#define _GST_CE_BASE_ENCODER_H_

#include <gst/gst.h>

G_BEGIN_DECLS
#define GST_TYPE_CE_BASE_ENCODER \
  (gst_ce_base_encoder_get_type())
#define GST_CE_BASE_ENCODER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_CE_BASE_ENCODER,GstCEBaseEncoder))
#define GST_CE_BASE_ENCODER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_CE_BASE_ENCODER,GstCEBaseEncoderClass))
#define GST_IS_CE_BASE_ENCODER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_CE_BASE_ENCODER))
#define GST_IS_CE_BASE_ENCODER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_CE_BASE_ENCODER))
#define CE_BASE_ENCODER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_CE_BASE_ENCODER, GstCEBaseEncoderClass  ))

typedef struct _GstCEBaseEncoder GstCEBaseEncoder;
typedef struct _GstCEBaseEncoderClass GstCEBaseEncoderClass;

/**
 * This is the base class for the CodecEngine based encoders
 * @extends GstElement
 */
struct _GstCEBaseEncoder
{
  GstElement element;
  
/** 
 * @memberof _GstCEBaseEncoder
 * @typedef GstPad* sink_pad
 * @brief Attribute that allows links to previous elements in the pipeline.
 * @details This object is responsible of set the caps of the buffers that pass through the encoder
 * @private
 */
  GstPad *sink_pad;
  GstPad *src_pad;

  /* Members for encode process */
  
  char *codec_name;
  
  /* Handler for the encoder instance */
  gpointer codec_handle;
  
  /* Static params for indicate the behavior of the encoder */
  gpointer codec_params;
  
  /* Static params for indicate the behavior of the encoder in run time*/
  gpointer codec_dynamic_params;
  
  /* Pointers to hold data submitted into CodecEngine */
  /* Input buffer for the encoder instance */
  gpointer submitted_input_buffers;
  /* Output buffer of the encoder instance */
  gpointer submitted_output_buffers;
  /* Input arguments for the encoder instance */
  gpointer submitted_input_arguments;
  /* Output arguments of the encoder instance */
  gpointer submitted_output_arguments;

};

struct _GstCEBaseEncoderClass
{
  GstElementClass parent_class;
  
  void (*encoder_alloc_params) (GstCEBaseEncoder * base_encoder);
  void (*encoder_free_params) (GstCEBaseEncoder * base_encoder);
  gint32 (*encoder_control) (GstCEBaseEncoder * base_encoder);
  void (*encoder_delete) (GstCEBaseEncoder * base_encoder);
  gpointer (*encoder_create) (GstCEBaseEncoder * base_encoder);
  gint32 (*encoder_process_async) (GstCEBaseEncoder * base_encoder,
  GstBuffer * input_buffer, GstBuffer * output_buffer);
  gint32 (*encoder_process_wait) (GstCEBaseEncoder * base_encoder);
    
};

GType gst_ce_base_encoder_get_type (void);
/*------------------*/
/* Public functions */
/*------------------*/
/**
 * @memberof _GstCEBaseEncoder
 * @brief Allocates output buffers for share efficiently with co-processors
 * @details This function allocates GstBuffers that are contiguous on memory
 *  (have #_GstCMEMMeta). This buffers can be shrinked efficiently to re-use the
 *  limited-available contiguous memory.
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @param size the size of the buffer
 */
GstBuffer *gst_ce_base_encoder_get_output_buffer (GstCEBaseEncoder *
    base_encoder, gsize size);
void gst_ce_base_encoder_shrink_output_buffer (GstCEBaseEncoder * base_encoder,
    GstBuffer * buffer, gsize new_size);
void gst_ce_base_encoder_encode (GstCEBaseEncoder * base_encoder,
    GstBuffer * input_buffer, GstBuffer * output_buffer);


/*--------------------*/
/* Abstract functions */
/*--------------------*/
/** 
 * @memberof _GstCEBaseEncoder
 * @fn void gst_ce_base_encoder_alloc_params(_GstCEBaseEncoder *base_encoder)
 * @brief Abstract function that implements the allocation of static parameters for
 *  the codec.
 * @details This function is implemented by a sub-class that handles the right CodecEngine API (live VIDENC1, or IMGENC)
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @protected
 */
#define gst_ce_base_encoder_alloc_params(obj) \
  CE_BASE_ENCODER_GET_CLASS(obj)->encoder_alloc_params(GST_CE_BASE_ENCODER(obj));
/** 
 * @memberof _GstCEBaseEncoder
 * @fn void gst_ce_base_encoder_free_params(_GstCEBaseEncoder *base_encoder)
 * @brief Abstract function that implements freeing of static parameters for
 *  the codec.
 * @details This function is implemented by a sub-class that handles the right CodecEngine API (live VIDENC1, or IMGENC)
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @protected
 */
#define gst_ce_base_encoder_free_params(obj) \
  CE_BASE_ENCODER_GET_CLASS(obj)->encoder_free_params(GST_CE_BASE_ENCODER(obj));

/** 
 * @memberof _GstCEBaseEncoder
 * @fn gint32 gst_ce_base_encoder_control(_GstCEBaseEncoder *base_encoder)
 * @brief Abstract function that implements controlling behavior of the codec.
 * @details This function is implemented by a sub-class that handles the right CodecEngine API (live VIDENC1, or IMGENC)
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @protected
 */
#define gst_ce_base_encoder_control(obj) \
  CE_BASE_ENCODER_GET_CLASS(obj)->encoder_control(GST_CE_BASE_ENCODER(obj));

/** 
 * @memberof _GstCEBaseEncoder
 * @fn void gst_ce_base_encoder_delete(_GstCEBaseEncoder *base_encoder)
 * @brief Abstract function that implements deleting the instance of the codec.
 * @details This function is implemented by a sub-class that handles the right CodecEngine API (live VIDENC1, or IMGENC)
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @protected
 */
#define gst_ce_base_encoder_delete(obj) \
  CE_BASE_ENCODER_GET_CLASS(obj)->encoder_delete(GST_CE_BASE_ENCODER(obj));

/** 
 * @memberof _GstCEBaseEncoder
 * @fn gpointer gst_ce_base_encoder_create(_GstCEBaseEncoder *base_encoder)
 * @brief Abstract function that implements creating an instance of the codec
 * @details This function is implemented by a sub-class that handles the right CodecEngine API (live VIDENC1, or IMGENC)
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @protected
 */
#define gst_ce_base_encoder_create(obj) \
  CE_BASE_ENCODER_GET_CLASS(obj)->encoder_create(GST_CE_BASE_ENCODER(obj));

/** 
 * @memberof _GstCEBaseEncoder
 * @fn gint32 gst_ce_base_encoder_process_async(_GstCEBaseEncoder *base_encoder, GstBuffer *input_buffer, GstBuffer *output_buffer)
 * @brief Abstract function that implements. Instance handles must not be concurrently accessed by multiple threads.
 * @details This function is implemented by a sub-class that handles the right CodecEngine API (live VIDENC1, or IMGENC)
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @param input_buffer a pointer containing input buffers.
 * @param output_buffer a pointer containing output buffers. 
 * @protected
 */
#define gst_ce_base_encoder_process_async(obj, in_buf, out_buf) \
  CE_BASE_ENCODER_GET_CLASS(obj)->encoder_process_async(GST_CE_BASE_ENCODER(obj), in_buf, out_buf);

/** 
 * @memberof _GstCEBaseEncoder
 * @fn gint32 gst_ce_base_encoder_process_wait(_GstCEBaseEncoder *base_encoder)
 * @brief Abstract function that implements waiting for a return message 
 * from a previous invocation of gst_ce_base_encoder_process_async() in this instance of the codec. 
 * @details This function is implemented by a sub-class that handles the right CodecEngine API (live VIDENC1, or IMGENC)
 * @param base_encoder a pointer to a _GstCEBaseEncoder object
 * @protected
 */
#define gst_ce_base_encoder_process_wait(obj) \
  CE_BASE_ENCODER_GET_CLASS(obj)->encoder_process_wait(GST_CE_BASE_ENCODER(obj));

G_END_DECLS
#endif
