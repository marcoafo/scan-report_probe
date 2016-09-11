#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include "handler_config.h" 

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
#define CONFIGFILE "scanReportProbe.conf"

#define GET_STRING_CONFIG_INTERFACE 0
#define GET_STRING_CONFIG_PKG_TYPE 1
#define GET_STRING_CONFIG_CURL_CONFIG 2

extern char *INTERFACE=NULL;
extern char *PKG_TYPE=NULL;
extern scp SCP;


int init_parameters(int varType, char *variableName){
  config_t cfg;
  config_setting_t *setting;
  config_init (&cfg); //initializes the config_t structure pointed by config as a new,empty configuration
  
 
  // Read and parse the file scanReportProbe.conf into the configuration object cfg. If there is an error, report it and exit.
  //It returns an int : CONFIG_TRUE on success, or CONFIG_FALSE on failure; the config_error_text() and config_error_line() functions, can be used to obtain information about the error. 
  if(! config_read_file(&cfg, CONFIGFILE))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }
  
  switch (varType) {
        case (GET_STRING_CONFIG_INTERFACE):
          setting = config_lookup(&cfg, INTERFACE);
          if (setting == NULL) {fprintf(stderr, "No 'Interface' setting in configuration file scanReportProbe.conf.\n");
                                config_destroy(&cfg);
                                return (EXIT_FAILURE);
                                }
          else  {(config_lookup_string(&cfg, "interface", &INTERFACE));
                 printf("Interface name : %s\n\n", INTERFACE); 
                 config_destroy(&cfg);
                 return (EXIT_SUCCESS);
                };
        break;
        
        case (GET_STRING_CONFIG_PKG_TYPE):
          setting = config_lookup(&cfg, PKG_TYPE);
          if (setting == NULL){fprintf(stderr, "No 'pkg_type' setting in configuration file scanReportProbe.conf.\n");
                               config_destroy(&cfg);
                               return (EXIT_FAILURE);
                               }
          else {(config_lookup_string(&cfg, "pkg_type", &PKG_TYPE)); 
                printf("pkg_type : %s\n\n", PKG_TYPE); 
                config_destroy(&cfg);
                return (EXIT_SUCCESS);
               };
        break;
        
        case (GET_STRING_CONFIG_CURL_CONFIG):
        setting = config_lookup(&cfg, &SCP);
        if (setting == NULL){fprintf(stderr, "No 'config_parameters_structure' setting in configuration file scanReportProbe.conf.\n");
                               config_destroy(&cfg);
                               return (EXIT_FAILURE);
                               }
          else {
  
  
  
        break;
 /*
 scp = {
      scp.URL= *config.URL,
      scp.CODE= *config.CODE,
      scp.VALIDATOR= *config.VALIDATOR,
      scp.PATH_CMX= *config.PATH_CMX,
      scp.SECRET= *config.SECRET,
      scp.MAC_AP= *config.MAC_AP;
       };
  };
  */
  

config_destroy(&cfg);//destroys the configuration config, deallocating all memory associated with the configuration, but does not attempt to deallocate the config_t structure itself
return(EXIT_SUCCESS);
}
