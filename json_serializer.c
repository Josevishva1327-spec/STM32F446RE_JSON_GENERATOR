#include "json_serializer.h"
#include <stdio.h>

#define APPEND(fmt, ...) \
    do { \
        int n = snprintf(out + pos, out_size - pos, fmt, ##__VA_ARGS__); \
        if (n < 0 || (size_t)n >= out_size - pos) return JSON_ERR_BUFFER_TOO_SMALL; \
        pos += n; \
    } while (0)

JsonStatus serialize_gateway_payload(
    const GatewayPayload *p,
    char *out,
    size_t out_size,
    size_t *written_len)
{
    if (!p || !out) return JSON_ERR_INVALID_INPUT;

    size_t pos = 0;

    APPEND("[{");
    APPEND("\"gatewayId\":\"%s\",", p->gatewayId);
    APPEND("\"date\":\"%s\",", p->date);
    APPEND("\"deviceType\":\"%s\",", p->deviceType);
    APPEND("\"interval_minutes\":%u,", p->interval_minutes);
    APPEND("\"total_readings\":%u,", p->total_readings);

    APPEND("\"values\":{");
    APPEND("\"device_count\":%u,", p->values.device_count);
    APPEND("\"readings\":[");

    for (uint8_t i = 0; i < p->values.device_count; i++) {
    	const DeviceReading *d = &p->values.devices[i];

        APPEND("{");
        APPEND("\"media\":\"%s\",", d->media);
        APPEND("\"meter\":\"%s\",", d->meter);
        APPEND("\"deviceId\":\"%s\",", d->deviceId);
        APPEND("\"unit\":\"%s\",", d->unit);
        APPEND("\"data\":[");

        for (uint8_t j = 0; j < d->data_count; j++) {
        	const MeterDataPoint *dp = &d->data[j];

            APPEND("{");
            APPEND("\"timestamp\":\"%s\",", dp->timestamp);
            APPEND("\"meter_datetime\":\"%s\",", dp->meter_datetime);
            APPEND("\"total_m3\":%.3f,", dp->total_m3);
            APPEND("\"status\":\"%s\"", dp->status);
            APPEND("}");

            if (j < d->data_count - 1) APPEND(",");
        }

        APPEND("]}");
        if (i < p->values.device_count - 1) APPEND(",");
    }

    APPEND("]}");
    APPEND("}]");

    if (written_len) *written_len = pos;
    return JSON_OK;
}
