#include <iostream>
#include <map>
#include <string>
#include <cassert>

// Define thresholds and tolerances
const float STATE_OF_CHARGE_MIN = 20.0f;
const float STATE_OF_CHARGE_MAX = 80.0f;
const float SOC_WARNING_MAX_TOLERANCE = 0.05f * STATE_OF_CHARGE_MAX; // 5% tolerance at the upper limit
const float SOC_WARNING_MIN_TOLERANCE = 0.05f * STATE_OF_CHARGE_MIN; // 5% tolerance at the lower limit

const float TEMPERATURE_MAX = 45.0f;
const float TEMPERATURE_WARNING_TOLERANCE = 0.05f * TEMPERATURE_MAX; // 5% tolerance

const float CHARGE_RATE_MAX = 0.8f;
const float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX; // 5% tolerance

// Define status codes
enum BatteryStatusCode {
    LOW_SOC_BREACH = 0,
    LOW_SOC_WARNING = 1,
    NORMAL = 2,
    HIGH_SOC_WARNING = 3,
    HIGH_SOC_BREACH = 4,
    SOC_OUT_OF_RANGE = 5,
    TEMPERATURE_OUT_OF_RANGE = 6,
    TEMPERATURE_WARNING = 7,
    CHARGE_RATE_WARNING = 8,
    CHARGE_RATE_OUT_OF_RANGE = 9
};

// Define status descriptions
std::map<BatteryStatusCode, std::string> createStatusDescriptionMap() {
    std::map<BatteryStatusCode, std::string> statusDescriptions;
    statusDescriptions[LOW_SOC_BREACH] = "LOW_SOC_BREACH";
    statusDescriptions[LOW_SOC_WARNING] = "LOW_SOC_WARNING: Approaching discharge";
    statusDescriptions[NORMAL] = "NORMAL";
    statusDescriptions[HIGH_SOC_WARNING] = "HIGH_SOC_WARNING: Approaching charge-peak";
    statusDescriptions[HIGH_SOC_BREACH] = "HIGH_SOC_BREACH";
    statusDescriptions[SOC_OUT_OF_RANGE] = "SOC_OUT_OF_RANGE";
    statusDescriptions[TEMPERATURE_WARNING] = "TEMPERATURE_WARNING: Approaching maximum temperature";
    statusDescriptions[TEMPERATURE_OUT_OF_RANGE] = "TEMPERATURE_OUT_OF_RANGE";
    statusDescriptions[CHARGE_RATE_WARNING] = "CHARGE_RATE_WARNING: Approaching maximum charge rate";
    statusDescriptions[CHARGE_RATE_OUT_OF_RANGE] = "CHARGE_RATE_OUT_OF_RANGE";
    return statusDescriptions;
}

// Function to check SOC boundaries
BatteryStatusCode checkStateOfChargeBounds(float stateOfCharge) {
    if (stateOfCharge < STATE_OF_CHARGE_MIN || stateOfCharge > STATE_OF_CHARGE_MAX) {
        return SOC_OUT_OF_RANGE;
    }
    return NORMAL;
}

// Function to check SOC warnings
BatteryStatusCode checkStateOfChargeWarnings(float stateOfCharge) {
    if (stateOfCharge < STATE_OF_CHARGE_MIN + SOC_WARNING_MIN_TOLERANCE) {
        return LOW_SOC_WARNING;
    } 
    if (stateOfCharge > STATE_OF_CHARGE_MAX - SOC_WARNING_MAX_TOLERANCE) {
        return HIGH_SOC_WARNING;
    }
    return NORMAL;
}

// Function to get SOC status
BatteryStatusCode getStateOfChargeStatus(float stateOfCharge) {
    BatteryStatusCode status = checkStateOfChargeBounds(stateOfCharge);
    if (status != NORMAL) {
        return status;
    }
    return checkStateOfChargeWarnings(stateOfCharge);
}

// Function to get temperature status
BatteryStatusCode getTemperatureStatus(float temperature) {
    if (temperature > TEMPERATURE_MAX) {
        return TEMPERATURE_OUT_OF_RANGE;
    }
    if (temperature > TEMPERATURE_MAX - TEMPERATURE_WARNING_TOLERANCE) {
        return TEMPERATURE_WARNING;
    }
    return NORMAL;
}

