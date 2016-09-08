#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <semaphore.h>

//Data structure which contains every information needed by the second process in order to work properly
struct parameters{
	char* directory_path;
	char* server_ip_address;
	int update_period;
	char** string_buffer;		//Pointer to the base of the circular buffer		
	char** read_pointer;		//Pointer used by the second process to access to each buffer slot
	sem_t* mutex;			//Note: it must be initialized with this funtion: mutex = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 1); sem_unlink ("pSem"); 
	//...and something else	
};

int consumer_process(void *arg);

struct parameters* init_parameters(char* directory_path, char* server_ip_address, int update_period, char** string_buffer, sem_t* mutex);
