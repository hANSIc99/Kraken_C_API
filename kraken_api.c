#include "kraken_api.h"
#include "kr_private_trading_functions.h"
#include "kr_private_user_functions.h"
#include "url.h"



static struct st_opt_list options_listen_table[] = {

	[ACLASS]	=	{.name = "aclass",	.b_flag =	FALSE,	.key = "aclass="},
	[ASSET]		=	{.name = "asset",	.b_flag =	FALSE,	.key = "asset="},	
	[TRADES]	=	{.name = "trades",	.b_flag =	FALSE,	.key = "trades="},
	[USERREF]	=	{.name ="userref",	.b_flag =	FALSE,	.key = "userref="},
	[START]		=	{.name = "start",	.b_flag =	FALSE,	.key = "start="},
	[END]		=	{.name = "end",		.b_flag =	FALSE,	.key = "end="},
	[OFS]		=	{.name = "ofs",		.b_flag =	FALSE,	.key = "ofs="},
	[CLOSETIME]	=	{.name = "closetime",	.b_flag =	FALSE,	.key = "closetime="},
	[DOCALCS]	=	{.name = "docalcs",	.b_flag =	FALSE,	.key = "docalcs="},
	[PAIR]		=	{.name = "pair",	.b_flag =	FALSE,	.key = "pair="},
	[FEE_INFO]	=	{.name = "fee-info",	.b_flag =	FALSE,	.key = "fee-info="},
	[OFLAGS]	=	{.name = "oflags",	.b_flag =	FALSE,	.key = "oflags="},
	[STARTTM]	=	{.name = "starttm",	.b_flag =	FALSE,	.key = "starttm="},
	[EXPIRETM]	=	{.name = "expiretm",	.b_flag =	FALSE,	.key = "expiretm="},
	[VALIDATE]	=	{.name = "validate",	.b_flag =	FALSE,	.key = "validate="},
	[LEVERAGE]	=	{.name = "leverage",	.b_flag =	FALSE,	.key = "leverage="},
	[CLOSE_TYPE]	=	{.name = "close-type",	.b_flag =	FALSE,	.key = "close[ordertype]="},
	[CLOSE_PRICE_1]	=	{.name = "close-pc-1",	.b_flag =	FALSE,	.key = "close[price]="},
	[CLOSE_PRICE_2]	=	{.name = "close-pc-2",	.b_flag =	FALSE,	.key = "close[price2]="}
};

#define SZ_LIST_TABLE (sizeof(options_listen_table))

#undef NKEYS
#define NKEYS (uint8_t)(sizeof(options_listen_table)/sizeof(options_listen_table[1]))

int kraken_init(struct kraken_api **kr_api, const char* api_key, const char *sec_key){

	uint8_t u8_i;

	/* new Init function */


	if(!((*kr_api) = malloc(sizeof(struct kraken_api)))){
		PERROR("ERROR on malloc");
		return -1;
	}

	(*kr_api)->priv_func	=	NULL;
	(*kr_api)->pub_func	=	NULL;
#if 0
	(*kr_api)->priv_opt	=	NULL;
#endif
	(*kr_api)->priv_opt_list =	NULL;

	if(!((*kr_api)->opt_table = malloc(sizeof(options_listen_table)))){
		PERROR("ERROR on malloc");
		return -1;
	}

	if(!((*kr_api)->priv_func = malloc(sizeof(struct private_functions)))){
		PERROR("ERROR on malloc");
		return -1;
	}

	if(!((*kr_api)->pub_func = malloc(sizeof(struct public_functions)))){
		PERROR("ERROR on malloc");
		return -1;
	}

#if 0
	if(!((*kr_api)->priv_opt = malloc(sizeof(struct private_optionals)))){
		PERROR("ERROR on malloc");
		return -1;
	}
#endif

#if 0
	if(!((*kr_api)->priv_opt_list = malloc(sizeof(struct private_opt_listen)))){
		PERROR("ERROR on malloc");
		return -1;
	}
#endif

	/* initialise the api-keys */

	(*kr_api)->s_api_key = NULL;
	(*kr_api)->s_sec_key = NULL;

	(*kr_api)->s_api_key = strdup(api_key);
	(*kr_api)->s_sec_key = strdup(sec_key);


	
	/* initialize with default values */
	(*kr_api)->s_url =			NULL;
	(*kr_api)->s_data =			NULL;
	(*kr_api)->s_result =			NULL;
	(*kr_api)->s_uri_private =		NULL;
	(*kr_api)->s_uri_addorder =		NULL;

	(*kr_api)->tmp_query_url =		NULL;

	/* create opt_listen_table  */

	memcpy((*kr_api)->opt_table, options_listen_table, SZ_LIST_TABLE); 

	/* set table lenght */

	(*kr_api)->opt_table_lenght = NKEYS;

	/* initialize option values */

	for(u8_i = 0; u8_i < NKEYS; u8_i++)
		(*kr_api)->opt_table[u8_i].val = NULL;


	/* assign the functions */

	(*kr_api)->priv_func->add_order = &addOrder;
	(*kr_api)->priv_func->cancel_order = &cancelOrder;
	(*kr_api)->priv_func->get_account_balance = &account_balance;
	(*kr_api)->priv_func->get_trade_balance = &trade_balance;
	(*kr_api)->priv_func->get_open_orders =	&open_orders;
	(*kr_api)->priv_func->get_closed_orders = &closed_orders;

	make_url(kr_api);

	return 0;
}

