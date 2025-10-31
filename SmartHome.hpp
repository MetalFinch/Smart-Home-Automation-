#ifndef SMARTHOME_HPP
#define SMARTHOME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace SmartHome {

    class DeviceManager;

    class Device {
    protected:
        std::string name;
        bool isOn;
        static int deviceCount;

        friend class DeviceManager;

    public:
        Device(const std::string& name);
        virtual ~Device();

        virtual std::string getType() const = 0;
        virtual void turnOn();
        virtual void turnOff();
        virtual void showStatus() const;

        std::string getName() const;
        bool getStatus() const;
        void setStatus(bool status);

        static int getDeviceCount();
        bool operator==(const Device& other) const;                //OPERATOR OVERLOADING
        operator bool() const;
    };

    class Logger {
    public:
        virtual void log(const std::string& msg) const;
    };

    class Light : public Device, public Logger {
    public:
        Light(const std::string& name);
        std::string getType() const override;
    };

    class Fan : public Device {
    public:
        Fan(const std::string& name);
        std::string getType() const override;
    };

    class AirConditioner : public Device {
    public:
        AirConditioner(const std::string& name);
        std::string getType() const override;
    };

    class Heater : public Device {
    public:
        Heater(const std::string& name);
        std::string getType() const override;
    };

    class SmartPlug : public Device {
    public:
        SmartPlug(const std::string& name);
        std::string getType() const override;
    };

    class TV : public Device {
    public:
        TV(const std::string& name);
        std::string getType() const override;
    };

    class DeviceManager {
    public:
        void showInternalState(const Device& d);
    };

    extern std::map<int, std::pair<std::string, bool>> schedule;

    void saveToFile(const std::vector<Device*>& devices, const std::string& filename);
    void loadFromFile(std::vector<Device*>& devices, const std::string& filename);
    void simulateClock(std::vector<Device*>& devices);
    Device* selectDevice(const std::vector<Device*>& devices);

} // namespace SmartHome

#endif
