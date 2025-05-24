#include <stdio.h>

#include "enet.h"
#include "enet_unit_times.c"

int main() {
    if (enet_initialize() != 0) {
        printf("An error occurred while initializing ENet.\n");
        return 1;
    }

    test_times();
}
