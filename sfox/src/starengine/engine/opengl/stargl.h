#ifndef __gl_h_
#define __gl_h_

#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright 1998-2002, NVIDIA Corporation.
** All Rights Reserved.
** 
** THE INFORMATION CONTAINED HEREIN IS PROPRIETARY AND CONFIDENTIAL TO
** NVIDIA, CORPORATION.  USE, REPRODUCTION OR DISCLOSURE TO ANY THIRD PARTY
** IS SUBJECT TO WRITTEN PRE-APPROVAL BY NVIDIA, CORPORATION.
** 
** 
** Copyright 1992-1999, Silicon Graphics, Inc.
** All Rights Reserved.
** 
** Portions of this file are UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon
** Graphics, Inc.; the contents of this file may not be disclosed to third
** parties, copied or duplicated in any form, in whole or in part, without
** the prior written permission of Silicon Graphics, Inc.
** 
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to
** restrictions as set forth in subdivision (c)(1)(ii) of the Rights in
** Technical Data and Computer Software clause at DFARS 252.227-7013,
** and/or in similar or successor clauses in the FAR, DOD or NASA FAR
** Supplement.  Unpublished - rights reserved under the Copyright Laws of
** the United States.
*/

/*From Mesa3D*/
#if !defined(__WIN32__) && (defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__))
#  define __WIN32__
#endif

/* GLAPI, part 1 (use WINGDIAPI, if defined) */
#if defined(__WIN32__) && defined(WINGDIAPI)
#  define GLAPI WINGDIAPI
#endif

/* GLAPI, part 2 */
#if !defined(GLAPI)
#  if defined(_MSC_VER)                        /* Microsoft Visual C++ */
#    define GLAPI __declspec(dllimport)
#  elif defined(__LCC__) && defined(__WIN32__) /* LCC-Win32 */
#    define GLAPI __stdcall
#  else                                        /* Others (e.g. MinGW, Cygwin, non-win32) */
#    define GLAPI extern
#  endif
#endif

/* APIENTRY */
#if !defined(APIENTRY)
#  if defined(__WIN32__)
#    define APIENTRY __stdcall
#  else
#    define APIENTRY
#  endif
#endif

/* #ifndef GLAPI */
/* # ifdef _WIN32 */
/* #  define GLAPI __stdcall */
/* # else */
/* #  define GLAPI */
/* # endif */
/* # define __DEFINED_GLAPI */
/* #endif */

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef unsigned short GLhalf;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

#if defined(_WIN64)
    typedef __int64 GLintptrARB;
    typedef __int64 GLsizeiptrARB;
#elif defined(__ia64__) || defined(__x86_64__)
    typedef long int GLintptrARB;
    typedef long int GLsizeiptrARB;
#else
    typedef int GLintptrARB;
    typedef int GLsizeiptrARB;
#endif

/*************************************************************/

/* Version */
#define GL_VERSION_1_1                    1
#define GL_VERSION_1_2                    1
#define GL_VERSION_1_3                    1
#define GL_VERSION_1_4                    1

/* Extensions */
#define GL_ARB_depth_texture              1
#define GL_ARB_fragment_program           1
#define GL_ARB_imaging                    1
#define GL_ARB_multisample                1
#define GL_ARB_multitexture               1
#define GL_ARB_point_parameters           1
#define GL_ARB_shadow                     1
#define GL_ARB_shadow_ambient             1
#define GL_ARB_texture_border_clamp       1
#define GL_ARB_texture_compression        1
#define GL_ARB_texture_cube_map           1
#define GL_ARB_texture_env_add            1
#define GL_ARB_texture_env_combine        1
#define GL_ARB_texture_env_dot3           1
#define GL_ARB_texture_mirrored_repeat    1
#define GL_ARB_transpose_matrix           1
#define GL_ARB_vertex_buffer_object       1
#define GL_ARB_vertex_program             1
#define GL_ARB_window_pos                 1
#define GL_Autodesk_valid_back_buffer_hint 1
#define GL_EXT_abgr                       1
#define GL_EXT_bgra                       1
#define GL_EXT_blend_color                1
#define GL_EXT_blend_func_separate        1
#define GL_EXT_blend_minmax               1
#define GL_EXT_blend_subtract             1
#define GL_EXT_clip_volume_hint           1
#define GL_EXT_compiled_vertex_array      1
#define GL_EXT_color_table                1
#define GL_EXT_depth_bounds_test          1
#define GL_EXT_draw_range_elements        1
#define GL_EXT_fog_coord                  1
#define GL_EXT_multi_draw_arrays          1
#define GL_EXT_packed_pixels              1
#define GL_EXT_paletted_texture           1
#define GL_EXT_point_parameters           1
#define GL_EXT_rescale_normal             1
#define GL_EXT_secondary_color            1
#define GL_EXT_separate_specular_color    1
#define GL_EXT_shadow_funcs               1
#define GL_EXT_shared_texture_palette     1
#define GL_EXT_stencil_two_side           1
#define GL_EXT_stencil_wrap               1
#define GL_EXT_texture3D                  1
#define GL_EXT_texture_compression_s3tc   1
#define GL_EXT_texture_cube_map           1
#define GL_EXT_texture_edge_clamp         1
#define GL_EXT_texture_env_add            1
#define GL_EXT_texture_env_combine        1
#define GL_EXT_texture_env_dot3           1
#define GL_EXT_texture_filter_anisotropic 1
#define GL_EXT_texture_lod_bias           1
#define GL_EXT_texture_object             1
#define GL_EXT_vertex_array               1
#define GL_EXT_vertex_weighting           1
#define GL_HP_occlusion_test              1
#define GL_IBM_texture_mirrored_repeat    1
#define GL_NV_blend_square                1
#define GL_NV_copy_depth_to_color         1
#define GL_NV_depth_clamp                 1
#define GL_NV_draw_mesh                   1
#define GL_NV_extended_combiner_program   1
#define GL_NV_fence                       1
#define GL_NV_float_buffer                1
#define GL_NV_flush_hold                  1
#define GL_NV_fog_distance                1
#define GL_NV_fragment_program            1
#define GL_NV_half_float                  1
#define GL_NV_light_max_exponent          1
#define GL_NV_mac_get_proc_address        1
#define GL_NV_multisample_filter_hint     1
#define GL_NV_occlusion_query             1
#define GL_NV_packed_depth_stencil        1
#define GL_NV_pixel_data_range            1
#define GL_NV_point_sprite                1
#define GL_NV_primitive_restart           1
#define GL_NV_register_combiners          1
#define GL_NV_register_combiners2         1
#define GL_NV_set_window_stereomode       1
#define GL_NV_texgen_reflection           1
#define GL_NV_texture_compression_vtc     1
#define GL_NV_texture_env_combine4        1
#define GL_NV_texture_expand_normal       1
#define GL_NV_texture_rectangle           1
#define GL_NV_texture_shader              1
#define GL_NV_texture_shader2             1
#define GL_NV_texture_shader3             1
#define GL_NV_vertex_array_range          1
#define GL_NV_vertex_array_range2         1
#define GL_NV_vertex_program              1
#define GL_NV_vertex_program1_1           1
#define GL_NV_vertex_program2             1
#define GL_S3_s3tc                        1
#define GL_SGIS_generate_mipmap           1
#define GL_SGIS_multitexture              1
#define GL_SGIS_texture_lod               1
#define GL_SGIX_depth_texture             1
#define GL_SGIX_shadow                    1
#define GL_APPLE_transform_hint           1
#define GL_WIN_swap_hint                  1
#define GL_NVX_ycrcb                      1

/* AttribMask */
#define GL_CURRENT_BIT                    0x00000001
#define GL_POINT_BIT                      0x00000002
#define GL_LINE_BIT                       0x00000004
#define GL_POLYGON_BIT                    0x00000008
#define GL_POLYGON_STIPPLE_BIT            0x00000010
#define GL_PIXEL_MODE_BIT                 0x00000020
#define GL_LIGHTING_BIT                   0x00000040
#define GL_FOG_BIT                        0x00000080
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_ACCUM_BUFFER_BIT               0x00000200
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_VIEWPORT_BIT                   0x00000800
#define GL_TRANSFORM_BIT                  0x00001000
#define GL_ENABLE_BIT                     0x00002000
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_HINT_BIT                       0x00008000
#define GL_EVAL_BIT                       0x00010000
#define GL_LIST_BIT                       0x00020000
#define GL_TEXTURE_BIT                    0x00040000
#define GL_SCISSOR_BIT                    0x00080000
#define GL_ALL_ATTRIB_BITS                0xFFFFFFFF

/* ClearBufferMask */
/*      GL_COLOR_BUFFER_BIT */
/*      GL_ACCUM_BUFFER_BIT */
/*      GL_STENCIL_BUFFER_BIT */
/*      GL_DEPTH_BUFFER_BIT */

/* ClientAttribMask */
#define GL_CLIENT_PIXEL_STORE_BIT         0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT        0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS         0xFFFFFFFF

/* Boolean */
#define GL_FALSE                          0
#define GL_TRUE                           1

/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_QUAD_STRIP                     0x0008
#define GL_POLYGON                        0x0009

/* AccumOp */
#define GL_ACCUM                          0x0100
#define GL_LOAD                           0x0101
#define GL_RETURN                         0x0102
#define GL_MULT                           0x0103
#define GL_ADD                            0x0104

/* AlphaFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* ColorMaterialFace */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* ColorMaterialParameter */
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */
/*      GL_EMISSION */
/*      GL_AMBIENT_AND_DIFFUSE */

/* ColorPointerType */
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* CullFaceMode */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* DepthFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* DrawBufferMode */
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_AUX0                           0x0409
#define GL_AUX1                           0x040A
#define GL_AUX2                           0x040B
#define GL_AUX3                           0x040C

/* EnableCap */
/*      GL_FOG */
/*      GL_LIGHTING */
/*      GL_TEXTURE_1D */
/*      GL_TEXTURE_2D */
/*      GL_LINE_STIPPLE */
/*      GL_POLYGON_STIPPLE */
/*      GL_CULL_FACE */
/*      GL_ALPHA_TEST */
/*      GL_BLEND */
/*      GL_INDEX_LOGIC_OP */
/*      GL_COLOR_LOGIC_OP */
/*      GL_DITHER */
/*      GL_STENCIL_TEST */
/*      GL_DEPTH_TEST */
/*      GL_CLIP_PLANE0 */
/*      GL_CLIP_PLANE1 */
/*      GL_CLIP_PLANE2 */
/*      GL_CLIP_PLANE3 */
/*      GL_CLIP_PLANE4 */
/*      GL_CLIP_PLANE5 */
/*      GL_LIGHT0 */
/*      GL_LIGHT1 */
/*      GL_LIGHT2 */
/*      GL_LIGHT3 */
/*      GL_LIGHT4 */
/*      GL_LIGHT5 */
/*      GL_LIGHT6 */
/*      GL_LIGHT7 */
/*      GL_TEXTURE_GEN_S */
/*      GL_TEXTURE_GEN_T */
/*      GL_TEXTURE_GEN_R */
/*      GL_TEXTURE_GEN_Q */
/*      GL_MAP1_VERTEX_3 */
/*      GL_MAP1_VERTEX_4 */
/*      GL_MAP1_COLOR_4 */
/*      GL_MAP1_INDEX */
/*      GL_MAP1_NORMAL */
/*      GL_MAP1_TEXTURE_COORD_1 */
/*      GL_MAP1_TEXTURE_COORD_2 */
/*      GL_MAP1_TEXTURE_COORD_3 */
/*      GL_MAP1_TEXTURE_COORD_4 */
/*      GL_MAP2_VERTEX_3 */
/*      GL_MAP2_VERTEX_4 */
/*      GL_MAP2_COLOR_4 */
/*      GL_MAP2_INDEX */
/*      GL_MAP2_NORMAL */
/*      GL_MAP2_TEXTURE_COORD_1 */
/*      GL_MAP2_TEXTURE_COORD_2 */
/*      GL_MAP2_TEXTURE_COORD_3 */
/*      GL_MAP2_TEXTURE_COORD_4 */
/*      GL_POINT_SMOOTH */
/*      GL_LINE_SMOOTH */
/*      GL_POLYGON_SMOOTH */
/*      GL_SCISSOR_TEST */
/*      GL_COLOR_MATERIAL */
/*      GL_NORMALIZE */
/*      GL_AUTO_NORMAL */
/*      GL_POLYGON_OFFSET_POINT */
/*      GL_POLYGON_OFFSET_LINE */
/*      GL_POLYGON_OFFSET_FILL */
/*      GL_VERTEX_ARRAY */
/*      GL_NORMAL_ARRAY */
/*      GL_COLOR_ARRAY */
/*      GL_INDEX_ARRAY */
/*      GL_TEXTURE_COORD_ARRAY */
/*      GL_EDGE_FLAG_ARRAY */

/* ErrorCode */
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_TABLE_TOO_LARGE                0x8031

/* FeedbackType */
#define GL_2D                             0x0600
#define GL_3D                             0x0601
#define GL_3D_COLOR                       0x0602
#define GL_3D_COLOR_TEXTURE               0x0603
#define GL_4D_COLOR_TEXTURE               0x0604

/* FeedBackToken */
#define GL_PASS_THROUGH_TOKEN             0x0700
#define GL_POINT_TOKEN                    0x0701
#define GL_LINE_TOKEN                     0x0702
#define GL_POLYGON_TOKEN                  0x0703
#define GL_BITMAP_TOKEN                   0x0704
#define GL_DRAW_PIXEL_TOKEN               0x0705
#define GL_COPY_PIXEL_TOKEN               0x0706
#define GL_LINE_RESET_TOKEN               0x0707

/* FogMode */
/*      GL_LINEAR */
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801

/* FogParameter */
/*      GL_FOG_COLOR */
/*      GL_FOG_DENSITY */
/*      GL_FOG_END */
/*      GL_FOG_INDEX */
/*      GL_FOG_MODE */
/*      GL_FOG_START */

/* FrontFaceDirection */
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

/* GetColorTableParameterPNameEXT */
/*      GL_COLOR_TABLE_FORMAT_EXT */
/*      GL_COLOR_TABLE_WIDTH_EXT */
/*      GL_COLOR_TABLE_RED_SIZE_EXT */
/*      GL_COLOR_TABLE_GREEN_SIZE_EXT */
/*      GL_COLOR_TABLE_BLUE_SIZE_EXT */
/*      GL_COLOR_TABLE_ALPHA_SIZE_EXT */
/*      GL_COLOR_TABLE_LUMINANCE_SIZE_EXT */
/*      GL_COLOR_TABLE_INTENSITY_SIZE_EXT */

/* GetMapQuery */
#define GL_COEFF                          0x0A00
#define GL_ORDER                          0x0A01
#define GL_DOMAIN                         0x0A02

/* GetPixelMap */
#define GL_PIXEL_MAP_I_TO_I               0x0C70
#define GL_PIXEL_MAP_S_TO_S               0x0C71
#define GL_PIXEL_MAP_I_TO_R               0x0C72
#define GL_PIXEL_MAP_I_TO_G               0x0C73
#define GL_PIXEL_MAP_I_TO_B               0x0C74
#define GL_PIXEL_MAP_I_TO_A               0x0C75
#define GL_PIXEL_MAP_R_TO_R               0x0C76
#define GL_PIXEL_MAP_G_TO_G               0x0C77
#define GL_PIXEL_MAP_B_TO_B               0x0C78
#define GL_PIXEL_MAP_A_TO_A               0x0C79

/* GetPointervPName */
#define GL_VERTEX_ARRAY_POINTER           0x808E
#define GL_NORMAL_ARRAY_POINTER           0x808F
#define GL_COLOR_ARRAY_POINTER            0x8090
#define GL_INDEX_ARRAY_POINTER            0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER        0x8093

