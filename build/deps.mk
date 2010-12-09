SRCPATH=../../src
ROOTPATH=../..


SOURCE= main.cpp renderer.cpp scene.cpp scenehandler.cpp sprite.cpp resources.cpp
SOURCE+= scene_maingame.cpp board.cpp block.cpp

SOURCE+= lodepng/lodepng.cpp

DEPS= image.h linkedlist.h linkedlist.hpp point.h vector.h scene.h scenehandler.h sprite.h texture.h time.h vector.h color.h resources.h labelmap.h labelmap.hpp grid.h grid.hpp constants.h
DEPS+= scene_maingame.h board.h block.h

DEPS+= lodepng/lodepng.h

REALSOURCE = $(addprefix $(SRCPATH)/, $(SOURCE))
REALDEPS = $(addprefix $(SRCPATH)/, $(DEPS))
