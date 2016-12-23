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

	switch(key_from_string(opt, opt_table, NKEYS)){

		case ACLASS:
			PTRACE("switch to case ACLASS");
			if(((*kr_api)->priv_opt->opt_aclass = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_aclass = %s", (*kr_api)->priv_opt->opt_aclass);
			break;
		case ASSET:
			PTRACE("switch to case ASSET");
			if(((*kr_api)->priv_opt->opt_asset = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_asset = %s", (*kr_api)->priv_opt->opt_asset);
			break;
		case TRADES:
			PTRACE("switch to case TRADES");
			if(((*kr_api)->priv_opt->opt_trades = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_trades = %s", (*kr_api)->priv_opt->opt_trades);
			break;
		case USERREF:
			PTRACE("switch to case USERREF");
			if(((*kr_api)->priv_opt->opt_userref = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_userref = %s", (*kr_api)->priv_opt->opt_userref);
			break;
		case START:
			PTRACE("switch to case START");
			if(((*kr_api)->priv_opt->opt_start = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_start = %s", (*kr_api)->priv_opt->opt_start);
			break;
		case END:
			PTRACE("switch to case END");
			if(((*kr_api)->priv_opt->opt_end = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_end = %s", (*kr_api)->priv_opt->opt_end);
			break;
		case OFS:
			PTRACE("switch to case OFS");
			if(((*kr_api)->priv_opt->opt_ofs = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_ofs = %s", (*kr_api)->priv_opt->opt_ofs);
			break;
		case CLOSETIME:
			PTRACE("switch to case CLOSETIME");
			if(((*kr_api)->priv_opt->opt_closetime = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_closetime = %s", (*kr_api)->priv_opt->opt_closetime);
			break;
		case DOCALCS:
			PTRACE("switch to case DOCALCS");
			if(((*kr_api)->priv_opt->opt_docalcs = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_docalcs = %s", (*kr_api)->priv_opt->opt_docalcs);
			break;
		case PAIR:
			PTRACE("switch to case PAIR");
			if(((*kr_api)->priv_opt->opt_pair = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_pair = %s", (*kr_api)->priv_opt->opt_pair);
			break;
		case FEE_INFO:
			PTRACE("switch to case FEE_INFO");
			if(((*kr_api)->priv_opt->opt_fee_info = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_fee_info = %s", (*kr_api)->priv_opt->opt_fee_info);
			break;
		case OFLAGS:
			PTRACE("switch to case OFLAGS");
			if(((*kr_api)->priv_opt->opt_oflags = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_oflags = %s", (*kr_api)->priv_opt->opt_oflags);
			break;
		case STARTTM:
			PTRACE("switch to case STARTTM");
			if(((*kr_api)->priv_opt->opt_starttm = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_starttm = %s", (*kr_api)->priv_opt->opt_starttm);
			break;
		case EXPIRETM:
			PTRACE("switch to case EXPIRETM");
			if(((*kr_api)->priv_opt->opt_expiretm = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_expiretm = %s", (*kr_api)->priv_opt->opt_expiretm);
			break;
		case VALIDATE:
			PTRACE("switch to case VALIDATE");
			if(((*kr_api)->priv_opt->opt_validate = strdup(val)) == NULL){
				PERROR("ERROR on strdup");
				return -1;
			}
			PTRACE("opt_validate = %s", (*kr_api)->priv_opt->opt_validate);
			break;
		case BADARG:
			PERROR("BADARG");
			return -1;

	}	
	
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
	char* tmp_str = NULL;
	int i;

	tmp_str = strdup(str);

	PTRACE("tmp_str = %s", tmp_str);
#if 1
	while(tmp_str[i]){
		tmp_str[i] = tolower(tmp_str[i]);
		i++;
	}
	tmp_str[i] = '\0';
#endif

#if 0
	for( ; *tmp_str; ++tmp_str) *tmp_str = tolower(*tmp_str);
#endif
	


	PTRACE("tmp_str = %s", tmp_str);
	PTRACE("u8_n_keys = %d", u8_n_keys);

	for(u8_i = 0; u8_i <  u8_n_keys; u8_i++){

		const struct st_list *typ = type_table + u8_i;

		if(!(strcmp(typ->key, str))){

			return typ->val;
		}
	}

	return BADARG;
}



