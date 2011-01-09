#include "keymap.h"

#include <vector>

using namespace std;

static vector<unsigned int> keyArray;

KeyMap* KeyMap::getInstance()
{
    static KeyMap instance;

    return &instance;
}
        
unsigned int KeyMap::getKey(unsigned int id)
{
    if (id > keyArray.size())
    {
        return KEY_UNDEFINED;
    }

    return keyArray[id];
}

void KeyMap::setKey(unsigned int id, unsigned int key)
{
    if (id >= keyArray.size())
    {
        keyArray.resize(id);
    }

    keyArray[id] = key;
}


