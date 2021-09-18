#pragma once

#include <stdbool.h>

// Init stuff
bool initConfig();
bool initConfigFromFile(const char* filename);
void freeConfig();

// Digest auth
const char* getUsername();
const char* getPassword();

// Networking
const char* getIp();
int getPort();
const char* getScheme();

// Identification
const char* getName();

// Graphics
int getScreenSizeX();
int getScreenSizeY();