#ifndef _LIB_PLUTO_API
#define _LIB_PLUTO_API

#define _PLUTO_CONFIG_F ""

#define _PLUTO_INITSTATUS_OK    0
#define _PLUTO_INITSTATUS_ERR   -1 

namespace pluto_dev_ini { 
    int ini();

    int config_parse(); 
    int config_validate();
}

#endif 