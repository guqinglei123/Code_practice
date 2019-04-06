#ifndef ERLOG_H
#define ERLOG_H


class ErLog
{
public:

  typedef enum {
    StdOut, ///< Use stdout for logging
    StdErr, ///< Use stderr for logging
    File, ///< Use a file for logging
    Colbert, ///< Use a Colbert stream for logging
    None ///< Disable logging
  } LogType;
  typedef enum {
    Terse, ///< Use terse logging
    Normal, ///< Use normal logging
    Verbose ///< Use verbose logging
  } LogLevel;


  /// Initialize the logging utility with options
static void log(LogLevel level, const char *str, ...);
static void logErrorFromOS(LogLevel level, const char *str, ...);

};


#endif // ERLOG_H
