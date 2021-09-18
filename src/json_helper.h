#pragma once

#include <string.h>
#include <jsmn.h>

char *getStrRepr_JSON(jsmntok_t token, const char *fileContent, size_t fileLength) {
    if (token.end <= fileLength) {
        char* str_repr = (char *) malloc((token.end - token.start) + 1);
        if (str_repr != NULL) {
            str_repr[token.end - token.start] = '\0';
            memcpy(str_repr, &fileContent[token.start], token.end - token.start);
        }
        return str_repr;
    }
    return NULL;
}