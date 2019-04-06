#ifndef ERROBOTSENDERTCP_H
#define ERROBOTSENDERTCP_H
#include <list>
#include <ros/ros.h>
#include "ErServer/ErLog.h"
#include "ErServer/ErNetPacket.h"


class RobotStatusclass
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
    RobotStatusclass();

  };

class ErRobotSenderTCP
{
public:
   ErRobotSenderTCP();
   ~ErRobotSenderTCP();
  void updateNumbers(ErNetPacket *packet =NULL);
  void sendPacket(ErNetPacket *packet);
  bool sendData(void);
 void updatemySocket(ErSocket *myAcceptingSocket);

  std::list<ErNetPacket *> myPacketList;
  ErNetPacket *myPacket;
  ErSocket *mySocket;
  int myAlreadySent;
  const char *myBuf;
  int myLength;
};


#endif // ERROBOTSENDERTCP_H
