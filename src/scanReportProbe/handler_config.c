#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include "handler_config.h" 

int init_parameters(){
  config_t cfg;
  config_init (&cfg); //initializes the config_t structure pointed to by config as a new,empty configuration
  //config_setting_t *setting;
  const char *str;

  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, "scanReportProbe.conf"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }
  if(config_lookup_string(&cfg, "interface", &str))  { //assegnare il valore ad una variabile globale ?
                                                      printf("Interface name : %s\n\n", str); }
  else
      fprintf(stderr, "No 'Interface' setting in configuration file scanReportProbe.conf.\n");
  
  if(config_lookup_string(&cfg, "pkg_type", &str))  {  //assegnare il valore ad una variabile globale ?
                                                      printf("pkg_type : %s\n\n", str); }
  else
      fprintf(stderr, "No 'pkg_type' setting in configuration file scanReportProbe.conf.\n");
 
 /*
 if ( config_read_file (config_t * config, const char * scanReportProbe.conf) == "CONFIG_TRUE"){  //config_read_file reads and parses a configuration from the file named scanReportProbe.conf into the configuration object config. 
 //It returns an int : CONFIG_TRUE on success, or CONFIG_FALSE on failure; the config_error_text() and config_error_line() functions, can be used to obtain information about the error. 
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
