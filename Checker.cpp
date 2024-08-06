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
    BatteryStatusCode status1 = printBatteryStatus(25, 40, 0.7);
    assert(isBatteryOk(25, 40, 0.7) == true); // SOC and charge rate within range, temperature within range

    BatteryStatusCode status2 = printBatteryStatus(50, 85, 0);
    assert(isBatteryOk(50, 85, 0) == false); // Temperature out of range

    // Additional test cases
    BatteryStatusCode status3 = printBatteryStatus(22, 30, 0.5);   // Temperature within range, SOC within range, charge rate within range
    assert(isBatteryOk(22, 30, 0.5) == true);

    BatteryStatusCode status4 = printBatteryStatus(0, 20, 0.9);    // Temperature out of range, SOC within range, charge rate out of range
    assert(isBatteryOk(0, 20, 0.9) == false);

    BatteryStatusCode status6 = printBatteryStatus(35, 75, 0.85);  // Temperature within range, SOC within range, charge rate out of range
    assert(isBatteryOk(35, 75, 0.85) == false);

    // Testing edge cases
    BatteryStatusCode status7 = printBatteryStatus(20, 45, 0.8);    // Minimum SOC, maximum temperature within range, maximum charge rate within range
    assert(isBatteryOk(20, 45, 0.8) == false);      // SOC just at threshold, temperature just at threshold, charge rate within range

    BatteryStatusCode status8 = printBatteryStatus(80, 45, 0.8);    // Maximum SOC, maximum temperature within range, maximum charge rate within range
    assert(isBatteryOk(80, 45, 0.8) == false);      // SOC just at threshold, temperature within range, charge rate within range

    BatteryStatusCode status9 = printBatteryStatus(19, 30, 0.79);   // SOC just below minimum, temperature within range, charge rate within range
    assert(isBatteryOk(19, 30, 0.79) == false);     // SOC below threshold

    BatteryStatusCode status10 = printBatteryStatus(21, 46, 0.81);  // SOC just above minimum, temperature just above maximum, charge rate just above maximum
    assert(isBatteryOk(21, 46, 0.81) == false);     // SOC just above threshold, temperature out of range, charge rate out of range

    // Test cases with different combinations of tolerance thresholds
    BatteryStatusCode status11 = printBatteryStatus(25, 42, 0.76);  // SOC and charge rate within range, temperature within warning tolerance
    assert(isBatteryOk(25, 42, 0.76) == true);      // SOC and charge rate within range, temperature within warning tolerance

    BatteryStatusCode status12 = printBatteryStatus(24.5, 44, 0.77); // SOC within warning tolerance, temperature within range, charge rate within range
    assert(isBatteryOk(24.5, 44, 0.77) == false);    // SOC within warning tolerance, temperature within range, charge rate within range

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
