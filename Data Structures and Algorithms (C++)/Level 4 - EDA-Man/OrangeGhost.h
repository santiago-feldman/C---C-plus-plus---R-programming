/**
*There are 5 classes that inherit the class "Robot"
* 1 for each robot present in the game:
* Robot1: EDAMan
* Robot2: RedGhost
* Robot3: PinkGhost
* Robot4: OrangeGhost
* Robot5: CyanGhost
*/

#ifndef ORANGEGHOST_H
#define ORANGEGHOST_H

#include "Ghost.h"

class OrangeGhost : public Ghost
{
public:
    void start(GameModel* gameModel, MQTTClient *mqttClient);

private:
    void getPersecutionModeMapPosition();
    void getDispersionModeMapPosition();
    void restart();
};

#endif