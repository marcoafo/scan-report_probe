#include "consumer.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 

/*
* The actual process body taken by the clone function.
* When you call "clone", you also need to specify the pointer to the data structure containing the parameters
*/
int consumer_process(void *arg){
	struct parameters* param;
	FILE* cmx_file;
	/*---------------------Instructions to be executed only once, at the very beginning------------------*/
	
	//Obtain the configuration parameters 
	param = (struct parameters*)arg;
	
	
	/*---------------------Instructions to be executed periodically--------------------------------------*/
	while(1){
		//Acquire lock
		//Consume the buffer content
		//Release lock
		
		printf("Child read: %s\n", param->string_buffer[0]);
		printf("Child read: %s\n", param->string_buffer[5]);
	
		//Nothing more to do, go to sleep.
		sleep(param->update_period);
	}
	return 0;
}

/*
* Function that allows you to initialize the parameters data structure containing
* the configuration information needed by the second process.
* It returns a pointer to a pre-allocated and initialized data structure.
*/
struct parameters* init_parameters(char* directory_path, char* server_ip_address, int update_period, char** string_buffer){
	struct parameters* result;
	if(directory_path == NULL || server_ip_address == NULL || update_period <= 0 || string_buffer == NULL)
		return NULL;
	//Allocate memory space for the data structure
	result = (struct parameters*)malloc(sizeof(struct parameters));
	//Copy update period
	result->update_period = update_period;
	//Allocate and copy directory path string
	result->directory_path = malloc(strlen(directory_path) + 1);
	strcpy(result->directory_path, directory_path);
	//Allocate and copy server ip address string
	result->server_ip_address = malloc(strlen(server_ip_address) + 1);
	strcpy(result->server_ip_address, server_ip_address);
	//Copy memory address that points to the shared buffer
	result->string_buffer = string_buffer;
	
	return result;
}
