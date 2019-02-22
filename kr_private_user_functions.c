#include "kr_private_user_functions.h"

int account_balance(struct kraken_api **kr_api){

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_balance);

	PTRACEX("Query URL: %s", (*kr_api)->tmp_query_url);
	query_private(kr_api);

	return 0;
}


int trade_balance(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[ASSET].b_flag  = TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_trade_balance);

	PTRACEX("Query URL: %s", (*kr_api)->tmp_query_url);
	
	/* set the recursive counter to zero */

	/* check if optionals are given */
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_private(kr_api);
	
	return 0;
}

int open_orders(struct kraken_api **kr_api){

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_open_orders);

	PTRACEX("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[TRADES].b_flag = TRUE;
	(*kr_api)->opt_table[USERREF].b_flag    = TRUE;

	/* set the recursive counter to zero */

	/* check if optionals are given */
	switch_opt(kr_api);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_private(kr_api);

	return 0;
}

int closed_orders(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[TRADES].b_flag     = TRUE;
	(*kr_api)->opt_table[USERREF].b_flag    = TRUE;
	(*kr_api)->opt_table[START].b_flag      = TRUE;
	(*kr_api)->opt_table[END].b_flag        = TRUE;
	(*kr_api)->opt_table[OFS].b_flag        = TRUE;
	(*kr_api)->opt_table[CLOSETIME].b_flag  = TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_closed_orders);

	PTRACEX("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the recursive counter to zero */
	
	/* check if optionals are given */
	switch_opt(kr_api);
	query_private(kr_api);

	return 0;

}

int query_orders(struct kraken_api **kr_api, const char* txid){

	const char* url_txid = "txid=";

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[TRADES].b_flag     = TRUE;
	(*kr_api)->opt_table[USERREF].b_flag    = TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_query_orders);

	/* start the data string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_txid);
	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, txid);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */
	
	/* check if optionals are given */
	switch_opt(kr_api);
	query_private(kr_api);

	return 0;

}

int trades_history(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[TYPE].b_flag   = TRUE;
	(*kr_api)->opt_table[TRADES].b_flag = TRUE;
	(*kr_api)->opt_table[START].b_flag  = TRUE;
	(*kr_api)->opt_table[END].b_flag    = TRUE;
	(*kr_api)->opt_table[OFS].b_flag    = TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_trades_history);

	PTRACEX("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the recursive counter to zero */
	
	/* check if optionals are given */
	switch_opt(kr_api);
	query_private(kr_api);

	return 0;
}

int trades_info(struct kraken_api **kr_api, const char* txid){

	const char* url_txid = "txid=";

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[TRADES].b_flag = TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_query_trades_info);

	/* start the data string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_txid);
	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, txid);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */
	
	/* check if optionals are given */
	switch_opt(kr_api);
	query_private(kr_api);

	return 0;
}

int open_positions(struct kraken_api **kr_api, const char* txid){

	const char* url_txid = "txid=";

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[DOCALCS].b_flag    = TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_open_positions);

	/* start the data string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_txid);
	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, txid);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */
	
	/* check if optionals are given */
	switch_opt(kr_api);
	query_private(kr_api);

	return 0;
}

int ledgers_info(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[ACLASS].b_flag = TRUE;
	(*kr_api)->opt_table[ASSET].b_flag  = TRUE;
	(*kr_api)->opt_table[TYPE].b_flag   = TRUE;
	(*kr_api)->opt_table[START].b_flag  = TRUE;
	(*kr_api)->opt_table[END].b_flag    = TRUE;
	(*kr_api)->opt_table[OFS].b_flag    = TRUE;


	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_ledgers_info);

	PTRACEX("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the recursive counter to zero */
	
	/* check if optionals are given */
	switch_opt(kr_api);
	query_private(kr_api);

	return 0;
}

int query_ledgers(struct kraken_api **kr_api, const char* id){

	const char* url_id = "id=";

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_query_ledgers);

	/* start the data string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_id);
	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, id);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);
	query_private(kr_api);

	return 0;
}

int trade_volume(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */
	(*kr_api)->opt_table[PAIR].b_flag   = TRUE;
	(*kr_api)->opt_table[FEE_INFO].b_flag   = TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_trade_volume);

	PTRACEX("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */
	
	/* check if optionals are given */
	switch_opt(kr_api);
	query_private(kr_api);

	return 0;
}

