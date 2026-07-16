/**
*There are 5 classes that inherit the class "Robot"
* 1 for each robot present in the game:
* Robot1: EDAMan
* Robot2: RedGhost
* Robot3: PinkGhost
* Robot4: OrangeGhost
* Robot5: CyanGhost
*/

#ifndef PINKGHOST_H
#define PINKGHOST_H

#include "Ghost.h"

class PinkGhost : public Ghost
{
public:
    void start(GameModel* gameModel_, MQTTClient *mqttClient_);

protected:
    void getPersecutionModeMapPosition();
    void getDispersionModeMapPosition();
    void restart();
};

#endif