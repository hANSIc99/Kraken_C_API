#ifndef __url_h
#define __url_h

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "logging.h"
#include "kraken_api.h"

#define TRUE 1
#define FALSE 0

int make_url(struct kraken_api **kr_data);
char *to_url(char* dest, const char *source);

#endif
