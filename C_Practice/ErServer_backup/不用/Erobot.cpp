#include "ErServer/Erobot.h"
#define ARINTERFACE
bool Erobot::ourRunning = false;
bool Erobot::ourExiting=false;
ArMutex Erobot::ourShuttingDownMutex;

bool Erobot::getRunning(void)
{
  return ourRunning;
}
 void Erobot::exit(int exitCode)
{
  bool doReturn = false;
  ourShuttingDownMutex.lock();
  ourRunning = false;
  if (ourExiting)
    doReturn=true;
  else
    ourExiting=true;
  ourShuttingDownMutex.unlock();

  if (doReturn)
    return;

  callExitCallbacks();
  ::exit(exitCode);
}
  void Erobot::callExitCallbacks(void)
 {
   ourRunning = false;

   ourShuttingDownMutex.lock();
   ourExiting = true;
   ourShuttingDownMutex.unlock();

   std::multimap<int, ArFunctor *>::reverse_iterator it;



   ourExitCallbacksMutex.lock();
   ArLog::log(ourExitCallbacksLogLevel, "Aria::exit: Starting exit callbacks");
   for (it = ourExitCallbacks.rbegin(); it != ourExitCallbacks.rend(); it++)
   {
     ArLog::log(ourExitCallbacksLogLevel,
          "Aria::exit: Calling callback at position %d with name '%s'",
          (*it).first, (*it).second->getName());
     (*it).second->invoke();
     ArLog::log(ourExitCallbacksLogLevel,
          "Aria::exit: Called callback at position %d with name '%s'",
          (*it).first, (*it).second->getName());

   }
   ArLog::log(ourExitCallbacksLogLevel, "Aria::exit: Finished exit callbacks");
   ourExitCallbacksMutex.unlock();
 }
  void Erobot::init(SigHandleMethod method, bool initSockets,
        bool sigHandleExitNotShutdown)
 {
 #ifndef ARINTERFACE
   // get this here so that the program update can be accurate
  ArSystemStatus::getUptime();
 #endif

   std::list<ArFunctor*>::iterator iter;
   std::string str;
   char buf[1024];

   // make an ArTime and set it to now so that the good clock value will be set
   ArTime timeInit;
   timeInit.setToNow();


   ourShuttingDownMutex.setLogName("Erobot::ourShuttingDownMutex");
   ourExitCallbacksMutex.setLogName("Erobot::ourExitCallbacksMutex");
   if (ourInited == true)
     return;

   ourRunning = true;
 #ifndef WIN32
   srand48(time(NULL));
 #endif

   ArThread::init();

   char* overrideSigMethod = getenv("Erobot_SIGHANDLE_METHOD");
   if(overrideSigMethod)
   {
     ArLog::log(ArLog::Terse, "Overriding signal handler method with %s from Erobot_SIGHANDLE_METHOD environment vErobotble.", overrideSigMethod);
     if(!strcmp(overrideSigMethod, "NONE"))
       method = SIGHANDLE_NONE;
     else if(!strcmp(overrideSigMethod, "SINGLE"))
       method = SIGHANDLE_SINGLE;
     else if(!strcmp(overrideSigMethod, "THREAD"))
       method = SIGHANDLE_THREAD;
   }

   if (method != SIGHANDLE_NONE)
   {
     ArSignalHandler::addHandlerCB(&ourSignalHandlerCB, ArListPos::LAST);
     ArSignalHandler::blockCommon();
     ArSignalHandler::handle(ArSignalHandler::SigHUP);
     ArSignalHandler::handle(ArSignalHandler::SigINT);
     ArSignalHandler::handle(ArSignalHandler::SigQUIT);
     ArSignalHandler::handle(ArSignalHandler::SigTERM);
     ArSignalHandler::handle(ArSignalHandler::SigPIPE);
     if (method == SIGHANDLE_SINGLE)
         ArSignalHandler::createHandlerNonThreaded();
     else if (method == SIGHANDLE_THREAD)
     {
       ArSignalHandler::blockCommonThisThread();
       ArSignalHandler::createHandlerThreaded();
     }
   }

   if (initSockets)
     ArSocket::init();

   if (ourDirectory.length() == 0)
   {
     if (getenv("Erobot") != NULL)
     {
       setDirectory(getenv("Erobot"));
     }
     else
     {
 #ifndef WIN32
       ArUtil::getStringFromFile("/etc/Erobot", buf, sizeof(buf));
       str = buf;
 #else // WIN32
       if (ArUtil::findFirstStringInRegistry(
           "SOFTWARE\\MobileRobots\\Erobot",
           "Install Directory", buf, 1024))
         str = buf;
       else
         if (ArUtil::findFirstStringInRegistry(
             "SOFTWARE\\ActivMedia Robotics\\Erobot",
             "Install Directory", buf, 1024))
           str = buf;
         else
           str = "";

   #endif // WIN32
         if (str.length() > 0)
         {
     setDirectory(str.c_str());
         }
         else
         {
   #ifndef ARINTERFACE
     ArLog::log(ArLog::Terse, "NonCritical Error: Erobot could not find where it is located.");
   #else
     ArLog::log(ArLog::Verbose, "NonCritical Error: Erobot could not find where it is located.");
   #endif
         }
       }
     }
   ourSigHandleExitNotShutdown = sigHandleExitNotShutdown;

 #ifndef ARINTERFACE
   Erobot::laserAddCreator("lms2xx", ArLaserCreatorHelper::getCreateLMS2xxCB());
   Erobot::laserAddCreator("urg", ArLaserCreatorHelper::getCreateUrgCB());
   Erobot::laserAddCreator("lms1XX", ArLaserCreatorHelper::getCreateLMS1XXCB());
   Erobot::laserAddCreator("urg2.0", ArLaserCreatorHelper::getCreateUrg_2_0CB());
   Erobot::laserAddCreator("s3series", ArLaserCreatorHelper::getCreateS3SeriesCB());
   Erobot::laserAddCreator("lms5XX", ArLaserCreatorHelper::getCreateLMS5XXCB());
   Erobot::laserAddCreator("tim3XX", ArLaserCreatorHelper::getCreateTiM3XXCB());
   Erobot::laserAddCreator("tim510", ArLaserCreatorHelper::getCreateTiM3XXCB());
   Erobot::laserAddCreator("tim551", ArLaserCreatorHelper::getCreateTiM551CB());
   Erobot::laserAddCreator("tim561", ArLaserCreatorHelper::getCreateTiM561CB());
   Erobot::laserAddCreator("tim571", ArLaserCreatorHelper::getCreateTiM571CB());
   Erobot::laserAddCreator("sZseries", ArLaserCreatorHelper::getCreateSZSeriesCB());
   Erobot::batteryAddCreator("mtx", ArBatteryMTXCreatorHelper::getCreateBatteryMTXCB());
   Erobot::lcdAddCreator("mtx", ArLCDMTXCreatorHelper::getCreateLCDMTXCB());
   Erobot::sonarAddCreator("mtx", ArSonarMTXCreatorHelper::getCreateSonarMTXCB());
   //Erobot::batteryAddCreator("mtxbatteryv1", ArBatteryMTXCreatorHelper::getCreateBatteryMTXCB());
   //Erobot::lcdAddCreator("mtxlcdv1", ArLCDMTXCreatorHelper::getCreateLCDMTXCB());
   //Erobot::sonarAddCreator("mtxsonarv1", ArSonarMTXCreatorHelper::getCreateSonarMTXCB());
   #endif // ARINTERFACE

   Erobot::deviceConnectionAddCreator(
     "serial", ArDeviceConnectionCreatorHelper::getCreateSerialCB());
   Erobot::deviceConnectionAddCreator(
     "serial422", ArDeviceConnectionCreatorHelper::getCreateSerial422CB());
   Erobot::deviceConnectionAddCreator(
     "tcp", ArDeviceConnectionCreatorHelper::getCreateTcpCB());

   ourInited = true;

   for (iter=ourInitCBs.begin(); iter !=  ourInitCBs.end(); ++iter)
     (*iter)->invoke();

   ArArgumentParser::addDefaultArgumentFile("/etc/Erobot.args");
   ArArgumentParser::addDefaultArgumentEnv("ErobotARGS");

   ArVCC4::registerPTZType();
   ArRVisionPTZ::registerPTZType();
   ArDPPTU::registerPTZType();
   ArSonyPTZ::registerPTZType();
 }
