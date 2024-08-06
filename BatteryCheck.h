#ifndef BATTERYCHECK_H
#define BATTERYCHECK_H

#include "BatteryStatus.h"

const float STATE_OF_CHARGE_MIN = 20.0f;
const float STATE_OF_CHARGE_MAX = 80.0f;
const float SOC_WARNING_MAX_TOLERANCE = 0.05f * STATE_OF_CHARGE_MAX;
const float SOC_WARNING_MIN_TOLERANCE = 0.05f * STATE_OF_CHARGE_MIN;

const float TEMPERATURE_MAX = 45.0f;
const float TEMPERATURE_WARNING_TOLERANCE = 0.05f * TEMPERATURE_MAX;

const float CHARGE_RATE_MAX = 0.8f;
const float CHARGE_RATE_WARNING_TOLERANCE = 0.05f * CHARGE_RATE_MAX;

BatteryStatusCode checkStateOfChargeBounds(float stateOfCharge);
BatteryStatusCode checkStateOfChargeWarnings(float stateOfCharge);
BatteryStatusCode getStateOfChargeStatus(float stateOfCharge);
BatteryStatusCode getTemperatureStatus(float temperature);
BatteryStatusCode getChargeRateStatus(float chargeRate);
BatteryStatusCode getHighestPriorityStatus(BatteryStatusCode firstStatus, BatteryStatusCode secondStatus);
BatteryStatusCode getOverallBatteryStatus(float stateOfCharge, float temperature, float chargeRate);
BatteryStatusCode validateBatterySystem(float stateOfCharge, float temperature, float chargeRate);
bool isBatteryOk(float stateOfCharge, float temperature, float chargeRate);

#endif // BATTERYCHECK_H
