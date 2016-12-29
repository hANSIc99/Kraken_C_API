#include "kr_private_user_functions.h"

/* counter for the switch_opt function */
uint8_t u8_count = 0;


void switch_opt(struct kraken_api **kr_api){

	const char* url_seperator = "&";
	uint8_t b_flag;
	char *value;


	b_flag	= (*kr_api)->opt_table[u8_count].b_flag;
	value	= (*kr_api)->opt_table[u8_count].val;

	/* if an option was set by the previous function */
	if(b_flag && value){

		/* check if the string is not empty */
		if((*kr_api)->s_data )
			/* place a "&" behind the excisting data */
			(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);	


		/* concatenate url with "KEY" + "VALUE" + "&" */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, (*kr_api)->opt_table[u8_count].key);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, value);
		/* set the flag to FALSE again in case of subsequent calls */
		(*kr_api)->opt_table[u8_count].b_flag = FALSE;
		/* free the value stored in the array (in case of subsequent calls) */
		free((*kr_api)->opt_table[u8_count].val);
		(*kr_api)->opt_table[u8_count].val = NULL;
	}else if(b_flag){
		/* if no data was found in "VALUE", just set the falg back to FALSE */
		(*kr_api)->opt_table[u8_count].b_flag = FALSE;
	}

	/* inkrement the global counter */
	u8_count++ ;

	PTRACE("u8_count: %d ; (*kr_api)->s_data: %s", u8_count, (*kr_api)->s_data);

	/* check if all option were tested; if yes: RECURSIVE call */
	if(u8_count < ((*kr_api)->opt_table_lenght))
		switch_opt(kr_api);	
	
}

int account_balance(struct kraken_api **kr_api){

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_balance);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	query_private(kr_api);

	return 0;
}


int trade_balance(struct kraken_api **kr_api, ...){

	const char* url_aclass = "aclass=";
	const char* var_arg = NULL;
	va_list ap;

	va_start(ap, kr_api);

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_trade_balance);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);
	
	if((strlen(var_arg = va_arg(ap, char*))) == 0){

		PDEBUG("No Argument");
	}else{
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_aclass);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("s_data = %s", (*kr_api)->s_data);
	}

	va_end(ap);

	query_private(kr_api);
	
	return 0;
}

int open_orders(struct kraken_api **kr_api){

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_open_orders);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the appropriate optionals for this function */
	
	(*kr_api)->opt_table[TRADES].b_flag	= TRUE;
	(*kr_api)->opt_table[USERREF].b_flag	= TRUE;

	/* set the recursive counter to zero */

	u8_count = 0;

	/* check if optionals are given */	

	switch_opt(kr_api);

	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	query_private(kr_api);

	return 0;
}

int closed_orders(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */

	(*kr_api)->opt_table[TRADES].b_flag	= TRUE;
	(*kr_api)->opt_table[USERREF].b_flag	= TRUE;
	(*kr_api)->opt_table[START].b_flag	= TRUE;
	(*kr_api)->opt_table[END].b_flag	= TRUE;
	(*kr_api)->opt_table[OFS].b_flag	= TRUE;
	(*kr_api)->opt_table[CLOSETIME].b_flag	= TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_closed_orders);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the recursive counter to zero */

	u8_count = 0;
	
	/* check if optionals are given */

	switch_opt(kr_api);

	query_private(kr_api);

	return 0;

}

int query_orders(struct kraken_api **kr_api, const char* txid){

	const char* url_txid = "txid=";

	/* set the appropriate optionals for this function */

	(*kr_api)->opt_table[TRADES].b_flag	= TRUE;
	(*kr_api)->opt_table[USERREF].b_flag	= TRUE;

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_query_orders);

	/* start the data string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_txid);
	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, txid);

	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */

	u8_count = 0;
	
	/* check if optionals are given */

	switch_opt(kr_api);

	query_private(kr_api);

	return 0;

}

int trades_history(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */

	(*kr_api)->opt_table[TYPE].b_flag	= TRUE;
	(*kr_api)->opt_table[TRADES].b_flag	= TRUE;
	(*kr_api)->opt_table[START].b_flag	= TRUE;
	(*kr_api)->opt_table[END].b_flag	= TRUE;
	(*kr_api)->opt_table[OFS].b_flag	= TRUE;

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_trades_history);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the recursive counter to zero */

	u8_count = 0;
	
	/* check if optionals are given */

	switch_opt(kr_api);

	query_private(kr_api);

	return 0;
}

int trades_info(struct kraken_api **kr_api, const char* txid){

	const char* url_txid = "txid=";

	/* set the appropriate optionals for this function */

	(*kr_api)->opt_table[TRADES].b_flag	= TRUE;

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_query_trades_info);

	/* start the data string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_txid);
	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, txid);

	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */

	u8_count = 0;
	
	/* check if optionals are given */

	switch_opt(kr_api);

	query_private(kr_api);

	return 0;

}

int open_positions(struct kraken_api **kr_api, const char* txid){

	const char* url_txid = "txid=";

	/* set the appropriate optionals for this function */

	(*kr_api)->opt_table[DOCALCS].b_flag	= TRUE;

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_open_positions);

	/* start the data string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_txid);
	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, txid);

	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */

	u8_count = 0;
	
	/* check if optionals are given */

	switch_opt(kr_api);

	query_private(kr_api);

	return 0;

}

int ledgers_info(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */

	(*kr_api)->opt_table[ACLASS].b_flag	= TRUE;
	(*kr_api)->opt_table[ASSET].b_flag	= TRUE;
	(*kr_api)->opt_table[TYPE].b_flag	= TRUE;
	(*kr_api)->opt_table[START].b_flag	= TRUE;
	(*kr_api)->opt_table[END].b_flag	= TRUE;
	(*kr_api)->opt_table[OFS].b_flag	= TRUE;


	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_ledgers_info);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	/* set the recursive counter to zero */

	u8_count = 0;
	
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

	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	query_private(kr_api);

	return 0;

}

int trade_volume(struct kraken_api **kr_api){

	/* set the appropriate optionals for this function */

	(*kr_api)->opt_table[PAIR].b_flag	= TRUE;
	(*kr_api)->opt_table[FEE_INFO].b_flag	= TRUE;


	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_trade_volume);

	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	/* set the recursive counter to zero */

	u8_count = 0;
	
	/* check if optionals are given */

	switch_opt(kr_api);

	query_private(kr_api);

	return 0;

}

