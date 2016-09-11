#include "handler_config.h" 

config_parameters init_parameters(){
                      void config_init (config_t * config); //initializes the config_t structure pointed to by config as a new, 
                                                           //empty configuration

                      if ( config_read_file (config_t * config, const char * scanReportProbe.conf) == "CONFIG_TRUE"){  //This function reads and parses a configuration from the file named scanReportProbe.conf into the configuration object config. 
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

                      void config_destroy (config_t * config); //destroys the configuration config, 
                                                              //deallocating all memory associated with the configuration, 
                                                             //but does not attempt to deallocate the config_t structure itself
              return scp
}
