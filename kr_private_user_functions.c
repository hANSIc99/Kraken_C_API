#include "kr_private_user_functions.h"


#undef NKEYS
#define NKEYS (uint8_t)(sizeof(type_table)/sizeof(type_table[0]))

int account_balance(struct kraken_api **kr_api){

	/* create the temporary url for this type of api call */
	if(((*kr_api)->tmp_query_url = strdup((*kr_api)->s_uri_private)) == NULL){
		PERROR("ERROR on strdup");
		return -1;
	}

	
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
	if(((*kr_api)->tmp_query_url = strdup((*kr_api)->s_uri_private)) == NULL){
		PERROR("ERROR on strdup");
		return -1;
	}
	
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

int open_orders(struct kraken_api **kr_api, ...){

	const char* url_trades = "trades=";
	const char* url_userref = "userref=";
	const char* url_seperator = "&";
	const char* var_arg = NULL;
	va_list ap;

	va_start(ap, kr_api);

	/* create the temporary url for this type of api call */
	if(((*kr_api)->tmp_query_url = strdup((*kr_api)->s_uri_private)) == NULL){
		PERROR("ERROR on strdup");
		return -1;
	}

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_open_orders);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	/* when the functions is called without arguments */
#if 0
	if((strlen(var_arg = va_arg(ap, char*))) == 0){

		PTRACE("Calling without argument");
		query_private(kr_api);
		va_end(ap);
		return 0;
	}
#endif
	


	va_end(ap);

	return 0;
}


