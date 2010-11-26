SRCPATH=../../src


SOURCE= main.cpp renderer.cpp scene.cpp scenehandler.cpp sprite.cpp
SOURCE+= scene_maingame.cpp

DEPS= image.h linkedlist.h linkedlist.hpp point.h vector.h scene.h scenehandler.h sprite.h texture.h time.h vector.h
DEPS+= scene_maingame.h

REALSOURCE = $(addprefix $(SRCPATH)/, $(SOURCE))
REALDEPS = $(addprefix $(SRCPATH)/, $(DEPS))
