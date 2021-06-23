#ifndef BOT_H
#define BOT_H

#include "field.h"

class Bot
{
private:
    Field *field;
    int verDot[20][20] = {};
    int m_n;
    int m_mineNumber;
public:
    Bot(Field*);
    void Step();
};

#endif // BOT_H
