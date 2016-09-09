#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define OK 100
#define KO 404

/*Data structure in which the parameters get from the file are stored*/
struct config_parameters{
	char *URL;/*URL of the server*/
	char *CODE;/*Code by which is possible to get the validator*/
	char *VALIDATOR;/*The local validator*/
	char *PATH_CMX;/*The path in which the CMX files are stored*/
	char *SECRET;/*The secret*/
	char *MAC_AP;/*MAC address appliance. Maybe not needed as configuration parameters*/
};

/*Prototypes of the functions*/
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
int check_validator();
int get_validator();
char* get_auth_url();
