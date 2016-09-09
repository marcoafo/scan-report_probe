#include "cmx_handler.h"

char* validator=NULL;

struct config_parameters CONFIG;

/*Hardcoded right now, to be get from file in a second time*/
void init_parameters(){
	CONFIG.URL="http://tribe.openia.it/MerakiCMXDataCollector/events?code=";
	CONFIG.CODE="UNIPING";
	CONFIG.VALIDATOR="f97ab62d-11fd-4f90-a352-e852ff684f4d";
	CONFIG.PATH_CMX="path_cmx/";//To be changed. TODO
	CONFIG.SECRET="uniping-tribe";
	CONFIG.MAC_AP="E4:95:6E:40:8D:2E";
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
	return OK;
}else{
	printf("The get validator isn't ok\n");
	return KO;
}	
}

/*It returns 1 if there is at least one file in the CONFIG.PATH, otherwise -1*/
int file_presence(){

	DIR *dir;
	char *THIS_DIR=".";
	char *PREVIOUS_DIR="..";
	char *file_name;

	CURL *curl;
	CURLM *multi_handle;
	static const char buf[] = "Expect:";
	int still_running;

	struct curl_httppost *formpost=NULL;
  	struct curl_httppost *lastptr=NULL;
  	struct curl_slist *headerlist=NULL;

	int number_files=0;
	
	struct dirent *ent;

	if ((dir = opendir (CONFIG.PATH_CMX)) != NULL) { 
		/*While there are file in the folder, put in a HTTP POST to send list*/
		while ((ent = readdir (dir)) != NULL) {
			if(strcmp(ent->d_name,THIS_DIR)!=0 && strcmp(ent->d_name,PREVIOUS_DIR)!=0){
				number_files++;
				file_name=ent->d_name;
				printf("Name file :%s\n",file_name);
				curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "Pippo", CURLFORM_FILE, file_name, CURLFORM_END);
				}
		}

	curl = curl_easy_init();
	multi_handle = curl_multi_init();
 
	/* initialize custom header list (stating that Expect: 100-continue is not wanted */ 
	headerlist = curl_slist_append(headerlist, buf);
	if(curl && multi_handle) {
	 
		char *url_post=get_auth_url();
		/* what URL that receives this POST */
		printf("URL POST:%s\n",url_post);

		curl_easy_setopt(curl, CURLOPT_URL, url_post);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
 
		curl_multi_add_handle(multi_handle, curl);
		 
		int res=curl_multi_perform(multi_handle, &still_running);
		printf("%d\n",res);
 		if(res != CURLE_OK){
			fprintf(stderr, "curl_multi_perform() failed: %s\n", curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			
		}

	curl_multi_cleanup(multi_handle);/* always cleanup */ 
	curl_easy_cleanup(curl);
	curl_formfree(formpost);/* then cleanup the formpost chain */ 
	curl_slist_free_all (headerlist); /* free slist */ 
  }

  closedir (dir);
} else {
  /* could not open directory */
  perror ("");
  return KO;
}
return OK;
}


/*It executes a HTTP POST on the server. It returns 1 if the post goes ok (in this case the corresponding file will be deleted), otherwise returns -1*/
int http_post_cmx(char *file_name){

	
	return 1;
}

/*Given in input the file name, it will be deleted*/
int delete_file(char* name_file){
	
	return 1;
}

/* This function simply concatenates URL and the CODE in the config parameters*/
char* get_auth_url(){
	size_t len_URL = strlen(CONFIG.URL);
	size_t len_CODE = strlen(CONFIG.CODE);

	char * URL_AUTH = malloc(len_URL + len_CODE + 2);

	memcpy(URL_AUTH, CONFIG.URL, len_URL);
	memcpy(URL_AUTH + len_URL, CONFIG.CODE, len_CODE + 1);

	//printf("Url Auth:%s\n",URL_AUTH);
	return URL_AUTH;
	
}
/*The validator is get from HTTP.. GET. This function returns 1 if the validator is get correctly, otherwise -1*/
int 
get_validator(){
	CURL *curl;
	CURLcode res;

	char * URL_AUTH = get_auth_url();

	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, URL_AUTH);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);/* Verbose for more information*/
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
		return KO;
		}

    curl_easy_cleanup(curl);
  }
  return OK;
}


int main()
{
	int check_val=0;
	init_parameters();

	if(get_validator()==OK){	
		check_val=check_validator();
		}else return KO;

	if(check_val==OK){
		file_presence();
		}else return KO;


}
