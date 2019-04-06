#include <ros/ros.h>
#include "ErServer/ErSocket.h"
#include "ErServer/ErLog.h"


/// We're always initialized in Linux
bool ErSocket::ourInitialized=true;

const char *ErSocket::toString(Type t)
{
  switch (t) {
  case TCP:
    return "TCP";
  case UDP:
    return "UDP";
  default:
    return "Unknown";
  }
  return "Unknown";

} 


ErSocket::ErSocket() :
  myType(Unknown),
  myError(NoErr),
  myErrorStr(),
  myDoClose(true),
  myFD(-1),
  myNonBlocking(false),
  mySin()
{
  internalInit();
}

/**
   Constructs the socket and connects it to the given host.
   @param host hostname of the server to connect to
   @param port port number of the server to connect to
   @param type protocol type to use
*/
ErSocket::ErSocket(const char *host, int port, Type type) :
  myType(type),
  myError(NoErr),
  myErrorStr(),
  myDoClose(true),
  myFD(-1),
  myNonBlocking(false),
  mySin()
{
  internalInit();
  connect(host, port, type);
}

ErSocket::ErSocket(int port, bool doClose, Type type) :
  myType(type),
  myError(NoErr),
  myErrorStr(),
  myDoClose(doClose),
  myFD(-1),
  myNonBlocking(false),
  mySin()
{
  internalInit();
  open(port, type);
}

ErSocket::~ErSocket()
{
  close();
}


void ErSocket::internalInit(void)
{
/*  myReadStringMutex.setLogName("ArMutex::myReadStringMutex");
  myWriteStringMutex.setLogName("ArMutex::myWriteStringMutex");
  myCloseFunctor = NULL;
  myStringAutoEcho = true;
  myStringEcho = false;
  myStringPosLast = 0;
  myStringPos = 0;
  myStringGotComplete = false;
  myStringBufEmpty[0] = '\0';
  myStringGotEscapeChars = false;
  myStringHaveEchoed = false;
  myLastStringReadTime.setToNow();
  myLogWriteStrings = false;
  sprintf(myRawIPString, "none");
  myIPString = "";
  myBadWrite = false;
  myBadRead = false;
  myStringIgnoreReturn = false;
  myStringWrongEndChars = false;
  myErrorTracking = false;
  myFakeWrites = false;
  resetTracking();*/
}


bool ErSocket::close(void)
{

  if (myFD == -1)
    return true;
  ErLog::log(ErLog::Verbose, "Closing socket");
/*  if (myCloseFunctor != NULL)
    myCloseFunctor->invoke();*/
  if (myDoClose && ::close(myFD))
  {
    myFD=-1;
    return(false);
  }
  else
  {
    myFD=-1;
    return(true);
  }
 
}
/**
   In Windows, the networking subsystem needs to be initialized and shutdown
   individyaly by each program. So when a program starts they will need to
   call the static function ErSocket::init() and call ErSocket::shutdown()
   when it exits. For programs that use Aria::init() and Aria::uninit()
   calling the ErSocket::init() and ErSocket::shutdown() is unnecessary. The
   Aria initialization functions take care of this. These functions do nothing
   in Linux.
*/
bool ErSocket::init()
{
    return(true);
}


/**
   In Windows, the networking subsystem needs to be initialized and shutdown
   individyaly by each program. So when a program starts they will need to
   call the static function ErSocket::init() and call ErSocket::shutdown()
   when it exits. For programs that use Aria::init() and Aria::uninit()
   calling the ErSocket::init() and ErSocket::shutdown() is unnecessary. The
   Aria initialization functions take care of this. These functions do nothing
   in Linux.
*/
void ErSocket::shutdown()
{
}
/**
获得地址信息，主机信息以及相关的格式转换
host 主机名
addr 地址信息
**/
//根据主机名返回对应于当前主机的IPV4的地址信息
bool ErSocket::hostAddr(const char *host, struct in_addr &addr)
{
  struct hostent *hp;
  if (!(hp=gethostbyname(host)))     
  {
    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::hostAddr: gethostbyname failed");
    memset(&addr, 0, sizeof(in_addr));
    return(false);
  }
  else
  {
    bcopy(hp->h_addr, &addr, hp->h_length);
    return(true);
  }
}
//根据地址返回对应于当前主机的主机名
bool ErSocket::addrHost(struct in_addr &addr, char *host)
{
  struct hostent *hp;

  hp=gethostbyaddr((char*)&addr.s_addr, sizeof(addr.s_addr), AF_INET);  
  if (hp)
    strcpy(host, hp->h_name);
  else
    strcpy(host, inet_ntoa(addr));   //？？？？

  return(true);
}
//得到本机的标准主机名
std::string ErSocket::getHostName()
{
  char localhost[maxHostNameLen()];

  if (gethostname(localhost, sizeof(localhost)) == 1)    
    return("");
  else
    return(localhost);
}
//得到192.168.0.1格式的IPV4的地址
void ErSocket::setRawIPString(void)
{
  unsigned char *bytes;
  bytes = (unsigned char *)inAddr();
  if (bytes != NULL)
    sprintf(myRawIPString, "%d.%d.%d.%d", 
	    bytes[0], bytes[1], bytes[2], bytes[3]);
  myIPString = myRawIPString;
}
//将主机字节序转换为16bit网络字节序
unsigned int ErSocket::hostToNetOrder(int i)
{
  return(htons(i));

}

