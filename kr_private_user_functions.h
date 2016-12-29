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

extern uint8_t u8_count;

void switch_opt(struct kraken_api **kr_api);

int account_balance(struct kraken_api **kr_api);
int trade_balance(struct kraken_api **kr_api, ...);
int open_orders(struct kraken_api **kr_api);
int closed_orders(struct kraken_api **kr_api);
int query_orders(struct kraken_api **kr_api, const char* txid);
int trades_history(struct kraken_api **kr_api);
int trades_info(struct kraken_api **kr_api, const char* txid);
int open_positions(struct kraken_api **kr_api, const char* txid);
int ledgers_info(struct kraken_api **kr_api);
int query_ledgers(struct kraken_api **kr_api, const char* id);
int trade_volume(struct kraken_api **kr_api);





#endif
