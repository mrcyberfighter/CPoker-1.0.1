#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([CPoker], [1.0.1], [mrcyberfighter@gmail.com])
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADERS([config.h])


# Checks for programs.
AC_PROG_CC_C_O
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MKDIR_P

HAVE_SDL2=no
HAVE_SDL2_IMAGE=no
HAVE_SDL2_TTF=no

prefix=/usr


# Checks for libraries.
AC_CHECK_LIB([SDL2],
             [SDL_CreateRenderer],
          
          
          
          
          
            HAVE_SDL2=yes,
         
          
             AC_MSG_ERROR(Cannot find SDL2 !!!
          
    ****************          CPoker required SDL2.        ***************
    Install the SDL2 library from your packet-manager or from the source.
  
    You most have the development files installed:
    The package is suffix with -dev or -devel and prefix with libsdl2.
  
    Then retry to build CPoker...
    **********************************************************************
                  , 1)
          
              )
            
AC_CHECK_LIB([SDL2_image],
             [IMG_Load],
          
          
          
          
          
            HAVE_SDL2_IMAGE=yes,
         
          
             AC_MSG_ERROR(Cannot find SDL2_image !!!
          
    ****************       CPoker required SDL2_image.     ***************
    Install the SDL2_image library from your packet-manager or from the
    source.
  
    You most have the development files installed:
    The package is suffix with -dev or -devel and prefix with
    libsdl2-image.
  
    Then retry to build CPoker...
    **********************************************************************
                  , 1)
          
              )
            
AC_CHECK_LIB([SDL2_ttf],
             [TTF_RenderText_Solid],
          
          
          
          
          
            HAVE_SDL2_TTF=yes,
         
          
             AC_MSG_ERROR(Cannot find SDL2_ttf !!!
          
    ****************       CPoker required SDL2_ttf.     ***************
    Install the SDL2_ttf library from your packet-manager or from the
    source.
  
    You most have the development files installed:
    The package is suffix with -dev or -devel and prefix with libsdl2-ttf.
  
    Then retry to build CPoker...
    **********************************************************************
                  , 1)
          
              )                            


# Checks for header files.
AC_CHECK_HEADERS([inttypes.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday memset])


#Warning about the libsdl2 package.
if test "x${HAVE_SDL2} = xyes" ; then
AC_MSG_NOTICE([sdl2 warning:

     ***********         WARNING ABOUT THE sdl2 PACKAGE          **********
   
     Make sure you get the development package from sdl2 installed the
     package is suffix with -dev or -devel and prefix with libsdl2.
     **********************************************************************
    ])
fi

#Warning about the gtksourceview-3.0 package.
if test "x${HAVE_SDL2_IMAGE} = xyes" ; then
AC_MSG_NOTICE([sdl2-image warning:

     ***********      WARNING ABOUT THE sdl2-image PACKAGE       **********
   
     Make sure you get the development package from sdl2-image installed
     the package is suffix with -dev or -devel and prefix with
     libsdl2-image.
     **********************************************************************
    ])
fi


#Warning about the libvte2_90 package.
if test "x${HAVE_SDL2_IMAGE} = xyes" ; then
AC_MSG_NOTICE([sdl2-ttf warning:

     *********         WARNING ABOUT THE sdl2-ttf PACKAGE         **********
   
     Make sure you get the development package from sdl2-ttf installed the
     Make sure you get the development package from sdl2-ttf installed the
     package is suffix with -dev or -devel and prefix with libsdl2-ttf.
     **********************************************************************
    ])
fi



AC_OUTPUT

echo "
  ************************ ${PACKAGE_STRING} **********************

  System check OK but take a look at the warnings upper.
 
  Package: ${PACKAGE_NAME}  
  Package dependencies: sdl2, sdl2-image, sdl2-ttf.

  Compiler: ${CC}
       
  Version: ${PACKAGE_VERSION}

  description: ${PACKAGE_NAME} an five-cards-draw poker game against the computer.

  Author: Brüggemann Eddie.
  contact: ${PACKAGE_BUGREPORT}

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}. "
