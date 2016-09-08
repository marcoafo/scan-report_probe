#include "cmx_handler.h"

char* validator=NULL;

struct config_parameters CONFIG;

/*Hardcoded right now, to be get from file in a second time*/
void init_parameters(){
	CONFIG.URL="http://tribe.openia.it/MerakiCMXDataCollector/events?code=";
	CONFIG.CODE="UNIPING";
	CONFIG.VALIDATOR="f97ab62d-11fd-4f90-a352-e852ff684f4d";
	CONFIG.PATH_CMX="Ezekiel25:17";//To be fixed
}

/*This callback function is called as soon as possibile when data is completely received*/
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	validator=contents;
	//printf("real size is %d\n",realsize);
	validator[realsize-2]='\0';//When the validator is get the  pre-last character is '\n'
	printf("%s\n",validator);
	return realsize;
}

/*It returns 1 if the validator received is equal to the local validator, otherwise returns -1*/
int check_validator(){
if(strcmp(validator,CONFIG.VALIDATOR)==0){
	printf("The get validator is ok\n");
	return 1;
}else{
	printf("The get validator isn't ok\n");
	return -1;
}	
}

/*It returns 1 if there is at least one file in the CONFIG.PATH, otherwise -1*/
int file_presence(){

return -1;
}


/*It executes a HTTP POST on the server. It returns 1 if the post goes ok (in this case the corresponding file will be deleted), otherwise returns -1*/
int post_cmx(){
	if(file_presence()){
	
	/*
	For each file in the folder, make an HTTP POST
		*/
	return 1;
	}
	return -1;
}

/*Given in input the file name, it will be deleted*/
void delete_file(char* name_file){

}

/*The validator is get from HTTP.. GET. This function returns 1 if the validator is get correctly, otherwise -1*/
int 
get_validator(){
	CURL *curl;
	CURLcode res;
	
	size_t len_URL = strlen(CONFIG.URL);
	size_t len_CODE = strlen(CONFIG.CODE);

	char * URL_AUTH = malloc(len_URL + len_CODE + 2);

	memcpy(URL_AUTH, CONFIG.URL, len_URL);
	memcpy(URL_AUTH + len_URL, CONFIG.CODE, len_CODE + 1);

	printf("Url Auth:%s\n",URL_AUTH);
	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, URL_AUTH);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

		/* Perform the request, res will get the return code */ 
		free(URL_AUTH);
		res = curl_easy_perform(curl);
			
		
		 /* Check for errors */ 
	    /* always cleanup */ 
	if(res != CURLE_OK){
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		return -1;
		}

    curl_easy_cleanup(curl);
  }
  return 1;
}


int main()
{
	init_parameters();
	get_validator();	
	check_validator();
	return 0;
}
