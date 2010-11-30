# Copyright (C) 2009 Anders Andersson <finrist@gmail.com>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Special init commands for Linux
#
AC_DEFUN([AC_INIT_LINUX],
	 [])

# Special init commands for Windows
#
# E.g. LIBS=-lsystem32
#
AC_DEFUN([AC_INIT_WIN32],
         [CFLAGS="$CFLAGS -mno-cygwin"])
	
# Default init parameters
AC_INIT([smug],[0.0.1],[Anders Andersson finrist@gmail.com],[smug])

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([dist-bzip2])

# Guess the hos system (win32, etc)
AC_CANONICAL_HOST

# Check for C compiler
AC_PROG_CXX

# Check for library function
# LT_INIT

# Check the OS and run corresponding init script
case $host_os in
     linux*) AC_INIT_LINUX() ;;
     *) AC_INIT_WIN32() ;;
esac

# Check for Python
# AC_PYTHON_DEVEL([>= 2.5])

# Check for gl, glu and glext 3.0

# Check for GLEW on win32 otherwise check for gl 3.0
case $host_os in
     linux*) ;; #AC_GL_DEVEL([3.0]);;
     *) AC_GLEW_DEVEL([1.5.1]) ;;
esac

# Check for GLFW
AC_GLFW_DEVEL([2.6.0])

# Append Python and GLFW flags to default flags
LIBS="$LIBS $GLFW_LIBS $GLEW_LIBS $PYTHON_LIBS"
CPPFLAGS="$CFLAGS $GLFW_CFLAGS $GLEW_CFLAGS $PYTHON_CFLAGS -Wall"  #-Werror=implicit-function-declaration"
LDFLAGS="$LDFLAGS $GLFW_LDFLAGS $GLEW_LDFLAGS $PYTHON_LDFLAGS"

AM_PROG_CC_C_O

# Allow the user to disable use of asserts
#AC_ARG_ENABLE([asserts], 
#			  [AS_HELP_STRING([--disable-asserts], 
#		          [Disable the use of asserts])],
#			  [],
#			  [enable_asserts=yes])

#if test "x$enable_asserts" != "xyes"; then
#	AC_DEFINE([DISABLE_ASSERTS], [1], [Disable use of asserts])
#fi

# Specify output files
AC_CONFIG_FILES([
   Makefile
   doc/Makefile
   m4/Makefile
   src/Makefile
])

AC_OUTPUT
