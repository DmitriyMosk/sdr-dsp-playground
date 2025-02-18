#include <iostream> 
#include "PlutoDevice.hpp"

int main(int argc, const char* argv) { 
    auto options = PlutoOptions::Create(); 
    
    options.SetFromArg(argc, argv);
    options.ReadFromFile()
    options.SetMTU(10000); 
    options.SetRXFreq();
    options.SetTXFreq();

    // один из типов буферов
    auto tx_buffer = PlutoBuffer::RingBuffer(1'000'000)
    auto rx_buffer = PlutoBuffer::RingBuffer(1'000'000)
    
    auto device = PlutoDevice::Create("usb:1.5.5", options, buffer); 

    if (PlutoLog err = device.Created(); !err.Exists()) { 
        std::cout << "Error creating: " << err.What();
        return EXIT_FAILURE; 
    }

    // после этого момента options = nullptr, надо запретить юзерам обращаться к полю options

    if (PlutoLog err = device.Attach(); !err.Exists()) { 
        std::cout << "Error attaching: " << err.What();
        return EXIT_FAILURE;
    }

    buffer.Push();
    buffer.Pull();

    if (PlutoLog err = device.Detach(); !err.Exists()) { 
        std::cout << "Error attaching: " << err.What();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}