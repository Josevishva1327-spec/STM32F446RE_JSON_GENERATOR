#ifndef DATA_MODEL_H
#define DATA_MODEL_H

#include <stdint.h>

#define MAX_DEVICES     4
#define MAX_DATA_POINTS 8

typedef struct {
    char timestamp[20];
    char meter_datetime[20];
    float total_m3;
    char status[8];
} MeterDataPoint;

typedef struct {
    char media[16];
    char meter[16];
    char deviceId[32];
    char unit[8];
    uint8_t data_count;
    MeterDataPoint data[MAX_DATA_POINTS];
} DeviceReading;

typedef struct {
    uint8_t device_count;
    DeviceReading devices[MAX_DEVICES];
} MeasurementValues;

typedef struct {
    char gatewayId[32];
    char date[11];
    char deviceType[16];
    uint16_t interval_minutes;
    uint16_t total_readings;
    MeasurementValues values;
} GatewayPayload;

#endif
