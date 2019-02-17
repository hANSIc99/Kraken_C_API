#include "kr_helper.h"

void switch_opt(struct kraken_api **kr_api){

	const char url_seperator = '&';
	uint8_t u8_opt_count = (*kr_api)->opt_table_lenght ;

	while (u8_opt_count--) {
		/* b_flag is set by the handler function and it defines if this opt
		 * is allowed in the scope of the current function */
		uint8_t cur_b_flag = (*kr_api)->opt_table[u8_opt_count].b_flag;
		/* .val is set by kraken_set_opt (called from the user application) */
		char *cur_val = (*kr_api)->opt_table[u8_opt_count].val;

		if( cur_b_flag && (cur_val != NULL) ){
			/* GO: let's construct s_data: */
			if( (*kr_api)->s_data != NULL )
				/* we have multiple arguments so we'll append an '&' to the existing string : */
				(*kr_api)->s_data = to_url((*kr_api)->s_data, &url_seperator);
			/* concatenate url with "KEY" + "VALUE" + "&" */
			(*kr_api)->s_data = to_url((*kr_api)->s_data, (*kr_api)->opt_table[u8_opt_count].key);
			(*kr_api)->s_data = to_url((*kr_api)->s_data, cur_val);
			PTRACEX("u8_count: %d, cur_val: %s", u8_opt_count, cur_val);
			/* prepare things for subsequent calls: */
			(*kr_api)->opt_table[u8_opt_count].b_flag = FALSE;
			free((*kr_api)->opt_table[u8_opt_count].val);
			(*kr_api)->opt_table[u8_opt_count].val = NULL;
		}
		else if(cur_b_flag) {
			/* only b_flaf present. reset b_flag so we are ready for new calls */
			(*kr_api)->opt_table[u8_opt_count].b_flag = FALSE;
		}
		else if(cur_val != NULL) {
			/* only cur_val present. free & reset val so we are ready for new calls.
			 * we need to have this since the library user could erroneusly set an option which
			 * is not accepted by the current function thus making the option to appear in an
			 * sunsequent call to a function which allows it.
			 * (This is actually an error state?) */
			PTRACEX("NOTE: Option \"%s\" not accepted with this function",
					(*kr_api)->opt_table[u8_opt_count].name);
			free((*kr_api)->opt_table[u8_opt_count].val);
			(*kr_api)->opt_table[u8_opt_count].val = NULL;
		}
	}
	PTRACEX( "(*kr_api)->s_data = %s", (*kr_api)->s_data );
}
