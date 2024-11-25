#pragma once

#include <stdint.h>

void ads_begin();
int16_t ads_read(uint16_t channel);
