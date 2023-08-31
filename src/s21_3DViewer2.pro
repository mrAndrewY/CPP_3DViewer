QT       += core gui opengl printsupport
include("QtGifImage/src/gifimage/qtgifimage.pri")

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

linux: LIBS += -lGLU
win32: LIBS += -lopengl32 -lglu32

SOURCES += \
    affins.cc \
    controller.cc \
    glwidget.cc \
    main.cc \
    model.cc \
    commands.cc \
    multipult.cc \
    settings.cc \
    view.cc

HEADERS += \
    affins.h \
    color.h \
    controller.h \
    glwidget.h \
    memento.h \
    model.h \
    commands.h \
    multipult.h \
    settings.h \
    view.h

FORMS += \
    view.ui

# Для Windows
win32: RC_ICONS += 3dv.ico

# Для MacOS
macx: ICON = 3dv.icns

# Для Linux
unix: RC_ICONS += 3dv.png

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
