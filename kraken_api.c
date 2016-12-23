#include "kraken_api.h"
#include "kr_private_trading_functions.h"
#include "kr_private_user_functions.h"
#include "url.h"

static struct st_list opt_table[] = {

	{"aclass",	ACLASS		},
	{"asset",	ASSET		},
	{"trades",	TRADES		},
	{"userref",	USERREF		},
	{"start",	START		},
	{"end",		END		},
	{"ofs",		OFS		},
	{"closetime",	CLOSETIME	},
	{"docalcs",	DOCALCS		},
	{"pair",	PAIR		},
	{"fee-info",	FEE_INFO	},
	{"oflags",	OFLAGS		},
	{"starttm",	STARTTM		},
	{"expiretm",	EXPIRETM	},
	{"validate",	VALIDATE	}

};

#undef NKEYS
#define NKEYS (uint8_t)(sizeof(opt_table)/sizeof(opt_table[0]))

int kraken_init(struct kraken_api **kr_api, const char* api_key, const char *sec_key){

	/* new Init function */


	if(((*kr_api) = malloc(sizeof(struct kraken_api))) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}

	(*kr_api)->priv_func = NULL;
	(*kr_api)->pub_func = NULL;
	(*kr_api)->priv_opt = NULL;

	if(((*kr_api)->priv_func = malloc(sizeof(struct private_functions))) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}

	if(((*kr_api)->pub_func = malloc(sizeof(struct public_functions))) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}


	if(((*kr_api)->priv_opt = malloc(sizeof(struct private_optionals))) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}

	/* initialise the api-keys */

	(*kr_api)->s_api_key = NULL;
	(*kr_api)->s_sec_key = NULL;

	(*kr_api)->s_api_key = strdup(api_key);
	(*kr_api)->s_sec_key = strdup(sec_key);


	
	/* initialize with default values */
	(*kr_api)->s_url =			NULL;
	(*kr_api)->s_data =			NULL;
	(*kr_api)->s_uri_private =		NULL;
	(*kr_api)->s_uri_addorder =		NULL;

	(*kr_api)->priv_opt->opt_aclass =	NULL;
	(*kr_api)->priv_opt->opt_asset =	NULL;
	(*kr_api)->priv_opt->opt_trades =	NULL;
	(*kr_api)->priv_opt->opt_userref =	NULL;
	(*kr_api)->priv_opt->opt_start =	NULL;
	(*kr_api)->priv_opt->opt_end =		NULL;
	(*kr_api)->priv_opt->opt_ofs =		NULL;
	(*kr_api)->priv_opt->opt_closetime =	NULL;
	(*kr_api)->priv_opt->opt_docalcs =	NULL;
	(*kr_api)->priv_opt->opt_pair =		NULL;
	(*kr_api)->priv_opt->opt_fee_info =	NULL;
	(*kr_api)->priv_opt->opt_oflags =	NULL;
	(*kr_api)->priv_opt->opt_starttm =	NULL;
	(*kr_api)->priv_opt->opt_expiretm =	NULL;
	(*kr_api)->priv_opt->opt_validate =	NULL;


	(*kr_api)->priv_func->add_order = &addOrder;
	(*kr_api)->priv_func->get_account_balance = &account_balance;
	(*kr_api)->priv_func->get_trade_balance = &trade_balance;
	(*kr_api)->priv_func->get_open_orders =	&open_orders;

	make_url(kr_api);

	return 0;
}

int kraken_set_opt(struct kraken_api **kr_api, const char* opt, const char* val){
	
	PTRACE("nkeys: %d", NKEYS);
#if 0
	switch(key_from_string(opt, opt_table, NKEYS)) 
#endif	
	
	return 0;

}

void kraken_clean(struct kraken_api **kr_api){

	PTRACE("API CLEANUP");

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
	free((*kr_api)->s_result);

	/* OPTIONALS */


	free(*kr_api);

}


/* helper functions to distinguish between command line arguments */

int key_from_string(const char *str, const struct st_list *type_table, const uint8_t u8_n_keys){

	uint8_t u8_i = 0;

	PTRACE("u8_n_keys = %d", u8_n_keys);

	for(u8_i = 0; u8_i <  u8_n_keys; u8_i++){

		const struct st_list *typ = type_table + u8_i;

		if(!(strcmp(typ->key, str))){

			return typ->val;
		}
	}

	return BADARG;
}



