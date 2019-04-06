
#include "ErServer/ErRobotStatus.h"

RobotDataclass::RobotDataclass():
haveStateOfCharge(false),
haveVoltage(false),
stateOfCharge(0.0),
voltage(0.0),
vel(12.0),
rotVel(10.0),
latVel(11.0),
haveTemperature(false),
temperature(12.3),
myX(8.0),
myY(4.0)
{

}
void ErRobotStatus::updateNumbers(ErServerClient *client,
                 ErNetPacket *packet)
{
  ErNetPacket sending;
  RobotDataclass RobotData;
  int th=50;
#ifdef debug
  th = ArMath::roundInt(ArMath::fixAngle(myRobot->getTh()));
  if (th == -180)
    th = 180;

  if (myRobot->haveStateOfCharge())
    sending.byte2ToBuf(ArMath::roundInt(myRobot->getStateOfCharge() * 10));
  else if (myRobot->getRealBatteryVoltage() > 0)
    sending.byte2ToBuf(ArMath::roundInt(
      myRobot->getRealBatteryVoltage() * 10));
  else
    sending.byte2ToBuf(ArMath::roundInt(
      myRobot->getBatteryVoltage() * 10));
#endif

  sending.byte4ToBuf((int)RobotData.myX);
  sending.byte4ToBuf((int)RobotData.myY);
  sending.byte2ToBuf(th);
  sending.byte2ToBuf((int)RobotData.vel);
  sending.byte2ToBuf((int)RobotData.rotVel);
  sending.byte2ToBuf((int)RobotData.latVel);
//  sending.byteToBuf((char)RobotData.haveTemperature);

  client->sendPacket(&sending);
}
