#include "SmartHome.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace SmartHome {

    int Device::deviceCount = 0;
    map<int, pair<string, bool>> schedule;

    Device::Device(const string& name) : name(name), isOn(false) {
        deviceCount++;
    }

    Device::~Device() {
        deviceCount--;
    }

    void Device::turnOn() { isOn = true; cout << name << " is ON." << endl; }
    void Device::turnOff() { isOn = false; cout << name << " is OFF." << endl; }
    void Device::showStatus() const { cout << name << " is " << (isOn ? "ON" : "OFF") << endl; }

    string Device::getName() const { return name; }
    bool Device::getStatus() const { return isOn; }
    void Device::setStatus(bool status) { isOn = status; }
    int Device::getDeviceCount() { return deviceCount; }

    bool Device::operator==(const Device& other) const {
        return name == other.name && getType() == other.getType();
    }

    Device::operator bool() const { return isOn; }

    void Logger::log(const string& msg) const {
        cout << "[LOG] " << msg << endl;
    }

    Light::Light(const string& name) : Device(name) {}
    string Light::getType() const { return "Light"; }

    Fan::Fan(const string& name) : Device(name) {}
    string Fan::getType() const { return "Fan"; }

    AirConditioner::AirConditioner(const string& name) : Device(name) {}
    string AirConditioner::getType() const { return "AirConditioner"; }

    Heater::Heater(const string& name) : Device(name) {}
    string Heater::getType() const { return "Heater"; }

    SmartPlug::SmartPlug(const string& name) : Device(name) {}
    string SmartPlug::getType() const { return "SmartPlug"; }

    TV::TV(const string& name) : Device(name) {}
    string TV::getType() const { return "TV"; }

    void DeviceManager::showInternalState(const Device& d) {
        cout << "[Friend Access] " << d.name << " internal status: " << (d.isOn ? "ON" : "OFF") << endl;
    }

    void saveToFile(const vector<Device*>& devices, const string& filename) {
        ofstream out(filename);
        if (!out) throw runtime_error("Unable to open file.");
        for (const auto& d : devices) {
            out << d->getName() << "," << d->getType() << "," << d->getStatus() << endl;
        }
        cout << "Saved to " << filename << endl;
    }

    void loadFromFile(vector<Device*>& devices, const string& filename) {
        ifstream in(filename);
        if (!in) throw runtime_error("Cannot read file.");

        // Clean up existing devices
        for (auto d : devices) delete d;
        devices.clear();

        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string name, type;
            bool status;
            getline(ss, name, ',');
            getline(ss, type, ',');
            ss >> status;

            Device* d = nullptr;
            if (type == "Light") d = new Light(name);
            else if (type == "Fan") d = new Fan(name);
            else if (type == "AirConditioner") d = new AirConditioner(name);
            else if (type == "Heater") d = new Heater(name);
            else if (type == "SmartPlug") d = new SmartPlug(name);
            else if (type == "TV") d = new TV(name);

            if (d) {
                d->setStatus(status);
                devices.push_back(d);
            }
        }

        cout << "Loaded from " << filename << endl;
    }

    void simulateClock(vector<Device*>& devices) {
        for (int hour = 0; hour <= 24; ++hour) {
            cout << "\n-- Hour " << hour << " --\n";
            if (schedule.count(hour)) {
                auto [name, on] = schedule[hour];
                for (auto d : devices) {
                    if (d->getName() == name) {
                        on ? d->turnOn() : d->turnOff();
                    }
                }
            }
        }
    }

    Device* selectDevice(const vector<Device*>& devices) {
        cout << "Choose a device:\n";
        for (size_t i = 0; i < devices.size(); ++i)
            cout << i + 1 << ". " << devices[i]->getName() << endl;

        int choice;
        cout << "Enter number: ";
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= devices.size())
            return devices[choice - 1];

        cout << "Invalid selection.\n";
        return nullptr;
    }

} // namespace SmartHome
