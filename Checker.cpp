#include <assert.h>
#include <iostream>
using namespace std;
 
bool isTemperatureOutOfRange(float temperature) {
  return temperature < 0 || temperature > 45;
}
 
bool isSocOutOfRange(float soc) {
  return soc < 20 || soc > 80;
}
 
bool isChargeRateOutOfRange(float chargeRate) {
  return chargeRate > 0.8;
}
 
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  return !isTemperatureOutOfRange(temperature) &&
         !isSocOutOfRange(soc) &&
         !isChargeRateOutOfRange(chargeRate);
}
 
 
int main() {
  // Test cases with expected results
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
 
  // Additional test cases
  assert(batteryIsOk(10, 30, 0.5) == true);   // Temperature within range, SOC within range, charge rate within range
  assert(batteryIsOk(0, 20, 0.9) == false);   // Temperature out of range, SOC within range, charge rate out of range
  assert(batteryIsOk(40, 10, 0.3) == false);  // Temperature within range, SOC out of range, charge rate within range
  assert(batteryIsOk(35, 75, 0.85) == false); // Temperature within range, SOC within range, charge rate out of range
 
  // Testing edge cases
  assert(batteryIsOk(0, 20, 0.8) == false);    // Minimum temperature, minimum SOC, maximum charge rate within range
  assert(batteryIsOk(45, 80, 0.8) == false);   // Maximum temperature, maximum SOC, maximum charge rate within range
  assert(batteryIsOk(-1, 19, 0.79) == false); // Temperature just below minimum, SOC just below minimum, charge rate within range
  assert(batteryIsOk(46, 81, 0.81) == false); // Temperature just above maximum, SOC just above maximum, charge rate just above maximum
  return 0;
 
  cout << "All test cases passed!\n";
}
