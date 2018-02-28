#-------------------------------------------------
#
# Project created by QtCreator 2018-02-24T17:12:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpacePirateTools
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    UI/fileexplorer.cpp \
    UI/mainwindow.cpp \
    UI/qsfmlcanvas.cpp \
    ProjectInfos/projectinfos.cpp \
    ProjectInfos/filelist.cpp \
    ProjectInfos/assettype.cpp \
    Events/Event.inl \
    ProjectInfos/configs.cpp

HEADERS += \
    UI/fileexplorer.h \
    UI/mainwindow.h \
    UI/qsfmlcanvas.h \
    ProjectInfos/projectinfos.h \
    ProjectInfos/filelist.h \
    ProjectInfos/assettype.h \
    Events/Event.h \
    Events/Args/openressourceevent.h \
    Events/Args/projectloadedevent.h \
    ProjectInfos/configs.h \
    Events/Args/clearevent.h \
    Events/Args/saveevent.h \
    UI/dock.h \
    Events/Args/renamedfileevent.h \
    Events/Args/removedfileevent.h

CONFIG += c++14

# SFML
DEFINES += SFML_STATIC
LIBS += -LC:/Users/Nicolas/Programation/c++/SFML/DW2_2.4_(Qt)/lib

CONFIG(release, debug|release): LIBS += -lsfml-graphics-s \
                                        -lsfml-window-s \
                                        -lsfml-audio-s \
                                        -lsfml-system-s \
                                        -lfreetype \
                                        -lgdi32 \
                                        #-lglew \
                                        -ljpeg \
                                        -lopengl32 \
                                        -lwinmm \
                                        -lopenal32 \
                                        -lflac \
                                        -lvorbisenc \
                                        -lvorbisfile \
                                        -lvorbis \
                                        -logg

CONFIG(debug, debug|release): LIBS +=   -lsfml-graphics-s-d \
                                        -lsfml-window-s-d \
                                        -lsfml-audio-s-d \
                                        -lsfml-system-s-d \
                                        -lfreetype \
                                        -lgdi32 \
                                        #-lglew \
                                        -ljpeg \
                                        -lopengl32 \
                                        -lwinmm \
                                        -lopenal32 \
                                        -lflac \
                                        -lvorbisenc \
                                        -lvorbisfile \
                                        -lvorbis \
                                        -logg

INCLUDEPATH += C:/Users/Nicolas/Programation/c++/SFML/DW2_2.4_(Qt)/include
DEPENDPATH += C:/Users/Nicolas/Programation/c++/SFML/DW2_2.4_(Qt)/include
