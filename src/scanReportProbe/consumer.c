#include "consumer.h"

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
	sleep(1);
	/*---------------------Instructions to be executed periodically--------------------------------------*/
	while(1){
		//Acquire lock
		sem_wait(param->mutex);
		//Consume the buffer content
		for(; *param->read_pointer != NULL; param->read_pointer += 1){
			printf("Child read: %s\n", *param->read_pointer);
			*param->read_pointer = NULL;						//This is necessary because it is the only way to let the first process understands that this buffer slot has been read
		}
		//Release lock
		sem_post(param->mutex);
		//Nothing more to do, go to sleep.
		sleep(param->update_period);
	}
	return 0;
}

/*
* Function that allows you to initialize the parameters data structure containing
* the configuration information needed by the second process.
* It returns a pointer to a pre-allocated and initialized data structure, or null in case of error.
*/
struct parameters* init_parameters(char* directory_path, char* server_ip_address, int update_period, char** string_buffer, sem_t* mutex){
	struct parameters* result;
	if(directory_path == NULL || server_ip_address == NULL || update_period <= 0 || string_buffer == NULL || mutex == NULL)
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
	//At the beginning the reading pointer points to the first slot of the buffer
	result->read_pointer = string_buffer;
	//Copy the pointer to the semaphore
	result->mutex = mutex;
	return result;
}
