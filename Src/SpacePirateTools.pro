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
    Object/objectdata.cpp \
    Object/objectproperty.cpp \
    Object/Value/objectvaluebase.cpp \
    UI/Object/objectinfos.cpp \
    UI/Object/propertywidget.cpp \
    UI/Object/addpropertydialog.cpp \
    Object/Value/objectvaluetransform.cpp \
    UI/Object/Value/transformvaluewidget.cpp \
    Object/Value/objectvaluebox2dcollider.cpp \
    UI/Object/Value/box2dcollidervaluewidget.cpp \
    Object/Value/objectvaluecirclecollider.cpp \
    UI/Object/Value/circlecollidervaluewidget.cpp \
    Object/Value/objectvalueconvexecollider.cpp \
    UI/Object/Value/convexcollidervaluewidget.cpp \
    Object/Value/objectvaluerigidbody.cpp \
    UI/Object/Value/rigidbodyvaluewidget.cpp \
    Object/Value/objectvalueasset.cpp \
    UI/Object/Value/assetvaluewidget.cpp \
    Object/Value/objectvaluespriterenderer.cpp \
    UI/Object/Value/spriterenderervaluewidget.cpp \
    Object/Value/objectvaluescript.cpp \
    UI/Object/Value/scriptvaluewidget.cpp \
    Object/Value/objectvaluefloat.cpp \
    UI/Object/Value/floatvaluewidget.cpp \
    Object/Value/objectvalueint.cpp \
    UI/Object/Value/intvaluewidget.cpp \
    Object/Value/objectvaluevector2f.cpp \
    UI/Object/Value/vector2fvaluewidget.cpp \
    Object/Value/objectvaluevector2i.cpp \
    UI/Object/Value/vector2ivaluewidget.cpp \
    Object/Value/objectvaluecolor.cpp \
    UI/Object/Value/colorvaluewidget.cpp \
    Object/Value/objectvaluetext.cpp \
    UI/Object/Value/textvaluewidget.cpp \
    UI/colliderlayerdialog.cpp \
    UI/verticallabel.cpp \
    Tilemap/tilemapdata.cpp \
    UI/Tilemap/tilemapinfos.cpp \
    UI/Tilemap/blockview.cpp \
    UI/Tilemap/centraltilemapwidget.cpp \
    UI/Tilemap/tilemaprenderer.cpp \
    UI/Tilemap/MapTool/basemaptool.cpp \
    UI/Tilemap/MapTool/singletilemaptool.cpp \
    UI/Tilemap/MapTool/randommaptool.cpp \
    UI/Tilemap/MapTool/fullbrushmaptool.cpp \
    UI/Tilemap/MapTool/horizontalbrushmaptool.cpp \
    UI/Tilemap/MapTool/paternmaptool.cpp \
    UI/Tilemap/MapTool/squarebrushmaptool.cpp \
    UI/Tilemap/MapTool/verticalbrushmaptool.cpp \
    UI/Tilemap/MapTool/copymaptool.cpp \
    UI/Tilemap/MapTool/pastemaptool.cpp \
    Scene/scenedata.cpp \
    Scene/scenelayer.cpp \
    Scene/scenenode.cpp \
    UI/Scene/scenelayersinfos.cpp \
    UI/Scene/scenelayerinfos.cpp \
    UI/Scene/scenenodeinfos.cpp \
    UI/Scene/addnodedialog.cpp \
    UI/Scene/selectionmodewidget.cpp \
    UI/Scene/centralscenewidget.cpp \
    UI/Scene/SceneTools/scenetooltransform.cpp \
    UI/Scene/SceneTools/scenetoolbase.cpp \
    UI/Scene/SceneTools/scenetoolscale.cpp \
    UI/Scene/SceneTools/scenetoolrotate.cpp \
    UI/Scene/NodeRenderer/valuerendererbase.cpp \
    UI/Scene/NodeRenderer/rendersystem.cpp \
    UI/Scene/NodeRenderer/valuerenderersprite.cpp \
    UI/Scene/NodeRenderer/valuerendererbox2dcollider.cpp \
    UI/Scene/NodeRenderer/valuerenderercirclecollider.cpp \
    UI/Scene/NodeRenderer/valuerendererconvexecollider.cpp \
    Object/Value/objectvaluecamera.cpp \
    UI/Object/Value/cameravaluewidget.cpp \
    UI/checkedcombobox.cpp \
    UI/Scene/NodeRenderer/valuerenderercamera.cpp \
    Object/Value/objectvaluetilemapcollider.cpp \
    UI/Object/Value/tilemapcollidervaluewidget.cpp \
    UI/Scene/NodeRenderer/valuerenderertilemapcollider.cpp \
    Object/Value/objectvaluetilemaprenderer.cpp \
    UI/Object/Value/tilemaprenderervaluewidget.cpp \
    UI/Scene/NodeRenderer/valuerenderertilemaprenderer.cpp

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
    enumiterators.h \
    Events/Args/editionevents.h \
    Object/objectdata.h \
    Object/objectproperty.h \
    Object/Value/objectvaluebase.h \
    UI/Object/objectinfos.h \
    UI/Object/propertywidget.h \
    UI/Object/addpropertydialog.h \
    Object/Value/objectvaluetransform.h \
    UI/Object/Value/transformvaluewidget.h \
    Object/Value/objectvaluebox2dcollider.h \
    UI/Object/Value/box2dcollidervaluewidget.h \
    Object/Value/objectvaluecirclecollider.h \
    UI/Object/Value/circlecollidervaluewidget.h \
    Object/Value/objectvalueconvexecollider.h \
    UI/Object/Value/convexcollidervaluewidget.h \
    Object/Value/objectvaluerigidbody.h \
    UI/Object/Value/rigidbodyvaluewidget.h \
    Object/Value/objectvalueasset.h \
    UI/Object/Value/assetvaluewidget.h \
    Object/Value/objectvaluespriterenderer.h \
    UI/Object/Value/spriterenderervaluewidget.h \
    Object/Value/objectvaluescript.h \
    UI/Object/Value/scriptvaluewidget.h \
    Object/Value/objectvaluefloat.h \
    UI/Object/Value/floatvaluewidget.h \
    Object/Value/objectvalueint.h \
    UI/Object/Value/intvaluewidget.h \
    Object/Value/objectvaluevector2f.h \
    UI/Object/Value/vector2fvaluewidget.h \
    Object/Value/objectvaluevector2i.h \
    UI/Object/Value/vector2ivaluewidget.h \
    Object/Value/objectvaluecolor.h \
    UI/Object/Value/colorvaluewidget.h \
    Object/Value/objectvaluetext.h \
    UI/Object/Value/textvaluewidget.h \
    UI/colliderlayerdialog.h \
    UI/verticallabel.h \
    Tilemap/tilemapdata.h \
    UI/Tilemap/tilemapinfos.h \
    UI/Tilemap/blockview.h \
    UI/Tilemap/centraltilemapwidget.h \
    Tilemap/tileinfos.h \
    UI/Tilemap/tilemaprenderer.h \
    UI/Tilemap/MapTool/basemaptool.h \
    UI/Tilemap/MapTool/singletilemaptool.h \
    UI/Tilemap/MapTool/randommaptool.h \
    UI/Tilemap/MapTool/fullbrushmaptool.h \
    UI/Tilemap/MapTool/horizontalbrushmaptool.h \
    UI/Tilemap/MapTool/paternmaptool.h \
    UI/Tilemap/MapTool/squarebrushmaptool.h \
    UI/Tilemap/MapTool/verticalbrushmaptool.h \
    UI/Tilemap/MapTool/copymaptool.h \
    UI/Tilemap/MapTool/pastemaptool.h \
    Scene/scenedata.h \
    Scene/scenelayer.h \
    Scene/scenenode.h \
    UI/Scene/scenelayersinfos.h \
    UI/Scene/scenelayerinfos.h \
    UI/Scene/scenenodeinfos.h \
    UI/Scene/addnodedialog.h \
    Events/Args/closeressourceevent.h \
    UI/Scene/selectionmodewidget.h \
    UI/Scene/centralscenewidget.h \
    UI/Scene/SceneTools/scenetooltransform.h \
    UI/Scene/SceneTools/scenetoolbase.h \
    UI/Scene/SceneTools/scenetoolscale.h \
    UI/Scene/SceneTools/scenetoolrotate.h \
    UI/Scene/NodeRenderer/valuerendererbase.h \
    UI/Scene/NodeRenderer/rendersystem.h \
    maperase.h \
    UI/Scene/NodeRenderer/valuerenderernone.h \
    UI/Scene/NodeRenderer/valuerenderersprite.h \
    UI/Scene/NodeRenderer/valuerendererbox2dcollider.h \
    UI/Scene/NodeRenderer/valuerenderercirclecollider.h \
    UI/Object/Value/fillcolliderlayercombobox.h \
    UI/Scene/NodeRenderer/valuerendererconvexecollider.h \
    Object/Value/objectvaluecamera.h \
    UI/Object/Value/cameravaluewidget.h \
    UI/checkedcombobox.h \
    UI/Scene/NodeRenderer/valuerenderercamera.h \
    Object/Value/objectvaluetilemapcollider.h \
    UI/Object/Value/tilemapcollidervaluewidget.h \
    UI/Scene/NodeRenderer/valuerenderertilemapcollider.h \
    Object/Value/objectvaluetilemaprenderer.h \
    UI/Object/Value/tilemaprenderervaluewidget.h \
    UI/Scene/NodeRenderer/valuerenderertilemaprenderer.h

CONFIG += c++14

# SFML
DEFINES += SFML_STATIC
LIBS += -LC:/Users/Nicolas/Programation/c++/SFML/DW2_2.4_(Qt)/lib
INCLUDEPATH += C:/Users/Nicolas/Programation/c++/SFML/DW2_2.4_(Qt)/include
DEPENDPATH += C:/Users/Nicolas/Programation/c++/SFML/DW2_2.4_(Qt)/include

LIBS += -L"C:/Users/Nicolas LAURENT/Desktop/Perso/SFML/SFML-2.4.2/lib"
INCLUDEPATH += "C:/Users/Nicolas LAURENT/Desktop/Perso/SFML/SFML-2.4.2/include"
DEPENDPATH += "C:/Users/Nicolas LAURENT/Desktop/Perso/SFML/SFML-2.4.2/include"

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