/****************************************************************
设置socket的一些选项
****************************************************************/
//设置套接字选项，到有报文未发送套接字为关闭时的延迟时间的设置
bool ErSocket::setLinger(int time)
{
  struct linger lin;
  myError = NoErr;
  myErrorStr.clear();

  if (time)
  {
    lin.l_onoff=1;
    lin.l_linger=time;
  }
  else
  {
    lin.l_onoff=0;
    lin.l_linger=time;
  }

  if (setsockopt(myFD, SOL_SOCKET, SO_LINGER, &lin, sizeof(lin)) != 0)
  {
    myErrorStr="Failure to setsockopt LINGER";
    myError = NetFail;
    ErLog::logErrorFromOS(ErLog::Normal,
        "ErSocket::setLinger: setsockopt failed");
    return(false);
  }
  else
    return(true);
}
//设置套接字选项，如果*opt 非0 重用bind地址
bool ErSocket::setReuseAddress()
{
  int opt=1;
  myError = NoErr;
  myErrorStr.clear();
  if (setsockopt(myFD, SOL_SOCKET, SO_REUSEADDR,
		 (char*)&opt, sizeof(opt)) != 0)
  {
    myErrorStr="Failure to setsockopt REUSEADDR";
    myError = NetFail;
   ErLog::logErrorFromOS(ErLog::Normal,
        "ErSocket::setReuseAddress: setsockopt failed");
    return(false);
  }
  else
    return(true);
}
/****************************************************************
打开服务器的网络功能
port:客户端的端口
type:选择TCP/UDP发送
openOnIP:要打开的IP地址
****************************************************************/

bool ErSocket::open(int port, Type type, const char *openOnIP)
{
   
  int ret;
  char localhost[maxHostNameLen()];

  myError=NoErr;
  myErrorStr.clear();
  if ((type == TCP) && ((myFD=socket(AF_INET, SOCK_STREAM, 0)) < 0))
  {
    myErrorStr="Failure to make TCP socket";
    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::open: could not create tcp socket");
    return(false);
  }
  else if ((type == UDP) && ((myFD=socket(AF_INET, SOCK_DGRAM, 0)) < 0))
  {
    myErrorStr="Failure to make UDP socket";
    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::open: could not create udp socket");
    return(false);
  }
#ifdef debug
  ArUtil::setFileCloseOnExec(myFD);  //？？？
#endif
  setLinger(0);    
  setReuseAddress();  

  myType=type;

  /* MPL removed this since with what I Took out down below months ago 
  if (gethostname(localhost, sizeof(localhost)) == 1)
  {
    myErrorStr="Failure to locate localhost";
    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::open: gethostname failed");
    return(false);
  }
  */
  bzero(&mySin, sizeof(mySin));//对mySin清0
  /* MPL took this out since it was just overriding it with the
     INADDR_ANY anyways and it could cause slowdowns if a machine wasn't
     configured so lookups are quick
  if (!hostAddr(localhost, mySin.sin_addr) && 
      !hostAddr("localhost", mySin.sin_addr))
    return(false); */

  if (openOnIP != NULL)
  {
    
    if (!hostAddr(openOnIP, mySin.sin_addr))
    {
    ErLog::log(ErLog::Normal, "Couldn't find ip of %s to open on", openOnIP);
      myError = NameLookup;
      myErrorStr = "Name lookup failed";
      ::close(myFD);
      myFD = -1;
      return(false); 
    }
    else
    {
      //printf("Opening on %s\n", openOnIP);
    }
  }
  else
  {
    mySin.sin_addr.s_addr=htonl(INADDR_ANY);
  }

  setRawIPString();
  mySin.sin_family=AF_INET;
  mySin.sin_port=hostToNetOrder(port);

  if ((ret=bind(myFD, (struct sockaddr *)&mySin, sizeof(mySin))) < 0)
  {
    myError = NetFail;
    myErrorStr="Failure to bind socket to port ";
    sprintf(localhost, "%d", port);
    myErrorStr+=localhost;
    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::open: could not bind");
    ::close(myFD);
    myFD = -1;
    return(false);
  }

  if ((type == TCP) && (listen(myFD, 5) < 0))
  {
    myError = NetFail;
    myErrorStr="Failure to listen on socket";
    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::open: could not listen");
    ::close(myFD);
    myFD = -1;
    return(false);
  }

  #ifdef debug
  myLastStringReadTime.setToNow();  //？？？
#endif

  return(true);
}
/****************************************************************
接受客户端的连接
****************************************************************/

