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
    ProjectInfos/configs.cpp \
    UI/Animation/centralanimationwidget.cpp \
    UI/Animation/animationsinfos.cpp \
    Animation/animationdata.cpp \
    UI/Animation/animationpreview.cpp \
    Animator/animatordata.cpp \
    Animator/animatorstate.cpp \
    Animator/animatortransition.cpp \
    UI/Animator/animatorinfos.cpp \
    UI/Animator/centralanimatorwidget.cpp \
    UI/imagewidget.cpp \
    UI/Tileset/singletileview.cpp \
    Tileset/tilecollider.cpp \
    UI/Tileset/tilesetinfos.cpp \
    Tileset/tilesetdata.cpp \
    Tileset/Brushs/brushbase.cpp \
    UI/flowlayout.cpp \
    UI/Tileset/brushcreatedialog.cpp \
    Tileset/Brushs/brushrandom.cpp \
    Tileset/Brushs/brushpatern.cpp \
    Tileset/Brushs/brushtiled.cpp \
    Tileset/Brushs/brushhorizontal.cpp \
    Tileset/Brushs/brushvertical.cpp \
    Tileset/Brushs/brushsquare.cpp \
    Tileset/Brushs/brushfull.cpp \
    UI/Tileset/BrushsWindow/brushwindowbase.cpp \
    UI/Tileset/centraltilesetwindow.cpp \
    UI/Tileset/BrushsWindow/brushwindowtiled.cpp \
    UI/Tileset/BrushsWindow/brushwindowpatern.cpp \
    UI/Tileset/BrushsWindow/brushwindowrandom.cpp \
    UI/Tileset/tileselectionwidget.cpp \
    UI/Tileset/tileselectiondialog.cpp \
    UI/Tileset/tilecolliderselectionwidget.cpp \
    UI/Tileset/tilecolliderselectiondialog.cpp \
    Scene/scenedata.cpp \
    Scene/Layers/layerbase.cpp \
    UI/Scene/sceneinfos.cpp \
    UI/Scene/newlayerdialog.cpp \
    Scene/Layers/tilesetlayer.cpp \
    Scene/Layers/objectslayer.cpp \
    UI/Scene/centralscenewindow.cpp \
    UI/Scene/layertoolholder.cpp \
    UI/Scene/LayerToolWindow/tilesetlayertoolwindow.cpp \
    UI/Scene/blockview.cpp \
    Scene/Tools/basetilesetscenetool.cpp

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
    Events/Args/removedfileevent.h \
    UI/Animation/centralanimationwidget.h \
    UI/Animation/animationsinfos.h \
    Animation/animationdata.h \
    UI/linewidget.h \
    Events/Args/addedfileevent.h \
    UI/Animation/animationpreview.h \
    Animator/animatordata.h \
    Animator/animatorstate.h \
    Animator/animatortransition.h \
    UI/Animator/animatorinfos.h \
    UI/Animator/centralanimatorwidget.h \
    vect2convert.h \
    UI/imagewidget.h \
    ressource.h \
    UI/Tileset/singletileview.h \
    Tileset/tileshape.h \
    Tileset/tilecollider.h \
    enumclasshash.h \
    UI/Tileset/tilesetinfos.h \
    Tileset/tilesetdata.h \
    Tileset/Brushs/brushbase.h \
    UI/flowlayout.h \
    UI/Tileset/brushcreatedialog.h \
    Tileset/Brushs/brushrandom.h \
    Tileset/Brushs/brushpatern.h \
    Tileset/Brushs/brushtiled.h \
    Tileset/Brushs/brushhorizontal.h \
    Tileset/Brushs/brushvertical.h \
    Tileset/Brushs/brushsquare.h \
    Tileset/Brushs/brushfull.h \
    UI/Tileset/BrushsWindow/brushwindowbase.h \
    UI/Tileset/centraltilesetwindow.h \
    UI/Tileset/BrushsWindow/brushwindowtiled.h \
    UI/Tileset/BrushsWindow/brushwindowpatern.h \
    UI/Tileset/BrushsWindow/brushwindowrandom.h \
    UI/Tileset/tileselectionwidget.h \
    UI/Tileset/tileselectiondialog.h \
    UI/Tileset/tilecolliderselectionwidget.h \
    UI/Tileset/tilecolliderselectiondialog.h \
    matrix.h \
    Scene/scenedata.h \
    Scene/Layers/layerbase.h \
    UI/Scene/sceneinfos.h \
    UI/Scene/newlayerdialog.h \
    enumiterators.h \
    Scene/Layers/tilesetlayer.h \
    Scene/Layers/objectslayer.h \
    UI/Scene/centralscenewindow.h \
    UI/Scene/layertoolholder.h \
    UI/Scene/LayerToolWindow/tilesetlayertoolwindow.h \
    UI/Scene/blockview.h \
    Scene/Tools/basescenetool.h \
    Scene/Tools/basetilesetscenetool.h

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