int kraken_set_opt(struct kraken_api **kr_api, const char* opt, const char* val){
	
	PTRACE("nkeys: %d", NKEYS);

	switch(key_from_string(opt, options_listen_table, NKEYS)){

		case ACLASS:
			PTRACE("switch to case ACLASS");
			if(!((*kr_api)->opt_table[ACLASS].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[ACLASS].val);
			break;
		case ASSET:
			PTRACE("switch to case ASSET");
			if(!((*kr_api)->opt_table[ASSET].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[ASSET].val);
			break;
		case TRADES:
			PTRACE("switch to case TRADES");
			if(!((*kr_api)->opt_table[TRADES].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[TRADES].val);
			break;
		case USERREF:
			PTRACE("switch to case USERREF");
			if(!((*kr_api)->opt_table[USERREF].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[USERREF].val);
			break;
		case START:
			PTRACE("switch to case START");
			if(!((*kr_api)->opt_table[START].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[START].val);
			break;
		case END:
			PTRACE("switch to case END");
			if(!((*kr_api)->opt_table[END].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[END].val);
			break;
		case OFS:
			PTRACE("switch to case OFS");
			if(!((*kr_api)->opt_table[OFS].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[OFS].val);
			break;
		case CLOSETIME:
			PTRACE("switch to case CLOSETIME");
			if(!((*kr_api)->opt_table[CLOSETIME].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[CLOSETIME].val);
			break;
		case DOCALCS:
			PTRACE("switch to case DOCALCS");
			if(!((*kr_api)->opt_table[DOCALCS].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[DOCALCS].val);
			break;
		case PAIR:
			PTRACE("switch to case PAIR");
			if(!((*kr_api)->opt_table[PAIR].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[PAIR].val);
			break;
		case FEE_INFO:
			PTRACE("switch to case FEE_INFO");
			if(!((*kr_api)->opt_table[FEE_INFO].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[FEE_INFO].val);
			break;
		case OFLAGS:
			PTRACE("switch to case OFLAGS");
			if(!((*kr_api)->opt_table[OFLAGS].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[OFLAGS].val);
			break;
		case STARTTM:
			PTRACE("switch to case STARTTM");
			if(!((*kr_api)->opt_table[STARTTM].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[STARTTM].val);
			break;
		case EXPIRETM:
			PTRACE("switch to case EXPIRETM");
			if(!((*kr_api)->opt_table[EXPIRETM].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[EXPIRETM].val);
			break;
		case VALIDATE:
			PTRACE("switch to case VALIDATE");
			if(!((*kr_api)->opt_table[VALIDATE].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[VALIDATE].val);
			break;
		case LEVERAGE:
			PTRACE("switch to case LEVERAGE");
			if(!((*kr_api)->opt_table[LEVERAGE].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[LEVERAGE].val);
			break;
		case CLOSE_TYPE:
			PTRACE("switch to case CLOSE_TYPE");
			if(!((*kr_api)->opt_table[CLOSE_TYPE].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[CLOSE_TYPE].val);
			break;
		case CLOSE_PRICE_1:
			PTRACE("switch to case CLOSE_PRICE_1");
			if(!((*kr_api)->opt_table[CLOSE_PRICE_1].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[CLOSE_PRICE_1].val);
			break;
		case CLOSE_PRICE_2:
			PTRACE("switch to case CLOSE_PRICE_2");
			if(!((*kr_api)->opt_table[CLOSE_PRICE_2].val = strdup(val))){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->opt_table[CLOSE_PRICE_2].val);
			break;
		case BADARG:
			PERROR("BADARG");
			return -1;

	}	
	
	return 0;

}

void kraken_clean(struct kraken_api **kr_api){

	PTRACE("API CLEANUP");
	char* tmp_ptr = NULL;
	uint8_t u8_i;

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

	/* BUFFER */
	if((*kr_api)->s_result != NULL) free((*kr_api)->s_result);  

	/* OPTIONALS */

	for(u8_i = 0; u8_i < (*kr_api)->opt_table_lenght; u8_i++){
		if((tmp_ptr = (*kr_api)->opt_table[u8_i].val)) free(tmp_ptr);
	}	

	free((*kr_api)->opt_table);


	free(*kr_api);

}


/* helper functions to distinguish between command line arguments */

int key_from_string(const char *str, const struct st_opt_list *type_table, const uint8_t u8_n_keys){

	uint8_t u8_i = 0;
	char* tmp_str = NULL;
	char* check_str = NULL;
	
	tmp_str = strdup(str);

	check_str = tmp_str ;

	/* convert to lower case chars */

	for( ; *tmp_str; ++tmp_str) *tmp_str = tolower(*tmp_str);

	PTRACE("u8_n_keys = %d", u8_n_keys);


	for(u8_i = 0; u8_i <  u8_n_keys; u8_i++){

		const struct st_opt_list *typ = type_table + u8_i;

		if(!(strcmp(typ->name, check_str))){
			free(check_str);
			return u8_i;
		}
	}
	
	free(check_str);
	return BADARG;
}