/* GetPName */
#define GL_CURRENT_COLOR                  0x0B00
#define GL_CURRENT_INDEX                  0x0B01
#define GL_CURRENT_NORMAL                 0x0B02
#define GL_CURRENT_TEXTURE_COORDS         0x0B03
#define GL_CURRENT_RASTER_COLOR           0x0B04
#define GL_CURRENT_RASTER_INDEX           0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS  0x0B06
#define GL_CURRENT_RASTER_POSITION        0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID  0x0B08
#define GL_CURRENT_RASTER_DISTANCE        0x0B09
#define GL_POINT_SMOOTH                   0x0B10
#define GL_POINT_SIZE                     0x0B11
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_POINT_SIZE_RANGE               GL_SMOOTH_POINT_SIZE_RANGE
#define GL_POINT_SIZE_GRANULARITY         GL_SMOOTH_POINT_SIZE_GRANULARITY
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_LINE_WIDTH_RANGE               GL_SMOOTH_LINE_WIDTH_RANGE
#define GL_LINE_WIDTH_GRANULARITY         GL_SMOOTH_LINE_WIDTH_GRANULARITY
#define GL_LINE_STIPPLE                   0x0B24
#define GL_LINE_STIPPLE_PATTERN           0x0B25
#define GL_LINE_STIPPLE_REPEAT            0x0B26
#define GL_LIST_MODE                      0x0B30
#define GL_MAX_LIST_NESTING               0x0B31
#define GL_LIST_BASE                      0x0B32
#define GL_LIST_INDEX                     0x0B33
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_POLYGON_STIPPLE                0x0B42
#define GL_EDGE_FLAG                      0x0B43
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_LIGHTING                       0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GL_LIGHT_MODEL_AMBIENT            0x0B53
#define GL_SHADE_MODEL                    0x0B54
#define GL_COLOR_MATERIAL_FACE            0x0B55
#define GL_COLOR_MATERIAL_PARAMETER       0x0B56
#define GL_COLOR_MATERIAL                 0x0B57
#define GL_FOG                            0x0B60
#define GL_FOG_INDEX                      0x0B61
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_ACCUM_CLEAR_VALUE              0x0B80
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_MATRIX_MODE                    0x0BA0
#define GL_NORMALIZE                      0x0BA1
#define GL_VIEWPORT                       0x0BA2
#define GL_MODELVIEW_STACK_DEPTH          0x0BA3
#define GL_PROJECTION_STACK_DEPTH         0x0BA4
#define GL_TEXTURE_STACK_DEPTH            0x0BA5
#define GL_MODELVIEW_MATRIX               0x0BA6
#define GL_PROJECTION_MATRIX              0x0BA7
#define GL_TEXTURE_MATRIX                 0x0BA8
#define GL_ATTRIB_STACK_DEPTH             0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH      0x0BB1
#define GL_ALPHA_TEST                     0x0BC0
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_INDEX_LOGIC_OP                 0x0BF1
#define GL_LOGIC_OP                       GL_INDEX_LOGIC_OP
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_AUX_BUFFERS                    0x0C00
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_INDEX_CLEAR_VALUE              0x0C20
#define GL_INDEX_WRITEMASK                0x0C21
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_INDEX_MODE                     0x0C30
#define GL_RGBA_MODE                      0x0C31
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_RENDER_MODE                    0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define GL_POINT_SMOOTH_HINT              0x0C51
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_FOG_HINT                       0x0C54
#define GL_TEXTURE_GEN_S                  0x0C60
#define GL_TEXTURE_GEN_T                  0x0C61
#define GL_TEXTURE_GEN_R                  0x0C62
#define GL_TEXTURE_GEN_Q                  0x0C63
#define GL_PIXEL_MAP_I_TO_I_SIZE          0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE          0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE          0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE          0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE          0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE          0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE          0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE          0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE          0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE          0x0CB9
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAP_COLOR                      0x0D10
#define GL_MAP_STENCIL                    0x0D11
#define GL_INDEX_SHIFT                    0x0D12
#define GL_INDEX_OFFSET                   0x0D13
#define GL_RED_SCALE                      0x0D14
#define GL_RED_BIAS                       0x0D15
#define GL_ZOOM_X                         0x0D16
#define GL_ZOOM_Y                         0x0D17
#define GL_GREEN_SCALE                    0x0D18
#define GL_GREEN_BIAS                     0x0D19
#define GL_BLUE_SCALE                     0x0D1A
#define GL_BLUE_BIAS                      0x0D1B
#define GL_ALPHA_SCALE                    0x0D1C
#define GL_ALPHA_BIAS                     0x0D1D
#define GL_DEPTH_SCALE                    0x0D1E
#define GL_DEPTH_BIAS                     0x0D1F
#define GL_MAX_EVAL_ORDER                 0x0D30
#define GL_MAX_LIGHTS                     0x0D31
#define GL_MAX_CLIP_PLANES                0x0D32
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_PIXEL_MAP_TABLE            0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH         0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define GL_MAX_NAME_STACK_DEPTH           0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH  0x0D3B
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_INDEX_BITS                     0x0D51
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_ACCUM_RED_BITS                 0x0D58
#define GL_ACCUM_GREEN_BITS               0x0D59
#define GL_ACCUM_BLUE_BITS                0x0D5A
#define GL_ACCUM_ALPHA_BITS               0x0D5B
#define GL_NAME_STACK_DEPTH               0x0D70
#define GL_AUTO_NORMAL                    0x0D80
#define GL_MAP1_COLOR_4                   0x0D90
#define GL_MAP1_INDEX                     0x0D91
#define GL_MAP1_NORMAL                    0x0D92
#define GL_MAP1_TEXTURE_COORD_1           0x0D93
#define GL_MAP1_TEXTURE_COORD_2           0x0D94
#define GL_MAP1_TEXTURE_COORD_3           0x0D95
#define GL_MAP1_TEXTURE_COORD_4           0x0D96
#define GL_MAP1_VERTEX_3                  0x0D97
#define GL_MAP1_VERTEX_4                  0x0D98
#define GL_MAP2_COLOR_4                   0x0DB0
#define GL_MAP2_INDEX                     0x0DB1
#define GL_MAP2_NORMAL                    0x0DB2
#define GL_MAP2_TEXTURE_COORD_1           0x0DB3
#define GL_MAP2_TEXTURE_COORD_2           0x0DB4
#define GL_MAP2_TEXTURE_COORD_3           0x0DB5
#define GL_MAP2_TEXTURE_COORD_4           0x0DB6
#define GL_MAP2_VERTEX_3                  0x0DB7
#define GL_MAP2_VERTEX_4                  0x0DB8
#define GL_MAP1_GRID_DOMAIN               0x0DD0
#define GL_MAP1_GRID_SEGMENTS             0x0DD1
#define GL_MAP2_GRID_DOMAIN               0x0DD2
#define GL_MAP2_GRID_SEGMENTS             0x0DD3
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_FEEDBACK_BUFFER_POINTER        0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE           0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE           0x0DF2
#define GL_SELECTION_BUFFER_POINTER       0x0DF3
#define GL_SELECTION_BUFFER_SIZE          0x0DF4
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_1D             0x8068
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_INDEX_ARRAY                    0x8077
#define GL_TEXTURE_COORD_ARRAY            0x8078
#define GL_EDGE_FLAG_ARRAY                0x8079
#define GL_VERTEX_ARRAY_SIZE              0x807A
#define GL_VERTEX_ARRAY_TYPE              0x807B
#define GL_VERTEX_ARRAY_STRIDE            0x807C
#define GL_NORMAL_ARRAY_TYPE              0x807E
#define GL_NORMAL_ARRAY_STRIDE            0x807F
#define GL_COLOR_ARRAY_SIZE               0x8081
#define GL_COLOR_ARRAY_TYPE               0x8082
#define GL_COLOR_ARRAY_STRIDE             0x8083
#define GL_INDEX_ARRAY_TYPE               0x8085
#define GL_INDEX_ARRAY_STRIDE             0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE         0x808C
/*      GL_VERTEX_ARRAY_COUNT_EXT */
/*      GL_NORMAL_ARRAY_COUNT_EXT */
/*      GL_COLOR_ARRAY_COUNT_EXT */
/*      GL_INDEX_ARRAY_COUNT_EXT */
/*      GL_TEXTURE_COORD_ARRAY_COUNT_EXT */
/*      GL_EDGE_FLAG_ARRAY_COUNT_EXT */
/*      GL_ARRAY_ELEMENT_LOCK_COUNT_EXT */
/*      GL_ARRAY_ELEMENT_LOCK_FIRST_EXT */

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_COMPONENTS             GL_TEXTURE_INTERNAL_FORMAT
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_TEXTURE_BORDER                 0x1005
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
#define GL_TEXTURE_LUMINANCE_SIZE         0x8060
#define GL_TEXTURE_INTENSITY_SIZE         0x8061
#define GL_TEXTURE_PRIORITY               0x8066
#define GL_TEXTURE_RESIDENT               0x8067

/* HintMode */
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102

/* HintTarget */
/*      GL_PERSPECTIVE_CORRECTION_HINT */
/*      GL_POINT_SMOOTH_HINT */
/*      GL_LINE_SMOOTH_HINT */
/*      GL_POLYGON_SMOOTH_HINT */
/*      GL_FOG_HINT */

/* IndexMaterialParameterSGI */
/*      GL_INDEX_OFFSET */

/* IndexPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* IndexFunctionSGI */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* LightModelParameter */
/*      GL_LIGHT_MODEL_AMBIENT */
/*      GL_LIGHT_MODEL_LOCAL_VIEWER */
/*      GL_LIGHT_MODEL_TWO_SIDE */

/* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

/* ListMode */
#define GL_COMPILE                        0x1300
#define GL_COMPILE_AND_EXECUTE            0x1301

/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_2_BYTES                        0x1407
#define GL_3_BYTES                        0x1408
#define GL_4_BYTES                        0x1409
#define GL_DOUBLE                         0x140A
#define GL_DOUBLE_EXT                     0x140A

/* ListNameType */
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_2_BYTES */
/*      GL_3_BYTES */
/*      GL_4_BYTES */

/* LogicOp */
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F

/* MapTarget */
/*      GL_MAP1_COLOR_4 */
/*      GL_MAP1_INDEX */
/*      GL_MAP1_NORMAL */
/*      GL_MAP1_TEXTURE_COORD_1 */
/*      GL_MAP1_TEXTURE_COORD_2 */
/*      GL_MAP1_TEXTURE_COORD_3 */
/*      GL_MAP1_TEXTURE_COORD_4 */
/*      GL_MAP1_VERTEX_3 */
/*      GL_MAP1_VERTEX_4 */
/*      GL_MAP2_COLOR_4 */
/*      GL_MAP2_INDEX */
/*      GL_MAP2_NORMAL */
/*      GL_MAP2_TEXTURE_COORD_1 */
/*      GL_MAP2_TEXTURE_COORD_2 */
/*      GL_MAP2_TEXTURE_COORD_3 */
/*      GL_MAP2_TEXTURE_COORD_4 */
/*      GL_MAP2_VERTEX_3 */
/*      GL_MAP2_VERTEX_4 */

/* MaterialFace */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
#define GL_COLOR_INDEXES                  0x1603
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */

/* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701
#define GL_TEXTURE                        0x1702

/* MeshMode1 */
/*      GL_POINT */
/*      GL_LINE */

/* MeshMode2 */
/*      GL_POINT */
/*      GL_LINE */
/*      GL_FILL */

/* NormalPointerType */
/*      GL_BYTE */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* PixelCopyType */
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802

/* PixelFormat */
#define GL_COLOR_INDEX                    0x1900
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A
/*      GL_ABGR_EXT */
/*      GL_BGR_EXT */
/*      GL_BGRA_EXT */

/* PixelMap */
/*      GL_PIXEL_MAP_I_TO_I */
/*      GL_PIXEL_MAP_S_TO_S */
/*      GL_PIXEL_MAP_I_TO_R */
/*      GL_PIXEL_MAP_I_TO_G */
/*      GL_PIXEL_MAP_I_TO_B */
/*      GL_PIXEL_MAP_I_TO_A */
/*      GL_PIXEL_MAP_R_TO_R */
/*      GL_PIXEL_MAP_G_TO_G */
/*      GL_PIXEL_MAP_B_TO_B */
/*      GL_PIXEL_MAP_A_TO_A */

/* PixelStoreParameter */
/*      GL_UNPACK_SWAP_BYTES */
/*      GL_UNPACK_LSB_FIRST */
/*      GL_UNPACK_ROW_LENGTH */
/*      GL_UNPACK_SKIP_ROWS */
/*      GL_UNPACK_SKIP_PIXELS */
/*      GL_UNPACK_ALIGNMENT */
/*      GL_PACK_SWAP_BYTES */
/*      GL_PACK_LSB_FIRST */
/*      GL_PACK_ROW_LENGTH */
/*      GL_PACK_SKIP_ROWS */
/*      GL_PACK_SKIP_PIXELS */
/*      GL_PACK_ALIGNMENT */

/* PixelTransferParameter */
/*      GL_MAP_COLOR */
/*      GL_MAP_STENCIL */
/*      GL_INDEX_SHIFT */
/*      GL_INDEX_OFFSET */
/*      GL_RED_SCALE */
/*      GL_RED_BIAS */
/*      GL_GREEN_SCALE */
/*      GL_GREEN_BIAS */
/*      GL_BLUE_SCALE */
/*      GL_BLUE_BIAS */
/*      GL_ALPHA_SCALE */
/*      GL_ALPHA_BIAS */
/*      GL_DEPTH_SCALE */
/*      GL_DEPTH_BIAS */

/* PixelType */
#define GL_BITMAP                         0x1A00
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_UNSIGNED_BYTE_3_3_2_EXT */
/*      GL_UNSIGNED_SHORT_4_4_4_4_EXT */
/*      GL_UNSIGNED_SHORT_5_5_5_1_EXT */
/*      GL_UNSIGNED_INT_8_8_8_8_EXT */
/*      GL_UNSIGNED_INT_10_10_10_2_EXT */

/* PolygonMode */
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

/* ReadBufferMode */
/*      GL_FRONT_LEFT */
/*      GL_FRONT_RIGHT */
/*      GL_BACK_LEFT */
/*      GL_BACK_RIGHT */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_LEFT */
/*      GL_RIGHT */
/*      GL_AUX0 */
/*      GL_AUX1 */
/*      GL_AUX2 */
/*      GL_AUX3 */

/* RenderingMode */
#define GL_RENDER                         0x1C00
#define GL_FEEDBACK                       0x1C01
#define GL_SELECT                         0x1C02

/* ShadingModel */
#define GL_FLAT                           0x1D00
#define GL_SMOOTH                         0x1D01

/* StencilFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
/*      GL_INVERT */

/* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

/* TexCoordPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* TextureCoordName */
#define GL_S                              0x2000
#define GL_T                              0x2001
#define GL_R                              0x2002
#define GL_Q                              0x2003

/* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
/*      GL_BLEND */
/*      GL_REPLACE */
/*      GL_ADD */

/* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

/* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

/* TextureGenMode */
#define GL_EYE_LINEAR                     0x2400
#define GL_OBJECT_LINEAR                  0x2401
#define GL_SPHERE_MAP                     0x2402

/* TextureGenParameter */
#define GL_TEXTURE_GEN_MODE               0x2500
#define GL_OBJECT_PLANE                   0x2501
#define GL_EYE_PLANE                      0x2502

/* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
/*      GL_TEXTURE_BORDER_COLOR */
/*      GL_TEXTURE_PRIORITY */

/* TextureTarget */
/*      GL_TEXTURE_1D */
/*      GL_TEXTURE_2D */
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064

/* TextureWrapMode */
#define GL_CLAMP                          0x2900
#define GL_REPEAT                         0x2901

/* PixelInternalFormat */
#define GL_R3_G3_B2                       0x2A10
#define GL_ALPHA4                         0x803B
#define GL_ALPHA8                         0x803C
#define GL_ALPHA12                        0x803D
#define GL_ALPHA16                        0x803E
#define GL_LUMINANCE4                     0x803F
#define GL_LUMINANCE8                     0x8040
#define GL_LUMINANCE12                    0x8041
#define GL_LUMINANCE16                    0x8042
#define GL_LUMINANCE4_ALPHA4              0x8043
#define GL_LUMINANCE6_ALPHA2              0x8044
#define GL_LUMINANCE8_ALPHA8              0x8045
#define GL_LUMINANCE12_ALPHA4             0x8046
#define GL_LUMINANCE12_ALPHA12            0x8047
#define GL_LUMINANCE16_ALPHA16            0x8048
#define GL_INTENSITY                      0x8049
#define GL_INTENSITY4                     0x804A
#define GL_INTENSITY8                     0x804B
#define GL_INTENSITY12                    0x804C
#define GL_INTENSITY16                    0x804D
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
/*      GL_COLOR_INDEX1_EXT */
/*      GL_COLOR_INDEX2_EXT */
/*      GL_COLOR_INDEX4_EXT */
/*      GL_COLOR_INDEX8_EXT */
/*      GL_COLOR_INDEX12_EXT */
/*      GL_COLOR_INDEX16_EXT */

/* InterleavedArrayFormat */
#define GL_V2F                            0x2A20
#define GL_V3F                            0x2A21
#define GL_C4UB_V2F                       0x2A22
#define GL_C4UB_V3F                       0x2A23
#define GL_C3F_V3F                        0x2A24
#define GL_N3F_V3F                        0x2A25
#define GL_C4F_N3F_V3F                    0x2A26
#define GL_T2F_V3F                        0x2A27
#define GL_T4F_V4F                        0x2A28
#define GL_T2F_C4UB_V3F                   0x2A29
#define GL_T2F_C3F_V3F                    0x2A2A
#define GL_T2F_N3F_V3F                    0x2A2B
#define GL_T2F_C4F_N3F_V3F                0x2A2C
#define GL_T4F_C4F_N3F_V4F                0x2A2D

/* VertexPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* ClipPlaneName */
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

/* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

/* EXT_abgr */
#define GL_ABGR_EXT                       0x8000

/* EXT_blend_color */
#define GL_CONSTANT_COLOR_EXT             0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT   0x8002
#define GL_CONSTANT_ALPHA_EXT             0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT   0x8004
#define GL_BLEND_COLOR_EXT                0x8005

/* EXT_blend_minmax */
#define GL_FUNC_ADD_EXT                   0x8006
#define GL_MIN_EXT                        0x8007
#define GL_MAX_EXT                        0x8008
#define GL_BLEND_EQUATION_EXT             0x8009

/* EXT_blend_subtract */
#define GL_FUNC_SUBTRACT_EXT              0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT      0x800B

/* EXT_packed_pixels */
#define GL_UNSIGNED_BYTE_3_3_2_EXT        0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT     0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT     0x8034
#define GL_UNSIGNED_INT_8_8_8_8_EXT       0x8035
#define GL_UNSIGNED_INT_10_10_10_2_EXT    0x8036

/* OpenGL12 */
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_RESCALE_NORMAL                 0x803A
#define GL_LIGHT_MODEL_COLOR_CONTROL      0x81F8
#define GL_SINGLE_COLOR                   0x81F9
#define GL_SEPARATE_SPECULAR_COLOR        0x81FA
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E

/* ARB_imaging */
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_BLEND_COLOR                    0x8005
#define GL_FUNC_ADD                       0x8006
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
#define GL_BLEND_EQUATION                 0x8009
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_COLOR_MATRIX                   0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH       0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH   0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE    0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE  0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE   0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE  0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS     0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS   0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS    0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS   0x80BB
#define GL_COLOR_TABLE                    0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE   0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE  0x80D2
#define GL_PROXY_COLOR_TABLE              0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE 0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE 0x80D5
#define GL_COLOR_TABLE_SCALE              0x80D6
#define GL_COLOR_TABLE_BIAS               0x80D7
#define GL_COLOR_TABLE_FORMAT             0x80D8
#define GL_COLOR_TABLE_WIDTH              0x80D9
#define GL_COLOR_TABLE_RED_SIZE           0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE         0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE          0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE         0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE     0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE     0x80DF
#define GL_CONVOLUTION_1D                 0x8010
#define GL_CONVOLUTION_2D                 0x8011
#define GL_SEPARABLE_2D                   0x8012
#define GL_CONVOLUTION_BORDER_MODE        0x8013
#define GL_CONVOLUTION_FILTER_SCALE       0x8014
#define GL_CONVOLUTION_FILTER_BIAS        0x8015
#define GL_REDUCE                         0x8016
#define GL_CONVOLUTION_FORMAT             0x8017
#define GL_CONVOLUTION_WIDTH              0x8018
#define GL_CONVOLUTION_HEIGHT             0x8019
#define GL_MAX_CONVOLUTION_WIDTH          0x801A
#define GL_MAX_CONVOLUTION_HEIGHT         0x801B
#define GL_POST_CONVOLUTION_RED_SCALE     0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE   0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE    0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE   0x801F
#define GL_POST_CONVOLUTION_RED_BIAS      0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS    0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS     0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS    0x8023
#define GL_IGNORE_BORDER                  0x8150
#define GL_CONSTANT_BORDER                0x8151
#define GL_REPLICATE_BORDER               0x8153
#define GL_CONVOLUTION_BORDER_COLOR       0x8154
#define GL_HISTOGRAM                      0x8024
#define GL_PROXY_HISTOGRAM                0x8025
#define GL_HISTOGRAM_WIDTH                0x8026
#define GL_HISTOGRAM_FORMAT               0x8027
#define GL_HISTOGRAM_RED_SIZE             0x8028
#define GL_HISTOGRAM_GREEN_SIZE           0x8029
#define GL_HISTOGRAM_BLUE_SIZE            0x802A
#define GL_HISTOGRAM_ALPHA_SIZE           0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE       0x802C
#define GL_HISTOGRAM_SINK                 0x802D
#define GL_MINMAX                         0x802E
#define GL_MINMAX_FORMAT                  0x802F
#define GL_MINMAX_SINK                    0x8030

