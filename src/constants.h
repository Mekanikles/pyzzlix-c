#ifndef _CONSTANTS_H
#define _CONSTANTS_H


const int LAYER_EFFECTS = 4;
const int LAYER_GUI = 3;
const int LAYER_MAKER = 2;
const int LAYER_BLOCKS = 1;


const int VOLUME_STEPS = 10;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 13;

const int NUM_BLOCKS_FOR_LEVEL = 40;

const int MIN_BLOCKS_FOR_CIRCLE_SCORE = 5;

const int MAX_PAUSE_TIME_SEC = 5;

const int POINTS_PER_LEVEL_FOR_CIRCLE_SCORE = 10;
const int POINTS_PER_LEVEL_FOR_BLOCK_SCORE = 10;

const int PERCENTAGE_TIME_GIVEN_PER_BLOCK = 1/30.0;

const int PAUSE_TIME_PER_BLOCK = 0.25;

const int HOURGLASS_DEFAULT = 2000;

const int USEREVENT = 100;

const int EVENT_CIRCLE_FOUND = USEREVENT;
const int EVENT_GAME_OVER = USEREVENT+1;
const int EVENT_LEVEL_UP = USEREVENT+2;
const int EVENT_PRELOADED_PART = USEREVENT+3;
const int EVENT_TIMER_STATE_CHANGED = USEREVENT+4;


const int STATUS_NONE = 0;
const int STATUS_MOVING = 1;
const int STATUS_WEIGHTLESS = 2;
const int STATUS_IN_CIRCLE = 4;
const int STATUS_OFFSCREEN = 8;

const int DEFAULT_GRAVITY_DELAY = 5;



#endif
