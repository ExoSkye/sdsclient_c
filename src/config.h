#pragma once

#include <stdbool.h>

// Init stuff
bool initConfig();
bool initConfigFromFile(const char* filename);

// Digest auth
const char* getUsername();
const char* getPassword();

// Networking
const char* getIp();
int getPort();

// Identification
const char* getName();

// Graphics
int getScreenSizeX();
int getScreenSizeY();