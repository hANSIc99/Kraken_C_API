#ifndef __kr_private_trading_functions_h
#define __kr_private_trading_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "logging.h"
#include "kraken_api.h"
#include "url.h"
#include "curl.h"
#include "crypto.h"

#define MARKET			1
#define LIMIT			2
#define STOP_LOSS		3
#define TAKE_PROFIT		4
#define STOP_LOSS_PROFIT	5
#define STOP_LOSS_PROFIT_LIMIT	6
#define STOP_LOSS_LIMIT		7
#define TAKE_PROFIT_LIMIT	8
#define TRAILING_STOP		9
#define TRAILING_STOP_LIMIT	10
#define STOP_LOSS_AND_LIMIT	11
#define SETTLE_POSITION		12
#define BADARG			-1


int addOrder(struct kraken_api **kr_api, const char *type, const char *order, const char *asset, const char* volume, ...);

int cancelOrder(struct kraken_api **kr_api, const char *txid);


#endif
