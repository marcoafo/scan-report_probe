#define LOGFILE	"gl.log"     //all Log(); messages will be appended to this file

extern bool LogCreated;      //keeps track whether the log file is created or not
void Log (char *message);    //logs a message to LOGFILE
void LogErr (char *message); //logs an ERROR message to LOGFILE
