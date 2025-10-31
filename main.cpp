#include "SmartHome.hpp"

using namespace std;
using namespace SmartHome;

int main() {
    vector<Device*> devices = {
        new Light("Bedroom Light"),
        new Fan("Ceiling Fan"),
        new AirConditioner("Living Room AC"),
        new Heater("Bathroom Heater"),
        new SmartPlug("Coffee Maker Plug"),
        new TV("Smart TV")
    };

    DeviceManager manager;
    int option;

    while (true) {
        cout << "\n=== Smart Home Menu ===\n"
            << "1. Turn ON device\n2. Turn OFF device\n3. Show device status\n"
            << "4. Schedule a device\n5. Simulate clock\n6. Save to file\n"
            << "7. Load from file\n8. Device count\n9. Friend class test\n0. Exit\n"
            << "Enter choice: ";
        cin >> option;
        cin.ignore();

        try {
            if (option == 0) break;
            else if (option == 1 || option == 2) {
                Device* d = selectDevice(devices);
                if (d) (option == 1 ? d->turnOn() : d->turnOff());
            }
            else if (option == 3) {
                for (auto d : devices) d->showStatus();
            }
            else if (option == 4) {
                cout << "Enter hour (0–23): ";
                int hour; cin >> hour; cin.ignore();
                Device* d = selectDevice(devices);
                if (d) {
                    cout << "Turn ON or OFF? (on/off): ";
                    string state; getline(cin, state);
                    schedule[hour] = { d->getName(), state == "on" };
                    cout << "Scheduled " << d->getName() << " at hour " << hour << endl;
                }
            }
            else if (option == 5) simulateClock(devices);
            else if (option == 6) saveToFile(devices, "devices.txt");
            else if (option == 7) loadFromFile(devices, "devices.txt");
            else if (option == 8) cout << "Total devices: " << Device::getDeviceCount() << endl;
            else if (option == 9) {
                Device* d = selectDevice(devices);
                if (d) manager.showInternalState(*d);
            }
            else cout << "Invalid choice.\n";
        }
        catch (const exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }

    // Free all dynamically allocated devices
    for (auto d : devices) delete d;
    devices.clear();

    cout << "Exiting Smart Home System.\n";
    return 0;
}