bool ErSocket::accept(ErSocket *sock)
{
  socklen_t len;
  //unsigned char *bytes;
  
  myError = NoErr;
  myErrorStr.clear();

  len=sizeof(struct sockaddr_in);
  sock->myFD=::accept(myFD, (struct sockaddr*)&(sock->mySin), &len);
  sock->myType=myType;
  sock->setRawIPString();
  /*
  bytes = (unsigned char *)sock->inAddr();
  sprintf(sock->myIPString, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], 
	
  bytes[3]);
  */
  if ((sock->myFD < 0 && !myNonBlocking) || 
      (sock->myFD < 0 && errno != EWOULDBLOCK && myNonBlocking))
  {
    myErrorStr="Failed to accept on socket";
    myError = ConRefused;
    ErLog::logErrorFromOS(ErLog::Terse,
      "ErSocket::accept: accept failed");
    return(false);
  }//？？？？

  return(true);
}
/****************************************************************
数据传输
****************************************************************/
int ErSocket::write(const void *buff, size_t len)
{
  // this is for when we're faking ArNetworking commands over the text server
  if (myFakeWrites)
    return len;

  if (myFD < 0)
  {
    ErLog::log(ErLog::Terse, "ErSocket::write: called after socket closed");
    return 0;
  }

  struct timeval tval;
  fd_set fdSet;
  tval.tv_sec = 0;
  tval.tv_usec = 0;
  FD_ZERO(&fdSet);
  FD_SET(myFD, &fdSet);


  if (select(myFD + 1, NULL, &fdSet, NULL, &tval) <= 0)

    return 0;

  int ret;

  ret = ::write(myFD, (char*)buff, len);


  if (ret > 0)
  {
    mySends++;
    myBytesSent += ret;
  }
  if (myErrorTracking && ret < 0)
  {
    if (myNonBlocking)
    {
      if (errno != EAGAIN)
    myBadWrite = true;

    }
    else
      myBadWrite = true;
  }
  return ret;
}

int ErSocket::read(void *buff, size_t len, unsigned int msWait)
{
  if (myFD < 0)
  {
    ErLog::log(ErLog::Terse, "ErSocket::read: called after socket closed");
    return 0;
  }

  int ret;
  if (msWait != 0)
  {
    struct timeval tval;
    fd_set fdSet;
    tval.tv_sec = msWait / 1000;
    tval.tv_usec = (msWait % 1000) * 1000;
    FD_ZERO(&fdSet);
    FD_SET(myFD, &fdSet);
    if (select(myFD + 1, &fdSet, NULL, NULL, &tval) <= 0)
      return 0;

  }
  ret = ::recv(myFD, (char*)buff, len, 0);
  if (ret > 0)
  {
    myRecvs++;
    myBytesRecvd += ret;
  }
  if (myErrorTracking && ret < 0)
  {
    if (myNonBlocking)
    {
      if (errno != EAGAIN)
    myBadRead = true;

    }
    else
      myBadRead = true;
  }

  return ret;
}




#ifdef TEST
/// Normally, write() should be used instead. This is a wrapper around the sendto() system call.
 int Ersocket::sendTo(const void *msg, int len)
{
  int ret;
  ret = ::sendto(myFD, (char*)msg, len, 0, (struct sockaddr*)&mySin,
		  sizeof(mySin));
  if (ret > 0)
  {
    mySends++;
    myBytesSent += ret;
  }
  return ret;
}

/// Normally, write() should be used instead. This is a wrapper around the sendto() system call.
 int Ersocket::sendTo(const void *msg, int len,
			      struct sockaddr_in *sin)
{ 
  int ret;
  ret = ::sendto(myFD, (char*)msg, len, 0, (struct sockaddr*)sin,
		  sizeof(struct sockaddr_in));
  if (ret > 0)
  {
    mySends++;
    myBytesSent += ret;
  }
  return ret;
}


