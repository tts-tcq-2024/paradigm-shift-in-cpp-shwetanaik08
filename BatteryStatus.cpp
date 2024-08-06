#include "BatteryStatus.h"

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

std::string statusCodeToString(BatteryStatusCode status) {
    auto statusDescriptions = createStatusDescriptionMap();
    return statusDescriptions.at(status);
}
