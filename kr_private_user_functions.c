#include "kr_private_user_functions.h"




static void switch_opt(struct kraken_api **kr_api){
#if 0
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
#endif
	const char* url_seperator =	"&";
	uint8_t u8_i = 0;

	if((*kr_api)->s_data){
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);	
	}


#if 0
	for(; u8_i < (*kr_api)->opt_table_lenght; u8_i++){
		PTRACE("u8_i: %d, name: %s", u8_i, (*kr_api)->opt_table[u8_i].name);


		if((*kr_api)->opt_table[u8_i].b_flag){
			(*kr_api)->s_data = to_url((*kr_api)->s_data, (*kr_api)->opt_table[u8_i].key);
		}
	}	

	PTRACE("asset value: %s", (*kr_api)->opt_table[ASSET].val);
	PTRACE("aclass value: %s", (*kr_api)->opt_table[ACLASS].val);

#endif




	



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

	PTRACE("Query URL: %s", (*kr_api)->tmp_query_url);

	switch_opt(kr_api);

	return 0;

}

