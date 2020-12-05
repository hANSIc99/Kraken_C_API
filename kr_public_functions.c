#include "kr_public_functions.h"


int server_time(struct kraken_api **kr_api){

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_server_time);

	PTRACEX("server time executed: %s", (*kr_api)->tmp_query_url);
	query_public(kr_api);

	return 0;
}

int system_status(struct kraken_api **kr_api){

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_system_status);

	PTRACEX("system status executed: %s", (*kr_api)->tmp_query_url);
	query_public(kr_api);

	return 0;
}

int asset_info(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[INFO].b_flag	= TRUE;
	(*kr_api)->opt_table[ACLASS].b_flag	= TRUE;
	(*kr_api)->opt_table[ASSET].b_flag	= TRUE;

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_asset_info);
	
	/* set the recursive counter to zero */

	/* check if optionals are given */	
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_public(kr_api);

	return 0;
}

int asset_pairs(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[INFO].b_flag	= TRUE;
	(*kr_api)->opt_table[PAIR].b_flag	= TRUE;

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_asset_pairs);
	
	/* set the recursive counter to zero */

	/* check if optionals are given */	
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_public(kr_api);

	return 0;
}

int ticker_info(struct kraken_api **kr_api, const char *pair){

	const char* url_pair = "pair=";

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_ticker);

	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_pair);
	(*kr_api)->s_data = to_url((*kr_api)->s_data, pair);

	query_public(kr_api);

	return 0;
}


int ohlc_data(struct kraken_api **kr_api, const char *pair){

	const char* url_pair = "pair=";

	(*kr_api)->opt_table[INTERVAL].b_flag	= TRUE;
	(*kr_api)->opt_table[SINCE].b_flag	= TRUE;

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_ohlc);

	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_pair);
	(*kr_api)->s_data = to_url((*kr_api)->s_data, pair);

	/* set the recursive counter to zero */

	/* check if optionals are given */	
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_public(kr_api);

	return 0;
}


int order_book(struct kraken_api **kr_api, const char *pair){

	const char* url_pair = "pair=";

	(*kr_api)->opt_table[COUNT].b_flag	= TRUE;
	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_order_book);

	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_pair);
	(*kr_api)->s_data = to_url((*kr_api)->s_data, pair);

	/* set the recursive counter to zero */

	/* check if optionals are given */	
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_public(kr_api);

	return 0;
}


int recent_trades(struct kraken_api **kr_api, const char *pair){

	const char* url_pair = "pair=";

	(*kr_api)->opt_table[SINCE].b_flag	= TRUE;
	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_recent_trades);

	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_pair);
	(*kr_api)->s_data = to_url((*kr_api)->s_data, pair);

	/* set the recursive counter to zero */

	/* check if optionals are given */	
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_public(kr_api);

	return 0;
}


int spread_data(struct kraken_api **kr_api, const char *pair){

	const char* url_pair = "pair=";

	(*kr_api)->opt_table[SINCE].b_flag	= TRUE;
	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_spread);

	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_pair);
	(*kr_api)->s_data = to_url((*kr_api)->s_data, pair);

	/* set the recursive counter to zero */

	/* check if optionals are given */	
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_public(kr_api);

	return 0;
}
