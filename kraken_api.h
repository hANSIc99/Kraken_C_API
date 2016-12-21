#ifndef __kraken_api_h
#define __kraken_api_h

#include "crypto.h"
#include <string.h>
#include <stdlib.h>
#include "logging.h"




struct kraken_api {

	struct private_functions *priv_func; 
	struct public_functions *pub_func;

	/* KEY'S */

	char* s_api_key;		/* account specific api-key */
	char* s_sec_key;		/* account specific secret key */

	/* GENERAL URI'S */

	char* s_uri_private;		/* e.g. /0/private */
	char* s_uri_public;		/* e.g. /0/public */
	char* s_url;			/* https://api.kraken.com */

	/* PRIVATE USER TRADING */

	char* s_uri_addorder;		/* e.g. /AddOrder */
	char* s_uri_cancel_order;	/* e.g. /CancelOrder */

	/* PRIVATE USER DATA */

	char* s_uri_balance;		/* e.g. /Balance */
	char* s_uri_trade_balance;	/* e.g. /TradeBalance */
	char* s_uri_open_orders;	/* e.g. /OpenOrders */
	char* s_uri_closed_orders;	/* e.g. /ClosedOrders */
	char* s_uri_query_orders;	/* e.g. /QueryOrders */
	char* s_uri_trades_history;	/* e.g. /TradesHistory */
	char* s_uri_query_trades_info;	/* e.g. /QueryTrades */
	char* s_uri_open_positions;	/* e.g. /OpenPositions */
	char* s_uri_ledgers_info;	/* e.g. /Ledgers */
	char* s_uri_query_ledgers;	/* e.g. /QueryLedgers */
	char* s_uri_trade_volume;	/* e.g. /TradeVolume */

	/* temporary arrays */

	char* tmp_query_url;		/* function specific url to query,
					  * not initialized */
	char* s_data;			/* e.g. pair=XXBTZEUR&type=buy 
					* not initialized! */
	/* BUFFER */

	char* s_result;			/* contains the answer from kraken */

};

struct private_functions {

	/* add_order = variable lenght argument list (p. 155 K&R) */

	/* order in function: type, ordertype, asset-pair */
	int (*add_order)(struct kraken_api**, const char*, const char*, const char*, const char*, ...);
	int (*cancel_order)(struct kraken_api**, int);

	int (*get_account_balance)(struct kraken_api**);
	int (*get_trade_balance)(struct kraken_api**, ...);
	int (*get_open_orders)(struct kraken_api**, int);
	int (*get_closed_orders)(struct kraken_api**, int);
	int (*query_order_info)(struct kraken_api**, int);
	int (*get_trades_history)(struct kraken_api**, int);
	int (*query_trades_info)(struct kraken_api**, int);
	int (*get_open_positions)(struct kraken_api**, int);
	int (*get_ledgers_info)(struct kraken_api**, int);
	int (*query_ledgers)(struct kraken_api**, int);
	int (*get_trade_volume)(struct kraken_api**, int);


};

struct public_functions {

	int (*get_server_time)(struct kraken_api*, int);
	int (*get_asset_info)(struct kraken_api*, int);
	int (*get_tradable_asset_pairs)(struct kraken_api*, int);
	int (*get_ticker_info)(struct kraken_api*, int);
	int (*get_ohlc_data)(struct kraken_api*, int);
	int (*get_order_book)(struct kraken_api*, int);
	int (*get_recent_trades)(struct kraken_api*, int);
	int (*get_recent_spread_data)(struct kraken_api*, int);

};


int kraken_init(struct kraken_api **kr_api, const char* api_key, const char *sec_key);
void kraken_clean(struct kraken_api **kr_api);




#endif