/* OpenGL13 */
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1
#define GL_MAX_TEXTURE_UNITS              0x84E2
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_NORMAL_MAP                     0x8511
#define GL_REFLECTION_MAP                 0x8512
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_RGB_SCALE                      0x8573
#define GL_ADD_SIGNED                     0x8574
#define GL_INTERPOLATE                    0x8575
#define GL_CONSTANT                       0x8576
#define GL_PRIMARY_COLOR                  0x8577
#define GL_PREVIOUS                       0x8578
#define GL_SOURCE0_RGB                    0x8580
#define GL_SOURCE1_RGB                    0x8581
#define GL_SOURCE2_RGB                    0x8582
#define GL_SOURCE0_ALPHA                  0x8588
#define GL_SOURCE1_ALPHA                  0x8589
#define GL_SOURCE2_ALPHA                  0x858A
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA                 0x8599
#define GL_OPERAND2_ALPHA                 0x859A
#define GL_SUBTRACT                       0x84E7
#define GL_TRANSPOSE_MODELVIEW_MATRIX     0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX    0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX       0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX         0x84E6
#define GL_COMPRESSED_ALPHA               0x84E9
#define GL_COMPRESSED_LUMINANCE           0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA     0x84EB
#define GL_COMPRESSED_INTENSITY           0x84EC
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_DOT3_RGB                       0x86AE
#define GL_DOT3_RGBA                      0x86AF
#define GL_CLAMP_TO_BORDER                0x812D
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_MULTISAMPLE_BIT                0x20000000

/* EXT_vertex_array */
#define GL_VERTEX_ARRAY_EXT               0x8074
#define GL_NORMAL_ARRAY_EXT               0x8075
#define GL_COLOR_ARRAY_EXT                0x8076
#define GL_INDEX_ARRAY_EXT                0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT        0x8078
#define GL_EDGE_FLAG_ARRAY_EXT            0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT          0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT          0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT        0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT         0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT          0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT        0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT         0x8080
#define GL_COLOR_ARRAY_SIZE_EXT           0x8081
#define GL_COLOR_ARRAY_TYPE_EXT           0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT         0x8083
#define GL_COLOR_ARRAY_COUNT_EXT          0x8084
#define GL_INDEX_ARRAY_TYPE_EXT           0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT         0x8086
#define GL_INDEX_ARRAY_COUNT_EXT          0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT   0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT   0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT 0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT  0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT     0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT      0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT       0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT       0x808F
#define GL_COLOR_ARRAY_POINTER_EXT        0x8090
#define GL_INDEX_ARRAY_POINTER_EXT        0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT 0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT    0x8093

/* EXT_texture3D */
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_SKIP_IMAGES_EXT           0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_PACK_IMAGE_HEIGHT_EXT          0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_SKIP_IMAGES_EXT         0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_UNPACK_IMAGE_HEIGHT_EXT        0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_TEXTURE_3D_EXT                 0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_PROXY_TEXTURE_3D_EXT           0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_DEPTH_EXT              0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_TEXTURE_WRAP_R_EXT             0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_MAX_3D_TEXTURE_SIZE_EXT        0x8073

/* EXT_color_table */
#define GL_TABLE_TOO_LARGE_EXT            0x8031
#define GL_COLOR_TABLE_FORMAT_EXT         0x80D8
#define GL_COLOR_TABLE_WIDTH_EXT          0x80D9
#define GL_COLOR_TABLE_RED_SIZE_EXT       0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_EXT     0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_EXT      0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT     0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT 0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT 0x80DF

/* EXT_bgra */
#define GL_BGR_EXT                        0x80E0
#define GL_BGRA_EXT                       0x80E1

/* SGIS_texture_lod */
#define GL_TEXTURE_MIN_LOD_SGIS           0x813A
#define GL_TEXTURE_MAX_LOD_SGIS           0x813B
#define GL_TEXTURE_BASE_LEVEL_SGIS        0x813C
#define GL_TEXTURE_MAX_LEVEL_SGIS         0x813D

/* EXT_paletted_texture */
#define GL_COLOR_INDEX1_EXT               0x80E2
#define GL_COLOR_INDEX2_EXT               0x80E3
#define GL_COLOR_INDEX4_EXT               0x80E4
#define GL_COLOR_INDEX8_EXT               0x80E5
#define GL_COLOR_INDEX12_EXT              0x80E6
#define GL_COLOR_INDEX16_EXT              0x80E7
#define GL_TEXTURE_INDEX_SIZE_EXT         0x80ED

/* EXT_clip_volume_hint */
#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT  0x80F0

/* EXT_point_parameters */
#define GL_POINT_SIZE_MIN_EXT             0x8126
#define GL_POINT_SIZE_MAX_EXT             0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT  0x8128
#define GL_DISTANCE_ATTENUATION_EXT       0x8129

/* EXT_compiled_vertex_array */
#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT   0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT   0x81A9

/* EXT_shared_texture_palette */
#define GL_SHARED_TEXTURE_PALETTE_EXT     0x81FB

/* SGIS_multitexture */
#define GL_SELECTED_TEXTURE_SGIS          0x835C
#define GL_MAX_TEXTURES_SGIS              0x835D
#define GL_TEXTURE0_SGIS                  0x835E
#define GL_TEXTURE1_SGIS                  0x835F
#define GL_TEXTURE2_SGIS                  0x8360
#define GL_TEXTURE3_SGIS                  0x8361

/* ARB_multitexture */
#define GL_ACTIVE_TEXTURE_ARB             0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB      0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB          0x84E2
#define GL_TEXTURE0_ARB                   0x84C0
#define GL_TEXTURE1_ARB                   0x84C1
#define GL_TEXTURE2_ARB                   0x84C2
#define GL_TEXTURE3_ARB                   0x84C3
#define GL_TEXTURE4_ARB                   0x84C4
#define GL_TEXTURE5_ARB                   0x84C5
#define GL_TEXTURE6_ARB                   0x84C6
#define GL_TEXTURE7_ARB                   0x84C7
#define GL_TEXTURE8_ARB                   0x84C8
#define GL_TEXTURE9_ARB                   0x84C9
#define GL_TEXTURE10_ARB                  0x84CA
#define GL_TEXTURE11_ARB                  0x84CB
#define GL_TEXTURE12_ARB                  0x84CC
#define GL_TEXTURE13_ARB                  0x84CD
#define GL_TEXTURE14_ARB                  0x84CE
#define GL_TEXTURE15_ARB                  0x84CF
#define GL_TEXTURE16_ARB                  0x84D0
#define GL_TEXTURE17_ARB                  0x84D1
#define GL_TEXTURE18_ARB                  0x84D2
#define GL_TEXTURE19_ARB                  0x84D3
#define GL_TEXTURE20_ARB                  0x84D4
#define GL_TEXTURE21_ARB                  0x84D5
#define GL_TEXTURE22_ARB                  0x84D6
#define GL_TEXTURE23_ARB                  0x84D7
#define GL_TEXTURE24_ARB                  0x84D8
#define GL_TEXTURE25_ARB                  0x84D9
#define GL_TEXTURE26_ARB                  0x84DA
#define GL_TEXTURE27_ARB                  0x84DB
#define GL_TEXTURE28_ARB                  0x84DC
#define GL_TEXTURE29_ARB                  0x84DD
#define GL_TEXTURE30_ARB                  0x84DE
#define GL_TEXTURE31_ARB                  0x84DF

/* EXT_fog_coord */
#define GL_FOG_COORDINATE_SOURCE_EXT      0x8450
#define GL_FOG_COORDINATE_EXT             0x8451
#define GL_FRAGMENT_DEPTH_EXT             0x8452
#define GL_CURRENT_FOG_COORDINATE_EXT     0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT  0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT 0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT 0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT       0x8457

/* EXT_secondary_color */
#define GL_COLOR_SUM_EXT                  0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT    0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT 0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT 0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT 0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT 0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT      0x845E

/* EXT_separate_specular_color */
#define GL_SINGLE_COLOR_EXT               0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT    0x81FA
#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT  0x81F8

/* EXT_rescale_normal */
#define GL_RESCALE_NORMAL_EXT             0x803A

/* EXT_stencil_wrap */
#define GL_INCR_WRAP_EXT                  0x8507
#define GL_DECR_WRAP_EXT                  0x8508

/* EXT_vertex_weighting */
#define GL_MODELVIEW0_MATRIX_EXT          GL_MODELVIEW_MATRIX
#define GL_MODELVIEW1_MATRIX_EXT          0x8506
#define GL_MODELVIEW0_STACK_DEPTH_EXT     GL_MODELVIEW_STACK_DEPTH
#define GL_MODELVIEW1_STACK_DEPTH_EXT     0x8502
#define GL_VERTEX_WEIGHTING_EXT           0x8509
#define GL_MODELVIEW0_EXT                 GL_MODELVIEW
#define GL_MODELVIEW1_EXT                 0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT      0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT        0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT   0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT   0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT 0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT 0x8510

/* NV_texgen_reflection */
#define GL_NORMAL_MAP_NV                  0x8511
#define GL_REFLECTION_MAP_NV              0x8512

/* EXT_texture_cube_map */
#define GL_NORMAL_MAP_EXT                 0x8511
#define GL_REFLECTION_MAP_EXT             0x8512
#define GL_TEXTURE_CUBE_MAP_EXT           0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_EXT   0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_EXT     0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT  0x851C

/* ARB_texture_cube_map */
#define GL_NORMAL_MAP_ARB                 0x8511
#define GL_REFLECTION_MAP_ARB             0x8512
#define GL_TEXTURE_CUBE_MAP_ARB           0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB   0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB     0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB  0x851C

/* NV_vertex_array_range */
#define GL_VERTEX_ARRAY_RANGE_NV          0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_NV   0x851E
#define GL_VERTEX_ARRAY_RANGE_VALID_NV    0x851F
#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV 0x8520
#define GL_VERTEX_ARRAY_RANGE_POINTER_NV  0x8521

/* NV_vertex_array_range2 */
#define GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV 0x8533

/* NV_register_combiners */
#define GL_REGISTER_COMBINERS_NV          0x8522
#define GL_COMBINER0_NV                   0x8550
#define GL_COMBINER1_NV                   0x8551
#define GL_COMBINER2_NV                   0x8552
#define GL_COMBINER3_NV                   0x8553
#define GL_COMBINER4_NV                   0x8554
#define GL_COMBINER5_NV                   0x8555
#define GL_COMBINER6_NV                   0x8556
#define GL_COMBINER7_NV                   0x8557
#define GL_VARIABLE_A_NV                  0x8523
#define GL_VARIABLE_B_NV                  0x8524
#define GL_VARIABLE_C_NV                  0x8525
#define GL_VARIABLE_D_NV                  0x8526
#define GL_VARIABLE_E_NV                  0x8527
#define GL_VARIABLE_F_NV                  0x8528
#define GL_VARIABLE_G_NV                  0x8529
/*      GL_ZERO */
#define GL_CONSTANT_COLOR0_NV             0x852A
#define GL_CONSTANT_COLOR1_NV             0x852B
/*      GL_FOG */
#define GL_PRIMARY_COLOR_NV               0x852C
#define GL_SECONDARY_COLOR_NV             0x852D
#define GL_SPARE0_NV                      0x852E
#define GL_SPARE1_NV                      0x852F
/*      GL_TEXTURE0_ARB */
/*      GL_TEXTURE1_ARB */
#define GL_UNSIGNED_IDENTITY_NV           0x8536
#define GL_UNSIGNED_INVERT_NV             0x8537
#define GL_EXPAND_NORMAL_NV               0x8538
#define GL_EXPAND_NEGATE_NV               0x8539
#define GL_HALF_BIAS_NORMAL_NV            0x853A
#define GL_HALF_BIAS_NEGATE_NV            0x853B
#define GL_SIGNED_IDENTITY_NV             0x853C
#define GL_SIGNED_NEGATE_NV               0x853D
#define GL_E_TIMES_F_NV                   0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV 0x8532
/*      GL_NONE */
#define GL_SCALE_BY_TWO_NV                0x853E
#define GL_SCALE_BY_FOUR_NV               0x853F
#define GL_SCALE_BY_ONE_HALF_NV           0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV   0x8541
#define GL_DISCARD_NV                     0x8530
#define GL_COMBINER_INPUT_NV              0x8542
#define GL_COMBINER_MAPPING_NV            0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV    0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV     0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV     0x8546
#define GL_COMBINER_MUX_SUM_NV            0x8547
#define GL_COMBINER_SCALE_NV              0x8548
#define GL_COMBINER_BIAS_NV               0x8549
#define GL_COMBINER_AB_OUTPUT_NV          0x854A
#define GL_COMBINER_CD_OUTPUT_NV          0x854B
#define GL_COMBINER_SUM_OUTPUT_NV         0x854C
#define GL_MAX_GENERAL_COMBINERS_NV       0x854D
#define GL_NUM_GENERAL_COMBINERS_NV       0x854E
#define GL_COLOR_SUM_CLAMP_NV             0x854F

/* NV_fog_distance */
#define GL_FOG_DISTANCE_MODE_NV           0x855A
#define GL_EYE_RADIAL_NV                  0x855B
/*      GL_EYE_PLANE */
#define GL_EYE_PLANE_ABSOLUTE_NV          0x855C

/* NV_fragment_program */
#define GL_FRAGMENT_PROGRAM_NV            0x8870
#define GL_MAX_TEXTURE_COORDS_NV          0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_NV     0x8872
#define GL_FRAGMENT_PROGRAM_BINDING_NV    0x8873
#define GL_PROGRAM_ERROR_STRING_NV        0x8874
#define GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV 0x8868

/* NV_light_max_exponent */
#define GL_MAX_SHININESS_NV               0x8504
#define GL_MAX_SPOT_EXPONENT_NV           0x8505

/* ARB_texture_env_combine */
#define GL_COMBINE_ARB                    0x8570
#define GL_COMBINE_RGB_ARB                0x8571
#define GL_COMBINE_ALPHA_ARB              0x8572
#define GL_RGB_SCALE_ARB                  0x8573
#define GL_ADD_SIGNED_ARB                 0x8574
#define GL_INTERPOLATE_ARB                0x8575
#define GL_CONSTANT_ARB                   0x8576
#define GL_PRIMARY_COLOR_ARB              0x8577
#define GL_PREVIOUS_ARB                   0x8578
#define GL_SOURCE0_RGB_ARB                0x8580
#define GL_SOURCE1_RGB_ARB                0x8581
#define GL_SOURCE2_RGB_ARB                0x8582
#define GL_SOURCE0_ALPHA_ARB              0x8588
#define GL_SOURCE1_ALPHA_ARB              0x8589
#define GL_SOURCE2_ALPHA_ARB              0x858A
#define GL_OPERAND0_RGB_ARB               0x8590
#define GL_OPERAND1_RGB_ARB               0x8591
#define GL_OPERAND2_RGB_ARB               0x8592
#define GL_OPERAND0_ALPHA_ARB             0x8598
#define GL_OPERAND1_ALPHA_ARB             0x8599
#define GL_OPERAND2_ALPHA_ARB             0x859A
#define GL_SUBTRACT_ARB                   0x84E7

/* EXT_texture_env_combine */
#define GL_COMBINE_EXT                    0x8570
#define GL_COMBINE_RGB_EXT                0x8571
#define GL_COMBINE_ALPHA_EXT              0x8572
#define GL_RGB_SCALE_EXT                  0x8573
#define GL_ADD_SIGNED_EXT                 0x8574
#define GL_INTERPOLATE_EXT                0x8575
#define GL_CONSTANT_EXT                   0x8576
#define GL_PRIMARY_COLOR_EXT              0x8577
#define GL_PREVIOUS_EXT                   0x8578
#define GL_SOURCE0_RGB_EXT                0x8580
#define GL_SOURCE1_RGB_EXT                0x8581
#define GL_SOURCE2_RGB_EXT                0x8582
#define GL_SOURCE0_ALPHA_EXT              0x8588
#define GL_SOURCE1_ALPHA_EXT              0x8589
#define GL_SOURCE2_ALPHA_EXT              0x858A
#define GL_OPERAND0_RGB_EXT               0x8590
#define GL_OPERAND1_RGB_EXT               0x8591
#define GL_OPERAND2_RGB_EXT               0x8592
#define GL_OPERAND0_ALPHA_EXT             0x8598
#define GL_OPERAND1_ALPHA_EXT             0x8599
#define GL_OPERAND2_ALPHA_EXT             0x859A

/* NV_texture_env_combine4 */
#define GL_COMBINE4_NV                    0x8503
#define GL_SOURCE3_RGB_NV                 0x8583
#define GL_SOURCE3_ALPHA_NV               0x858B
#define GL_OPERAND3_RGB_NV                0x8593
#define GL_OPERAND3_ALPHA_NV              0x859B

/* EXT_texture_filter_anisotropic */
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

/* EXT_texture_lod_bias */
#define GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#define GL_TEXTURE_LOD_BIAS_EXT           0x8501

/* EXT_texture_edge_clamp */
#define GL_CLAMP_TO_EDGE_EXT              0x812F

