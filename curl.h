#ifndef __curl_h
#define __curl_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include "kraken_api.h"
#include "url.h"
#include "logging.h"

#define BUFFER_SIZE 4096

char* curl_get(char *query_string);
int query_private(struct kraken_api **kr_api);


#endif

