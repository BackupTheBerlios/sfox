CFLAGS=@SDL_CFLAGS@ @X_CFLAGS@ @FT2_CFLAGS@ @CFLAGS@
noinst_LIBRARIES=libengine.a
INCLUDES=-I$(top_srcdir)/src/starengine/math -I$(top_srcdir)/src/starengine/engine/opengl -I$(top_srcdir)/src/starengine/framework -I$(top_srcdir)/src/starengine/starutils
libengine_a_SOURCES=viewport.c camera.c vertexbuffer.c vertex.c object3d.c \
                    color.c material.c texture.c object_factory.c \
                    dds.c heightfield.c skybox.c fontgl.c \
                    scene.c plan.c frustum.c heightfieldinfo.c object2d.c \
                    line.c bbox.c utility.c starengine.c
