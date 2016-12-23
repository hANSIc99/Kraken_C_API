#include "kraken_api.h"
#include "kr_private_trading_functions.h"
#include "kr_private_user_functions.h"
#include "url.h"

int kraken_init(struct kraken_api **kr_api, const char* api_key, const char *sec_key){

	/* new Init function */
	*kr_api = malloc(sizeof(struct kraken_api));

	(*kr_api)->s_api_key = NULL;
	(*kr_api)->s_sec_key = NULL;

	if(((*kr_api)->s_api_key = malloc((size_t)strlen(api_key)+1)) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}
	if(((*kr_api)->s_sec_key = malloc((size_t)strlen(sec_key)+1)) == NULL){
		PERROR("ERROR on malloc");
		return -1;
	}

	strcpy((*kr_api)->s_api_key, api_key);
	strcpy((*kr_api)->s_sec_key, sec_key);

	(*kr_api)->priv_func = NULL;
	(*kr_api)->priv_func = NULL;

	(*kr_api)->priv_func = malloc(sizeof(struct private_functions));
	(*kr_api)->pub_func = malloc(sizeof(struct public_functions));

	(*kr_api)->s_url = NULL;
	(*kr_api)->s_data = NULL;
	(*kr_api)->s_uri_private = NULL;
	(*kr_api)->s_uri_addorder = NULL;


	(*kr_api)->priv_func->add_order = &addOrder;
	(*kr_api)->priv_func->get_account_balance = &account_balance;
	(*kr_api)->priv_func->get_trade_balance = &trade_balance;
	(*kr_api)->priv_func->get_open_orders = &open_orders;

	make_url(kr_api);

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



