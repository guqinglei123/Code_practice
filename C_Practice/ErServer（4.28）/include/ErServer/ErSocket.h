/*
功能：
作者：
修改时间：
*/


#ifndef ErSOCKET_H
#define ErSOCKET_H
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>

#define MAXHOSTNAMELEN	64	/* max length of hostname */

/// socket communication wrapper
/**
   ArSocket is a layer which allows you to use the sockets networking
   interface in an operating system independent manner. All of the standard
   commonly used socket functions are implemented such as open(), close(),
   connect(), accept(), read(), write(), hostToNetOrder(), netToHostOrder().  ArSocket extends some of these functions to set useful options (see method documentation for details). It also provides additional useful functions like
   writeString(), readString, setCloseCallback(), and more.

   In Windows, the sockets subsystem needs to be initialized and shutdown
   by the program. So when a program starts it must call Aria::init() and
   call Aria::shutdown() when it exits. (Or, to only initialize the socket
   system, and not do any other global Aria initialization, use ArSocket::init()
   and ArSocket::shutdown().)

   Some calls set an error code on failure in addition to returning false. This value is available from getError().
   If getError() returns something other than NoErr, a text description of the error may be available from getErrorStr().  

   @sa @ref socketServerExample.cpp
   @sa @ref socketClientExample.cpp

    @ingroup UtilityClasses
*/


class ErSocket
{
public:

  enum Type {UDP, TCP, Unknown};
  enum Error {NoErr, NetFail, ConBadHost, ConNoRoute, ConRefused, NameLookup};

   /// Constructor. You must then use either connect() or open().
   ErSocket();

  /// Constructor which immediately connects to a server as a client
  /// @a host Hostname or IP address of remote server
  /// @a port Port number on server
  /// @a Which IP protocol to use, type ErSocket::TCP or ErSocket::UDP
   ErSocket(const char *host, int port, Type type);

  /// Constructor which immediately opens a port as a server
  /// @a port Port number to open. Use a value greater than 1024.
  /// @a doClose Automatically close the port when ErSocket is destroyed (recommend using true)
  /// @a type Which IP protocol to use, ErSocket::TCP or ErSocket::UDP
   ErSocket(int port, bool doClose, Type type);

  /// Destructor
  ~ErSocket();

  /// Initialize the OS sockets system, if neccesary
  static bool init();

  /// Shutdown the OS sockets system, if neccesary
  static void shutdown();

  static size_t maxHostNameLen() {return(MAXHOSTNAMELEN);}
  struct in_addr * inAddr() {return(&mySin.sin_addr);}

  static bool hostAddr(const char *host, struct in_addr &addr);

  /// Convert an address structure to a hostname string
  static bool addrHost(struct in_addr &addr, char *host);

  /// Get the localhost address
  static std::string getHostName();

  void setRawIPString(void);
  static unsigned int hostToNetOrder(int i);
  bool setLinger(int time);
  bool setReuseAddress();

  bool connect(const char *host, int port, Type type = TCP,
 const char *openOnIP = NULL);

  bool open(int port, Type type, const char *openOnIP= NULL);
  bool accept(ErSocket *sock);

  int write(const void *buff, size_t len);
  int read(void *buff, size_t len, unsigned int msWait = 0);
const std::string & getErrorStr() const {return(myErrorStr);}
  static const char *toString(Type t);

  bool close();
  void internalInit();
  int getFD() const {return(myFD);}


  Type myType;            //TCP/UDP 选择传输方式
  Error myError;          //错误类别
  std::string myErrorStr; //错误信息
  bool myDoClose;
  int myFD;               //返回的套接值描述符
  bool myNonBlocking;
  struct sockaddr_in mySin;//IPV4中的套接字地址

  std::string myIPString;
  char myRawIPString[128];//？？？

  static bool ourInitialized;

  long mySends;
  long myBytesSent;
  long myRecvs;
  long myBytesRecvd;

  bool myBadWrite;
  bool myBadRead;
  bool myErrorTracking;

  bool myFakeWrites;


};



#endif
