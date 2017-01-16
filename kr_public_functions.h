#ifndef __public_functions_h
#define __public_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "kr_helper.h"
#include "logging.h"
#include "url.h"
#include "curl.h"

int server_time(struct kraken_api **kr_api);
int asset_info(struct kraken_api **kr_api);
int asset_pairs(struct kraken_api **kr_api);




#endif
