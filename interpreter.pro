#-------------------------------------------------
#
# Project file
#
#-------------------------------------------------

QT          +=  core

QT          -=  gui

TARGET      =   interpreter
CONFIG      +=  console c++11
CONFIG      -=  app_bundle

TEMPLATE    =   app


SOURCES     +=  \
		src/main.cpp \
    src/variable.cpp \
    src/common.cpp \
    src/tests.cpp


HEADERS     +=  \
                include/common.h \
    include/variable.h \
    include/std_lib.h \
    include/traits.h \
    include/tests.h
