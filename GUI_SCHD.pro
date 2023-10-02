#-----------------------------------------------------------------------------------------------------------------------------------
#
# PROJECT:            msmERP
# FILE:								userTransaction_IMM.pro
# SUBSYSTEM:          Project File Financial Module User Transations
# LANGUAGE:						C++
# TARGET OS:          LINUX
# LIBRARY DEPENDANCE:	None.
# NAMESPACE:          N/A
# AUTHOR:							Gavin Blakeman.
# LICENSE:            GPLv2
#
#                     Copyright 2023 Gavin Blakeman.
#
# OVERVIEW:						Project file for compiling the project
#
# HISTORY:            2023-07-19/GGB - File Created
#
#-----------------------------------------------------------------------------------------------------------------------------------

TARGET = GUI_SCHD

DESTDIR = ../../../engineeringShop/plugins/GUI

TEMPLATE = lib

QT += core
QT -= gui

CONFIG += cmdline
CONFIG += plugin no_plugin_name_prefix
CONFIG -= app_bundle
CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += -std=c++20
QMAKE_LFLAGS += -Wl,--version-script=$${PWD}/pluginUserTransaction.version

#OBJECTS_DIR = "objects"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  \
    "../../../engineeringShop" \
    "../../../GCL" \
    "../../../MCL" \
    "../../../PCL" \
    "../../../SCL" \
    "/usr/local/lib" \
    "../../../WtExtensions" \
    "../../../modules/module_SCHD" \

SOURCES += \
  source/GUI_SCHD.cpp \
  source/pages/pageJobDetails.cpp \
  source/pages/pageJobHistory.cpp \
  source/pages/pageScheduleJobs.cpp


HEADERS += \
  include/pages/GUI_Templates.h \
  include/pages/pageJobDetails.h \
  include/pages/pageJobHistory.h \
  include/pages/pageScheduleJobs.h



LIBS += -L../../../GCL -lGCL

DISTFILES += \
  pluginUserTransaction.version

