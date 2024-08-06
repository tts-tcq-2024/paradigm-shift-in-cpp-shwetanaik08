#include <iostream>
#include <cassert>
#include "BatteryCheck.h"
#include "BatteryStatus.h"

int main() {
    // Test cases with expected results
    float soc1 = 25, temp1 = 40, chargeRate1 = 0.7;
    BatteryStatusCode status1 = validateBatterySystem(soc1, temp1, chargeRate1);
    std::cout << "SOC: " << soc1 << ", Temp: " << temp1 << ", Charge Rate: " << chargeRate1
              << " -> Status: " << statusCodeToString(status1) << std::endl;
    assert(isBatteryOk(soc1, temp1, chargeRate1) == true); // SOC and charge rate within range, temperature within range

    float soc2 = 50, temp2 = 85, chargeRate2 = 0;
    BatteryStatusCode status2 = validateBatterySystem(soc2, temp2, chargeRate2);
    std::cout << "SOC: " << soc2 << ", Temp: " << temp2 << ", Charge Rate: " << chargeRate2
              << " -> Status: " << statusCodeToString(status2) << std::endl;
    assert(isBatteryOk(soc2, temp2, chargeRate2) == false); // Temperature out of range

    // Additional test cases
    float soc3 = 22, temp3 = 30, chargeRate3 = 0.5;
    BatteryStatusCode status3 = validateBatterySystem(soc3, temp3, chargeRate3);
    std::cout << "SOC: " << soc3 << ", Temp: " << temp3 << ", Charge Rate: " << chargeRate3
              << " -> Status: " << statusCodeToString(status3) << std::endl;
    assert(isBatteryOk(soc3, temp3, chargeRate3) == true);

    float soc4 = 0, temp4 = 20, chargeRate4 = 0.9;
    BatteryStatusCode status4 = validateBatterySystem(soc4, temp4, chargeRate4);
    std::cout << "SOC: " << soc4 << ", Temp: " << temp4 << ", Charge Rate: " << chargeRate4
              << " -> Status: " << statusCodeToString(status4) << std::endl;
    assert(isBatteryOk(soc4, temp4, chargeRate4) == false);

    float soc6 = 35, temp6 = 75, chargeRate6 = 0.85;
    BatteryStatusCode status6 = validateBatterySystem(soc6, temp6, chargeRate6);
    std::cout << "SOC: " << soc6 << ", Temp: " << temp6 << ", Charge Rate: " << chargeRate6
              << " -> Status: " << statusCodeToString(status6) << std::endl;
    assert(isBatteryOk(soc6
