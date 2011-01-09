#ifndef _KEYMAP_H
#define _KEYMAP_H

const unsigned int KEY_UNDEFINED = 0;
const unsigned int KEY_RIGHT = 1;
const unsigned int KEY_LEFT = 2;
const unsigned int KEY_DOWN = 3;
const unsigned int KEY_UP = 4;
const unsigned int KEY_ROTATE_LEFT = 5;
const unsigned int KEY_ROTATE_RIGHT = 6;


class KeyMap
{
    public:   
        
        KeyMap()
        {}

        static KeyMap* getInstance();
        
        unsigned int getKey(unsigned int id);
        void setKey(unsigned int id, unsigned int key);
};


#endif
