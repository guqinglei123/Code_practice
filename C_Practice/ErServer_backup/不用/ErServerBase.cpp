#include "ErServerBase.h"

ErServerBase::ErServerBase()
{

}

ErServerBase::~ErServerBase()
{

}


/****************************************************************
   功能：打开/关闭给定端口的服务器，监听连接的客户端
   参数：
    port：服务器端口
    openOnIP：如果不为空，仅仅监听这个地址的网络接口
    tcpOnly：是否仅仅使用TCP
   返回：
    成功为1，失败为0
******************************************************************/
AREXPORT bool ArServerBase::open(unsigned int port, const char *openOnIP,
				 bool tcpOnly)
{
  myDataMutex.lock();  //？？？
  myTcpPort = port;
  myTcpOnly = tcpOnly;
  if (openOnIP != NULL)
    myOpenOnIP = openOnIP;
  else
    myOpenOnIP = "";


  if (myTcpSocket.open(myTcpPort, ArSocket::TCP, openOnIP))
  {
    // This can be taken out since the open does this now
    //myTcpSocket.setLinger(0);
    myTcpSocket.setNonBlock();   //？？？
  }
  else
  {
    myOpened = false;
    myDataMutex.unlock();       //？？？
    return false;
  }

  if (myTcpOnly)
  {
    if (openOnIP != NULL)
//      ArLog::log(ArLog::Normal, 
//		 "%sStarted on tcp port %d on ip %s.", 
//		 myLogPrefix.c_str(), myTcpPort, openOnIP);
    else
 //     ArLog::log(ArLog::Normal, "%sStarted on tcp port %d.",
//		 myLogPrefix.c_str(), myTcpPort);
    myOpened = true;
    myUdpPort = 0;
    myDataMutex.unlock();
    return true;
  }
  
  if (myUdpSocket.create(ArSocket::UDP) &&
      myUdpSocket.findValidPort(myTcpPort, openOnIP) &&
      myUdpSocket.setNonBlock())
  {
 // not possible on udp?   myUdpSocket.setLinger(0);
    myUdpPort = ArSocket::netToHostOrder(myUdpSocket.inPort());
    myUdpReceiver.setSocket(&myUdpSocket);
    if (openOnIP != NULL)
 /*     ArLog::log(ArLog::Normal, 
		 "%sStarted on tcp port %d and udp port %d on ip %s.", 
		 myLogPrefix.c_str(), myTcpPort, myUdpPort, openOnIP);*/
    else
  /*    ArLog::log(ArLog::Normal, "%sStarted on tcp port %d and udp port %d.", 
		 myLogPrefix.c_str(), myTcpPort, myUdpPort);*/
  
  }
  else
  {
    myOpened = false;
    myTcpSocket.close();
    myDataMutex.unlock();
    return false;
  }
  myOpened = true;
  myDataMutex.unlock();
  return true;
}

AREXPORT void ArServerBase::close(void)
{
  std::list<ArServerClient *>::iterator it;
  ArServerClient *client;

  myClientsMutex.lock();
  if (!myOpened)
  {
    myClientsMutex.unlock();
    return;
  }

  ArLog::log(ArLog::Normal, "%sServer shutting down.", 
	     myLogPrefix.c_str());
  myOpened = false;
  // now send off the client packets to shut down
  for (it = myClients.begin(); it != myClients.end(); ++it)
  {
    client = (*it);
    client->shutdown();
    printf("Sending shutdown\n");
  }

  ArUtil::sleep(10);

  while ((it = myClients.begin()) != myClients.end())
  {
    client = (*it);
    myClients.pop_front();
    delete client;
  }
  myTcpSocket.close();
  if (!myTcpOnly)
    myUdpSocket.close();
  myClientsMutex.unlock();
  
  /// MPL adding this since it looks like its leaked
  myDataMutex.lock();
  ArUtil::deleteSetPairs(myDataMap.begin(), myDataMap.end());
  myDataMap.clear();
  myDataMutex.unlock();
}