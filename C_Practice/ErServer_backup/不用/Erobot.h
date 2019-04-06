#ifndef EROBOT_H
#define EROBOT_H
#ifdef debug
class Erobot
{
Erobot();
~Erobot();
static void init(SigHandleMethod method = SIGHANDLE_THREAD,
          bool initSockets = true,
          bool sigHandleExitNotShutdown = true);

 static void exit(int exitCode = 0);


 static bool getRunning(void);

 static bool ourRunning;
 static bool ourExiting;
 static ArMutex ourShuttingDownMutex;
static void callExitCallbacks(void);
}
#endif
#endif // EROBOT_H
