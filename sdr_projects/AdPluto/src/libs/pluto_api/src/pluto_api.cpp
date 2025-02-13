#include "pluto_api.hpp"

#include "stdio.h"
#include <stdlib.h>

namespace pluto_dev_ini { 
    int ini() { 
        if (_PLUTO_CONFIG_F == "" || config_parse() != _PLUTO_INITSTATUS_OK) { 
            fprintf(stderr, "func %s \t|\t Error reading file: %s.\n", __FUNCTION__, _PLUTO_CONFIG_F); 
            return _PLUTO_INITSTATUS_ERR;
        }

        if (config_validate() != _PLUTO_INITSTATUS_OK) { 
            fprintf(stderr, "func %s \t|\t Error validating config file: %s.\n", __FUNCTION__, _PLUTO_CONFIG_F); 
            return _PLUTO_INITSTATUS_ERR; 
        }

        return _PLUTO_INITSTATUS_OK; 
    }
    
    int config_parse() {
        FILE *fd = fopen(_PLUTO_CONFIG_F, "r"); 

        if (fd != NULL) { 
            return _PLUTO_INITSTATUS_ERR;
        }

        char buff[128];  

        while (fgets(buff, sizeof(buff), fd)) { 
            printf("%s\n", buff); 
        }
        
        fclose(fd);
        return _PLUTO_INITSTATUS_OK; 
    }
    
    int config_validate() {

        

        return _PLUTO_INITSTATUS_OK;
    }
}
