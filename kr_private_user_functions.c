#include "kr_private_user_functions.h"

/* counter for the switch_opt function */
uint8_t u8_count = 0;

static void switch_opt(struct kraken_api **kr_api){

	const char* url_seperator =	"&";
	uint8_t b_flag;
	char *value;


	PTRACE("u8_i: %d, name: %s", u8_count, (*kr_api)->opt_table[u8_count].name);
		
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

	PTRACE("(*kr_api)->s_data: %s", (*kr_api)->s_data);

	/* check if all option were tested; if yes: RECURSIVE call */
	if(u8_count < ((*kr_api)->opt_table_lenght)){
		switch_opt(kr_api);	
	}
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
		(*kr_api)->s_data = strdup(url_aclass);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("s_data = %s", (*kr_api)->s_data);
	}

	va_end(ap);

	query_private(kr_api);
	
	return 0;
}

int open_orders(struct kraken_api **kr_api){

	const char* url_trades	=	"trades=";
	const char* url_userref	=	"userref=";
	const char* url_seperator =	"&";
#if 0	
	const char* trades	=	(*kr_api)->priv_opt->opt_trades;
	const char* userref	=	(*kr_api)->priv_opt->opt_userref;
#endif
	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_open_orders);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

#if 0	
	if(trades || userref){
		PTRACE("optionals found");

		if((trades) && (!userref)){
			PTRACE("trades given, userref omitted");
			(*kr_api)->s_data = strdup(url_trades);
			(*kr_api)->s_data = to_url((*kr_api)->s_data, trades);
		}
		else if((userref) && (!trades)){
			PTRACE("userref given, trades omitted");
			(*kr_api)->s_data = strdup(url_userref);
			(*kr_api)->s_data = to_url((*kr_api)->s_data, userref);
		}
		else{
			PTRACE("userref and trades given");
			(*kr_api)->s_data = strdup(url_userref);
			(*kr_api)->s_data = to_url((*kr_api)->s_data, userref);
			(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
			(*kr_api)->s_data = to_url((*kr_api)->s_data, url_trades);
			(*kr_api)->s_data = to_url((*kr_api)->s_data, trades);
		}

	}else
		PTRACE("no optionals found, proceed without them");
	
#endif
	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	query_private(kr_api);

	return 0;
}

int closed_orders(struct kraken_api **kr_api){


	(*kr_api)->opt_table[TRADES].b_flag	= TRUE;
	(*kr_api)->opt_table[USERREF].b_flag	= TRUE;
	(*kr_api)->opt_table[START].b_flag	= TRUE;
	(*kr_api)->opt_table[END].b_flag	= TRUE;
	(*kr_api)->opt_table[OFS].b_flag	= TRUE;
	(*kr_api)->opt_table[CLOSETIME].b_flag	= TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_closed_orders);

#if 1
	(*kr_api)->s_data = to_url((*kr_api)->s_data, "just_a_test");	
#endif

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	u8_count = 0;
	switch_opt(kr_api);

	return 0;

}