/// Normally, read() should be used instead. This is a wrapper around the recvfrom() system call.
 int Ersocket::recvFrom(void *msg, int len, sockaddr_in *sin)
{

  socklen_t i=sizeof(sockaddr_in);

  int ret;
  ret = ::recvfrom(myFD, (char*)msg, len, 0, (struct sockaddr*)sin, &i);
  if (ret > 0)
  {
    myRecvs++;
    myBytesRecvd += ret;
  }
  return ret;
}
 //将16bit网络字节序转换为主机字节序
 unsigned int ErSocket::netToHostOrder(int i)
 {
   return(ntohs(i));
 }
/****************************************************************

****************************************************************/

 bool Ersocket::setNonBlock()
{
  myError = NoErr;
  myErrorStr.clear();
  if (fcntl(myFD, F_SETFL, O_NONBLOCK) != 0)
  {
    myErrorStr="Failure to fcntl O_NONBLOCK";
    myError = NetFail;
//    ErLog::logErrorFromOS(ErLog::Normal,
//			  "Ersocket::setNonBlock: fcntl failed");
    return(false);
  }
  else
  {
    myNonBlocking = true;
    return(true);
  }
}

bool Ersocket::getSockName()
{
  socklen_t size;
  myError = NoErr;
  myErrorStr.clear();
  if (myFD < 0)
  {
    myErrorStr="Trying to get socket name on an unopened socket";
    myError = NetFail;
    printf(myErrorStr.c_str());
    return(false);
  }

  size=sizeof(mySin);
  if (getsockname(myFD, (struct sockaddr *)&mySin, &size) != 0)
  {
    myErrorStr="Error getting socket name";
    myError = NetFail;
//    ErLog::logErrorFromOS(ErLog::Normal,
//			  "Ersocket::getSockName: getSockName failed");
    return(false);
  }

  return(true);
}



bool Ersocket::create(Type type)
{
  myError = NoErr;
  myErrorStr.clear();

  if ((type == TCP) && ((myFD=socket(AF_INET, SOCK_STREAM, 0)) < 0))
  {
    myError = NetFail;
    myErrorStr="Failure to make TCP socket";
//    ErLog::logErrorFromOS(ErLog::Normal, "Ersocket::create: could not create tcp socket");
    return(false);
  }
  else if ((type == UDP) && ((myFD=socket(AF_INET, SOCK_DGRAM, 0)) < 0))
  {
    myError = NetFail;
    myErrorStr="Failure to make UDP socket";
//   ErLog::logErrorFromOS(ErLog::Normal, "Ersocket::create: could not create udp socket");
    return(false);
  }

  ArUtil::setFileCloseOnExec(myFD);  //？？？/

  myType=type;

  if (getSockName())
    return(true);
  else
    return(false);
}

/** @return false on error */
bool Ersocket::findValidPort(int startPort, const char *openOnIP)
{
  //char localhost[maxHostNameLen()];

  /*
  if (gethostname(localhost, sizeof(localhost)) == 1)
  {
    myErrorStr="Failure to locate localhost";
    ErLog::logErrorFromOS(ErLog::Normal, "Ersocket::findValidPort: gethostname failed");
    return(false);
  }
  */

  for (int i=0; i+startPort < 65000; ++i)
  {
    bzero(&mySin, sizeof(mySin));
    /*
    if (!hostAddr(localhost, mySin.sin_addr) && 
	!hostAddr("localhost", mySin.sin_addr))
      return(false);
    */
    setRawIPString();
    
    if (openOnIP != NULL)
    {
      
      if (!hostAddr(openOnIP, mySin.sin_addr))
      {
//	ErLog::log(ErLog::Normal, "Couldn't find ip of %s to open udp on", openOnIP);
//	return(false); 
      }
      else
      {
	//printf("Opening on %s\n", openOnIP);
      }
    }
    else
    {
      mySin.sin_addr.s_addr=htonl(INADDR_ANY);
    }
    
    mySin.sin_family=AF_INET;
    mySin.sin_port=hostToNetOrder(startPort+i);

    if (bind(myFD, (struct sockaddr *)&mySin, sizeof(mySin)) == 0)
      break;
  }

  return(true);
}


