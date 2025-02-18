#include <stdexcept>
#include "IPluto/Device.hpp"
#include "helpers.hpp"

using namespace std;

PlutoDevice::PlutoDevice(string uri) { 
    if (uri.find("usb") != string::npos){

    } else if (uri.find("ip") != string::npos) {

    } else { 
        throw std::invalid_argument("");
    }

    plutoThreadController(std::make_shared<PlutoDevice>(this));
}

bool PlutoDevice::Attach() {
    if (ctx.is_attached) { 
        return false; 
    }



    return true; 
}

bool PlutoDevice::Detach() {
    if (!ctx.is_attached) { 
        return false; 
    }

    return true; 
}

PlutoDevice::~PlutoDevice() { 

}