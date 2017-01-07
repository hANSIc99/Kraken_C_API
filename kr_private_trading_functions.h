#ifndef __kr_private_trading_functions_h
#define __kr_private_trading_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "logging.h"
#include "url.h"
#include "curl.h"
#include "crypto.h"
#include "kr_private_user_functions.h"

#define MARKET			0
#define LIMIT			1
#define STOP_LOSS		2
#define TAKE_PROFIT		3
#define STOP_LOSS_PROFIT	4
#define STOP_LOSS_PROFIT_LIMIT	5
#define STOP_LOSS_LIMIT		6
#define TAKE_PROFIT_LIMIT	7
#define TRAILING_STOP		8
#define TRAILING_STOP_LIMIT	9
#define STOP_LOSS_AND_LIMIT	10
#define SETTLE_POSITION		11
#define BADARG			-1


int addOrder(struct kraken_api **kr_api, const char *type, const char *order, const char *asset, const char* volume, ...);

int cancelOrder(struct kraken_api **kr_api, const char *txid);


#endif
