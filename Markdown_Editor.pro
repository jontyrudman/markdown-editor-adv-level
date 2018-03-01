#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T11:45:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Markdown_Editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any featu"re of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    include/notebook.cpp \
    main.cpp \
    mainwindow.cpp \
    include/md-parser/autolink.c \
    include/md-parser/buffer.c \
    include/md-parser/markdown.c \
    include/md-parser/stack.c \
    include/md-parser/html.c \
    include/md-parser/sundown.c \
    include/md-parser/houdini_href_e.c \
    include/md-parser/houdini_html_e.c \
    notebookswitcher.cpp

HEADERS += \
    include/notebook.h \
    mainwindow.h \
    include/md-parser/autolink.h \
    include/md-parser/buffer.h \
    include/md-parser/html_blocks.h \
    include/md-parser/markdown.h \
    include/md-parser/stack.h \
    include/md-parser/html.h \
    include/md-parser/houdini.h \
    include/md-parser/html_blocks.h \
    notebookswitcher.h

FORMS += \
        mainwindow.ui \
    notebookswitcher.ui

INCLUDEPATH += \
        include \
        include/md-parser \
        /usr/include/glib-2.0 \
        /usr/lib/glib-2.0/include

LIBS += \
#        -L"include/peg-markdown" -lpeg-markdown \
        -L"/usr/lib/glib-2.0/include" -lglib-2.0
