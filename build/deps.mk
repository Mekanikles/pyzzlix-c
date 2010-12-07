SRCPATH=../../src


SOURCE= main.cpp renderer.cpp scene.cpp scenehandler.cpp sprite.cpp resources.cpp labelmap.cpp
SOURCE+= scene_maingame.cpp board.cpp

DEPS= image.h linkedlist.h linkedlist.hpp point.h vector.h scene.h scenehandler.h sprite.h texture.h time.h vector.h resources.h labelmap.h
DEPS+= scene_maingame.h board.h

REALSOURCE = $(addprefix $(SRCPATH)/, $(SOURCE))
REALDEPS = $(addprefix $(SRCPATH)/, $(DEPS))