// Function to get charge rate status
BatteryStatusCode getChargeRateStatus(float chargeRate) {
    if (chargeRate > CHARGE_RATE_MAX) {
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    if (chargeRate > CHARGE_RATE_MAX - CHARGE_RATE_WARNING_TOLERANCE) {
        return CHARGE_RATE_WARNING;
    }
    return NORMAL;
}

// Function to get the highest priority status
BatteryStatusCode getHighestPriorityStatus(BatteryStatusCode firstStatus, BatteryStatusCode secondStatus) {
    if (firstStatus != NORMAL) return firstStatus;
    return secondStatus;
}

// Function to get overall battery status
BatteryStatusCode getOverallBatteryStatus(float stateOfCharge, float temperature, float chargeRate) {
    BatteryStatusCode stateOfChargeStatus = getStateOfChargeStatus(stateOfCharge);
    BatteryStatusCode temperatureStatus = getTemperatureStatus(temperature);
    BatteryStatusCode chargeRateStatus = getChargeRateStatus(chargeRate);

    // Combine the status codes to get the highest priority status
    BatteryStatusCode status = getHighestPriorityStatus(stateOfChargeStatus, temperatureStatus);
    return getHighestPriorityStatus(status, chargeRateStatus);
}

// Function to validate the battery system
BatteryStatusCode validateBatterySystem(float stateOfCharge, float temperature, float chargeRate) {
    return getOverallBatteryStatus(stateOfCharge, temperature, chargeRate);
}

// Function to check if the battery is OK
bool isBatteryOk(float stateOfCharge, float temperature, float chargeRate) {
    return validateBatterySystem(stateOfCharge, temperature, chargeRate) == NORMAL;
}

// Function to get a descriptive string for BatteryStatusCode
std::string statusCodeToString(BatteryStatusCode status) {
    auto statusDescriptions = createStatusDescriptionMap();
    return statusDescriptions.at(status);
}

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
    assert(isBatteryOk(soc7, temp7, chargeRate7) == false); // SOC just at threshold, temperature just at threshold, charge rate within range

    float soc8 = 80, temp8 = 45, chargeRate8 = 0.8;
    BatteryStatusCode status8 = validateBatterySystem(soc8, temp8, chargeRate8);
    std::cout << "SOC: " << soc8 << ", Temp: " << temp8 << ", Charge Rate: " << chargeRate8
              << " -> Status: " << statusCodeToString(status8) << std::endl;
    assert(isBatteryOk(soc8, temp8, chargeRate8) == false); // SOC just at threshold, temperature within range, charge rate within range

    float soc9 = 19, temp9 = 30, chargeRate9 = 0.79;
    BatteryStatusCode status9 = validateBatterySystem(soc9, temp9, chargeRate9);
    std::cout << "SOC: " << soc9 << ", Temp: " << temp9 << ", Charge Rate: " << chargeRate9
              << " -> Status: " << statusCodeToString(status9) << std::endl;
    assert(isBatteryOk(soc9, temp9, chargeRate9) == false); // SOC below threshold

    float soc10 = 21, temp10 = 46, chargeRate10 = 0.81;
    BatteryStatusCode status10 = validateBatterySystem(soc10, temp10, chargeRate10);
    std::cout << "SOC: " << soc10 << ", Temp: " << temp10 << ", Charge Rate: " << chargeRate10
              << " -> Status: " << statusCodeToString(status10) << std::endl;
    assert(isBatteryOk(soc10, temp10, chargeRate10) == false); // SOC just above threshold, temperature out of range, charge rate out of range

    // Test cases with different combinations of tolerance thresholds
    float soc11 = 25, temp11 = 42, chargeRate11 = 0.76;
    BatteryStatusCode status11 = validateBatterySystem(soc11, temp11, chargeRate11);
    std::cout << "SOC: " << soc11 << ", Temp: " << temp11 << ", Charge Rate: " << chargeRate11
              << " -> Status: " << statusCodeToString(status11) << std::endl;
    assert(isBatteryOk(soc11, temp11, chargeRate11) == true); // SOC and charge rate within range, temperature within warning tolerance

    float soc12 = 24.5, temp12 = 44, chargeRate12 = 0.77;
    BatteryStatusCode status12 = validateBatterySystem(soc12, temp12, chargeRate12);
    std::cout << "SOC: " << soc12 << ", Temp: " << temp12 << ", Charge Rate: " << chargeRate12
              << " -> Status: " << statusCodeToString(status12) << std::endl;
    assert(isBatteryOk(soc12, temp12, chargeRate12) == false); // SOC within warning tolerance, temperature within range, charge rate within range

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
