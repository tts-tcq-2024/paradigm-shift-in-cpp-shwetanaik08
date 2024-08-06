#include <iostream>
#include <cassert>
#include "BatteryCheck.h"
#include "BatteryStatus.h"

int main() {
    // Test cases with expected results
    float soc1 = 25, temp1 = 40, chargeRate1 = 0.7;
    BatteryStatusCode status1 = validateBatterySystem(soc1, temp1, chargeRate1);
    assert(isBatteryOk(soc1, temp1, chargeRate1) == true); // SOC and charge rate within range, temperature within range

    float soc2 = 50, temp2 = 85, chargeRate2 = 0;
    BatteryStatusCode status2 = validateBatterySystem(soc2, temp2, chargeRate2);
    assert(isBatteryOk(soc2, temp2, chargeRate2) == false); // Temperature out of range

    // Additional test cases
    float soc3 = 22, temp3 = 30, chargeRate3 = 0.5;
    BatteryStatusCode status3 = validateBatterySystem(soc3, temp3, chargeRate3);
    assert(isBatteryOk(soc3, temp3, chargeRate3) == true);

    float soc4 = 0, temp4 = 20, chargeRate4 = 0.9;
    BatteryStatusCode status4 = validateBatterySystem(soc4, temp4, chargeRate4);
    assert(isBatteryOk(soc4, temp4, chargeRate4) == false);

    float soc6 = 35, temp6 = 75, chargeRate6 = 0.85;
    BatteryStatusCode status6 = validateBatterySystem(soc6, temp6, chargeRate6);
    assert(isBatteryOk(soc6, temp6, chargeRate6) == false);

    // Testing edge cases
    float soc7 = 20, temp7 = 45, chargeRate7 = 0.8;
    BatteryStatusCode status7 = validateBatterySystem(soc7, temp7, chargeRate7);
    assert(isBatteryOk(soc7, temp7, chargeRate7) == false);

    float soc8 = 80, temp8 = 45, chargeRate8 = 0.8;
    BatteryStatusCode status8 = validateBatterySystem(soc8, temp8, chargeRate8);
    assert(isBatteryOk(soc8, temp8, chargeRate8) == false);

    float soc9 = 19, temp9 = 30, chargeRate9 = 0.79;
    BatteryStatusCode status9 = validateBatterySystem(soc9, temp9, chargeRate9);
    assert(isBatteryOk(soc9, temp9, chargeRate9) == false);

    float soc10 = 21, temp10 = 46, chargeRate10 = 0.81;
    BatteryStatusCode status10 = validateBatterySystem(soc10, temp10, chargeRate10);
    assert(isBatteryOk(soc10, temp10, chargeRate10) == false);

    // Test cases with different combinations of tolerance thresholds
    float soc11 = 25, temp11 = 42, chargeRate11 = 0.76;
    BatteryStatusCode status11 = validateBatterySystem(soc11, temp11, chargeRate11);
    assert(isBatteryOk(soc11, temp11, chargeRate11) == true);

    float soc12 = 24.5, temp12 = 44, chargeRate12 = 0.77;
    BatteryStatusCode status12 = validateBatterySystem(soc12, temp12, chargeRate12);
    assert(isBatteryOk(soc12, temp12, chargeRate12) == false);

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
