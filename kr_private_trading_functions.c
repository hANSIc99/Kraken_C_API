#include "kr_private_trading_functions.h"


static struct st_list type_table[] = {

	{"market",		MARKET},
	{"limit",		LIMIT},
	{"stop-loss",		STOP_LOSS},
	{"take-profit",		TAKE_PROFIT},
	{"stop-loss-profit",	STOP_LOSS_PROFIT},
	{"stop-loss-profit-limit", STOP_LOSS_PROFIT_LIMIT},
	{"stop-loss-limit",	STOP_LOSS_LIMIT},
	{"take-profit-limit",	TAKE_PROFIT_LIMIT},
	{"trailing-stop",	TRAILING_STOP},
	{"trailing-stop-limit",	TRAILING_STOP_LIMIT},
	{"stop-loss-and-limit",	STOP_LOSS_AND_LIMIT},
	{"settle-position",	SETTLE_POSITION}

};

static int key_from_string(const char *str){

	uint8_t u8_i = 0;

	for(u8_i = 0; u8_i <  NKEYS; u8_i++){

		struct st_list *typ = &type_table[u8_i];

		if(!(strcmp(typ->key, str))){

			return typ->val;
		}
	}

	return BADARG;
}






int addOrder(struct kraken_api **kr_api, const char *type, const char *order, const char *asset, const char* volume, ...){


	va_list ap;
	const char *var_arg = NULL;
	va_start(ap, volume);

	const char* url_seperator = "&";
	const char* url_pair = "pair=";
	const char* url_type = "type=";
	const char* url_ordertype = "ordertype=";
	const char* url_volume = "volume=";
	const char* url_price_1 = "price=";
	const char* url_price_2 = "price2=";
	const char* url_trading = "trading_agreement=";
	const char* var_agreement = "agree";


	PTRACE("type: %s\n", type);
	PTRACE("order: %s\n", order);
	PTRACE("asset: %s\n", asset);
	
	/* create the temporary url for this type of api call */

	if(((*kr_api)->tmp_query_url = strdup((*kr_api)->s_uri_private)) == NULL){
		PDEBUG("ERROR on strdup");
		exit(-1);
	}

	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_addorder);
	
	/* start the data string */
	if(((*kr_api)->s_data = strdup(url_pair)) == NULL){
		PDEBUG("ERROR on strdup");
		exit(-1);
	}	

	/* add XXBTZEUR to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, asset);
	/* add seperator to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
	/* add the type to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_type);
	/* add the type BUY to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, type);
	/* add seperator to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
	/* add order_type to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_ordertype);
	/* add order_type MARKET to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, order);
	/* add seperator to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
	/* add volume to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_volume);
	/* add volume VOLUME to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, volume);
	/* add seperator to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
	/* add trading agreement to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, url_trading);
	/* add trading agreement = AGREE to the string */
	(*kr_api)->s_data = to_url((*kr_api)->s_data, var_agreement);
	/* add seperator to the string */



switch (key_from_string(order)){

	case MARKET:
		PTRACE("switch to case market");
		/* market only needs VOLUME */
		PTRACE("MARKET URL: %s", (*kr_api)->s_data);
		break;
	case LIMIT:
		PTRACE("switch to case limit\n");
		/* limit needs 1x va_arg: limit price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("LIMIT URL: %s", (*kr_api)->s_data);
		break;
	case STOP_LOSS:
		PTRACE("switch to case stop-loss\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = stop-loss-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("STOP LOSS URL: %s", (*kr_api)->s_data);
		break;
	case TAKE_PROFIT:
		PTRACE("switch to case take-profit\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = take-profit-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("TAKE PROFIT URL: %s", (*kr_api)->s_data);
		break;
	case STOP_LOSS_PROFIT:
		PTRACE("switch to case stop-loss-profit\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = stop-loss-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		/* price_2 = take-profit-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_2);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("STOP LOSS PROFIT URL: %s", (*kr_api)->s_data);
		break;
	case STOP_LOSS_PROFIT_LIMIT:
		PTRACE("switch to case stop-loss-profit-limit\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = stop-loss-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		/* price_2 = take-profit-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_2);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("STOP LOSS PROFIT LIMIT URL: %s", (*kr_api)->s_data);
		break;
	case STOP_LOSS_LIMIT:
		PTRACE("switch to case stop-loss-limit\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = stop-loss-trigger-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		/* price_2 = triggered-limit-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_2);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("STOP LOSS LIMIT URL: %s", (*kr_api)->s_data);
		break;
	case TAKE_PROFIT_LIMIT:
		PTRACE("switch to case take-profit-limit\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = take-profit-trigger-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		/* price_2 = triggered-limit-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_2);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("TAKE PROFIT URL: %s", (*kr_api)->s_data);
		break;
	case TRAILING_STOP:
		PTRACE("switch to case trailing-stop\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = trailing stop offset */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("TRAILING STOP URL: %s", (*kr_api)->s_data);
		break;
	case TRAILING_STOP_LIMIT:
		PTRACE("switch to case trailing-stop-limit\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = trailing stop offset */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		/* price_2 = triggered-limit-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_2);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("TRAILING STOP URL: %s", (*kr_api)->s_data);
		break;
	case STOP_LOSS_AND_LIMIT:
		PTRACE("switch to case stop-loss-and-limit\n");
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		/* price_1 = stop-loss-price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_1);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		/* price_2 = limit price */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, url_price_2);
		var_arg = va_arg(ap, char*);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, var_arg);
		PTRACE("STOP LOSS AND LIMIT URL: %s", (*kr_api)->s_data);
		break;
	case SETTLE_POSITION:
		PTRACE("switch to case settle-position\n");
		/* settle-position only needs VOLUME */
		PTRACE("SETTLE POSITION URL: %s", (*kr_api)->s_data);
		break;
	case BADARG:
		
		PDEBUG("switch to case BADARG ERROR\n");
		return -1;
		break;


}
	/* clean up var-args */
	va_end(ap);
	
query_private(kr_api);

return 0;

}
