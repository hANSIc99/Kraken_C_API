#include "kr_public_functions.h"


int server_time(struct kraken_api **kr_api){


	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_public);	
	(*kr_api)->tmp_query_url = to_url((*kr_api)->tmp_query_url, (*kr_api)->s_uri_server_time);

	PTRACE("server time executed: %s", (*kr_api)->tmp_query_url);

	query_public(kr_api);

	return 0;
}

