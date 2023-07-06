#ifndef SYSTEM_H
#define SYSTEM_H

#include "stdint.h"
#include "stdbool.h"

#define CPU_FREQ      (72000000)
#define SYSTICK_FREQ  (1000)

void system_setup(void);
uint64_t system_get_ticks(void);


#endif // HEADER_H
