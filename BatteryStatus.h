#ifndef BATTERYSTATUS_H
#define BATTERYSTATUS_H

#include <map>
#include <string>

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

std::map<BatteryStatusCode, std::string> createStatusDescriptionMap();
std::string statusCodeToString(BatteryStatusCode status);

#endif // BATTERYSTATUS_H
