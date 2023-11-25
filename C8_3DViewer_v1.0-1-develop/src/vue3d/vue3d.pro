QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui openglwidgets

CONFIG += c++17
CONFIG += warn_off

include(../libs/gifimage/qtgifimage.pri)
ICON = images.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../back_end/vue_affine.c \
    ../back_end/vue_analyseur.c \
    mainwindow.cpp \
    main.cpp \
    glwidget.cpp     


HEADERS += \
    glwidget.h \
    ../includes/vue_modele.h \
    mainwindow.h


FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
