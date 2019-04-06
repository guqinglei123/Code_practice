#include "ErServer/ErServercClient.h"
#include <ros/ros.h>
ErServerClient::ErServerClient():
    mySocket(NULL),
    myPacketList(),
    myPacket(NULL),
    myBuf(NULL),
    myLength(0)
{

}
ErServerClient::~ErServerClient()

{

}


void ErServerClient::looponce(void)
{

}

bool ErServerClient::openTcpSockets(void)
{

   // 打开服务器的socket
   if (myTcpSocket.open(7777, ErSocket::TCP))
   {
     ROS_INFO("Opened the server port.%s","7777");
     return true;
   }

   else
   {
    ROS_INFO("Failed to open the server port");
     return false;
   }

  //myClientsMutex.unlock();
}

bool ErServerClient::acceptTcpSockets(void)
{

  ROS_INFO("waiting client connect1....");
  while (!(myTcpSocket.accept(&myAcceptingSocket) &&
   myAcceptingSocket.getFD() >= 0))
  {

  }
  mySocket=&myAcceptingSocket;
  ROS_INFO(" client connect success....");
  return true;
  //myClientsMutex.unlock();
}


void ErServerClient::sendPacket(ErNetPacket *packet)
{
 ErNetPacket *sendPacket;
 packet->finalizePacket();
//  trackPacketSent(packet, true);
  sendPacket = new ErNetPacket(packet->getLength() + 5);
  sendPacket->duplicatePacket(packet);
  myPacketList.push_back(sendPacket);
}

bool ErServerClient::sendData(void)
{
  int ret;
#ifdef test
  const char *strToSend="Start Send Data test";
  ret = mySocket->write(strToSend, strlen(strToSend)) == (int) strlen(strToSend);
#endif
  while (myPacketList.begin() != myPacketList.end() || myPacket != NULL)
  {
    if (myPacket == NULL)
    {
      //printf("!startedSending %g\n", start.mSecSince() / 1000.0);
      ROS_INFO("myPacket is NULL, ");
      myPacket = myPacketList.front();
      myPacketList.pop_front();
      myAlreadySent = 0;
      myBuf = myPacket->getBuf();
      myLength = myPacket->getLength();
    }
    ret = mySocket->write(&myBuf[myAlreadySent], myLength - myAlreadySent);
    if(ret > 0)
    {
        ROS_INFO("write Data %d",ret);
        // we sent some data, count it as a good send
        myAlreadySent += ret;
         if (myAlreadySent == myLength)
         {
         //printf("sent one %g\n", start.mSecSince() / 1000.0);
         delete myPacket;
         myPacket = NULL;
         continue;
         }
         else
         {

         }

    }
    else
    {

    }
  }
  ROS_INFO("finish Send Data");
     return true;
}

