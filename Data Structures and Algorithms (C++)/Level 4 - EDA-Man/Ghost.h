#ifndef _GHOST_H
#define _GHOST_H

#include "Robot.h"

#define MAZE_WIDTH 28
#define MAZE_HEIGHT 36
#define MAZE (MAZE_WIDTH + MAZE_HEIGHT)


class Ghost : public Robot
{
public:
    void update(float deltaTime);
    int virtualImageIndex;
protected:
    virtual void getPersecutionModeMapPosition() = 0;
    virtual void getDispersionModeMapPosition() = 0;
    virtual void restart() = 0;
    void getBlueModeMapPosition();
    
    Vector2 objectiveMapPoint;

    void setTargetMapPosition();

    void move(void);
    void updateImage(void);

};

#endif