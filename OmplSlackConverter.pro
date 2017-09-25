QT += core
QT -= gui

CONFIG += c++11

TARGET = OmplSlackConverter
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    iconverter.cpp \
    opmltoslackconverter.cpp \
    slacktoomplconverter.cpp

HEADERS += \
    iconverter.h \
    opmltoslackconverter.h \
    slacktoomplconverter.h
