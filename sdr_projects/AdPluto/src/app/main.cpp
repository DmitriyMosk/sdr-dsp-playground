#include <iostream> 
#include <string.h>

#include "pluto_api.hpp"

int main(int argc, const char* argv) { 
    if (pluto_dev_ini::ini() != _PLUTO_INITSTATUS_OK) { 
        fprintf(stderr, "func %s \t|\t Error pluto initialization.\n", __FUNCTION__); 
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}