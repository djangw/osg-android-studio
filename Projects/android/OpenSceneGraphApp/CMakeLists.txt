cmake_minimum_required(VERSION 3.4.1)

include_directories(
    ${CMAKE_SOURCE_DIR}/External/OpenSceneGraph/include
    ${CMAKE_BINARY_DIR}/External/OpenSceneGraph/include
)

set(OPENSCENEGRAPH_NATIVE_SRC
    src/main/cpp/JNIMain.cpp
    src/main/cpp/OpenSceneGraphNative.cpp
)

add_library(openscenegraph-native SHARED ${OPENSCENEGRAPH_NATIVE_SRC})

target_link_libraries(openscenegraph-native
    png
    jpeg
    libtiff
    freetype
    libcurl
    osg
    osgAnimation
    osgDB
    osgFX
    osgGA
    osgManipulator
    osgParticle
    osgPresentation
    osgShadow
    osgSim
    osgTerrain
    osgText
    osgUI
    osgUtil
    osgViewer
    osgVolume
    osgWidget
    # osgDB plugins
    osgdb_osg
    osgdb_serializers_osg
    # NDK libraries
    log
    z
)
