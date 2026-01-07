#ifndef METER_SERIALIZER_H
#define METER_SERIALIZER_H
#include <stddef.h> 
#include <stdint.h> 

typedef struct {
    const char* gatewayId;
    const char* date;
    const char* deviceType;
    int interval_minutes;
    int total_readings;
} GatewayMeta;

typedef struct {
    const char* timestamp;
    const char* meter_datetime;
    float total_m3;
    const char* status;
} MeterReading;

typedef struct {
    const char* media;
    const char* meter_type;
    const char* deviceId;
    const char* unit;
    MeterReading* reading_list; 
    int reading_count;
} DeviceData;

int serialize_meter_data(const GatewayMeta* meta, const DeviceData* devices, int device_count, char* buffer, size_t bufferSize);

#endif