/* S3_s3tc */
#define GL_RGB_S3TC                       0x83A0
#define GL_RGB4_S3TC                      0x83A1
#define GL_RGBA_S3TC                      0x83A2
#define GL_RGBA4_S3TC                     0x83A3
#define GL_RGBA_DXT5_S3TC                 0x83A4
#define GL_RGBA4_DXT5_S3TC                0x83A5

/* ARB_transpose_matrix */
#define GL_TRANSPOSE_MODELVIEW_MATRIX_ARB 0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX_ARB 0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX_ARB   0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX_ARB     0x84E6

/* ARB_texture_compression */
#define GL_COMPRESSED_ALPHA_ARB           0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB       0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB 0x84EB
#define GL_COMPRESSED_INTENSITY_ARB       0x84EC
#define GL_COMPRESSED_RGB_ARB             0x84ED
#define GL_COMPRESSED_RGBA_ARB            0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB   0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB 0x86A0
#define GL_TEXTURE_COMPRESSED_ARB         0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB 0x86A3

/* EXT_texture_compression_s3tc */
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3

/* NV_fence */
#define GL_ALL_COMPLETED_NV               0x84F2
#define GL_FENCE_STATUS_NV                0x84F3
#define GL_FENCE_CONDITION_NV             0x84F4

/* NV_mac_get_proc_address */
#define GL_ALL_EXTENSIONS_NV              0x84FB
#define GL_MAC_GET_PROC_ADDRESS_NV        0x84FC

/* NV_vertex_program */
#define GL_VERTEX_PROGRAM_NV              0x8620
#define GL_VERTEX_STATE_PROGRAM_NV        0x8621
#define GL_ATTRIB_ARRAY_SIZE_NV           0x8623
#define GL_ATTRIB_ARRAY_STRIDE_NV         0x8624
#define GL_ATTRIB_ARRAY_TYPE_NV           0x8625
#define GL_CURRENT_ATTRIB_NV              0x8626
#define GL_PROGRAM_LENGTH_NV              0x8627
#define GL_PROGRAM_STRING_NV              0x8628
#define GL_MODELVIEW_PROJECTION_NV        0x8629
#define GL_IDENTITY_NV                    0x862A
#define GL_INVERSE_NV                     0x862B
#define GL_TRANSPOSE_NV                   0x862C
#define GL_INVERSE_TRANSPOSE_NV           0x862D
#define GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV 0x862E
#define GL_MAX_TRACK_MATRICES_NV          0x862F
#define GL_MATRIX0_NV                     0x8630
#define GL_MATRIX1_NV                     0x8631
#define GL_MATRIX2_NV                     0x8632
#define GL_MATRIX3_NV                     0x8633
#define GL_MATRIX4_NV                     0x8634
#define GL_MATRIX5_NV                     0x8635
#define GL_MATRIX6_NV                     0x8636
#define GL_MATRIX7_NV                     0x8637
#define GL_CURRENT_MATRIX_STACK_DEPTH_NV  0x8640
#define GL_CURRENT_MATRIX_NV              0x8641
#define GL_VERTEX_PROGRAM_POINT_SIZE_NV   0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_NV     0x8643
#define GL_PROGRAM_PARAMETER_NV           0x8644
#define GL_ATTRIB_ARRAY_POINTER_NV        0x8645
#define GL_PROGRAM_TARGET_NV              0x8646
#define GL_PROGRAM_RESIDENT_NV            0x8647
#define GL_TRACK_MATRIX_NV                0x8648
#define GL_TRACK_MATRIX_TRANSFORM_NV      0x8649
#define GL_VERTEX_PROGRAM_BINDING_NV      0x864A
#define GL_PROGRAM_ERROR_POSITION_NV      0x864B
#define GL_VERTEX_ATTRIB_ARRAY0_NV        0x8650
#define GL_VERTEX_ATTRIB_ARRAY1_NV        0x8651
#define GL_VERTEX_ATTRIB_ARRAY2_NV        0x8652
#define GL_VERTEX_ATTRIB_ARRAY3_NV        0x8653
#define GL_VERTEX_ATTRIB_ARRAY4_NV        0x8654
#define GL_VERTEX_ATTRIB_ARRAY5_NV        0x8655
#define GL_VERTEX_ATTRIB_ARRAY6_NV        0x8656
#define GL_VERTEX_ATTRIB_ARRAY7_NV        0x8657
#define GL_VERTEX_ATTRIB_ARRAY8_NV        0x8658
#define GL_VERTEX_ATTRIB_ARRAY9_NV        0x8659
#define GL_VERTEX_ATTRIB_ARRAY10_NV       0x865A
#define GL_VERTEX_ATTRIB_ARRAY11_NV       0x865B
#define GL_VERTEX_ATTRIB_ARRAY12_NV       0x865C
#define GL_VERTEX_ATTRIB_ARRAY13_NV       0x865D
#define GL_VERTEX_ATTRIB_ARRAY14_NV       0x865E
#define GL_VERTEX_ATTRIB_ARRAY15_NV       0x865F
#define GL_MAP1_VERTEX_ATTRIB0_4_NV       0x8660
#define GL_MAP1_VERTEX_ATTRIB1_4_NV       0x8661
#define GL_MAP1_VERTEX_ATTRIB2_4_NV       0x8662
#define GL_MAP1_VERTEX_ATTRIB3_4_NV       0x8663
#define GL_MAP1_VERTEX_ATTRIB4_4_NV       0x8664
#define GL_MAP1_VERTEX_ATTRIB5_4_NV       0x8665
#define GL_MAP1_VERTEX_ATTRIB6_4_NV       0x8666
#define GL_MAP1_VERTEX_ATTRIB7_4_NV       0x8667
#define GL_MAP1_VERTEX_ATTRIB8_4_NV       0x8668
#define GL_MAP1_VERTEX_ATTRIB9_4_NV       0x8669
#define GL_MAP1_VERTEX_ATTRIB10_4_NV      0x866A
#define GL_MAP1_VERTEX_ATTRIB11_4_NV      0x866B
#define GL_MAP1_VERTEX_ATTRIB12_4_NV      0x866C
#define GL_MAP1_VERTEX_ATTRIB13_4_NV      0x866D
#define GL_MAP1_VERTEX_ATTRIB14_4_NV      0x866E
#define GL_MAP1_VERTEX_ATTRIB15_4_NV      0x866F
#define GL_MAP2_VERTEX_ATTRIB0_4_NV       0x8670
#define GL_MAP2_VERTEX_ATTRIB1_4_NV       0x8671
#define GL_MAP2_VERTEX_ATTRIB2_4_NV       0x8672
#define GL_MAP2_VERTEX_ATTRIB3_4_NV       0x8673
#define GL_MAP2_VERTEX_ATTRIB4_4_NV       0x8674
#define GL_MAP2_VERTEX_ATTRIB5_4_NV       0x8675
#define GL_MAP2_VERTEX_ATTRIB6_4_NV       0x8676
#define GL_MAP2_VERTEX_ATTRIB7_4_NV       0x8677
#define GL_MAP2_VERTEX_ATTRIB8_4_NV       0x8678
#define GL_MAP2_VERTEX_ATTRIB9_4_NV       0x8679
#define GL_MAP2_VERTEX_ATTRIB10_4_NV      0x867A
#define GL_MAP2_VERTEX_ATTRIB11_4_NV      0x867B
#define GL_MAP2_VERTEX_ATTRIB12_4_NV      0x867C
#define GL_MAP2_VERTEX_ATTRIB13_4_NV      0x867D
#define GL_MAP2_VERTEX_ATTRIB14_4_NV      0x867E
#define GL_MAP2_VERTEX_ATTRIB15_4_NV      0x867F

/* NV_texture_shader */
#define GL_OFFSET_TEXTURE_RECTANGLE_NV    0x864C
#define GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV 0x864D
#define GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV 0x864E
#define GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV 0x86D9
#define GL_UNSIGNED_INT_S8_S8_8_8_NV      0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV  0x86DB
#define GL_DSDT_MAG_INTENSITY_NV          0x86DC
#define GL_SHADER_CONSISTENT_NV           0x86DD
#define GL_TEXTURE_SHADER_NV              0x86DE
#define GL_SHADER_OPERATION_NV            0x86DF
#define GL_CULL_MODES_NV                  0x86E0
#define GL_OFFSET_TEXTURE_MATRIX_NV       0x86E1
#define GL_OFFSET_TEXTURE_SCALE_NV        0x86E2
#define GL_OFFSET_TEXTURE_BIAS_NV         0x86E3
#define GL_OFFSET_TEXTURE_2D_MATRIX_NV    GL_OFFSET_TEXTURE_MATRIX_NV
#define GL_OFFSET_TEXTURE_2D_SCALE_NV     GL_OFFSET_TEXTURE_SCALE_NV
#define GL_OFFSET_TEXTURE_2D_BIAS_NV      GL_OFFSET_TEXTURE_BIAS_NV
#define GL_PREVIOUS_TEXTURE_INPUT_NV      0x86E4
#define GL_CONST_EYE_NV                   0x86E5
#define GL_PASS_THROUGH_NV                0x86E6
#define GL_CULL_FRAGMENT_NV               0x86E7
#define GL_OFFSET_TEXTURE_2D_NV           0x86E8
#define GL_DEPENDENT_AR_TEXTURE_2D_NV     0x86E9
#define GL_DEPENDENT_GB_TEXTURE_2D_NV     0x86EA
#define GL_DOT_PRODUCT_NV                 0x86EC
#define GL_DOT_PRODUCT_DEPTH_REPLACE_NV   0x86ED
#define GL_DOT_PRODUCT_TEXTURE_2D_NV      0x86EE
#define GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV 0x86F0
#define GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV 0x86F1
#define GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV 0x86F2
#define GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV 0x86F3
#define GL_HILO_NV                        0x86F4
#define GL_DSDT_NV                        0x86F5
#define GL_DSDT_MAG_NV                    0x86F6
#define GL_DSDT_MAG_VIB_NV                0x86F7
#define GL_HILO16_NV                      0x86F8
#define GL_SIGNED_HILO_NV                 0x86F9
#define GL_SIGNED_HILO16_NV               0x86FA
#define GL_SIGNED_RGBA_NV                 0x86FB
#define GL_SIGNED_RGBA8_NV                0x86FC
#define GL_SIGNED_RGB_NV                  0x86FE
#define GL_SIGNED_RGB8_NV                 0x86FF
#define GL_SIGNED_LUMINANCE_NV            0x8701
#define GL_SIGNED_LUMINANCE8_NV           0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV      0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV    0x8704
#define GL_SIGNED_ALPHA_NV                0x8705
#define GL_SIGNED_ALPHA8_NV               0x8706
#define GL_SIGNED_INTENSITY_NV            0x8707
#define GL_SIGNED_INTENSITY8_NV           0x8708
#define GL_DSDT8_NV                       0x8709
#define GL_DSDT8_MAG8_NV                  0x870A
#define GL_DSDT8_MAG8_INTENSITY8_NV       0x870B
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV   0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV 0x870D
#define GL_HI_SCALE_NV                    0x870E
#define GL_LO_SCALE_NV                    0x870F
#define GL_DS_SCALE_NV                    0x8710
#define GL_DT_SCALE_NV                    0x8711
#define GL_MAGNITUDE_SCALE_NV             0x8712
#define GL_VIBRANCE_SCALE_NV              0x8713
#define GL_HI_BIAS_NV                     0x8714
#define GL_LO_BIAS_NV                     0x8715
#define GL_DS_BIAS_NV                     0x8716
#define GL_DT_BIAS_NV                     0x8717
#define GL_MAGNITUDE_BIAS_NV              0x8718
#define GL_VIBRANCE_BIAS_NV               0x8719
#define GL_TEXTURE_BORDER_VALUES_NV       0x871A
#define GL_TEXTURE_HI_SIZE_NV             0x871B
#define GL_TEXTURE_LO_SIZE_NV             0x871C
#define GL_TEXTURE_DS_SIZE_NV             0x871D
#define GL_TEXTURE_DT_SIZE_NV             0x871E
#define GL_TEXTURE_MAG_SIZE_NV            0x871F

/* NV_texture_shader2 */
#define GL_DOT_PRODUCT_TEXTURE_3D_NV      0x86EF

/* NV_texture_shader3 */
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_NV 0x8850
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV 0x8851
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV 0x8852
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV 0x8853
#define GL_OFFSET_HILO_TEXTURE_2D_NV      0x8854
#define GL_OFFSET_HILO_TEXTURE_RECTANGLE_NV 0x8855
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV 0x8856
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV 0x8857
#define GL_DEPENDENT_HILO_TEXTURE_2D_NV   0x8858
#define GL_DEPENDENT_RGB_TEXTURE_3D_NV    0x8859
#define GL_DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV 0x885A
#define GL_DOT_PRODUCT_PASS_THROUGH_NV    0x885B
#define GL_DOT_PRODUCT_TEXTURE_1D_NV      0x885C
#define GL_DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV 0x885D
#define GL_HILO8_NV                       0x885E
#define GL_SIGNED_HILO8_NV                0x885F
#define GL_FORCE_BLUE_TO_ONE_NV           0x8860

/* NV_register_combiners2 */
#define GL_PER_STAGE_CONSTANTS_NV         0x8535

/* IBM_texture_mirrored_repeat */
#define GL_MIRRORED_REPEAT_IBM            0x8370

/* ARB_texture_env_dot3 */
#define GL_DOT3_RGB_ARB                   0x86AE
#define GL_DOT3_RGBA_ARB                  0x86AF

/* EXT_texture_env_dot3 */
#define GL_DOT3_RGB_EXT                   0x8740
#define GL_DOT3_RGBA_EXT                  0x8741

/* APPLE_transform_hint */
#define GL_TRANSFORM_HINT_APPLE           0x85B1

/* ARB_texture_border_clamp */
#define GL_CLAMP_TO_BORDER_ARB            0x812D

/* NV_texture_rectangle */
#define GL_TEXTURE_RECTANGLE_NV           0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_NV   0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_NV     0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_NV  0x84F8

/* SGIX_shadow */
#define GL_TEXTURE_COMPARE_SGIX           0x819A
#define GL_TEXTURE_COMPARE_OPERATOR_SGIX  0x819B
#define GL_TEXTURE_LEQUAL_R_SGIX          0x819C
#define GL_TEXTURE_GEQUAL_R_SGIX          0x819D

/* SGIX_depth_texture */
#define GL_DEPTH_COMPONENT16_SGIX         0x81A5
#define GL_DEPTH_COMPONENT24_SGIX         0x81A6
#define GL_DEPTH_COMPONENT32_SGIX         0x81A7

/* ARB_multisample */
#define GL_MULTISAMPLE_ARB                0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE_ARB   0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_ARB        0x809F
#define GL_SAMPLE_COVERAGE_ARB            0x80A0
#define GL_SAMPLE_BUFFERS_ARB             0x80A8
#define GL_SAMPLES_ARB                    0x80A9
#define GL_SAMPLE_COVERAGE_VALUE_ARB      0x80AA
#define GL_SAMPLE_COVERAGE_INVERT_ARB     0x80AB
#define GL_MULTISAMPLE_BIT_ARB            0x20000000

/* NV_multisample_filter_hint */
#define GL_MULTISAMPLE_FILTER_HINT_NV     0x8534

/* NV_packed_depth_stencil */
#define GL_DEPTH_STENCIL_NV               0x84F9
#define GL_UNSIGNED_INT_24_8_NV           0x84FA

/* EXT_draw_range_elements */
#define GL_MAX_ELEMENTS_VERTICES_EXT      0x80E8
#define GL_MAX_ELEMENTS_INDICES_EXT       0x80E9

/* SGIS_generate_mipmap */
#define GL_GENERATE_MIPMAP_SGIS           0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS      0x8192

/* NV_pixel_data_range */
#define GL_WRITE_PIXEL_DATA_RANGE_NV      0x8878
#define GL_READ_PIXEL_DATA_RANGE_NV       0x8879
#define GL_WRITE_PIXEL_DATA_RANGE_LENGTH_NV 0x887A
#define GL_READ_PIXEL_DATA_RANGE_LENGTH_NV 0x887B
#define GL_WRITE_PIXEL_DATA_RANGE_POINTER_NV 0x887C
#define GL_READ_PIXEL_DATA_RANGE_POINTER_NV 0x887D

/* NV_packed_normal */
#define GL_UNSIGNED_INT_S10_S11_S11_REV_NV 0x886B

/* NV_half_float */
#define GL_HALF_FLOAT_NV                  0x140B

/* NV_copy_depth_to_color */
#define GL_DEPTH_STENCIL_TO_RGBA_NV       0x886E
#define GL_DEPTH_STENCIL_TO_BGRA_NV       0x886F

/* HP_occlusion_test */
#define GL_OCCLUSION_TEST_HP              0x8165
#define GL_OCCLUSION_TEST_RESULT_HP       0x8166

/* NV_occlusion_query */
#define GL_PIXEL_COUNTER_BITS_NV          0x8864
#define GL_CURRENT_OCCLUSION_QUERY_ID_NV  0x8865
#define GL_PIXEL_COUNT_NV                 0x8866
#define GL_PIXEL_COUNT_AVAILABLE_NV       0x8867

/* NV_point_sprite */
#define GL_POINT_SPRITE_NV                0x8861
#define GL_COORD_REPLACE_NV               0x8862
#define GL_POINT_SPRITE_R_MODE_NV         0x8863

/* 3DFX_tbuffer */
#define GL_TBUFFER_WRITE_MASK_3DFX        0x86D8

/* NV_depth_clamp */
#define GL_DEPTH_CLAMP_NV                 0x864F

/* NV_float_buffer */
#define GL_FLOAT_R_NV                     0x8880
#define GL_FLOAT_RG_NV                    0x8881
#define GL_FLOAT_RGB_NV                   0x8882
#define GL_FLOAT_RGBA_NV                  0x8883
#define GL_FLOAT_R16_NV                   0x8884
#define GL_FLOAT_R32_NV                   0x8885
#define GL_FLOAT_RG16_NV                  0x8886
#define GL_FLOAT_RG32_NV                  0x8887
#define GL_FLOAT_RGB16_NV                 0x8888
#define GL_FLOAT_RGB32_NV                 0x8889
#define GL_FLOAT_RGBA16_NV                0x888A
#define GL_FLOAT_RGBA32_NV                0x888B
#define GL_TEXTURE_FLOAT_COMPONENTS_NV    0x888C
#define GL_FLOAT_CLEAR_COLOR_VALUE_NV     0x888D
#define GL_FLOAT_RGBA_MODE_NV             0x888E

