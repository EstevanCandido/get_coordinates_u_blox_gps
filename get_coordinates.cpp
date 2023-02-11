#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Open the serial port to communicate with the ZED-F9P module
    std::ofstream serial_port("/dev/ttyACM0");
    if (!serial_port.is_open()) {
        std::cerr << "Error opening serial port" << std::endl;
        return 1;
    }

    // Send the UBX-NAV-PVT message to request the GPS data
    serial_port << "\xb5\x62\x01\x07\x00\x00\x04\x46\x3b\x0b";

    // Read the response from the module
    std::string response(2048, '\0');
    serial_port.read(&response[0], response.size());

    // Parse the response to extract the latitude, longitude, and altitude
    int32_t lat = *reinterpret_cast<int32_t*>(&response[24]);
    int32_t lon = *reinterpret_cast<int32_t*>(&response[28]);
    int32_t alt = *reinterpret_cast<int32_t*>(&response[52]);

    // Print the results
    std::cout << "Latitude: " << lat * 1e-7 << " degrees" << std::endl;
    std::cout << "Longitude: " << lon * 1e-7 << " degrees" << std::endl;
    std::cout << "Altitude: " << alt * 1e-3 << " meters" << std::endl;

    return 0;
}
