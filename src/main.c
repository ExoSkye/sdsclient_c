#include "config.h"
#include "timepoints.h"
#include "netapi.h"

int main() {
    initConfig();
    netInit();
    netGetConfig();
    netDelete();
    freeConfig();
    return 0;
}
