#include "config.h"
#include <jsmn.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

bool config_initted = false;

// Data

char* username;
char* password;
char* ip;
char* name;
int port;
int x;
int y;

// Init stuff
bool initConfig() {
    return initConfigFromFile("config.json");
}

bool initConfigFromFile(const char* filename) {
    FILE* file = fopen(filename,"r");

    fseek(file, 0, SEEK_END);
    size_t flength = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* config_str = (char*)malloc(flength*sizeof(char));

    size_t total_read = fread(config_str,sizeof(char),flength,file);

    if (total_read != flength) {
        printf("Couldn't load config file");
        return false;
    }

    jsmn_parser p;
    jsmntok_t tokens[128];

    jsmn_init(&p);
    int ret_val = jsmn_parse(&p, config_str, strlen(config_str), tokens, 128);

    if (ret_val < 0) {
        return false;
    }

    for (int i = 1; i < 128; i++) {
        jsmntok_t token = tokens[i];
        char *json_str = (char *) malloc((token.end - token.start) + 1);
        if (json_str != NULL) {
            json_str[token.end - token.start] = '\0';
            memcpy(json_str, &config_str[token.start], token.end - token.start);
            if (strcmp(json_str,"screen") == 0) {
                jsmntok_t x_tok = tokens[i+3];
                char *x_str = (char *) malloc((x_tok.end - x_tok.start) + 1);
                x_str[x_tok.end - x_tok.start] = '\0';
                memcpy(x_str, &config_str[x_tok.start], x_tok.end - x_tok.start);

                jsmntok_t y_tok = tokens[i+5];
                char *y_str = (char *) malloc((y_tok.end - y_tok.start) + 1);
                y_str[y_tok.end - y_tok.start] = '\0';
                memcpy(y_str, &config_str[y_tok.start], y_tok.end - y_tok.start);

                x = atoi(x_str);
                y = atoi(y_str);

                printf("x = %d\ny = %d\n",x,y);
            }
            else if (strcmp(json_str,"network") == 0) {

            }
            else if (strcmp(json_str,"auth") == 0) {

            }
            else if (strcmp(json_str,"ident") == 0) {

            }
        }
    }
    return true;
}

// Digest auth
const char* getUsername() {
    return config_initted ? username : "";
}

const char* getPassword() {
    return config_initted ? password : "";
}

// Networking
const char* getIp() {
    return config_initted ? ip : "";
}

int getPort() {
    return config_initted ? port : 17420;
}

// Identification
const char* getName() {
    return config_initted ? name : "";
}

// Graphics
int getScreenSizeX() {
    return config_initted ? x : 640;
}

int getScreenSizeY() {
    return config_initted ? y : 480;
}