/* EXT_stencil_two_side */
#define GL_STENCIL_TEST_TWO_SIDE_EXT      0x8910
#define GL_ACTIVE_STENCIL_FACE_EXT        0x8911

/* EXT_blend_func_separate */
#define GL_BLEND_DST_RGB_EXT              0x80C8
#define GL_BLEND_SRC_RGB_EXT              0x80C9
#define GL_BLEND_DST_ALPHA_EXT            0x80CA
#define GL_BLEND_SRC_ALPHA_EXT            0x80CB

/* ARB_texture_mirrored_repeat */
#define GL_MIRRORED_REPEAT_ARB            0x8370

/* ARB_depth_texture */
#define GL_DEPTH_COMPONENT16_ARB          0x81A5
#define GL_DEPTH_COMPONENT24_ARB          0x81A6
#define GL_DEPTH_COMPONENT32_ARB          0x81A7
#define GL_TEXTURE_DEPTH_SIZE_ARB         0x884A
#define GL_DEPTH_TEXTURE_MODE_ARB         0x884B

/* ARB_shadow */
#define GL_TEXTURE_COMPARE_MODE_ARB       0x884C
#define GL_TEXTURE_COMPARE_FUNC_ARB       0x884D
#define GL_COMPARE_R_TO_TEXTURE_ARB       0x884E

/* ARB_shadow_ambient */
#define GL_TEXTURE_COMPARE_FAIL_VALUE_ARB 0x80BF

/* NV_force_software */
#define GL_FORCE_SOFTWARE_NV              0x6007

/* NV_flush_hold */
#define GL_CURRENT_FLUSHHOLD_NVX          0x6008
#define GL_MAX_PENDING_FLUSHHOLD_NVX      0x6009

/* ARB_point_parameters */
#define GL_POINT_SIZE_MIN_ARB             0x8126
#define GL_POINT_SIZE_MAX_ARB             0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB  0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB 0x8129

/* EXT_depth_bounds_test */
#define GL_DEPTH_BOUNDS_TEST_EXT          0x8890
#define GL_DEPTH_BOUNDS_EXT               0x8891

/* ARB_vertex_program */
#define GL_VERTEX_PROGRAM_ARB             0x8620
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB  0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB    0x8643
#define GL_COLOR_SUM_ARB                  0x8458
#define GL_PROGRAM_FORMAT_ASCII_ARB       0x8875
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB   0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB   0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB 0x886A
#define GL_CURRENT_VERTEX_ATTRIB_ARB      0x8626
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB 0x8645
#define GL_PROGRAM_LENGTH_ARB             0x8627
#define GL_PROGRAM_FORMAT_ARB             0x8876
#define GL_PROGRAM_BINDING_ARB            0x8677
#define GL_PROGRAM_INSTRUCTIONS_ARB       0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB   0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB 0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB 0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB        0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB    0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB 0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB 0x88A7
#define GL_PROGRAM_PARAMETERS_ARB         0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB     0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB  0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB 0x88AB
#define GL_PROGRAM_ATTRIBS_ARB            0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB        0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB     0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB 0x88AF
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB  0x88B0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB 0x88B1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB 0x88B2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB 0x88B3
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB 0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB 0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB 0x88B6
#define GL_PROGRAM_STRING_ARB             0x8628
#define GL_PROGRAM_ERROR_POSITION_ARB     0x864B
#define GL_CURRENT_MATRIX_ARB             0x8641
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB   0x88B7
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB 0x8640
#define GL_MAX_VERTEX_ATTRIBS_ARB         0x8869
#define GL_MAX_PROGRAM_MATRICES_ARB       0x862F
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB 0x862E
#define GL_PROGRAM_ERROR_STRING_ARB       0x8874
#define GL_MATRIX0_ARB                    0x88C0
#define GL_MATRIX1_ARB                    0x88C1
#define GL_MATRIX2_ARB                    0x88C2
#define GL_MATRIX3_ARB                    0x88C3
#define GL_MATRIX4_ARB                    0x88C4
#define GL_MATRIX5_ARB                    0x88C5
#define GL_MATRIX6_ARB                    0x88C6
#define GL_MATRIX7_ARB                    0x88C7
#define GL_MATRIX8_ARB                    0x88C8
#define GL_MATRIX9_ARB                    0x88C9
#define GL_MATRIX10_ARB                   0x88CA
#define GL_MATRIX11_ARB                   0x88CB
#define GL_MATRIX12_ARB                   0x88CC
#define GL_MATRIX13_ARB                   0x88CD
#define GL_MATRIX14_ARB                   0x88CE
#define GL_MATRIX15_ARB                   0x88CF
#define GL_MATRIX16_ARB                   0x88D0
#define GL_MATRIX17_ARB                   0x88D1
#define GL_MATRIX18_ARB                   0x88D2
#define GL_MATRIX19_ARB                   0x88D3
#define GL_MATRIX20_ARB                   0x88D4
#define GL_MATRIX21_ARB                   0x88D5
#define GL_MATRIX22_ARB                   0x88D6
#define GL_MATRIX23_ARB                   0x88D7
#define GL_MATRIX24_ARB                   0x88D8
#define GL_MATRIX25_ARB                   0x88D9
#define GL_MATRIX26_ARB                   0x88DA
#define GL_MATRIX27_ARB                   0x88DB
#define GL_MATRIX28_ARB                   0x88DC
#define GL_MATRIX29_ARB                   0x88DD
#define GL_MATRIX30_ARB                   0x88DE
#define GL_MATRIX31_ARB                   0x88DF

/* OpenGL14 */
#define GL_POINT_SIZE_MIN                 0x8126
#define GL_POINT_SIZE_MAX                 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_POINT_DISTANCE_ATTENUATION     0x8129
#define GL_FOG_COORDINATE_SOURCE          0x8450
#define GL_FOG_COORDINATE                 0x8451
#define GL_FRAGMENT_DEPTH                 0x8452
#define GL_CURRENT_FOG_COORDINATE         0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE      0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE    0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER   0x8456
#define GL_FOG_COORDINATE_ARRAY           0x8457
#define GL_COLOR_SUM                      0x8458
#define GL_CURRENT_SECONDARY_COLOR        0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE     0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE     0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE   0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER  0x845D
#define GL_SECONDARY_COLOR_ARRAY          0x845E
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_FILTER_CONTROL         0x8500
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_GENERATE_MIPMAP                0x8191
#define GL_GENERATE_MIPMAP_HINT           0x8192
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_MIRRORED_REPEAT                0x8370
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_DEPTH_TEXTURE_MODE             0x884B
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D
#define GL_COMPARE_R_TO_TEXTURE           0x884E

/* NV_primitive_restart */
#define GL_PRIMITIVE_RESTART_NV           0x8558
#define GL_PRIMITIVE_RESTART_INDEX_NV     0x8559

/* SGIS_texture_color_mask */
#define GL_TEXTURE_COLOR_WRITEMASK_SGIS   0x81EF

/* NVX_ycrcb */
#define GL_CRYCBY_422_NVX                 0x600A
#define GL_YCRYCB_422_NVX                 0x600B

/* NV_texture_expand_normal */
#define GL_TEXTURE_UNSIGNED_REMAP_MODE_NV 0x888F

/* ARB_fragment_program */
#define GL_FRAGMENT_PROGRAM_ARB           0x8804
/*      GL_PROGRAM_FORMAT_ASCII_ARB */
/*      GL_PROGRAM_LENGTH_ARB */
/*      GL_PROGRAM_FORMAT_ARB */
/*      GL_PROGRAM_BINDING_ARB */
/*      GL_PROGRAM_INSTRUCTIONS_ARB */
/*      GL_MAX_PROGRAM_INSTRUCTIONS_ARB */
/*      GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB */
/*      GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB */
/*      GL_PROGRAM_TEMPORARIES_ARB */
/*      GL_MAX_PROGRAM_TEMPORARIES_ARB */
/*      GL_PROGRAM_NATIVE_TEMPORARIES_ARB */
/*      GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB */
/*      GL_PROGRAM_PARAMETERS_ARB */
/*      GL_MAX_PROGRAM_PARAMETERS_ARB */
/*      GL_PROGRAM_NATIVE_PARAMETERS_ARB */
/*      GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB */
/*      GL_PROGRAM_ATTRIBS_ARB */
/*      GL_MAX_PROGRAM_ATTRIBS_ARB */
/*      GL_PROGRAM_NATIVE_ATTRIBS_ARB */
/*      GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB */
/*      GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB */
/*      GL_MAX_PROGRAM_ENV_PARAMETERS_ARB */
/*      GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB */
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB   0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB   0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB   0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB 0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB 0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB 0x880A
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB 0x880B
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB 0x880C
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB 0x880D
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB 0x880E
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB 0x880F
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB 0x8810
/*      GL_PROGRAM_STRING_ARB */
/*      GL_PROGRAM_ERROR_POSITION_ARB */
/*      GL_CURRENT_MATRIX_ARB */
/*      GL_TRANSPOSE_CURRENT_MATRIX_ARB */
/*      GL_CURRENT_MATRIX_STACK_DEPTH_ARB */
/*      GL_MAX_PROGRAM_MATRICES_ARB */
/*      GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB */
#define GL_MAX_TEXTURE_COORDS_ARB         0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB    0x8872
/*      GL_PROGRAM_ERROR_STRING_ARB */
/*      GL_MATRIX0_ARB */
/*      GL_MATRIX1_ARB */
/*      GL_MATRIX2_ARB */
/*      GL_MATRIX3_ARB */
/*      GL_MATRIX4_ARB */
/*      GL_MATRIX5_ARB */
/*      GL_MATRIX6_ARB */
/*      GL_MATRIX7_ARB */
/*      GL_MATRIX8_ARB */
/*      GL_MATRIX9_ARB */
/*      GL_MATRIX10_ARB */
/*      GL_MATRIX11_ARB */
/*      GL_MATRIX12_ARB */
/*      GL_MATRIX13_ARB */
/*      GL_MATRIX14_ARB */
/*      GL_MATRIX15_ARB */
/*      GL_MATRIX16_ARB */
/*      GL_MATRIX17_ARB */
/*      GL_MATRIX18_ARB */
/*      GL_MATRIX19_ARB */
/*      GL_MATRIX20_ARB */
/*      GL_MATRIX21_ARB */
/*      GL_MATRIX22_ARB */
/*      GL_MATRIX23_ARB */
/*      GL_MATRIX24_ARB */
/*      GL_MATRIX25_ARB */
/*      GL_MATRIX26_ARB */
/*      GL_MATRIX27_ARB */
/*      GL_MATRIX28_ARB */
/*      GL_MATRIX29_ARB */
/*      GL_MATRIX30_ARB */
/*      GL_MATRIX31_ARB */

/* ARB_vertex_buffer_object */
#define GL_ARRAY_BUFFER_ARB               0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB       0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB       0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB 0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB 0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB 0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB 0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB 0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB 0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB 0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB 0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB 0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB 0x889F
#define GL_STREAM_DRAW_ARB                0x88E0
#define GL_STREAM_READ_ARB                0x88E1
#define GL_STREAM_COPY_ARB                0x88E2
#define GL_STATIC_DRAW_ARB                0x88E4
#define GL_STATIC_READ_ARB                0x88E5
#define GL_STATIC_COPY_ARB                0x88E6
#define GL_DYNAMIC_DRAW_ARB               0x88E8
#define GL_DYNAMIC_READ_ARB               0x88E9
#define GL_DYNAMIC_COPY_ARB               0x88EA
#define GL_READ_ONLY_ARB                  0x88B8
#define GL_WRITE_ONLY_ARB                 0x88B9
#define GL_READ_WRITE_ARB                 0x88BA
#define GL_BUFFER_SIZE_ARB                0x8764
#define GL_BUFFER_USAGE_ARB               0x8765
#define GL_BUFFER_ACCESS_ARB              0x88BB
#define GL_BUFFER_MAPPED_ARB              0x88BC
#define GL_BUFFER_MAP_POINTER_ARB         0x88BD

/*************************************************************/

