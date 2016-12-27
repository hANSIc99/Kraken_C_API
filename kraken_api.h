#ifndef __kraken_api_h
#define __kraken_api_h

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "logging.h"
#include "crypto.h"

#define TRUE	1
#define FALSE	0

#define ACLASS		1
#define ASSET		2
#define TRADES		3
#define USERREF		4
#define START		5
#define END		6
#define OFS		7
#define CLOSETIME	8
#define DOCALCS		10
#define PAIR		11
#define FEE_INFO	12
#define OFLAGS		13
#define STARTTM		14
#define EXPIRETM	15
#define VALIDATE	16
#define LEVERAGE	17
#define CLOSE_TYPE	18
#define CLOSE_PRICE_1	19
#define CLOSE_PRICE_2	20

#define BADARG -1

/* this structure is used to distinguish diffrent commanline
 * arguments on kr_private_trading_functions
 * and on kr_private_user_functions */

struct st_list {

	char *key;
	uint8_t val;
};

struct st_opt_list {

	uint8_t key;
	uint8_t val;
};





/* main api-structure */

struct kraken_api {

	struct private_functions *priv_func; 
	struct public_functions *pub_func;
	struct private_optionals *priv_opt;
	struct private_opt_listen *priv_opt_list;

	struct st_opt_list *opt_listen_table;
       




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
	int (*cancel_order)(struct kraken_api**, const char*);

	int (*get_account_balance)(struct kraken_api**);
	int (*get_trade_balance)(struct kraken_api**, ...);
	int (*get_open_orders)(struct kraken_api**);
	int (*get_closed_orders)(struct kraken_api**);
	int (*query_order_info)(struct kraken_api**, int);
	int (*get_trades_history)(struct kraken_api**, int);
	int (*query_trades_info)(struct kraken_api**, int);
	int (*get_open_positions)(struct kraken_api**, int);
	int (*get_ledgers_info)(struct kraken_api**, int);
	int (*query_ledgers)(struct kraken_api**, int);
	int (*get_trade_volume)(struct kraken_api**, int);

};



struct private_optionals {

	char* opt_aclass;
	char* opt_asset;
	char* opt_trades;
	char* opt_userref;
	char* opt_start;
	char* opt_end;
	char* opt_ofs;
	char* opt_closetime;
	char* opt_docalcs;
	char* opt_pair;
	char* opt_fee_info;
	char* opt_oflags;
	char* opt_starttm;
	char* opt_expiretm;
	char* opt_validate;
	char* opt_leverage;
	char* opt_close_type;
	char* opt_close_pc_1;
	char* opt_close_pc_2;
};
struct private_opt_listen {

	uint8_t bool_aclass;
	uint8_t bool_asset;
	uint8_t bool_trades;
	uint8_t bool_userref;
	uint8_t bool_start;
	uint8_t bool_end;
	uint8_t bool_ofs;
	uint8_t bool_closetime;
	uint8_t bool_docalcs;
	uint8_t bool_pair;
	uint8_t bool_fee_info;
	uint8_t bool_oflags;
	uint8_t bool_starttm;
	uint8_t bool_expiretm;
	uint8_t bool_validate;
	uint8_t bool_leverage;
	uint8_t bool_close_type;
	uint8_t bool_close_pc_1;
	uint8_t bool_close_pc_2;
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
int key_from_string(const char *str, const struct st_list *type_table, const uint8_t u8_n_keys);
int kraken_set_opt(struct kraken_api **kr_api, const char* opt, const char* val);




#endif
