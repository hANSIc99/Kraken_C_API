#include "kraken_api.h"
#include "kr_private_trading_functions.h"
#include "kr_private_user_functions.h"
#include "kr_public_functions.h"
#include "url.h"

static struct st_opt_list options_listen_table[] = {
	[INFO]          = {.name = "info",        .b_flag =   FALSE,  .key = "info=",             .val = NULL },
	[ACLASS]        = {.name = "aclass",      .b_flag =   FALSE,  .key = "aclass=",           .val = NULL },
	[ASSET]         = {.name = "asset",       .b_flag =   FALSE,  .key = "asset=",            .val = NULL },
	[TRADES]        = {.name = "trades",      .b_flag =   FALSE,  .key = "trades=",           .val = NULL },
	[USERREF]       = {.name = "userref",     .b_flag =   FALSE,  .key = "userref=",          .val = NULL },
	[START]         = {.name = "start",       .b_flag =   FALSE,  .key = "start=",            .val = NULL },
	[END]           = {.name = "end",         .b_flag =   FALSE,  .key = "end=",              .val = NULL },
	[OFS]           = {.name = "ofs",         .b_flag =   FALSE,  .key = "ofs=",              .val = NULL },
	[CLOSETIME]     = {.name = "closetime",   .b_flag =   FALSE,  .key = "closetime=",        .val = NULL },
	[DOCALCS]       = {.name = "docalcs",     .b_flag =   FALSE,  .key = "docalcs=",          .val = NULL },
	[PAIR]          = {.name = "pair",        .b_flag =   FALSE,  .key = "pair=",             .val = NULL },
	[FEE_INFO]      = {.name = "fee-info",    .b_flag =   FALSE,  .key = "fee-info=",         .val = NULL },
	[OFLAGS]        = {.name = "oflags",      .b_flag =   FALSE,  .key = "oflags=",           .val = NULL },
	[STARTTM]       = {.name = "starttm",     .b_flag =   FALSE,  .key = "starttm=",          .val = NULL },
	[EXPIRETM]      = {.name = "expiretm",    .b_flag =   FALSE,  .key = "expiretm=",         .val = NULL },
	[VALIDATE]      = {.name = "validate",    .b_flag =   FALSE,  .key = "validate=",         .val = NULL },
	[LEVERAGE]      = {.name = "leverage",    .b_flag =   FALSE,  .key = "leverage=",         .val = NULL },
	[TYPE]          = {.name = "type",        .b_flag =   FALSE,  .key = "type=",             .val = NULL },
	[CLOSE_TYPE]    = {.name = "close-type",  .b_flag =   FALSE,  .key = "close[ordertype]=", .val = NULL },
	[CLOSE_PRICE_1] = {.name = "close-pc-1",  .b_flag =   FALSE,  .key = "close[price]=",     .val = NULL },
	[CLOSE_PRICE_2] = {.name = "close-pc-2",  .b_flag =   FALSE,  .key = "close[price2]=",    .val = NULL },
	[INTERVAL]      = {.name = "interval",    .b_flag =   FALSE,  .key = "interval=",         .val = NULL },
	[SINCE]         = {.name = "since",       .b_flag =   FALSE,  .key = "since=",            .val = NULL },
	[COUNT]         = {.name = "count",       .b_flag =   FALSE,  .key = "count=",            .val = NULL }
};

#define SZ_LIST_TABLE (sizeof(options_listen_table))

#undef NKEYS
#define NKEYS (uint8_t)(sizeof(options_listen_table)/sizeof(options_listen_table[1]))

int kraken_init(struct kraken_api **kr_api, const char *api_key, const char *sec_key){

	PTRACEX("INFO NKEYS = %u", NKEYS);

	if(!((*kr_api) = malloc(sizeof(struct kraken_api)))){
		PERROR("ERROR on malloc");
		return -1;
	}

	(*kr_api)->priv_func = NULL;
	(*kr_api)->pub_func = NULL;
	(*kr_api)->priv_opt_list = NULL;

	if(((*kr_api)->opt_table = malloc(SZ_LIST_TABLE)) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}

	if(((*kr_api)->priv_func = malloc(sizeof(struct private_functions))) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}

	if(((*kr_api)->pub_func = malloc(sizeof(struct public_functions))) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}

	/* initialise the api-keys */
	(*kr_api)->s_api_key = NULL;
	(*kr_api)->s_sec_key = NULL;

	if(!(api_key || sec_key)){
		PERROR("No String found on api_key or sec_key");
		return -1;
	}

	(*kr_api)->s_api_key = strdup(api_key);
	(*kr_api)->s_sec_key = strdup(sec_key);
	
	/* initialize with default values */
	(*kr_api)->s_url            = NULL;
	(*kr_api)->s_data           = NULL;
	(*kr_api)->s_result         = NULL;
	(*kr_api)->s_uri_private    = NULL;
	(*kr_api)->s_uri_addorder   = NULL;
	(*kr_api)->tmp_query_url    = NULL;

	/* create opt_listen_table  */
	memcpy((*kr_api)->opt_table, options_listen_table, SZ_LIST_TABLE);

	/* set table lenght */
	(*kr_api)->opt_table_lenght = NKEYS;

	/* assign the private functions */
	(*kr_api)->priv_func->add_order           = &addOrder;
	(*kr_api)->priv_func->cancel_order        = &cancelOrder;
	(*kr_api)->priv_func->get_account_balance = &account_balance;
	(*kr_api)->priv_func->get_trade_balance   = &trade_balance;
	(*kr_api)->priv_func->get_open_orders     = &open_orders;
	(*kr_api)->priv_func->get_closed_orders   = &closed_orders;
	(*kr_api)->priv_func->query_order_info    = &query_orders;
	(*kr_api)->priv_func->get_trades_history  = &trades_history;
	(*kr_api)->priv_func->query_trades_info   = &trades_info;
	(*kr_api)->priv_func->get_open_positions  = &open_positions;
	(*kr_api)->priv_func->get_ledgers_info    = &ledgers_info;
	(*kr_api)->priv_func->query_ledgers       = &query_ledgers;
	(*kr_api)->priv_func->get_trade_volume    = &trade_volume;

	/* assign the public functions */
	(*kr_api)->pub_func->get_server_time          = &server_time;
	(*kr_api)->pub_func->get_system_status        = &system_status;
	(*kr_api)->pub_func->get_asset_info           = &asset_info;
	(*kr_api)->pub_func->get_tradable_asset_pairs = &asset_pairs;
	(*kr_api)->pub_func->get_ticker_info          = &ticker_info;
	(*kr_api)->pub_func->get_ohlc_data            = &ohlc_data;
	(*kr_api)->pub_func->get_order_book           = &order_book;
	(*kr_api)->pub_func->get_recent_trades        = &recent_trades;
	(*kr_api)->pub_func->get_recent_spread_data   = &spread_data;

	make_url(kr_api);

	return 0;
}

