#ifndef _LIB_PLUTO_API
#define _LIB_PLUTO_API

#include <thread>
#include <memory>
#include <mutex>
#include <iostream>
#include <optional>

#include "IPluto/Types.hpp"

#define _PLUTO_CONFIG_F ""

#define _PLUTO_INITSTATUS_OK    0
#define _PLUTO_INITSTATUS_ERR   -1 

typedef struct {
    const std::string       uri;
} PlutoContext; 

static constexpr const char* E_INVALID_DRIVER = "exc=E_INVALID_DRIVER"; 

class PlutoLog {
public:
    PlutoLog(const char* fmt, ...) = default;
    PlutoLog(std::string msg) : message(std::move(msg)) {}
    bool Exists() const { return !message.empty(); }
    const std::string& What() const { return message; }
private:
    std::string message;
};

class PlutoException : public std::exception { 
public:

}; 

class PlutoOptions {
public:
    static std::unique_ptr<PlutoOptions> Create() {
        std::unique_ptr<PlutoOptions> options(new PlutoOptions());
    }

    void ReadFromFile(const std::string path); 

    void SetMTU(int mtu) { this->mtu = mtu; }
    void SetFWBufferSize(int size) { this->fwBufferSize = size; }
    void SetRXFreq(double freq) { this->rxFreq = freq; }
    void SetTXFreq(double freq) { this->txFreq = freq; }
    
private:
    int mtu = 0;
    int fwBufferSize = 0;
    double rxFreq = 0.0;
    double txFreq = 0.0;
    
    friend class PlutoDevice; // Только PlutoDevice может читать параметры
};

class PlutoDevice : public SoapySDR::Device, public std::enable_shared_from_this<PlutoDevice> {
public:
    static std::shared_ptr<PlutoDevice> Create(const std::string& uri, PlutoOptions options) {
        std::shared_ptr<PlutoDevice> device(new PlutoDevice(uri, std::move(options)));
        return device;
    }

    PlutoLog Created() {
        return PlutoLog(); // Заглушка, реальная логика внутри
    }
    
    PlutoLog Attach() {
        std::lock_guard<std::mutex> lock(mutex);
        if (ctx.is) return PlutoLog("Already attached");
        attached = true;
        return PlutoLog();
    }
    
    PlutoLog Detach() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!attached) return PlutoLog("Not attached");
        attached = false;
        return PlutoLog();
    }
    
private:
    PlutoDevice(std::string uri, PlutoOptions options)
        : uri(std::move(uri)), options(std::move(options)) {}

    std::string     uri;
    std::mutex      mutex;
    PlutoOptions    options;
};
    
#endif 