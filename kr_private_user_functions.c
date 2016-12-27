#include "kr_private_user_functions.h"


#undef NKEYS
#define NKEYS (uint8_t)(sizeof(type_table)/sizeof(type_table[0]))

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
	
	const char* trades	=	(*kr_api)->priv_opt->opt_trades;
	const char* userref	=	(*kr_api)->priv_opt->opt_userref;

	/* create the temporary url for this type of api call */

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_open_orders);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	
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
	

	PTRACE("(*kr_api)->s_data = %s", (*kr_api)->s_data);

	query_private(kr_api);

	return 0;
}

int closed_orders(struct kraken_api **kr_api){

	/* create the temporary url for this type of api call */

	const char* trades	=	(*kr_api)->priv_opt->opt_trades;
	const char* userref	=	(*kr_api)->priv_opt->opt_userref;
	const char* start	=	(*kr_api)->priv_opt->opt_start;
	const char* end		=	(*kr_api)->priv_opt->opt_end;
	const char* ofs		=	(*kr_api)->priv_opt->opt_ofs;
	const char* closetime	=	(*kr_api)->priv_opt->opt_closetime;
	

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_closed_orders);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);


	return 0;

}

