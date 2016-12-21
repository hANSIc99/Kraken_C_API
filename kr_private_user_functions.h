#ifndef __kr_private_user_functions_h
#define __kr_private_user_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "logging.h"
#include "kraken_api.h"
#include "url.h"
#include "curl.h"
#include "crypto.h"
#include "kr_private_trading_functions.h"

int account_balance(struct kraken_api **kr_api);
int trade_balance(struct kraken_api **kr_api, ...);





#endif
