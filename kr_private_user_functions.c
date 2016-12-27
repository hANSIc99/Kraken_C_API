#include "kr_private_user_functions.h"


#undef NKEYS
#define NKEYS (uint8_t)(sizeof(type_table)/sizeof(type_table[0]))



static void switch_opt(struct kraken_api **kr_api){

	const char* aclass	=	(*kr_api)->priv_opt->opt_aclass;
	const char* asset	=	(*kr_api)->priv_opt->opt_asset;
	const char* trades	=	(*kr_api)->priv_opt->opt_trades;
	const char* userref	=	(*kr_api)->priv_opt->opt_userref;
	const char* start	=	(*kr_api)->priv_opt->opt_start;
	const char* end		=	(*kr_api)->priv_opt->opt_end;
	const char* ofs		=	(*kr_api)->priv_opt->opt_ofs;
	const char* closetime	=	(*kr_api)->priv_opt->opt_closetime;
	const char* docalcs	=	(*kr_api)->priv_opt->opt_docalcs;
	const char* pair	=	(*kr_api)->priv_opt->opt_pair;
	const char* fee_info	=	(*kr_api)->priv_opt->opt_fee_info;
	const char* oflags	=	(*kr_api)->priv_opt->opt_oflags;
	const char* starttm	=	(*kr_api)->priv_opt->opt_starttm;
	const char* expiretm	=	(*kr_api)->priv_opt->opt_expiretm;
	const char* validate	=	(*kr_api)->priv_opt->opt_validate;
	const char* leverage	=	(*kr_api)->priv_opt->opt_leverage;
	const char* close_type	=	(*kr_api)->priv_opt->opt_close_type;
	const char* close_pc_1	=	(*kr_api)->priv_opt->opt_close_pc_1;
	const char* close_pc_2	=	(*kr_api)->priv_opt->opt_close_pc_2;
	
	uint8_t* b_aclass	=	&((*kr_api)->priv_opt_list->bool_aclass);
	uint8_t* b_asset	=	&((*kr_api)->priv_opt_list->bool_asset);
	uint8_t* b_trades	=	&((*kr_api)->priv_opt_list->bool_trades);
	uint8_t* b_userref	=	&((*kr_api)->priv_opt_list->bool_userref);
	uint8_t* b_start	=	&((*kr_api)->priv_opt_list->bool_start);
	uint8_t* b_end		=	&((*kr_api)->priv_opt_list->bool_end);
	uint8_t* b_ofs		=	&((*kr_api)->priv_opt_list->bool_ofs);
	uint8_t* b_closetime	=	&((*kr_api)->priv_opt_list->bool_closetime);
	uint8_t* b_docalcs	=	&((*kr_api)->priv_opt_list->bool_docalcs);
	uint8_t* b_pair		=	&((*kr_api)->priv_opt_list->bool_pair);
	uint8_t* b_fee_info	=	&((*kr_api)->priv_opt_list->bool_fee_info);
	uint8_t* b_fee_oflags	=	&((*kr_api)->priv_opt_list->bool_oflags);
	uint8_t* b_fee_starttm	=	&((*kr_api)->priv_opt_list->bool_starttm);
	uint8_t* b_fee_expiretm	=	&((*kr_api)->priv_opt_list->bool_expiretm);
	uint8_t* b_fee_validate	=	&((*kr_api)->priv_opt_list->bool_validate);
	uint8_t* b_fee_leverage	=	&((*kr_api)->priv_opt_list->bool_leverage);
	uint8_t* b_close_type	=	&((*kr_api)->priv_opt_list->bool_close_type);
	uint8_t* b_close_pc_1	=	&((*kr_api)->priv_opt_list->bool_close_pc_1);
	uint8_t* b_close_pc_2	=	&((*kr_api)->priv_opt_list->bool_close_pc_2);

	const char* url_seperator =	"&";

	if((*kr_api)->s_data){
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);	
	}

	PTRACE("b_trades: %d", *b_trades);
	PTRACE("b_close_pc_1: %d", *b_close_pc_1);

	PTRACE("opt_listen_table leverage = %d", (*kr_api)->opt_listen_table[LEVERAGE]);

	



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



	(*kr_api)->priv_opt_list->bool_trades	= TRUE;
	(*kr_api)->priv_opt_list->bool_userref	= TRUE;
	(*kr_api)->priv_opt_list->bool_start	= TRUE;
	(*kr_api)->priv_opt_list->bool_end	= TRUE;
	(*kr_api)->priv_opt_list->bool_ofs	= TRUE;
	(*kr_api)->priv_opt_list->bool_closetime= TRUE;

	/* create the temporary url for this type of api call */
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_private);
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_closed_orders);

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	switch_opt(kr_api);

	return 0;

}

