#ifndef __kraken_api_h
#define __kraken_api_h

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "logging.h"

#define TRUE	1
#define FALSE	0

#define INFO		0
#define ACLASS		1
#define ASSET		2
#define TRADES		3
#define USERREF		4
#define START		5
#define END		6
#define OFS		7
#define CLOSETIME	8
#define DOCALCS		9
#define PAIR		10
#define FEE_INFO	11
#define OFLAGS		12
#define STARTTM		13
#define EXPIRETM	14
#define VALIDATE	15
#define LEVERAGE	16
#define TYPE		17
#define CLOSE_TYPE	18
#define CLOSE_PRICE_1	19
#define CLOSE_PRICE_2	20
#define INTERVAL	21
#define SINCE		22
#define COUNT		23

#define BADARG -1


/*!
 * \file kraken_api.h 
 * \brief Contains the definition of the API structures
 *
 * The structures are initialized in kraken_init() 
 *
 */

/*! \file kraken_api.c
 *  
 * \var st_opt_list options_listen_table[]
 * \brief Options Table
 *
 * This table contains all possible options that can be processed
 * by specific API calls.
 *
 */

/* this structure is used to distinguish diffrent commanline
 * arguments on kr_private_trading_functions
 * and on kr_private_user_functions */




struct st_opt_list {

	uint8_t	b_flag;	/*!< If true, then switch_opt will check for content */

	char*	name;	/*!< Overall name of the option */
	char*	key;	/*!< String which is called */
	char*	val;	/*!< Content which is appended to #key after in an REST call */
};

/* main api-structure */

struct kraken_api {

	struct private_functions *priv_func; 
	struct public_functions *pub_func;
	struct private_optionals *priv_opt;
	struct private_opt_listen *priv_opt_list;

	struct st_opt_list *opt_table;

	uint8_t opt_table_lenght;


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

	/* PUBLUC FUNTIONS */

	char* s_uri_server_time;	/* e.g. /Time */
	char* s_uri_asset_info;		/* e.g. /Assets */
	char* s_uri_asset_pairs;	/* e.g. /AssetPairs */
	char* s_uri_ticker;		/* e.g. /Ticker */
	char* s_uri_ohlc;		/* e.g. /OHLC */
	char* s_uri_order_book;		/* e.g. /Depth */
	char* s_uri_recent_trades;	/* e.g. /Trades */
	char* s_uri_spread;		/* e.g. /Spread */

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
	int (*get_trade_balance)(struct kraken_api**);
	int (*get_open_orders)(struct kraken_api**);
	int (*get_closed_orders)(struct kraken_api**);
	int (*query_order_info)(struct kraken_api**, const char*);
	int (*get_trades_history)(struct kraken_api**);
	int (*query_trades_info)(struct kraken_api**, const char*);
	int (*get_open_positions)(struct kraken_api**, const char*);
	int (*get_ledgers_info)(struct kraken_api**);
	int (*query_ledgers)(struct kraken_api**, const char*);
	int (*get_trade_volume)(struct kraken_api**);

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

	int (*get_server_time)(struct kraken_api**);
	int (*get_asset_info)(struct kraken_api**);
	int (*get_tradable_asset_pairs)(struct kraken_api**);
	int (*get_ticker_info)(struct kraken_api**, const char*);
	int (*get_ohlc_data)(struct kraken_api**, const char*);
	int (*get_order_book)(struct kraken_api**, const char*);
	int (*get_recent_trades)(struct kraken_api**, const char*);
	int (*get_recent_spread_data)(struct kraken_api**, const char*);

};

/*! 
 * \brief Initialization of the required structures
 * 
 * \param **kr_api Adress of a pointer to the appropriate structure (not initialized)
 *
 * \param *api_key API Key (log into kraken.com and go to settings->API)
 *
 * \param *sec_key Secret API key (log into kraken.com and go to settings->API)
 *
 * This functions initialize the required structures with the addresses for the api calls.
 * The memory which is allocated in this function will be freed in kraken_clean()
 *
 * */
int kraken_init(struct kraken_api **kr_api, const char *api_key, const char *sec_key);
/*! 
 * \brief De-initialization of the structures
 * 
 * \param **kr_api Adress of a pointer to the initialized structure.
 *
 *
 * This function frees the memory which was allocated by kraken_init().
 *
 * */
void kraken_clean(struct kraken_api **kr_api);
/*! 
 * \brief Helper function for the lookup-table
 * 
 * \param *str String to search for .
 * \param *type_table Lookup-table structure.
 * \param u8_n_keys Number of keywords in the lookup-table.
 *
 *
 * The function returns the number of the (defined) option.
 *
 * */
int key_from_string(const char *str, const struct st_opt_list *type_table, const uint8_t u8_n_keys);
/*! 
 * \brief Helper function to set optional arguments in api calls.
 *  
 * \param **kr_api Adress of a pointer to the initialized structure.
 * \param *opt Name of the optional to be set (to be found in lookup-table).
 *
 *
 * This function frees the memory which was allocated by kraken_init().\n\n
 *
 * Available options: \n
 * <b>info</b>\n
 * <b>aclass</b>\n
 * <b>asset</b>\n
 * <b>trades</b>\n
 * <b>userref</b>\n
 * <b>start</b>\n
 * <b>end</b>\n
 * <b>ofs</b>\n
 * <b>closetime</b>\n
 * <b>pair</b>\n
 * <b>fee-info</b>\n
 * <b>oflags</b>\n
 * <b>starttm</b>\n
 * <b>expiretm</b>\n
 * <b>validate</b>\n
 * <b>leverage</b>\n
 * <b>type</b>\n
 * <b>close-type</b>\n
 * <b>close-pc-1</b>\n
 * <b>close-pc-2</b>\n
 * <b>interval</b>\n
 * <b>since</b>\n
 * <b>count</b>\n
 *
 * */
int kraken_set_opt(struct kraken_api **kr_api, const char* opt, const char* val);




#endif
