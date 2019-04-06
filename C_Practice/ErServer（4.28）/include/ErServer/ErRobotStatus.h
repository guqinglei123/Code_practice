#ifndef ERROBOTSTATUS_H
#define ERROBOTSTATUS_H
#include "ErServer/ErLog.h"
#include "ErServer/ErNetPacket.h"
#include "ErServer/ErServercClient.h"
class RobotDataclass
  {
 //   ArPose pose;
 public:
    bool haveStateOfCharge; ///< Whether stateOfCharge is a valid value or not.
    bool haveVoltage; ///< Whether voltage is a valid value or not.
    double stateOfCharge;
    double voltage;
    double vel;
    double rotVel;
    double latVel;
    bool haveTemperature; ///< Whether temperature is a valid value or not.
    double temperature;
    double myX;
    double myY;
    double myTh;
    RobotDataclass();

  };
class ErRobotStatus{


public:
  void updateNumbers(ErServerClient *client,
                   ErNetPacket *packet =NULL);

};


#endif // ERROBOTSTATUS_H
