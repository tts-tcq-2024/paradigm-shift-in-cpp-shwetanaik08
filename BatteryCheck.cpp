#include "BatteryCheck.h"

BatteryStatusCode checkStateOfChargeBounds(float stateOfCharge) {
    if (stateOfCharge < STATE_OF_CHARGE_MIN || stateOfCharge > STATE_OF_CHARGE_MAX) {
        return SOC_OUT_OF_RANGE;
    }
    return NORMAL;
}

BatteryStatusCode checkStateOfChargeWarnings(float stateOfCharge) {
    if (stateOfCharge < STATE_OF_CHARGE_MIN + SOC_WARNING_MIN_TOLERANCE) {
        return LOW_SOC_WARNING;
    } 
    if (stateOfCharge > STATE_OF_CHARGE_MAX - SOC_WARNING_MAX_TOLERANCE) {
        return HIGH_SOC_WARNING;
    }
    return NORMAL;
}

BatteryStatusCode getStateOfChargeStatus(float stateOfCharge) {
    BatteryStatusCode status = checkStateOfChargeBounds(stateOfCharge);
    if (status != NORMAL) {
        return status;
    }
    return checkStateOfChargeWarnings(stateOfCharge);
}

BatteryStatusCode getTemperatureStatus(float temperature) {
    if (temperature > TEMPERATURE_MAX) {
        return TEMPERATURE_OUT_OF_RANGE;
    }
    if (temperature > TEMPERATURE_MAX - TEMPERATURE_WARNING_TOLERANCE) {
        return TEMPERATURE_WARNING;
    }
    return NORMAL;
}

BatteryStatusCode getChargeRateStatus(float chargeRate) {
    if (chargeRate > CHARGE_RATE_MAX) {
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    if (chargeRate > CHARGE_RATE_MAX - CHARGE_RATE_WARNING_TOLERANCE) {
        return CHARGE_RATE_WARNING;
    }
    return NORMAL;
}

BatteryStatusCode getHighestPriorityStatus(BatteryStatusCode firstStatus, BatteryStatusCode secondStatus) {
    if (firstStatus != NORMAL) return firstStatus;
    return secondStatus;
}

BatteryStatusCode getOverallBatteryStatus(float stateOfCharge, float temperature, float chargeRate) {
    BatteryStatusCode stateOfChargeStatus = getStateOfChargeStatus(stateOfCharge);
    BatteryStatusCode temperatureStatus = getTemperatureStatus(temperature);
    BatteryStatusCode chargeRateStatus = getChargeRateStatus(chargeRate);

    // Combine the status codes to get the highest priority status
    BatteryStatusCode status = getHighestPriorityStatus(stateOfChargeStatus, temperatureStatus);
    return getHighestPriorityStatus(status, chargeRateStatus);
}

BatteryStatusCode validateBatterySystem(float stateOfCharge, float temperature, float chargeRate) {
    return getOverallBatteryStatus(stateOfCharge, temperature, chargeRate);
}

bool isBatteryOk(float stateOfCharge, float temperature, float chargeRate) {
    return validateBatterySystem(stateOfCharge, temperature, chargeRate) == NORMAL;
}
