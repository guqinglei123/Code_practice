#ifndef ERSERVERCCLIENT_H
#define ERSERVERCCLIENT_H
#include "ErServer/ErSocket.h"
#include "ErServer/ErLog.h"
#include <list>
#include "ErServer/ErNetPacket.h"
class ErServerClient
{
  public:
  ErServerClient();
  ~ErServerClient();
  void looponce(void);
  bool openTcpSockets(void);
  bool acceptTcpSockets(void);
  void sendPacket(ErNetPacket *packet);
  bool sendData(void);
  ErSocket myAcceptingSocket;
  ErSocket myTcpSocket;
  std::list<ErNetPacket *> myPacketList;
  ErNetPacket *myPacket;
  ErSocket *mySocket;
  int myAlreadySent;
  const char *myBuf;
  int myLength;
};




#endif // ERSERVERCCLIENT_H
