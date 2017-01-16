#include "kr_helper.h"


uint8_t u8_opt_count = 0; 

void switch_opt(struct kraken_api **kr_api){

	const char* url_seperator = "&";
	uint8_t b_flag;
	char *value;


	b_flag	= (*kr_api)->opt_table[u8_opt_count].b_flag;
	value	= (*kr_api)->opt_table[u8_opt_count].val;

	/* if an option was set by the previous function */
	if(b_flag && value){

		/* check if the string is not empty */
		if((*kr_api)->s_data)
			/* place a "&" behind the excisting data */
			(*kr_api)->s_data = to_url((*kr_api)->s_data, url_seperator);	


		/* concatenate url with "KEY" + "VALUE" + "&" */
		(*kr_api)->s_data = to_url((*kr_api)->s_data, (*kr_api)->opt_table[u8_opt_count].key);
		(*kr_api)->s_data = to_url((*kr_api)->s_data, value);
		/* set the flag to FALSE again in case of subsequent calls */
		(*kr_api)->opt_table[u8_opt_count].b_flag = FALSE;
		/* free the value stored in the array (in case of subsequent calls) */
		free((*kr_api)->opt_table[u8_opt_count].val);
		(*kr_api)->opt_table[u8_opt_count].val = NULL;
	}else if(b_flag){
		/* if no data was found in "VALUE", just set the falg back to FALSE */
		(*kr_api)->opt_table[u8_opt_count].b_flag = FALSE;
	}

	/* inkrement the global counter */
	u8_opt_count++ ;

	PTRACE("u8_count: %d ; (*kr_api)->s_data: %s", u8_opt_count, (*kr_api)->s_data);

	/* check if all option were tested; if yes: RECURSIVE call */
	if(u8_opt_count < ((*kr_api)->opt_table_lenght))
		switch_opt(kr_api);	
	
}