GLAPI void APIENTRY glAccum (GLenum op, GLfloat value);
GLAPI void APIENTRY glActiveStencilFaceEXT (GLenum face);
GLAPI void APIENTRY glActiveTexture (GLenum texture);
GLAPI void APIENTRY glActiveTextureARB (GLenum texture);
GLAPI void APIENTRY glAddSwapHintRectWIN (GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glAlphaFunc (GLenum func, GLclampf ref);
GLboolean glAreProgramsResidentNV (GLsizei n, const GLuint *programs, GLboolean *residences);
GLboolean glAreTexturesResident (GLsizei n, const GLuint *textures, GLboolean *residences);
GLboolean glAreTexturesResidentEXT (GLsizei n, const GLuint *textures, GLboolean *residences);
GLAPI void APIENTRY glArrayElement (GLint i);
GLAPI void APIENTRY glArrayElementEXT (GLint i);
GLAPI void APIENTRY glBegin (GLenum mode);
GLAPI void APIENTRY glBeginOcclusionQueryNV (GLuint id);
GLAPI void APIENTRY glBindBufferARB (GLenum target, GLuint buffer);
GLAPI void APIENTRY glBindProgramARB (GLenum target, GLuint program);
GLAPI void APIENTRY glBindProgramNV (GLenum target, GLuint id);
GLAPI void APIENTRY glBindTexture (GLenum target, GLuint texture);
GLAPI void APIENTRY glBindTextureEXT (GLenum target, GLuint texture);
GLAPI void APIENTRY glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
GLAPI void APIENTRY glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GLAPI void APIENTRY glBlendColorEXT (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GLAPI void APIENTRY glBlendEquation (GLenum mode);
GLAPI void APIENTRY glBlendEquationEXT (GLenum mode);
GLAPI void APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GLAPI void APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GLAPI void APIENTRY glBlendFuncSeparateEXT (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GLAPI void APIENTRY glBufferDataARB (GLenum target, GLsizeiptrARB size, const GLvoid *data, GLenum usage);
GLAPI void APIENTRY glBufferSubDataARB (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data);
GLAPI void APIENTRY glCallList (GLuint list);
GLAPI void APIENTRY glCallLists (GLsizei n, GLenum type, const GLvoid *lists);
GLAPI void APIENTRY glClear (GLbitfield mask);
GLAPI void APIENTRY glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI void APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GLAPI void APIENTRY glClearDepth (GLclampd depth);
GLAPI void APIENTRY glClearIndex (GLfloat c);
GLAPI void APIENTRY glClearStencil (GLint s);
GLAPI void APIENTRY glClientActiveTexture (GLenum texture);
GLAPI void APIENTRY glClientActiveTextureARB (GLenum texture);
GLAPI void APIENTRY glClipPlane (GLenum plane, const GLdouble *equation);
GLAPI void APIENTRY glColor3b (GLbyte red, GLbyte green, GLbyte blue);
GLAPI void APIENTRY glColor3bv (const GLbyte *v);
GLAPI void APIENTRY glColor3d (GLdouble red, GLdouble green, GLdouble blue);
GLAPI void APIENTRY glColor3dv (const GLdouble *v);
GLAPI void APIENTRY glColor3f (GLfloat red, GLfloat green, GLfloat blue);
GLAPI void APIENTRY glColor3fv (const GLfloat *v);
GLAPI void APIENTRY glColor3hNV (GLhalf red, GLhalf green, GLhalf blue);
GLAPI void APIENTRY glColor3hvNV (const GLhalf *v);
GLAPI void APIENTRY glColor3i (GLint red, GLint green, GLint blue);
GLAPI void APIENTRY glColor3iv (const GLint *v);
GLAPI void APIENTRY glColor3s (GLshort red, GLshort green, GLshort blue);
GLAPI void APIENTRY glColor3sv (const GLshort *v);
GLAPI void APIENTRY glColor3ub (GLubyte red, GLubyte green, GLubyte blue);
GLAPI void APIENTRY glColor3ubv (const GLubyte *v);
GLAPI void APIENTRY glColor3ui (GLuint red, GLuint green, GLuint blue);
GLAPI void APIENTRY glColor3uiv (const GLuint *v);
GLAPI void APIENTRY glColor3us (GLushort red, GLushort green, GLushort blue);
GLAPI void APIENTRY glColor3usv (const GLushort *v);
GLAPI void APIENTRY glColor4b (GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
GLAPI void APIENTRY glColor4bv (const GLbyte *v);
GLAPI void APIENTRY glColor4d (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
GLAPI void APIENTRY glColor4dv (const GLdouble *v);
GLAPI void APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI void APIENTRY glColor4fv (const GLfloat *v);
GLAPI void APIENTRY glColor4hNV (GLhalf red, GLhalf green, GLhalf blue, GLhalf alpha);
GLAPI void APIENTRY glColor4hvNV (const GLhalf *v);
GLAPI void APIENTRY glColor4i (GLint red, GLint green, GLint blue, GLint alpha);
GLAPI void APIENTRY glColor4iv (const GLint *v);
GLAPI void APIENTRY glColor4s (GLshort red, GLshort green, GLshort blue, GLshort alpha);
GLAPI void APIENTRY glColor4sv (const GLshort *v);
GLAPI void APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
GLAPI void APIENTRY glColor4ubv (const GLubyte *v);
GLAPI void APIENTRY glColor4ui (GLuint red, GLuint green, GLuint blue, GLuint alpha);
GLAPI void APIENTRY glColor4uiv (const GLuint *v);
GLAPI void APIENTRY glColor4us (GLushort red, GLushort green, GLushort blue, GLushort alpha);
GLAPI void APIENTRY glColor4usv (const GLushort *v);
GLAPI void APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GLAPI void APIENTRY glColorMaterial (GLenum face, GLenum mode);
GLAPI void APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glColorPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
GLAPI void APIENTRY glColorSubTable (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
GLAPI void APIENTRY glColorSubTableEXT (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *table);
GLAPI void APIENTRY glColorTable (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
GLAPI void APIENTRY glColorTableEXT (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
GLAPI void APIENTRY glColorTableParameterfv (GLenum target, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glColorTableParameteriv (GLenum target, GLenum pname, const GLint *params);
GLAPI void APIENTRY glCombinerInputNV (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
GLAPI void APIENTRY glCombinerOutputNV (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
GLAPI void APIENTRY glCombinerParameterfNV (GLenum pname, GLfloat param);
GLAPI void APIENTRY glCombinerParameterfvNV (GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glCombinerParameteriNV (GLenum pname, GLint param);
GLAPI void APIENTRY glCombinerParameterivNV (GLenum pname, const GLint *params);
GLAPI void APIENTRY glCombinerStageParameterfvNV (GLenum stage, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexImage1DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexImage2DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexImage3DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexSubImage1DARB (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexSubImage2DARB (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glCompressedTexSubImage3DARB (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
GLAPI void APIENTRY glConvolutionFilter1D (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
GLAPI void APIENTRY glConvolutionFilter2D (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
GLAPI void APIENTRY glConvolutionParameterf (GLenum target, GLenum pname, GLfloat params);
GLAPI void APIENTRY glConvolutionParameterfv (GLenum target, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glConvolutionParameteri (GLenum target, GLenum pname, GLint params);
GLAPI void APIENTRY glConvolutionParameteriv (GLenum target, GLenum pname, const GLint *params);
GLAPI void APIENTRY glCopyColorSubTable (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
GLAPI void APIENTRY glCopyColorTable (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
GLAPI void APIENTRY glCopyConvolutionFilter1D (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
GLAPI void APIENTRY glCopyConvolutionFilter2D (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
GLAPI void APIENTRY glCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
GLAPI void APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GLAPI void APIENTRY glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
GLAPI void APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glCopyTexSubImage3DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glCullFace (GLenum mode);
GLAPI void APIENTRY glDeleteBuffersARB (GLsizei n, const GLuint *buffers);
GLAPI void APIENTRY glDeleteFencesNV (GLsizei n, const GLuint *fences);
GLAPI void APIENTRY glDeleteLists (GLuint list, GLsizei range);
GLAPI void APIENTRY glDeleteOcclusionQueriesNV (GLsizei n, const GLuint *ids);
GLAPI void APIENTRY glDeleteProgramsARB (GLsizei n, const GLuint *programs);
GLAPI void APIENTRY glDeleteProgramsNV (GLsizei n, const GLuint *programs);
GLAPI void APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures);
GLAPI void APIENTRY glDeleteTexturesEXT (GLsizei n, const GLuint *textures);
GLAPI void APIENTRY glDepthBoundsEXT (GLclampd zmin, GLclampd zmax);
GLAPI void APIENTRY glDepthFunc (GLenum func);
GLAPI void APIENTRY glDepthMask (GLboolean flag);
GLAPI void APIENTRY glDepthRange (GLclampd zNear, GLclampd zFar);
GLAPI void APIENTRY glDisable (GLenum cap);
GLAPI void APIENTRY glDisableClientState (GLenum array);
GLAPI void APIENTRY glDisableVertexAttribArrayARB (GLuint index);
GLAPI void APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count);
GLAPI void APIENTRY glDrawArraysEXT (GLenum mode, GLint first, GLsizei count);
GLAPI void APIENTRY glDrawBuffer (GLenum mode);
GLAPI void APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
GLAPI void APIENTRY glDrawMeshNV (GLenum mode, GLsizei count, GLenum type, GLsizei stride, const GLvoid *indicesTexCoord, const GLvoid *indicesNormal, const GLvoid *indicesVertex);
GLAPI void APIENTRY glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
GLAPI void APIENTRY glDrawRangeElementsEXT (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
GLAPI void APIENTRY glEdgeFlag (GLboolean flag);
GLAPI void APIENTRY glEdgeFlagPointer (GLsizei stride, const GLboolean *pointer);
GLAPI void APIENTRY glEdgeFlagPointerEXT (GLsizei stride, GLsizei count, const GLboolean *pointer);
GLAPI void APIENTRY glEdgeFlagv (const GLboolean *flag);
GLAPI void APIENTRY glEnable (GLenum cap);
GLAPI void APIENTRY glEnableClientState (GLenum array);
GLAPI void APIENTRY glEnableVertexAttribArrayARB (GLuint index);
GLAPI void APIENTRY glEnd (void);
GLAPI void APIENTRY glEndList (void);
GLAPI void APIENTRY glEndOcclusionQueryNV (void);
GLAPI void APIENTRY glEvalCoord1d (GLdouble u);
GLAPI void APIENTRY glEvalCoord1dv (const GLdouble *u);
GLAPI void APIENTRY glEvalCoord1f (GLfloat u);
GLAPI void APIENTRY glEvalCoord1fv (const GLfloat *u);
GLAPI void APIENTRY glEvalCoord2d (GLdouble u, GLdouble v);
GLAPI void APIENTRY glEvalCoord2dv (const GLdouble *u);
GLAPI void APIENTRY glEvalCoord2f (GLfloat u, GLfloat v);
GLAPI void APIENTRY glEvalCoord2fv (const GLfloat *u);
GLAPI void APIENTRY glEvalMesh1 (GLenum mode, GLint i1, GLint i2);
GLAPI void APIENTRY glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
GLAPI void APIENTRY glEvalPoint1 (GLint i);
GLAPI void APIENTRY glEvalPoint2 (GLint i, GLint j);
GLAPI void APIENTRY glExecuteProgramNV (GLenum target, GLuint id, const GLfloat *params);
GLAPI void APIENTRY glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer);
GLAPI void APIENTRY glFinalCombinerInputNV (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
GLAPI void APIENTRY glFinish (void);
GLAPI void APIENTRY glFinishFenceNV (GLuint fence);
GLAPI void APIENTRY glFlush (void);
GLuint glFlushHold (void);
GLAPI void APIENTRY glFlushPixelDataRangeNV (GLenum target);
GLAPI void APIENTRY glFlushVertexArrayRangeNV (void);
GLAPI void APIENTRY glFogCoordPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glFogCoordPointerEXT (GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glFogCoordd (GLdouble fog);
GLAPI void APIENTRY glFogCoorddEXT (GLdouble fog);
GLAPI void APIENTRY glFogCoorddv (const GLdouble *fog);
GLAPI void APIENTRY glFogCoorddvEXT (const GLdouble *fog);
GLAPI void APIENTRY glFogCoordf (GLfloat fog);
GLAPI void APIENTRY glFogCoordfEXT (GLfloat fog);
GLAPI void APIENTRY glFogCoordfv (const GLfloat *fog);
GLAPI void APIENTRY glFogCoordfvEXT (const GLfloat *fog);
GLAPI void APIENTRY glFogCoordhNV (GLhalf fog);
GLAPI void APIENTRY glFogCoordhvNV (const GLhalf *fog);
GLAPI void APIENTRY glFogf (GLenum pname, GLfloat param);
GLAPI void APIENTRY glFogfv (GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glFogi (GLenum pname, GLint param);
GLAPI void APIENTRY glFogiv (GLenum pname, const GLint *params);
GLAPI void APIENTRY glFrontFace (GLenum mode);
GLAPI void APIENTRY glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
GLAPI void APIENTRY glGenBuffersARB (GLsizei n, GLuint *buffers);
GLAPI void APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GLuint glGenLists (GLsizei range);
GLAPI void APIENTRY glGenOcclusionQueriesNV (GLsizei n, GLuint *ids);
GLAPI void APIENTRY glGenProgramsARB (GLsizei n, GLuint *programs);
GLAPI void APIENTRY glGenProgramsNV (GLsizei n, GLuint *programs);
GLAPI void APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GLAPI void APIENTRY glGenTexturesEXT (GLsizei n, GLuint *textures);
GLAPI void APIENTRY glGetBooleanv (GLenum pname, GLboolean *params);
GLAPI void APIENTRY glGetBufferParameterivARB (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetBufferPointervARB (GLenum target, GLenum pname, GLvoid* *params);
GLAPI void APIENTRY glGetBufferSubDataARB (GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid *data);
GLAPI void APIENTRY glGetClipPlane (GLenum plane, GLdouble *equation);
GLAPI void APIENTRY glGetColorTable (GLenum target, GLenum format, GLenum type, GLvoid *table);
GLAPI void APIENTRY glGetColorTableEXT (GLenum target, GLenum format, GLenum type, GLvoid *table);
GLAPI void APIENTRY glGetColorTableParameterfv (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetColorTableParameterfvEXT (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetColorTableParameteriv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetColorTableParameterivEXT (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetCombinerInputParameterfvNV (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetCombinerInputParameterivNV (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetCombinerOutputParameterfvNV (GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetCombinerOutputParameterivNV (GLenum stage, GLenum portion, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetCombinerStageParameterfvNV (GLenum stage, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetCompressedTexImage (GLenum target, GLint lod, GLvoid *img);
GLAPI void APIENTRY glGetCompressedTexImageARB (GLenum target, GLint lod, GLvoid *img);
GLAPI void APIENTRY glGetConvolutionFilter (GLenum target, GLenum format, GLenum type, GLvoid *image);
GLAPI void APIENTRY glGetConvolutionParameterfv (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetConvolutionParameteriv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetDoublev (GLenum pname, GLdouble *params);
GLAPI GLenum APIENTRY glGetError (void);
GLAPI void APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetFinalCombinerInputParameterfvNV (GLenum variable, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetFinalCombinerInputParameterivNV (GLenum variable, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetFloatv (GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetHistogram (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
GLAPI void APIENTRY glGetHistogramParameterfv (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetHistogramParameteriv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetIntegerv (GLenum pname, GLint *params);
GLAPI void APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetLightiv (GLenum light, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetMapdv (GLenum target, GLenum query, GLdouble *v);
GLAPI void APIENTRY glGetMapfv (GLenum target, GLenum query, GLfloat *v);
GLAPI void APIENTRY glGetMapiv (GLenum target, GLenum query, GLint *v);
GLAPI void APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetMaterialiv (GLenum face, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetMinmax (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
GLAPI void APIENTRY glGetMinmaxParameterfv (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetMinmaxParameteriv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetOcclusionQueryivNV (GLuint id, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetOcclusionQueryuivNV (GLuint id, GLenum pname, GLuint *params);
GLAPI void APIENTRY glGetPixelMapfv (GLenum map, GLfloat *values);
GLAPI void APIENTRY glGetPixelMapuiv (GLenum map, GLuint *values);
GLAPI void APIENTRY glGetPixelMapusv (GLenum map, GLushort *values);
GLAPI void APIENTRY glGetPointerv (GLenum pname, GLvoid* *params);
GLAPI void APIENTRY glGetPointervEXT (GLenum pname, GLvoid* *params);
GLAPI void APIENTRY glGetPolygonStipple (GLubyte *mask);
GLAPI void APIENTRY glGetProgramEnvParameterdvARB (GLenum target, GLuint index, GLdouble *params);
GLAPI void APIENTRY glGetProgramEnvParameterfvARB (GLenum target, GLuint index, GLfloat *params);
GLAPI void APIENTRY glGetProgramLocalParameterdvARB (GLenum target, GLuint index, GLdouble *params);
GLAPI void APIENTRY glGetProgramLocalParameterfvARB (GLenum target, GLuint index, GLfloat *params);
GLAPI void APIENTRY glGetProgramNamedParameterdvNV (GLuint id, GLsizei len, const GLubyte *name, GLdouble *params);
GLAPI void APIENTRY glGetProgramNamedParameterfvNV (GLuint id, GLsizei len, const GLubyte *name, GLfloat *params);
GLAPI void APIENTRY glGetProgramParameterdvNV (GLenum target, GLuint index, GLenum pname, GLdouble *params);
GLAPI void APIENTRY glGetProgramParameterfvNV (GLenum target, GLuint index, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetProgramStringARB (GLenum target, GLenum pname, GLvoid *string);
GLAPI void APIENTRY glGetProgramStringNV (GLuint id, GLenum pname, GLubyte *program);
GLAPI void APIENTRY glGetProgramivARB (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetProgramivNV (GLuint id, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetSeparableFilter (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
GLAPI const GLubyte * APIENTRY glGetString (GLenum name);
GLAPI void APIENTRY glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetTexGendv (GLenum coord, GLenum pname, GLdouble *params);
GLAPI void APIENTRY glGetTexGenfv (GLenum coord, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetTexGeniv (GLenum coord, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
GLAPI void APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetTrackMatrixivNV (GLenum target, GLuint address, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetVertexAttribPointervARB (GLuint index, GLenum pname, GLvoid* *pointer);
GLAPI void APIENTRY glGetVertexAttribPointervNV (GLuint index, GLenum pname, GLvoid* *pointer);
GLAPI void APIENTRY glGetVertexAttribdvARB (GLuint index, GLenum pname, GLdouble *params);
GLAPI void APIENTRY glGetVertexAttribdvNV (GLuint index, GLenum pname, GLdouble *params);
GLAPI void APIENTRY glGetVertexAttribfvARB (GLuint index, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetVertexAttribfvNV (GLuint index, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetVertexAttribivARB (GLuint index, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetVertexAttribivNV (GLuint index, GLenum pname, GLint *params);
GLAPI void APIENTRY glHint (GLenum target, GLenum mode);
GLAPI void APIENTRY glHistogram (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
GLAPI void APIENTRY glIndexMask (GLuint mask);
GLAPI void APIENTRY glIndexPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glIndexPointerEXT (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
GLAPI void APIENTRY glIndexd (GLdouble c);
GLAPI void APIENTRY glIndexdv (const GLdouble *c);
GLAPI void APIENTRY glIndexf (GLfloat c);
GLAPI void APIENTRY glIndexfv (const GLfloat *c);
GLAPI void APIENTRY glIndexi (GLint c);
GLAPI void APIENTRY glIndexiv (const GLint *c);
GLAPI void APIENTRY glIndexs (GLshort c);
GLAPI void APIENTRY glIndexsv (const GLshort *c);
GLAPI void APIENTRY glIndexub (GLubyte c);
GLAPI void APIENTRY glIndexubv (const GLubyte *c);
GLAPI void APIENTRY glInitNames (void);
GLAPI void APIENTRY glInterleavedArrays (GLenum format, GLsizei stride, const GLvoid *pointer);
GLboolean glIsBufferARB (GLuint buffer);
GLboolean glIsEnabled (GLenum cap);
GLboolean glIsFenceNV (GLuint fence);
GLboolean glIsList (GLuint list);
GLboolean glIsOcclusionQueryNV (GLuint id);
GLboolean glIsProgramARB (GLuint program);
GLboolean glIsProgramNV (GLuint id);
GLboolean glIsTexture (GLuint texture);
GLboolean glIsTextureEXT (GLuint texture);
GLAPI void APIENTRY glLightModelf (GLenum pname, GLfloat param);
GLAPI void APIENTRY glLightModelfv (GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glLightModeli (GLenum pname, GLint param);
GLAPI void APIENTRY glLightModeliv (GLenum pname, const GLint *params);
GLAPI void APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
GLAPI void APIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glLighti (GLenum light, GLenum pname, GLint param);
GLAPI void APIENTRY glLightiv (GLenum light, GLenum pname, const GLint *params);
GLAPI void APIENTRY glLineStipple (GLint factor, GLushort pattern);
GLAPI void APIENTRY glLineWidth (GLfloat width);
GLAPI void APIENTRY glListBase (GLuint base);
GLAPI void APIENTRY glLoadIdentity (void);
GLAPI void APIENTRY glLoadMatrixd (const GLdouble *m);
GLAPI void APIENTRY glLoadMatrixf (const GLfloat *m);
GLAPI void APIENTRY glLoadName (GLuint name);
GLAPI void APIENTRY glLoadProgramNV (GLenum target, GLuint id, GLsizei len, const GLubyte *program);
GLAPI void APIENTRY glLoadTransposeMatrixd (const GLdouble *m);
GLAPI void APIENTRY glLoadTransposeMatrixdARB (const GLdouble *m);
GLAPI void APIENTRY glLoadTransposeMatrixf (const GLfloat *m);
GLAPI void APIENTRY glLoadTransposeMatrixfARB (const GLfloat *m);
GLAPI void APIENTRY glLockArraysEXT (GLint first, GLsizei count);
GLAPI void APIENTRY glLogicOp (GLenum opcode);
GLAPI void APIENTRY glMap1d (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
GLAPI void APIENTRY glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
GLAPI void APIENTRY glMap2d (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
GLAPI void APIENTRY glMap2f (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
GLvoid* glMapBufferARB (GLenum target, GLenum access);
GLAPI void APIENTRY glMapGrid1d (GLint un, GLdouble u1, GLdouble u2);
GLAPI void APIENTRY glMapGrid1f (GLint un, GLfloat u1, GLfloat u2);
GLAPI void APIENTRY glMapGrid2d (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
GLAPI void APIENTRY glMapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
GLAPI void APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
GLAPI void APIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glMateriali (GLenum face, GLenum pname, GLint param);
GLAPI void APIENTRY glMaterialiv (GLenum face, GLenum pname, const GLint *params);
GLAPI void APIENTRY glMatrixMode (GLenum mode);
GLAPI void APIENTRY glMinmax (GLenum target, GLenum internalformat, GLboolean sink);
GLAPI void APIENTRY glMultMatrixd (const GLdouble *m);
GLAPI void APIENTRY glMultMatrixf (const GLfloat *m);
GLAPI void APIENTRY glMultTransposeMatrixd (const GLdouble *m);
GLAPI void APIENTRY glMultTransposeMatrixdARB (const GLdouble *m);
GLAPI void APIENTRY glMultTransposeMatrixf (const GLfloat *m);
GLAPI void APIENTRY glMultTransposeMatrixfARB (const GLfloat *m);
GLAPI void APIENTRY glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
GLAPI void APIENTRY glMultiDrawArraysEXT (GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
GLAPI void APIENTRY glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);
GLAPI void APIENTRY glMultiDrawElementsEXT (GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);
GLAPI void APIENTRY glMultiTexCoord1d (GLenum target, GLdouble s);
GLAPI void APIENTRY glMultiTexCoord1dARB (GLenum target, GLdouble s);
GLAPI void APIENTRY glMultiTexCoord1dSGIS (GLenum target, GLdouble s);
GLAPI void APIENTRY glMultiTexCoord1dv (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord1dvARB (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord1dvSGIS (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord1f (GLenum target, GLfloat s);
GLAPI void APIENTRY glMultiTexCoord1fARB (GLenum target, GLfloat s);
GLAPI void APIENTRY glMultiTexCoord1fSGIS (GLenum target, GLfloat s);
GLAPI void APIENTRY glMultiTexCoord1fv (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord1fvARB (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord1fvSGIS (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord1hNV (GLenum target, GLhalf s);
GLAPI void APIENTRY glMultiTexCoord1hvNV (GLenum target, const GLhalf *v);
GLAPI void APIENTRY glMultiTexCoord1i (GLenum target, GLint s);
GLAPI void APIENTRY glMultiTexCoord1iARB (GLenum target, GLint s);
GLAPI void APIENTRY glMultiTexCoord1iSGIS (GLenum target, GLint s);
GLAPI void APIENTRY glMultiTexCoord1iv (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord1ivARB (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord1ivSGIS (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord1s (GLenum target, GLshort s);
GLAPI void APIENTRY glMultiTexCoord1sARB (GLenum target, GLshort s);
GLAPI void APIENTRY glMultiTexCoord1sSGIS (GLenum target, GLshort s);
GLAPI void APIENTRY glMultiTexCoord1sv (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord1svARB (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord1svSGIS (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord2d (GLenum target, GLdouble s, GLdouble t);
GLAPI void APIENTRY glMultiTexCoord2dARB (GLenum target, GLdouble s, GLdouble t);
GLAPI void APIENTRY glMultiTexCoord2dSGIS (GLenum target, GLdouble s, GLdouble t);
GLAPI void APIENTRY glMultiTexCoord2dv (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord2dvARB (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord2dvSGIS (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord2f (GLenum target, GLfloat s, GLfloat t);
GLAPI void APIENTRY glMultiTexCoord2fARB (GLenum target, GLfloat s, GLfloat t);
GLAPI void APIENTRY glMultiTexCoord2fSGIS (GLenum target, GLfloat s, GLfloat t);
GLAPI void APIENTRY glMultiTexCoord2fv (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord2fvARB (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord2fvSGIS (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord2hNV (GLenum target, GLhalf s, GLhalf t);
GLAPI void APIENTRY glMultiTexCoord2hvNV (GLenum target, const GLhalf *v);
GLAPI void APIENTRY glMultiTexCoord2i (GLenum target, GLint s, GLint t);
GLAPI void APIENTRY glMultiTexCoord2iARB (GLenum target, GLint s, GLint t);
GLAPI void APIENTRY glMultiTexCoord2iSGIS (GLenum target, GLint s, GLint t);
GLAPI void APIENTRY glMultiTexCoord2iv (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord2ivARB (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord2ivSGIS (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord2s (GLenum target, GLshort s, GLshort t);
GLAPI void APIENTRY glMultiTexCoord2sARB (GLenum target, GLshort s, GLshort t);
GLAPI void APIENTRY glMultiTexCoord2sSGIS (GLenum target, GLshort s, GLshort t);
GLAPI void APIENTRY glMultiTexCoord2sv (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord2svARB (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord2svSGIS (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord3d (GLenum target, GLdouble s, GLdouble t, GLdouble r);
GLAPI void APIENTRY glMultiTexCoord3dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r);
GLAPI void APIENTRY glMultiTexCoord3dSGIS (GLenum target, GLdouble s, GLdouble t, GLdouble r);
GLAPI void APIENTRY glMultiTexCoord3dv (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord3dvARB (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord3dvSGIS (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord3f (GLenum target, GLfloat s, GLfloat t, GLfloat r);
GLAPI void APIENTRY glMultiTexCoord3fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r);
GLAPI void APIENTRY glMultiTexCoord3fSGIS (GLenum target, GLfloat s, GLfloat t, GLfloat r);
GLAPI void APIENTRY glMultiTexCoord3fv (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord3fvARB (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord3fvSGIS (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord3hNV (GLenum target, GLhalf s, GLhalf t, GLhalf r);
GLAPI void APIENTRY glMultiTexCoord3hvNV (GLenum target, const GLhalf *v);
GLAPI void APIENTRY glMultiTexCoord3i (GLenum target, GLint s, GLint t, GLint r);
GLAPI void APIENTRY glMultiTexCoord3iARB (GLenum target, GLint s, GLint t, GLint r);
GLAPI void APIENTRY glMultiTexCoord3iSGIS (GLenum target, GLint s, GLint t, GLint r);
GLAPI void APIENTRY glMultiTexCoord3iv (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord3ivARB (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord3ivSGIS (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord3s (GLenum target, GLshort s, GLshort t, GLshort r);
GLAPI void APIENTRY glMultiTexCoord3sARB (GLenum target, GLshort s, GLshort t, GLshort r);
GLAPI void APIENTRY glMultiTexCoord3sSGIS (GLenum target, GLshort s, GLshort t, GLshort r);
GLAPI void APIENTRY glMultiTexCoord3sv (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord3svARB (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord3svSGIS (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord4d (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
GLAPI void APIENTRY glMultiTexCoord4dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
GLAPI void APIENTRY glMultiTexCoord4dSGIS (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
GLAPI void APIENTRY glMultiTexCoord4dv (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord4dvARB (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord4dvSGIS (GLenum target, const GLdouble *v);
GLAPI void APIENTRY glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GLAPI void APIENTRY glMultiTexCoord4fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GLAPI void APIENTRY glMultiTexCoord4fSGIS (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GLAPI void APIENTRY glMultiTexCoord4fv (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord4fvARB (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord4fvSGIS (GLenum target, const GLfloat *v);
GLAPI void APIENTRY glMultiTexCoord4hNV (GLenum target, GLhalf s, GLhalf t, GLhalf r, GLhalf q);
GLAPI void APIENTRY glMultiTexCoord4hvNV (GLenum target, const GLhalf *v);
GLAPI void APIENTRY glMultiTexCoord4i (GLenum target, GLint s, GLint t, GLint r, GLint q);
GLAPI void APIENTRY glMultiTexCoord4iARB (GLenum target, GLint s, GLint t, GLint r, GLint q);
GLAPI void APIENTRY glMultiTexCoord4iSGIS (GLenum target, GLint s, GLint t, GLint r, GLint q);
GLAPI void APIENTRY glMultiTexCoord4iv (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord4ivARB (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord4ivSGIS (GLenum target, const GLint *v);
GLAPI void APIENTRY glMultiTexCoord4s (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
GLAPI void APIENTRY glMultiTexCoord4sARB (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
GLAPI void APIENTRY glMultiTexCoord4sSGIS (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
GLAPI void APIENTRY glMultiTexCoord4sv (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord4svARB (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoord4svSGIS (GLenum target, const GLshort *v);
GLAPI void APIENTRY glMultiTexCoordPointerSGIS (GLenum target, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glNewList (GLuint list, GLenum mode);
GLAPI void APIENTRY glNormal3b (GLbyte nx, GLbyte ny, GLbyte nz);
GLAPI void APIENTRY glNormal3bv (const GLbyte *v);
GLAPI void APIENTRY glNormal3d (GLdouble nx, GLdouble ny, GLdouble nz);
GLAPI void APIENTRY glNormal3dv (const GLdouble *v);
GLAPI void APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
GLAPI void APIENTRY glNormal3fv (const GLfloat *v);
GLAPI void APIENTRY glNormal3hNV (GLhalf nx, GLhalf ny, GLhalf nz);
GLAPI void APIENTRY glNormal3hvNV (const GLhalf *v);
GLAPI void APIENTRY glNormal3i (GLint nx, GLint ny, GLint nz);
GLAPI void APIENTRY glNormal3iv (const GLint *v);
GLAPI void APIENTRY glNormal3s (GLshort nx, GLshort ny, GLshort nz);
GLAPI void APIENTRY glNormal3sv (const GLshort *v);
GLAPI void APIENTRY glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glNormalPointerEXT (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
GLAPI void APIENTRY glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
GLAPI void APIENTRY glPassThrough (GLfloat token);
GLAPI void APIENTRY glPixelDataRangeNV (GLenum target, GLsizei size, const GLvoid *pointer);
GLAPI void APIENTRY glPixelMapfv (GLenum map, GLint mapsize, const GLfloat *values);
GLAPI void APIENTRY glPixelMapuiv (GLenum map, GLint mapsize, const GLuint *values);
GLAPI void APIENTRY glPixelMapusv (GLenum map, GLint mapsize, const GLushort *values);
GLAPI void APIENTRY glPixelStoref (GLenum pname, GLfloat param);
GLAPI void APIENTRY glPixelStorei (GLenum pname, GLint param);
GLAPI void APIENTRY glPixelTransferf (GLenum pname, GLfloat param);
GLAPI void APIENTRY glPixelTransferi (GLenum pname, GLint param);
GLAPI void APIENTRY glPixelZoom (GLfloat xfactor, GLfloat yfactor);
GLAPI void APIENTRY glPointParameterf (GLenum pname, GLfloat param);
GLAPI void APIENTRY glPointParameterfARB (GLenum pname, GLfloat param);
GLAPI void APIENTRY glPointParameterfEXT (GLenum pname, GLfloat param);
GLAPI void APIENTRY glPointParameterfv (GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glPointParameterfvARB (GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glPointParameterfvEXT (GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glPointParameteri (GLenum pname, GLint param);
GLAPI void APIENTRY glPointParameteriNV (GLenum pname, GLint param);
GLAPI void APIENTRY glPointParameteriv (GLenum pname, const GLint *params);
GLAPI void APIENTRY glPointParameterivNV (GLenum pname, const GLint *params);
GLAPI void APIENTRY glPointSize (GLfloat size);
GLAPI void APIENTRY glPolygonMode (GLenum face, GLenum mode);
GLAPI void APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
GLAPI void APIENTRY glPolygonStipple (const GLubyte *mask);
GLAPI void APIENTRY glPopAttrib (void);
GLAPI void APIENTRY glPopClientAttrib (void);
GLAPI void APIENTRY glPopMatrix (void);
GLAPI void APIENTRY glPopName (void);
GLAPI void APIENTRY glPrimitiveRestartIndexNV (GLuint index);
GLAPI void APIENTRY glPrimitiveRestartNV (void);
GLAPI void APIENTRY glPrioritizeTextures (GLsizei n, const GLuint *textures, const GLclampf *priorities);
GLAPI void APIENTRY glPrioritizeTexturesEXT (GLsizei n, const GLuint *textures, const GLclampf *priorities);
GLAPI void APIENTRY glProgramEnvParameter4dARB (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glProgramEnvParameter4dvARB (GLenum target, GLuint index, const GLdouble *params);
GLAPI void APIENTRY glProgramEnvParameter4fARB (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glProgramEnvParameter4fvARB (GLenum target, GLuint index, const GLfloat *params);
GLAPI void APIENTRY glProgramLocalParameter4dARB (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glProgramLocalParameter4dvARB (GLenum target, GLuint index, const GLdouble *params);
GLAPI void APIENTRY glProgramLocalParameter4fARB (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glProgramLocalParameter4fvARB (GLenum target, GLuint index, const GLfloat *params);
GLAPI void APIENTRY glProgramNamedParameter4dNV (GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glProgramNamedParameter4dvNV (GLuint id, GLsizei len, const GLubyte *name, const GLdouble *v);
GLAPI void APIENTRY glProgramNamedParameter4fNV (GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glProgramNamedParameter4fvNV (GLuint id, GLsizei len, const GLubyte *name, const GLfloat *v);
GLAPI void APIENTRY glProgramParameter4dNV (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glProgramParameter4dvNV (GLenum target, GLuint index, const GLdouble *v);
GLAPI void APIENTRY glProgramParameter4fNV (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glProgramParameter4fvNV (GLenum target, GLuint index, const GLfloat *v);
GLAPI void APIENTRY glProgramParameters4dvNV (GLenum target, GLuint index, GLsizei count, const GLdouble *v);
GLAPI void APIENTRY glProgramParameters4fvNV (GLenum target, GLuint index, GLsizei count, const GLfloat *v);
GLAPI void APIENTRY glProgramStringARB (GLenum target, GLenum format, GLsizei len, const GLvoid *string);
GLAPI void APIENTRY glPushAttrib (GLbitfield mask);
GLAPI void APIENTRY glPushClientAttrib (GLbitfield mask);
GLAPI void APIENTRY glPushMatrix (void);
GLAPI void APIENTRY glPushName (GLuint name);
GLAPI void APIENTRY glRasterPos2d (GLdouble x, GLdouble y);
GLAPI void APIENTRY glRasterPos2dv (const GLdouble *v);
GLAPI void APIENTRY glRasterPos2f (GLfloat x, GLfloat y);
GLAPI void APIENTRY glRasterPos2fv (const GLfloat *v);
GLAPI void APIENTRY glRasterPos2i (GLint x, GLint y);
GLAPI void APIENTRY glRasterPos2iv (const GLint *v);
GLAPI void APIENTRY glRasterPos2s (GLshort x, GLshort y);
GLAPI void APIENTRY glRasterPos2sv (const GLshort *v);
GLAPI void APIENTRY glRasterPos3d (GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glRasterPos3dv (const GLdouble *v);
GLAPI void APIENTRY glRasterPos3f (GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glRasterPos3fv (const GLfloat *v);
GLAPI void APIENTRY glRasterPos3i (GLint x, GLint y, GLint z);
GLAPI void APIENTRY glRasterPos3iv (const GLint *v);
GLAPI void APIENTRY glRasterPos3s (GLshort x, GLshort y, GLshort z);
GLAPI void APIENTRY glRasterPos3sv (const GLshort *v);
GLAPI void APIENTRY glRasterPos4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glRasterPos4dv (const GLdouble *v);
GLAPI void APIENTRY glRasterPos4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glRasterPos4fv (const GLfloat *v);
GLAPI void APIENTRY glRasterPos4i (GLint x, GLint y, GLint z, GLint w);
GLAPI void APIENTRY glRasterPos4iv (const GLint *v);
GLAPI void APIENTRY glRasterPos4s (GLshort x, GLshort y, GLshort z, GLshort w);
GLAPI void APIENTRY glRasterPos4sv (const GLshort *v);
GLAPI void APIENTRY glReadBuffer (GLenum mode);
GLAPI void APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
GLAPI void APIENTRY glRectd (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
GLAPI void APIENTRY glRectdv (const GLdouble *v1, const GLdouble *v2);
GLAPI void APIENTRY glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
GLAPI void APIENTRY glRectfv (const GLfloat *v1, const GLfloat *v2);
GLAPI void APIENTRY glRecti (GLint x1, GLint y1, GLint x2, GLint y2);
GLAPI void APIENTRY glRectiv (const GLint *v1, const GLint *v2);
GLAPI void APIENTRY glRects (GLshort x1, GLshort y1, GLshort x2, GLshort y2);
GLAPI void APIENTRY glRectsv (const GLshort *v1, const GLshort *v2);
GLenum glReleaseFlushHold (GLuint id);
GLint glRenderMode (GLenum mode);
GLAPI void APIENTRY glRequestResidentProgramsNV (GLsizei n, const GLuint *programs);
GLAPI void APIENTRY glResetHistogram (GLenum target);
GLAPI void APIENTRY glResetMinmax (GLenum target);
GLAPI void APIENTRY glRotated (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glSampleCoverage (GLclampf value, GLboolean invert);
GLAPI void APIENTRY glSampleCoverageARB (GLclampf value, GLboolean invert);
GLAPI void APIENTRY glScaled (GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glSecondaryColor3b (GLbyte red, GLbyte green, GLbyte blue);
GLAPI void APIENTRY glSecondaryColor3bEXT (GLbyte red, GLbyte green, GLbyte blue);
GLAPI void APIENTRY glSecondaryColor3bv (const GLbyte *v);
GLAPI void APIENTRY glSecondaryColor3bvEXT (const GLbyte *v);
GLAPI void APIENTRY glSecondaryColor3d (GLdouble red, GLdouble green, GLdouble blue);
GLAPI void APIENTRY glSecondaryColor3dEXT (GLdouble red, GLdouble green, GLdouble blue);
GLAPI void APIENTRY glSecondaryColor3dv (const GLdouble *v);
GLAPI void APIENTRY glSecondaryColor3dvEXT (const GLdouble *v);
GLAPI void APIENTRY glSecondaryColor3f (GLfloat red, GLfloat green, GLfloat blue);
GLAPI void APIENTRY glSecondaryColor3fEXT (GLfloat red, GLfloat green, GLfloat blue);
GLAPI void APIENTRY glSecondaryColor3fv (const GLfloat *v);
GLAPI void APIENTRY glSecondaryColor3fvEXT (const GLfloat *v);
GLAPI void APIENTRY glSecondaryColor3hNV (GLhalf red, GLhalf green, GLhalf blue);
GLAPI void APIENTRY glSecondaryColor3hvNV (const GLhalf *v);
GLAPI void APIENTRY glSecondaryColor3i (GLint red, GLint green, GLint blue);
GLAPI void APIENTRY glSecondaryColor3iEXT (GLint red, GLint green, GLint blue);
GLAPI void APIENTRY glSecondaryColor3iv (const GLint *v);
GLAPI void APIENTRY glSecondaryColor3ivEXT (const GLint *v);
GLAPI void APIENTRY glSecondaryColor3s (GLshort red, GLshort green, GLshort blue);
GLAPI void APIENTRY glSecondaryColor3sEXT (GLshort red, GLshort green, GLshort blue);
GLAPI void APIENTRY glSecondaryColor3sv (const GLshort *v);
GLAPI void APIENTRY glSecondaryColor3svEXT (const GLshort *v);
GLAPI void APIENTRY glSecondaryColor3ub (GLubyte red, GLubyte green, GLubyte blue);
GLAPI void APIENTRY glSecondaryColor3ubEXT (GLubyte red, GLubyte green, GLubyte blue);
GLAPI void APIENTRY glSecondaryColor3ubv (const GLubyte *v);
GLAPI void APIENTRY glSecondaryColor3ubvEXT (const GLubyte *v);
GLAPI void APIENTRY glSecondaryColor3ui (GLuint red, GLuint green, GLuint blue);
GLAPI void APIENTRY glSecondaryColor3uiEXT (GLuint red, GLuint green, GLuint blue);
GLAPI void APIENTRY glSecondaryColor3uiv (const GLuint *v);
GLAPI void APIENTRY glSecondaryColor3uivEXT (const GLuint *v);
GLAPI void APIENTRY glSecondaryColor3us (GLushort red, GLushort green, GLushort blue);
GLAPI void APIENTRY glSecondaryColor3usEXT (GLushort red, GLushort green, GLushort blue);
GLAPI void APIENTRY glSecondaryColor3usv (const GLushort *v);
GLAPI void APIENTRY glSecondaryColor3usvEXT (const GLushort *v);
GLAPI void APIENTRY glSecondaryColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glSecondaryColorPointerEXT (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glSelectBuffer (GLsizei size, GLuint *buffer);
GLAPI void APIENTRY glSelectTextureCoordSetSGIS (GLenum target);
GLAPI void APIENTRY glSelectTextureSGIS (GLenum target);
GLAPI void APIENTRY glSeparableFilter2D (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
GLAPI void APIENTRY glSetFenceNV (GLuint fence, GLenum condition);
GLAPI void APIENTRY glSetWindowStereoModeNV (GLboolean displayMode);
GLAPI void APIENTRY glShadeModel (GLenum mode);
GLAPI void APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GLAPI void APIENTRY glStencilMask (GLuint mask);
GLAPI void APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GLAPI void APIENTRY glTbufferMask3DFX (GLuint mask);
GLboolean glTestFenceNV (GLuint fence);
GLAPI void APIENTRY glTexCoord1d (GLdouble s);
GLAPI void APIENTRY glTexCoord1dv (const GLdouble *v);
GLAPI void APIENTRY glTexCoord1f (GLfloat s);
GLAPI void APIENTRY glTexCoord1fv (const GLfloat *v);
GLAPI void APIENTRY glTexCoord1hNV (GLhalf s);
GLAPI void APIENTRY glTexCoord1hvNV (const GLhalf *v);
GLAPI void APIENTRY glTexCoord1i (GLint s);
GLAPI void APIENTRY glTexCoord1iv (const GLint *v);
GLAPI void APIENTRY glTexCoord1s (GLshort s);
GLAPI void APIENTRY glTexCoord1sv (const GLshort *v);
GLAPI void APIENTRY glTexCoord2d (GLdouble s, GLdouble t);
GLAPI void APIENTRY glTexCoord2dv (const GLdouble *v);
GLAPI void APIENTRY glTexCoord2f (GLfloat s, GLfloat t);
GLAPI void APIENTRY glTexCoord2fv (const GLfloat *v);
GLAPI void APIENTRY glTexCoord2hNV (GLhalf s, GLhalf t);
GLAPI void APIENTRY glTexCoord2hvNV (const GLhalf *v);
GLAPI void APIENTRY glTexCoord2i (GLint s, GLint t);
GLAPI void APIENTRY glTexCoord2iv (const GLint *v);
GLAPI void APIENTRY glTexCoord2s (GLshort s, GLshort t);
GLAPI void APIENTRY glTexCoord2sv (const GLshort *v);
GLAPI void APIENTRY glTexCoord3d (GLdouble s, GLdouble t, GLdouble r);
GLAPI void APIENTRY glTexCoord3dv (const GLdouble *v);
GLAPI void APIENTRY glTexCoord3f (GLfloat s, GLfloat t, GLfloat r);
GLAPI void APIENTRY glTexCoord3fv (const GLfloat *v);
GLAPI void APIENTRY glTexCoord3hNV (GLhalf s, GLhalf t, GLhalf r);
GLAPI void APIENTRY glTexCoord3hvNV (const GLhalf *v);
GLAPI void APIENTRY glTexCoord3i (GLint s, GLint t, GLint r);
GLAPI void APIENTRY glTexCoord3iv (const GLint *v);
GLAPI void APIENTRY glTexCoord3s (GLshort s, GLshort t, GLshort r);
GLAPI void APIENTRY glTexCoord3sv (const GLshort *v);
GLAPI void APIENTRY glTexCoord4d (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
GLAPI void APIENTRY glTexCoord4dv (const GLdouble *v);
GLAPI void APIENTRY glTexCoord4f (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GLAPI void APIENTRY glTexCoord4fv (const GLfloat *v);
GLAPI void APIENTRY glTexCoord4hNV (GLhalf s, GLhalf t, GLhalf r, GLhalf q);
GLAPI void APIENTRY glTexCoord4hvNV (const GLhalf *v);
GLAPI void APIENTRY glTexCoord4i (GLint s, GLint t, GLint r, GLint q);
GLAPI void APIENTRY glTexCoord4iv (const GLint *v);
GLAPI void APIENTRY glTexCoord4s (GLshort s, GLshort t, GLshort r, GLshort q);
GLAPI void APIENTRY glTexCoord4sv (const GLshort *v);
GLAPI void APIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glTexCoordPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
GLAPI void APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param);
GLAPI void APIENTRY glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param);
GLAPI void APIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params);
GLAPI void APIENTRY glTexGend (GLenum coord, GLenum pname, GLdouble param);
GLAPI void APIENTRY glTexGendv (GLenum coord, GLenum pname, const GLdouble *params);
GLAPI void APIENTRY glTexGenf (GLenum coord, GLenum pname, GLfloat param);
GLAPI void APIENTRY glTexGenfv (GLenum coord, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glTexGeni (GLenum coord, GLenum pname, GLint param);
GLAPI void APIENTRY glTexGeniv (GLenum coord, GLenum pname, const GLint *params);
GLAPI void APIENTRY glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTexImage3DEXT (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GLAPI void APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GLAPI void APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
GLAPI void APIENTRY glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTexSubImage3DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
GLAPI void APIENTRY glTextureColorMaskSGIS (GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GLAPI void APIENTRY glTrackMatrixNV (GLenum target, GLuint address, GLenum matrix, GLenum transform);
GLAPI void APIENTRY glTranslated (GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glUnlockArraysEXT (void);
GLboolean glUnmapBufferARB (GLenum target);
GLboolean glValidBackBufferHintAutodesk (GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glVertex2d (GLdouble x, GLdouble y);
GLAPI void APIENTRY glVertex2dv (const GLdouble *v);
GLAPI void APIENTRY glVertex2f (GLfloat x, GLfloat y);
GLAPI void APIENTRY glVertex2fv (const GLfloat *v);
GLAPI void APIENTRY glVertex2hNV (GLhalf x, GLhalf y);
GLAPI void APIENTRY glVertex2hvNV (const GLhalf *v);
GLAPI void APIENTRY glVertex2i (GLint x, GLint y);
GLAPI void APIENTRY glVertex2iv (const GLint *v);
GLAPI void APIENTRY glVertex2s (GLshort x, GLshort y);
GLAPI void APIENTRY glVertex2sv (const GLshort *v);
GLAPI void APIENTRY glVertex3d (GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glVertex3dv (const GLdouble *v);
GLAPI void APIENTRY glVertex3f (GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glVertex3fv (const GLfloat *v);
GLAPI void APIENTRY glVertex3hNV (GLhalf x, GLhalf y, GLhalf z);
GLAPI void APIENTRY glVertex3hvNV (const GLhalf *v);
GLAPI void APIENTRY glVertex3i (GLint x, GLint y, GLint z);
GLAPI void APIENTRY glVertex3iv (const GLint *v);
GLAPI void APIENTRY glVertex3s (GLshort x, GLshort y, GLshort z);
GLAPI void APIENTRY glVertex3sv (const GLshort *v);
GLAPI void APIENTRY glVertex4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glVertex4dv (const GLdouble *v);
GLAPI void APIENTRY glVertex4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glVertex4fv (const GLfloat *v);
GLAPI void APIENTRY glVertex4hNV (GLhalf x, GLhalf y, GLhalf z, GLhalf w);
GLAPI void APIENTRY glVertex4hvNV (const GLhalf *v);
GLAPI void APIENTRY glVertex4i (GLint x, GLint y, GLint z, GLint w);
GLAPI void APIENTRY glVertex4iv (const GLint *v);
GLAPI void APIENTRY glVertex4s (GLshort x, GLshort y, GLshort z, GLshort w);
GLAPI void APIENTRY glVertex4sv (const GLshort *v);
GLAPI void APIENTRY glVertexArrayRangeNV (GLsizei size, const GLvoid *pointer);
GLAPI void APIENTRY glVertexAttrib1dARB (GLuint index, GLdouble x);
GLAPI void APIENTRY glVertexAttrib1dNV (GLuint index, GLdouble x);
GLAPI void APIENTRY glVertexAttrib1dvARB (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib1dvNV (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib1fARB (GLuint index, GLfloat x);
GLAPI void APIENTRY glVertexAttrib1fNV (GLuint index, GLfloat x);
GLAPI void APIENTRY glVertexAttrib1fvARB (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib1fvNV (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib1hNV (GLuint index, GLhalf x);
GLAPI void APIENTRY glVertexAttrib1hvNV (GLuint index, const GLhalf *v);
GLAPI void APIENTRY glVertexAttrib1sARB (GLuint index, GLshort x);
GLAPI void APIENTRY glVertexAttrib1sNV (GLuint index, GLshort x);
GLAPI void APIENTRY glVertexAttrib1svARB (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib1svNV (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib2dARB (GLuint index, GLdouble x, GLdouble y);
GLAPI void APIENTRY glVertexAttrib2dNV (GLuint index, GLdouble x, GLdouble y);
GLAPI void APIENTRY glVertexAttrib2dvARB (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib2dvNV (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib2fARB (GLuint index, GLfloat x, GLfloat y);
GLAPI void APIENTRY glVertexAttrib2fNV (GLuint index, GLfloat x, GLfloat y);
GLAPI void APIENTRY glVertexAttrib2fvARB (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib2fvNV (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib2hNV (GLuint index, GLhalf x, GLhalf y);
GLAPI void APIENTRY glVertexAttrib2hvNV (GLuint index, const GLhalf *v);
GLAPI void APIENTRY glVertexAttrib2sARB (GLuint index, GLshort x, GLshort y);
GLAPI void APIENTRY glVertexAttrib2sNV (GLuint index, GLshort x, GLshort y);
GLAPI void APIENTRY glVertexAttrib2svARB (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib2svNV (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib3dARB (GLuint index, GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glVertexAttrib3dNV (GLuint index, GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glVertexAttrib3dvARB (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib3dvNV (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib3fARB (GLuint index, GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glVertexAttrib3fNV (GLuint index, GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glVertexAttrib3fvARB (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib3fvNV (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib3hNV (GLuint index, GLhalf x, GLhalf y, GLhalf z);
GLAPI void APIENTRY glVertexAttrib3hvNV (GLuint index, const GLhalf *v);
GLAPI void APIENTRY glVertexAttrib3sARB (GLuint index, GLshort x, GLshort y, GLshort z);
GLAPI void APIENTRY glVertexAttrib3sNV (GLuint index, GLshort x, GLshort y, GLshort z);
GLAPI void APIENTRY glVertexAttrib3svARB (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib3svNV (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib4NbvARB (GLuint index, const GLbyte *v);
GLAPI void APIENTRY glVertexAttrib4NivARB (GLuint index, const GLint *v);
GLAPI void APIENTRY glVertexAttrib4NsvARB (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib4NubARB (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
GLAPI void APIENTRY glVertexAttrib4NubvARB (GLuint index, const GLubyte *v);
GLAPI void APIENTRY glVertexAttrib4NuivARB (GLuint index, const GLuint *v);
GLAPI void APIENTRY glVertexAttrib4NusvARB (GLuint index, const GLushort *v);
GLAPI void APIENTRY glVertexAttrib4bvARB (GLuint index, const GLbyte *v);
GLAPI void APIENTRY glVertexAttrib4dARB (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glVertexAttrib4dNV (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void APIENTRY glVertexAttrib4dvARB (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib4dvNV (GLuint index, const GLdouble *v);
GLAPI void APIENTRY glVertexAttrib4fARB (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glVertexAttrib4fNV (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void APIENTRY glVertexAttrib4fvARB (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib4fvNV (GLuint index, const GLfloat *v);
GLAPI void APIENTRY glVertexAttrib4hNV (GLuint index, GLhalf x, GLhalf y, GLhalf z, GLhalf w);
GLAPI void APIENTRY glVertexAttrib4hvNV (GLuint index, const GLhalf *v);
GLAPI void APIENTRY glVertexAttrib4ivARB (GLuint index, const GLint *v);
GLAPI void APIENTRY glVertexAttrib4sARB (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
GLAPI void APIENTRY glVertexAttrib4sNV (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
GLAPI void APIENTRY glVertexAttrib4svARB (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib4svNV (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttrib4ubNV (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
GLAPI void APIENTRY glVertexAttrib4ubvARB (GLuint index, const GLubyte *v);
GLAPI void APIENTRY glVertexAttrib4ubvNV (GLuint index, const GLubyte *v);
GLAPI void APIENTRY glVertexAttrib4uivARB (GLuint index, const GLuint *v);
GLAPI void APIENTRY glVertexAttrib4usvARB (GLuint index, const GLushort *v);
GLAPI void APIENTRY glVertexAttribPointerARB (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glVertexAttribPointerNV (GLuint index, GLint fsize, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glVertexAttribs1dvNV (GLuint index, GLsizei count, const GLdouble *v);
GLAPI void APIENTRY glVertexAttribs1fvNV (GLuint index, GLsizei count, const GLfloat *v);
GLAPI void APIENTRY glVertexAttribs1hvNV (GLuint index, GLsizei count, const GLhalf *v);
GLAPI void APIENTRY glVertexAttribs1svNV (GLuint index, GLsizei count, const GLshort *v);
GLAPI void APIENTRY glVertexAttribs2dvNV (GLuint index, GLsizei count, const GLdouble *v);
GLAPI void APIENTRY glVertexAttribs2fvNV (GLuint index, GLsizei count, const GLfloat *v);
GLAPI void APIENTRY glVertexAttribs2hvNV (GLuint index, GLsizei count, const GLhalf *v);
GLAPI void APIENTRY glVertexAttribs2svNV (GLuint index, GLsizei count, const GLshort *v);
GLAPI void APIENTRY glVertexAttribs3dvNV (GLuint index, GLsizei count, const GLdouble *v);
GLAPI void APIENTRY glVertexAttribs3fvNV (GLuint index, GLsizei count, const GLfloat *v);
GLAPI void APIENTRY glVertexAttribs3hvNV (GLuint index, GLsizei count, const GLhalf *v);
GLAPI void APIENTRY glVertexAttribs3svNV (GLuint index, GLsizei count, const GLshort *v);
GLAPI void APIENTRY glVertexAttribs4dvNV (GLuint index, GLsizei count, const GLdouble *v);
GLAPI void APIENTRY glVertexAttribs4fvNV (GLuint index, GLsizei count, const GLfloat *v);
GLAPI void APIENTRY glVertexAttribs4hvNV (GLuint index, GLsizei count, const GLhalf *v);
GLAPI void APIENTRY glVertexAttribs4svNV (GLuint index, GLsizei count, const GLshort *v);
GLAPI void APIENTRY glVertexAttribs4ubvNV (GLuint index, GLsizei count, const GLubyte *v);
GLAPI void APIENTRY glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glVertexPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
GLAPI void APIENTRY glVertexWeightPointerEXT (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);
GLAPI void APIENTRY glVertexWeightfEXT (GLfloat weight);
GLAPI void APIENTRY glVertexWeightfvEXT (const GLfloat *weight);
GLAPI void APIENTRY glVertexWeighthNV (GLhalf weight);
GLAPI void APIENTRY glVertexWeighthvNV (const GLhalf *weight);
GLAPI void APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glWindowBackBufferHintAutodesk (void);
GLAPI void APIENTRY glWindowPos2d (GLdouble x, GLdouble y);
GLAPI void APIENTRY glWindowPos2dARB (GLdouble x, GLdouble y);
GLAPI void APIENTRY glWindowPos2dv (const GLdouble *p);
GLAPI void APIENTRY glWindowPos2dvARB (const GLdouble *p);
GLAPI void APIENTRY glWindowPos2f (GLfloat x, GLfloat y);
GLAPI void APIENTRY glWindowPos2fARB (GLfloat x, GLfloat y);
GLAPI void APIENTRY glWindowPos2fv (const GLfloat *p);
GLAPI void APIENTRY glWindowPos2fvARB (const GLfloat *p);
GLAPI void APIENTRY glWindowPos2i (GLint x, GLint y);
GLAPI void APIENTRY glWindowPos2iARB (GLint x, GLint y);
GLAPI void APIENTRY glWindowPos2iv (const GLint *p);
GLAPI void APIENTRY glWindowPos2ivARB (const GLint *p);
GLAPI void APIENTRY glWindowPos2s (GLshort x, GLshort y);
GLAPI void APIENTRY glWindowPos2sARB (GLshort x, GLshort y);
GLAPI void APIENTRY glWindowPos2sv (const GLshort *p);
GLAPI void APIENTRY glWindowPos2svARB (const GLshort *p);
GLAPI void APIENTRY glWindowPos3d (GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glWindowPos3dARB (GLdouble x, GLdouble y, GLdouble z);
GLAPI void APIENTRY glWindowPos3dv (const GLdouble *p);
GLAPI void APIENTRY glWindowPos3dvARB (const GLdouble *p);
GLAPI void APIENTRY glWindowPos3f (GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glWindowPos3fARB (GLfloat x, GLfloat y, GLfloat z);
GLAPI void APIENTRY glWindowPos3fv (const GLfloat *p);
GLAPI void APIENTRY glWindowPos3fvARB (const GLfloat *p);
GLAPI void APIENTRY glWindowPos3i (GLint x, GLint y, GLint z);
GLAPI void APIENTRY glWindowPos3iARB (GLint x, GLint y, GLint z);
GLAPI void APIENTRY glWindowPos3iv (const GLint *p);
GLAPI void APIENTRY glWindowPos3ivARB (const GLint *p);
GLAPI void APIENTRY glWindowPos3s (GLshort x, GLshort y, GLshort z);
GLAPI void APIENTRY glWindowPos3sARB (GLshort x, GLshort y, GLshort z);
GLAPI void APIENTRY glWindowPos3sv (const GLshort *p);
GLAPI void APIENTRY glWindowPos3svARB (const GLshort *p);


/* #ifdef __DEFINED_GLAPI */
/* # undef GLAPI */
/* # undef __DEFINED_GLAPI */
/* #endif */

#ifdef __cplusplus
}
#endif

#endif /* __gl_h_ */
