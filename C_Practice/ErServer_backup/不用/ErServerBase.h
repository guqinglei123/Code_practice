/*
功能：
作者：
修改时间：
*/
#ifndef NLSERVERBASE_H
#define NLSERVERBASE_H

/**
   Base server for all networking services.

   This class is the "base" server for network services. Start
   this server by calling open(), and then running the loop with run() or runAsync(),
   (or loopOnce() if it is absolutely neccesary to use your own loop; see the
   implementation of run()).
   You can then pass this object to the various "ArServerInfo", "ArServerHandler", and ArServerMode classes. 

   Data request callbacks are added to an ErServerBase object by calling
   addData().

   This class takes care of locking in its own function calls so you
   don't need to worry about locking and unlocking the class before
   you do things.

    The counterpart of this class for clients is ArClientBase.

   You can require user names and passwords for making connections to
   the server, so each user has a set of permissions for different
   command groups. To do this, load configuration from a userInfo file 
   with loadUserInfo().  You can log the
   user info (and what commands users have) with logUserInfo().  You can
   log the command groups with logCommandGroups() or
   logCommandGroupsToFile().  For a description of the file see
   ArServerUserInfo.  There is also an example in
   <code>ArNetworking/examples/serverDemo.userInfo</code>.

   In addition to the user and password requirement you can set a server "key"
   (a special string of text) required (in addition to user and password)
   to access the server with setServerKey(), though this is ONLY used if
   user and password information is requied (so that older clients can
   connect if there's no user and password information required).  

   The way that the passwords are transmitted across the network is this:
   Upon connection the server sends a randomly generated (for that
   connection) string of text to the client which we'll call the
   passwordKey.  The client then combines the serverKey (a string which must be
   known to connect to the server at all), the password, and the
   passwordKey (that string that is generated uniquely for each
   connection) and comes up with an md5 of that string and sends that
   md5 value across the line.  The server then compares the md5 from
   the client with the md5 generated with the correct information on
   the server... if they match the password is good, otherwise it
   rejects the connection.  This is NOT perfect security but should be
   much better then plaintext.  If you care about perfect security
   then use an ssh tunnel with something like PUTTY from the machine
   the client is on to the machine the server is on with an openssh
   server set up (this'll likely even work in windows with cygwin) and
   set up a firewall on the machine the server is on that disallows
   port the server port connection from outside and only allows ssh
   from outside (and get a book or three and read those).

   This class now handles identifiers for the ArServerClients... all
   server bases will let a client set a self identifier string, and a
   here goal... those may be used by any server.  Messages can be sent
   to just server clients that match that message (so that its easier
   to send messages to people who sent commands).  

   Master servers (the main connection server base on the central
   server) can also give each connection an id number (with
   identGetConnectionID).  Things that then connect to the other
   server bases on a master server (slave servers) should then set
   their ConnectionID (with identSetConnectionID) so that things can
   relate the different connections together.

   @sa ArServerSimpleOpener
   @sa ArClientBase
   @sa ArServerMode
**/

class ErServerBase:
{
  #ifndef TEST
public:
  /// Constructor
 /* ErServerBase(
	  bool addAriaExitCB = true, 
	  const char *serverName = "",
	  bool addBackupTimeoutToConfig = true,
	  const char *backupTimeoutName = "RobotToClientTimeoutInMins",
	  const char *backupTimeoutDesc = "The amount of time the central server can go without sending a packet to the robot successfully (when there are packets to send).  A number less than 0 means this won't happen.  The time is in minutes but takes doubles (ie .5) (5 seconds is used if the value is positive, but less than that amount)",
	  bool masterServer = false, bool slaveServer = false,
	  bool logPasswordFailureVerbosely = false, 
	  bool allowSlowPackets = true, bool allowIdlePackets = true,
	  int maxClientsAllowed = -1,
	  int warningTimeMSec = 250);*/
  ErServerBase();

  /// Destructor
  virtual ~ErServerBase();
  
  /// Opens the server to accept new client connections
  bool open(unsigned int port, const char *openOnIP = NULL,
		     bool tcpOnly = false);
  /// Closes the server
  void close(void);
  /// Runs the server loop once
  void loopOnce(void);


  ArSocket myTcpSocket;   //类还没有加入
  ArSocket myUdpSocket;

  ArNetPacketReceiverUdp myUdpReceiver;//ArNetPacketReceiverUdp

  unsigned int myTcpPort;
  unsigned int myUdpPort;
  std::string myOpenOnIP; 

  bool myTcpOnly;
  bool mySentTcpOnly;
 #endif
};


#endif
