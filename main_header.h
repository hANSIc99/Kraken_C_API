#ifndef __main_header_h
#define __main_header_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "kraken_api.h"


size_t calcDecodeLength(const char* b64input);
int Base64Encode(const unsigned char* buffer, size_t length, char** b64text);


#endif
