/**
*There are 5 classes that inherit the class "Robot"
* 1 for each robot present in the game:
* Robot1: EDAMan
* Robot2: RedGhost
* Robot3: PinkGhost
* Robot4: OrangeGhost
* Robot5: CyanGhost
*/

#ifndef REDGHOST_H
#define REDGHOST_H

#include "Ghost.h"

class RedGhost : public Ghost
{
public:
    void start(GameModel* gameModel, MQTTClient *mqttClient);

protected:
    void getPersecutionModeMapPosition();
    void getDispersionModeMapPosition();
    void restart();

};

#endif