#include <assert.h>
#include <iostream>
using namespace std;

// Function to check if a value is within the specified range and determine breach type
bool checkRange(float value, float minValue, float maxValue, const char* name) {
    if (value < minValue) {
        cout << name << " too low!\n";
        return false;
    } else if (value > maxValue) {
        cout << name << " too high!\n";
        return false;
    }
    return true;
}

// Function to check if the battery is ok
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    bool isTemperatureOk = checkRange(temperature, 0, 45, "Temperature");
    bool isSocOk = checkRange(soc, 20, 80, "State of Charge");
    bool isChargeRateOk = checkRange(chargeRate, 0, 0.8, "Charge Rate");

    return isTemperatureOk && isSocOk && isChargeRateOk;
}

// Unit tests
void testBatteryIsOk() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    assert(batteryIsOk(-1, 50, 0.7) == false);
    assert(batteryIsOk(25, 90, 0.7) == false);
    assert(batteryIsOk(25, 50, 0.9) == false);
    assert(batteryIsOk(25, 50, -0.1) == false);
    assert(batteryIsOk(45, 20, 0.8) == true);
}

int main() {
    testBatteryIsOk();
    cout << "All tests passed!\n";
    return 0;
}