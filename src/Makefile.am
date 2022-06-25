AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

bin_PROGRAMS = uinputdev

uinputdev_SOURCES = \
	uinputdev.c 

uinputdev_LDADD = \
	-lrt -lpthread \
	@LIBEVDEV_LIBS@ 

#		@GIO2_LIBS@

# C compiler options
uinputdev_CFLAGS = \
	-I$(top_srcdir)/include \
	@LIBEVDEV_CFLAGS@ \
	-D_GNU_SOURCE

#		@GIO2_CFLAGS@ 

# Linker options
uinputdev_LDFLAGS = 


# configure option 
#if ENABLE_USERDEBUG
#exsample_CFLAGS   += -D_USER_DEBUG_
#exsample_CXXFLAGS += -D_USER_DEBUG_
#endif
#
#if ENABLE_PRINTFDEBUG
#exsample_CFLAGS   += -D_PRINTF_DEBUG_
#exsample_CXXFLAGS += -D_PRINTF_DEBUG_
#endif

