#include <stdlib.h>
#include <stdio.h>
#include "log.h"
 
bool LogCreated = false;
 
void Log (char *message)
{
	FILE *file;
 
	if (!LogCreated) {
		file = fopen(LOGFILE, "w");
		LogCreated = true;
	}
	else		
		file = fopen(LOGFILE, "a");
		
	if (file == NULL) {
		if (LogCreated)
			LogCreated = false;
		return;
	}
	else
	{	//fprintf(file, message); 
		//fprintf(file, "/n"); 
		fputs(message, file);
		fclose(file);
	}
 
	if (file)
		fclose(file);
}
 
void LogErr (char *message)
{	Log("Error message : ");
	Log(message);
	Log("\n");
}
