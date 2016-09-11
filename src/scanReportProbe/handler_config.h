 
 typedef struct config_parameters {char URL[58];		    //URL of the server
		                                    char CODE[7];      //Code by which is possible to get the validator
		                                    char VALIDATOR[36];//The local validator
		                                    char PATH_CMX[30];//The path in which the CMX files are stored
 		                                    char SECRET[13]; //The secret 
                                        char MAC_AP[17]; } scp;
