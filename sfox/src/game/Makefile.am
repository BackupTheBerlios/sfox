CFLAGS=@SDL_CFLAGS@ @X_CFLAGS@ @CFLAGS@ @FT2_CFLAGS@
LIBS=@SDL_LIBS@ @OPENGL_LIBS@ @X_LIBS@ @FT2_LIBS@ @LIBS@
INCLUDES=-I$(top_srcdir)/src/starengine/framework -I$(top_srcdir)/src/starengine/engine -I$(top_srcdir)/src/starengine/math -I$(top_srcdir)/src/starengine/engine/opengl

EXTRA_PROGRAMS = starmain starmain.exe
bin_PROGRAMS = @TARGETS@

starmain_SOURCES=starmain.c
starmain_LDADD=$(top_builddir)/src/starengine/framework/libframework.a $(top_builddir)/src/starengine/engine/libengine.a $(top_builddir)/src/starengine/math/libmath.a $(top_builddir)/src/starengine/starutils/libstarutils.a

#For win32 we want starmain.exe
starmain_exe_SOURCES=starmain.c
starmain_exe_LDADD=$(top_builddir)/src/starengine/framework/libframework.a $(top_builddir)/src/starengine/engine/libengine.a $(top_builddir)/src/starengine/math/libmath.a $(top_builddir)/src/starengine/starutils/libstarutils.a
