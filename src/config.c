#include "config.h"
#include <jsmn.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "json_helper.h"

bool config_initted = false;

// Data

char* username;
char* password;
char* ip;
char* name;
char* scheme;
int port;
int x;
int y;

// Init stuff
bool initConfig() {
    return initConfigFromFile("config.json");
}

bool initConfigFromFile(const char* filename) {
    if (config_initted) {
        return false;
    }
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
        char *json_str = getStrRepr_JSON(tokens[i], config_str, flength);
        if (json_str != NULL) {
            if (strcmp(json_str,"screen") == 0) {
                char* x_str = NULL;
                char* y_str = NULL;
                for (int j = i; j < 128; j++){
                    char* str_repr = getStrRepr_JSON(tokens[j], config_str, flength);

                    if (strcmp(str_repr, "x") == 0) {
                        x_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }
                    else if (strcmp(str_repr, "y") == 0) {
                        y_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }
                    if (x_str != NULL && y_str != NULL) {
                        break;
                    }
                    free(str_repr);
                }

                x = atoi(x_str);
                y = atoi(y_str);

                free(x_str);
                free(y_str);

                printf("x = %d\ny = %d\n",x,y);
            }
            else if (strcmp(json_str,"network") == 0) {
                char* port_str = NULL;
                char* ip_str = NULL;
                char* scheme_str = NULL;

                for (int j = i; j < 128; j++){
                    char* str_repr = getStrRepr_JSON(tokens[j], config_str, flength);

                    if (strcmp(str_repr, "port") == 0) {
                        port_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }
                    else if (strcmp(str_repr, "ip") == 0) {
                        ip_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }
                    else if (strcmp(str_repr, "scheme") == 0) {
                        scheme_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }
                    if (port_str != NULL && ip_str != NULL && scheme_str != NULL) {
                        break;
                    }
                    free(str_repr);
                }

                port = atoi(port_str);
                free(port_str);
                ip = ip_str;
                scheme = scheme_str;
                printf("Server IP Address = %s://%s:%d\n",scheme,ip,port);
            }
            else if (strcmp(json_str,"auth") == 0) {
                char* username_str = NULL;
                char* pw_str = NULL;

                for (int j = i; j < 128; j++){
                    char* str_repr = getStrRepr_JSON(tokens[j], config_str, flength);

                    if (strcmp(str_repr, "user") == 0) {
                        username_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }
                    else if (strcmp(str_repr, "pass") == 0) {
                        pw_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }
                    if (username_str != NULL && pw_str != NULL) {
                        break;
                    }
                    free(str_repr);
                }

                username = username_str;
                password = pw_str;
                printf("Authentication details:\nUsername: %s\nPassword: %s\n",username,password);
            }
            else if (strcmp(json_str,"ident") == 0) {
                char* name_str = NULL;

                for (int j = i; j < 128; j++){
                    char* str_repr = getStrRepr_JSON(tokens[j], config_str, flength);

                    if (strcmp(str_repr, "name") == 0) {
                        name_str = getStrRepr_JSON(tokens[j + 1], config_str, flength);
                    }

                    if (name_str != NULL) {
                        break;
                    }
                    free(str_repr);
                }

                name = name_str;
                printf("Client name: %s\n",name);
            }
        }
        free(json_str);
    }
    free(config_str);
    config_initted = true;
    return true;
}

void freeConfig() {
    free(username);
    free(password);
    free(ip);
    free(name);
    config_initted = false;
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

const char* getScheme() {
    return config_initted ? scheme : "";
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