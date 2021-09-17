#include "config.h"

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
    return initConfigFromFile("config.yaml");
}

bool initConfigFromFile(const char* filename) {
    return false;
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