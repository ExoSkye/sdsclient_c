#pragma once

#include <stdbool.h>

bool netInit();
void netDelete();

const char* netGetConfig();
const char* netGetReload();