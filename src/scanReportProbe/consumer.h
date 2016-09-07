//Data structure which contains every information needed by the second process in order to work properly
struct parameters{
	char* directory_path;
	char* server_ip_address;
	int update_period;
	char** string_buffer;
	//...and something else	
};

int consumer_process(void *arg);

struct parameters* init_parameters(char* directory_path, char* server_ip_address, int update_period, char** string_buffer);
