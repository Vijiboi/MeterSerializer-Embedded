#include "MeterSerializer.h"
#include <stdio.h> 
#include <string.h> 

int serialize_meter_data(const GatewayMeta* meta, const DeviceData* devices, int device_count, char* buffer, size_t bufferSize) {
    int offset = 0;
    if (buffer == NULL || bufferSize == 0) return -1;

    int written = snprintf(buffer + offset, bufferSize - offset, 
        "[{\"gatewayId\":\"%s\",\"date\":\"%s\",\"deviceType\":\"%s\",\"interval minutes\":%d,\"total_readings\":%d,\"values\":{\"device_count\":%d,\"readings\":[",
        meta->gatewayId, meta->date, meta->deviceType, meta->interval_minutes, meta->total_readings, device_count);
    if (written < 0 || written >= (int)(bufferSize - offset)) return -1; 
    offset += written;

    for (int i = 0; i < device_count; i++) {
        const DeviceData* dev = &devices[i];
        if (i > 0) {
            written = snprintf(buffer + offset, bufferSize - offset, ",");
            if (written < 0 || written >= (int)(bufferSize - offset)) return -1;
            offset += written;
        }
        written = snprintf(buffer + offset, bufferSize - offset,
            "{\"media\":\"%s\",\"meter\":\"%s\",\"deviceId\":\"%s\",\"unit\":\"%s\",\"data\":[",
            dev->media, dev->meter_type, dev->deviceId, dev->unit);
        if (written < 0 || written >= (int)(bufferSize - offset)) return -1;
        offset += written;

        for (int j = 0; j < dev->reading_count; j++) {
            MeterReading* r = &dev->reading_list[j];

            if (j > 0) {
                written = snprintf(buffer + offset, bufferSize - offset, ",");
                if (written < 0 || written >= (int)(bufferSize - offset)) return -1;
                offset += written;
            }
            written = snprintf(buffer + offset, bufferSize - offset,
                "{\"timestamp\":\"%s\",\"meter datetime\":\"%s\",\"total m3\":%.3f,\"status\":\"%s\"}",
                r->timestamp, r->meter_datetime, r->total_m3, r->status);

            if (written < 0 || written >= (int)(bufferSize - offset)) return -1;
            offset += written;
        }
        written = snprintf(buffer + offset, bufferSize - offset, "] }");
        if (written < 0 || written >= (int)(bufferSize - offset)) return -1;
        offset += written;
    }
    written = snprintf(buffer + offset, bufferSize - offset, "] } } ]");
    if (written < 0 || written >= (int)(bufferSize - offset)) return -1;
    offset += written;

    return 0; 
}