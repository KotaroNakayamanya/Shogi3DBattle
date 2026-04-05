#pragma once

class GameObjIdManager
{
public:
    static unsigned int GetId()
    {
        static unsigned int id = 0;
        return id++;
    }
};