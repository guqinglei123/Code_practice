#ifndef ERROBOTRECEIVETCP_H
#define ERROBOTRECEIVETCP_H
#include <list>
#include <ros/ros.h>
#include "ErServer/ErLog.h"
#include "ErServer/ErNetPacket.h"
class ErRobotReceiveTCP
{
public:
    ErRobotReceiveTCP();
    ~ErRobotReceiveTCP();
    bool readData();
    Ret readPacket(int msWait);




protected:
    enum Ret {
      RET_CONN_CLOSED, // the connection was closed (in a good manner)
      RET_CONN_ERROR, // the connection was has an error (so close it)
      RET_GOT_PACKET, // we got a good packet
      RET_BAD_PACKET, // we got a bad packet (checksum wrong)
      RET_FAILED_READ, // our read failed (no data)
      RET_TIMED_OUT}; // we were reading and timed out
    /// Reads in a single packet, returns NULL if not one
    enum State { STATE_SYNC1, STATE_SYNC2, STATE_LENGTH1,
             STATE_LENGTH2, STATE_ACQUIRE_DATA };

    enum {
      TOTAL_PACKET_LENGTH = ErNetPacket::MAX_LENGTH+ErNetPacket::HEADER_LENGTH+ErNetPacket::FOOTER_LENGTH
    };
    bool myQuiet;
    State myState;
     bool myQuiet;
     ErSocket *mySocket;
     ErNetPacket myPacket;


     char myReadBuff[TOTAL_PACKET_LENGTH];
     int myReadCount;
     int myReadLength;
     int myReadCommand;
     unsigned char mySync1;
     unsigned char mySync2;

}

#endif // ERROBOTRECEIVETCP_H