/****************************************************************
与服务器建立连接
host:本机的地址
port:客户端的端口
type:选择TCP/UDP发送
openOnIP:要打开的IP地址
****************************************************************/
bool ErSocket::connect(const char *host, int port, Type type,
		       const char *openOnIP)
{
  char localhost[maxHostNameLen()];
  myError=NoErr;
  myErrorStr.clear();
  if (!host)
  {
    if (gethostname(localhost, sizeof(localhost)) == 1)
    {
      myError=ConBadHost;
      myErrorStr="Failure to locate host '";
      myErrorStr+=localhost;
      myErrorStr+="'";
//      ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::connect: gethostname failed");
      return(false);
    }
    host=localhost;
  }

  bzero(&mySin, sizeof(mySin));  //是否需要修改
  // MPL taking out this next code line from the if since it makes
  // everything we can't resolve try to connect to localhost
  // &&  !hostAddr("localhost", mySin.sin_addr))

  char useHost[1024];
  int usePort;
  separateHost(host, port, useHost, sizeof(useHost), &usePort);  //???

  if (!hostAddr(useHost, mySin.sin_addr))
    return(false);
  setRawIPString();
  mySin.sin_family=AF_INET;
  mySin.sin_port=hostToNetOrder(usePort);

  if ((type == TCP) && ((myFD=socket(AF_INET, SOCK_STREAM, 0)) < 0))
  {
    myError=NetFail;
    myErrorStr="Failure to make TCP socket";
 //   ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::connect: could not make tcp socket");
    return(false);
  }
  else if ((type == UDP) && ((myFD=socket(AF_INET, SOCK_DGRAM, 0)) < 0))
  {
    myError=NetFail;
    myErrorStr="Failure to make UDP socket";
//    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::connect: could not make udp socket");
    return(false);
  }

  ArUtil::setFileCloseOnExec(myFD);   //？？？

  if (openOnIP != NULL)
  {
    struct sockaddr_in outSin;
    if (!hostAddr(openOnIP, outSin.sin_addr))
    {
      myError = NameLookup;
      myErrorStr = "Name lookup failed";
      ErLog::log(ErLog::Normal, "Couldn't find ip of %s to open on", openOnIP);
      return(false); 
    }
    outSin.sin_family=AF_INET;
    outSin.sin_port=hostToNetOrder(0);
    if (bind(myFD, (struct sockaddr *)&outSin, sizeof(outSin)) < 0)
    {
  //    ErLog::logErrorFromOS(ErLog::Normal, "ErSocket::connect: Failure to bind socket to port %d", 0);
      return(false);
    }
  }

  myType=type;

  if (::connect(myFD, (struct sockaddr *)&mySin,
		sizeof(struct sockaddr_in)) < 0)
  {
    myErrorStr="Failure to connect socket";
    switch (errno)
    {
    case ECONNREFUSED:
      myError=ConRefused;
      myErrorStr+="; Connection refused";
      break;
    case ENETUNREACH:
      myError=ConNoRoute;
      myErrorStr+="; No route to host";
      break;
    default:
      myError=NetFail;
      break;
    }
//    ErLog::logErrorFromOS(ErLog::Verbose, "ErSocket::connect: could not connect");

    ::close(myFD);
    myFD = -1;
    return(false);
  }

  return(true);
}
//

void ErSocket::separateHost(const char *rawHost, int rawPort, char *useHost, 
			    size_t useHostSize, int *port)
{
  if (useHost == NULL)
  {
//    ErLog::log(ErLog::Normal, "ErSocket: useHost was NULL");
    return;
  }
  if (port == NULL)
  {
 //   ErLog::log(ErLog::Normal, "ErSocket: port was NULL");
    return;
  }

  useHost[0] = '\0';

  if (rawHost == NULL || rawHost[0] == '\0')
  {
 //   ErLog::log(ErLog::Normal, "ErSocket: rawHost was NULL or empty");
    return;
  }
  
  ArArgumentBuilder separator(512, ':');
  separator.add(rawHost);

  if (separator.getArgc() <= 0)
  {
//    ErLog::log(ErLog::Normal, "ErSocket: rawHost was empty");
    return;
  }
  if (separator.getArgc() == 1)
  {
    snprintf(useHost, useHostSize, separator.getArg(0));
    *port = rawPort;
    return;
  }
  if (separator.getArgc() == 2)
  {
    if (separator.isArgInt(1))
    {
      snprintf(useHost, useHostSize, separator.getArg(0));
      *port = separator.getArgInt(1);
      return;
    }
    else
    {
//      ErLog::log(ErLog::Normal, "ErSocket: port given in hostname was not an integer it was %s", separator.getArg(1));
      return;
    }
  }

  // if we get down here there's too many args
//  ErLog::log(ErLog::Normal, "ErSocket: too many arguments in hostname %s", separator.getFullString());
  return;
}
#endif
bool ErSocket::connect(const char *host, int port, Type type,
           const char *openOnIP)
{

}




