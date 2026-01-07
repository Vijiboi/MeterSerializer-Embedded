#include "MeterSerializer.h"
void setup() {
    Serial.begin(115200);
    while(!Serial); 
    Serial.println("Starting JSON Serialization Demo");
    MeterReading r1 = {"1970-01-01 00:00", "1970-01-01 00:00", 107.752, "OK"};
    MeterReading readings[] = { r1 }; 
    DeviceData d1 = {
        "water", "waterstarm", "stromleser_50898527", "m3",
        readings, 1 
    };
    DeviceData devices[] = { d1 };
    GatewayMeta meta = {
        "gateway_1234", "1970-01-01", "stromleser", 15, 1
    };

    char jsonOutput[1024]; 
    int result = serialize_meter_data(&meta, devices, 1, jsonOutput, sizeof(jsonOutput));
    if (result == 0) {
        Serial.println("Serialization Success:");
        Serial.println(jsonOutput);
    } else {
        Serial.println("Error: Buffer too small or invalid input.");
    }
}

void loop() {
    
}