int kraken_set_opt(struct kraken_api **kr_api, const char* opt, const char* val){

	int option;
	char* tmp_ptr;

	if((option = key_from_string(opt, options_listen_table, NKEYS)) < 0){
		PDEBUG("ERROR: option unknown");
		return -1;
	}

	PTRACEX("option found: %s", (*kr_api)->opt_table[option].name);

	/* check if there is already a variable stored */
	if((tmp_ptr = (*kr_api)->opt_table[option].val)) free(tmp_ptr);


	(*kr_api)->opt_table[option].val = strdup(val);
	PTRACEX("value set: %s", (*kr_api)->opt_table[option].val);

	return 0;

}

void kraken_clean(struct kraken_api **kr_api){

	PTRACE("API CLEANUP");
	char* tmp_ptr = NULL;

	free((*kr_api)->priv_func);
	free((*kr_api)->pub_func);

	free((*kr_api)->s_api_key);
	free((*kr_api)->s_sec_key);

	free((*kr_api)->s_uri_private);
	free((*kr_api)->s_uri_public);
	free((*kr_api)->s_url);
	
	/* PRIVATE USER TRADING */
	free((*kr_api)->s_uri_addorder);
	free((*kr_api)->s_uri_cancel_order);
	free((*kr_api)->s_uri_open_orders);
	free((*kr_api)->s_uri_closed_orders);
	free((*kr_api)->s_uri_query_orders);
	free((*kr_api)->s_uri_trades_history);
	free((*kr_api)->s_uri_query_trades_info);
	free((*kr_api)->s_uri_open_positions);
	free((*kr_api)->s_uri_ledgers_info);
	free((*kr_api)->s_uri_query_ledgers);
	free((*kr_api)->s_uri_trade_volume);

	/* PRIVATE USER DATA */
	free((*kr_api)->s_uri_balance);
	free((*kr_api)->s_uri_trade_balance);

	/* PUBLIC MARKET DATA */
	free((*kr_api)->s_uri_server_time);
	free((*kr_api)->s_uri_system_status);
	free((*kr_api)->s_uri_asset_info);
	free((*kr_api)->s_uri_asset_pairs);
	free((*kr_api)->s_uri_ticker);
	free((*kr_api)->s_uri_ohlc);
	free((*kr_api)->s_uri_order_book);
	free((*kr_api)->s_uri_recent_trades);
	free((*kr_api)->s_uri_spread);

	/* BUFFER */
	if((*kr_api)->s_result != NULL) free((*kr_api)->s_result);

	/* OPTIONALS */
	for(uint8_t u8_i = 0; u8_i < (*kr_api)->opt_table_lenght; u8_i++)
		if((tmp_ptr = (*kr_api)->opt_table[u8_i].val)) free(tmp_ptr);

	free((*kr_api)->opt_table);

	free(*kr_api);
}


/* helper functions to find names in the lookuptable */
int key_from_string(const char *str, const struct st_opt_list *type_table, const uint8_t u8_n_keys){

	char* tmp_str = NULL;
	char* check_str = NULL;
	
	tmp_str = strdup(str);
	check_str = tmp_str ;

	/* convert to lower case chars */
	for( ; *tmp_str; ++tmp_str) *tmp_str = tolower(*tmp_str);

	for(uint8_t u8_i = 0; u8_i <  u8_n_keys; u8_i++){

		const struct st_opt_list *typ = type_table + u8_i;

		if(!(strcmp(typ->name, check_str))){
			free(check_str);
			return u8_i;
		}
	}
	
	free(check_str);
	return BADARG;
}
