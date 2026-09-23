#include "include/kstdio.h"
#include "include/system.h"

void sys_initializer() {
    /* Irroittavaa moniajoa ei käytetä batch-mallissa. */
    run_init();
}

void init() {
    sys_initializer();
    while (1) {
        
    }
}