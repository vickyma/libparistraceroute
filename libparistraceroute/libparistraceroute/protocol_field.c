#include "config.h"

#include <string.h> // memcpy
#include <stdio.h>  // fprintf

#include "protocol_field.h"

bool protocol_field_set(const protocol_field_t * protocol_field, uint8_t * buffer, const field_t * field)
{
    bool      ret = true;
    uint8_t * segment = buffer + protocol_field->offset;

    switch (protocol_field->type) {
        case TYPE_IPV4:
            memcpy(segment, &field->value.ipv4, sizeof(ipv4_t));
            break;
        case TYPE_IPV6:
            memcpy(segment, &field->value.ipv6, sizeof(ipv6_t));
            break;
        case TYPE_UINT8:
            *(uint8_t *) segment = field->value.int8;
            break;
        case TYPE_UINT16:
            *(uint16_t *) segment = htons(field->value.int16);
            break;
        case TYPE_UINT32:
            *(uint32_t *) segment = htonl(field->value.int32);
            break;
        case TYPE_UINT4:
        case TYPE_STRING:
        default:
            fprintf(stderr, "protocol_field_set: Type not supported");
            ret = false;
            break;
    }
    return ret;
}

inline size_t protocol_field_get_offset(const protocol_field_t * protocol_field) {
    return protocol_field->offset;
}

inline size_t protocol_field_get_size(const protocol_field_t * protocol_field) {
   return field_get_type_size(protocol_field->type);
}

void protocol_field_dump(const protocol_field_t * protocol_field) {
    printf("> %s\n", protocol_field->key);
}

