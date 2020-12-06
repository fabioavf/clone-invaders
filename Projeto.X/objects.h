#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdbool.h>

struct Object {
    bool isAlive, projectileAlive, state;
    int x, y, projX, projY;
};

#endif