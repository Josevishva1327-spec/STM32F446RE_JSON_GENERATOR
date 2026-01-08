#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>
#include "data_model.h"

typedef enum {
    JSON_OK = 0,
    JSON_ERR_BUFFER_TOO_SMALL,
    JSON_ERR_INVALID_INPUT
} JsonStatus;

JsonStatus serialize_gateway_payload(
    const GatewayPayload *payload,
    char *out,
    size_t out_size,
    size_t *written_len
);

#endif
