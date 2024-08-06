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
    assert(isBatteryOk(soc6, temp6, chargeRate6) == false);

    // Testing edge cases
    float soc7 = 20, temp7 = 45, chargeRate7 = 0.8;
    BatteryStatusCode status7 = validateBatterySystem(soc7, temp7, chargeRate7);
    std::cout << "SOC: " << soc7 << ", Temp: " << temp7 << ", Charge Rate: " << chargeRate7
              << " -> Status: " << statusCodeToString(status7) << std::endl;
    assert(isBatteryOk(soc7, temp7, chargeRate7) == false);

    float soc8 = 80, temp8 = 45, chargeRate8 = 0.8;
    BatteryStatusCode status8 = validateBatterySystem(soc8, temp8, chargeRate8);
    std::cout << "SOC: " << soc8 << ", Temp: " << temp8 << ", Charge Rate: " << chargeRate8
              << " -> Status: " << statusCodeToString(status8) << std::endl;
    assert(isBatteryOk(soc8, temp8, chargeRate8) == false);

    float soc9 = 19, temp9 = 30, chargeRate9 = 0.79;
    BatteryStatusCode status9 = validateBatterySystem(soc9, temp9, chargeRate9);
    std::cout << "SOC: " << soc9 << ", Temp: " << temp9 << ", Charge Rate: " << chargeRate9
              << " -> Status: " << statusCodeToString(status9) << std::endl;
    assert(isBatteryOk(soc9, temp9, chargeRate9) == false);

    float soc10 = 21, temp10 = 46, chargeRate10 = 0.81;
    BatteryStatusCode status10 = validateBatterySystem(soc10, temp10, chargeRate10);
    std::cout << "SOC: " << soc10 << ", Temp: " << temp10 << ", Charge Rate: " << chargeRate10
              << " -> Status: " << statusCodeToString(status10) << std::endl;
    assert(isBatteryOk(soc10, temp10, chargeRate10) == false);

    // Test cases with different combinations of tolerance thresholds
    float soc11 = 25, temp11 = 42, chargeRate11 = 0.76;
    BatteryStatusCode status11 = validateBatterySystem(soc11, temp11, chargeRate11);
    std::cout << "SOC: " << soc11 << ", Temp: " << temp11 << ", Charge Rate: " << chargeRate11
              << " -> Status: " << statusCodeToString(status11) << std::endl;
    assert(isBatteryOk(soc11, temp11, chargeRate11) == true);

    float soc12 = 24.5, temp12 = 44, chargeRate12 = 0.77;
    BatteryStatusCode status12 = validateBatterySystem(soc12, temp12, chargeRate12);
    std::cout << "SOC: " << soc12 << ", Temp: " << temp12 << ", Charge Rate: " << chargeRate12
              << " -> Status: " << statusCodeToString(status12) << std::endl;
    assert(isBatteryOk(soc12, temp12, chargeRate12) == false);

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
