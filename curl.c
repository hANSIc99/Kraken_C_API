#include <inttypes.h>

#include "curl.h"
#include "kraken_api.h"

char* curl_get(char *curl_cmd_string){

	FILE *curl_out = NULL;
	char *result = NULL;
	int ext_status, i_char = 0;
	size_t memcount = 0;
	size_t buf_size = BUFFER_SIZE;

	curl_out = popen(curl_cmd_string, "r");
	if(curl_out == NULL) {
		free(curl_cmd_string);
		return NULL;    /* ERROR */
	}

	if ( (result = malloc(buf_size)) == NULL ) {
		PERROR("malloc failed");
		free(curl_cmd_string);
		return NULL;           /* return on ERROR */
	}

	while (i_char != EOF) {
		i_char = fgetc(curl_out);

		if (memcount >= buf_size) {
			buf_size += BUFFER_SIZE;
			char *newres = realloc(result, buf_size);
			if (newres == NULL) {
				free(curl_cmd_string);
				free(result);  /* OK! */
				PERROR("realloc failed");
				return NULL;   /* return on ERROR */
			}
			result = newres;
		}

		/* skip newline chars */
		(i_char == '\n') ? i_char = ' ' : i_char;

		*(result + memcount) = (char)i_char;
		memcount++;
	}
	/* replace the EOF char with the terminate string char */
	memcount--;
	*(result + memcount) = '\0';

	if((ext_status = pclose(curl_out)) != 0){
		PERRORX("ERROR on pclose - errno-string: %s, curl exit status: %i\n",strerror(errno), ext_status);
		free(curl_cmd_string);
		free(result);
		return NULL;
	}

	/* free memory allocated by query_[private/public]() */
	free(curl_cmd_string);
	return result;
}

int query_private(struct kraken_api **kr_api){

	uint64_t u64_nonce;
	int uri_length, uc_data_size;
	unsigned char digest[32], *uc_data;
	unsigned char *uc_b64_decoded = NULL;
	unsigned char *uc_hmac_output = NULL;
	char* hmac_out = NULL;
	char* str_nonce = NULL;
	const char* url_nonce = "nonce=";
	char* url_seperator ="&";
	char* s_sha256 = NULL;
	char* curl_cmd_string = NULL;
	char* curl_query_url = NULL;
	char* curl_nonce_url = NULL;
	struct timeval sys_time;
	struct timezone sys_tz;

	if(strlen((*kr_api)->s_sec_key) != 88){
		PDEBUG("Error: Private key must be 88 characters long");
		return -1;
	}

	/* create nonce */
	sys_tz.tz_minuteswest = 0;
	sys_tz.tz_dsttime = 0;

	gettimeofday(&sys_time, &sys_tz);

	u64_nonce = ((uint64_t)sys_time.tv_sec * 1000000) + sys_time.tv_usec;

	/* create string from nonce */
	if( (asprintf(&str_nonce, "%" PRIu64, u64_nonce)) < 0){
		PDEBUG("ERROR - asprintf malloc failed");
		return -1;
	}

	PTRACEX("Nonce: %s", str_nonce);

	/* create nonce url with the nonce + the specific data */
	/*   set the "nonce=" to the string */
	curl_nonce_url = to_url(curl_nonce_url, url_nonce);
	/*   append the nonce string to the url */
	curl_nonce_url = to_url(curl_nonce_url, str_nonce);
	/* example curl_nonce_url = "nonce=1234567890123456" */

	if(((*kr_api)->s_data)){
		/* add seperator to the string */
		curl_nonce_url = to_url(curl_nonce_url, url_seperator);
		/* add the rest URI-data to the url-string */
		curl_nonce_url = to_url(curl_nonce_url, (*kr_api)->s_data);
	}

	PTRACEX("curl_nonce_url: %s", curl_nonce_url);

	/* CRYPTO FUNCTIONS */
	/*   s_sha256 = "1234567890123456nonce=12332.....pair=XBT.."  */
	s_sha256 = to_url(s_sha256, str_nonce);
	s_sha256 = to_url(s_sha256, curl_nonce_url);
	PTRACEX("s_sha256 nonce: %s", s_sha256);

	/* execute SHA256 hash-algorithm */
	if((sha256(s_sha256, digest)) != 0){
		PDEBUG("Error calling SHA256");
		return -1;
	}

	uri_length = (int)strlen((*kr_api)->tmp_query_url);
	PTRACEX("uri_path: %s", (*kr_api)->tmp_query_url);

	uc_data_size = uri_length + SHA256_DIGEST_LENGTH;

	/* MALLOC: posix functions cannot be used;
	 * a trailing '\0' must not exist */
	uc_data = malloc(uc_data_size);

	memcpy(uc_data, (*kr_api)->tmp_query_url, uri_length);
	memcpy(uc_data+uri_length, digest, SHA256_DIGEST_LENGTH);

	/* BASE64 decoding */
	uc_b64_decoded = base64_decode((*kr_api)->s_sec_key, uc_b64_decoded);

	/* HMAC decoding */
	uc_hmac_output = hmac_sha512(uc_data, uc_b64_decoded, uc_hmac_output, uc_data_size);

	hmac_out = base64_encode(uc_hmac_output);

	PTRACEX("HMAC out: %s", hmac_out);

	/* create the curl query string:
	 * complete tmp_query_url */
	curl_query_url = strdup((*kr_api)->s_url);
	curl_query_url = to_url(curl_query_url, (*kr_api)->tmp_query_url);

	/* GENERATE THE CURL COMMAND LINE ARGUMENT STRING */
	/* -tlsv1.3 to force TLS V1.3 support */
	curl_cmd_string = strdup("curl -sS -tlsv1.3 --data ");
	curl_cmd_string = to_url(curl_cmd_string, "\"");
	curl_cmd_string = to_url(curl_cmd_string, curl_nonce_url);
	curl_cmd_string = to_url(curl_cmd_string, "\" ");
	curl_cmd_string = to_url(curl_cmd_string, "--header ");
	curl_cmd_string = to_url(curl_cmd_string, "\"");
	curl_cmd_string = to_url(curl_cmd_string, "API-Key: ");
	curl_cmd_string = to_url(curl_cmd_string, (*kr_api)->s_api_key);
	curl_cmd_string = to_url(curl_cmd_string, "\" ");
	curl_cmd_string = to_url(curl_cmd_string, "--header ");
	curl_cmd_string = to_url(curl_cmd_string, "\"");
	curl_cmd_string = to_url(curl_cmd_string, "API-Sign: ");
	curl_cmd_string = to_url(curl_cmd_string, hmac_out);
	curl_cmd_string = to_url(curl_cmd_string, "\" ");
	curl_cmd_string = to_url(curl_cmd_string, curl_query_url);

	/* free s_data only if it was used */
	if( (*kr_api)->s_data != NULL ){
		free((*kr_api)->s_data);
		(*kr_api)->s_data = NULL;
	}

	free(curl_query_url);
	free(curl_nonce_url);
	free((*kr_api)->tmp_query_url);
	(*kr_api)->tmp_query_url = NULL;
	free(str_nonce);
	free(s_sha256);
	free(uc_data);
	free(uc_b64_decoded);
	free(hmac_out);
	free(uc_hmac_output);

	PTRACEX("\n%s\n", curl_cmd_string);
	(*kr_api)->s_result = curl_get(curl_cmd_string);

	return 0;
}

int query_public(struct kraken_api **kr_api){
	char* curl_query_url = NULL;
	char* curl_cmd_string = NULL;

	/* create the curl query string:
	 * complete tmp_query_url */
	curl_query_url = strdup((*kr_api)->s_url);
	curl_query_url = to_url(curl_query_url, (*kr_api)->tmp_query_url);

	/* GENERATE THE CURL COMMAND LINE ARGUMENT STRING */
	/* -tlsv1.3 to force TLS V1.3 support */
	curl_cmd_string = strdup("curl -sS -tlsv1.3 ");

	PTRACEX("curl query: %s", (*kr_api)->s_data);

	if((*kr_api)->s_data){
		curl_cmd_string = to_url(curl_cmd_string, "--data ");
		curl_cmd_string = to_url(curl_cmd_string, "\"");
		curl_cmd_string = to_url(curl_cmd_string, (*kr_api)->s_data);
		curl_cmd_string = to_url(curl_cmd_string, "\" ");
	}

	curl_cmd_string = to_url(curl_cmd_string, "\"");
	curl_cmd_string = to_url(curl_cmd_string, curl_query_url);
	curl_cmd_string = to_url(curl_cmd_string, "\"");

	PTRACEX("curl query: %s", curl_cmd_string);

	/* free s_data only if it was used */
	if( (*kr_api)->s_data != NULL ){
		free((*kr_api)->s_data);
		(*kr_api)->s_data = NULL;
	}

	free((*kr_api)->tmp_query_url);
	(*kr_api)->tmp_query_url = NULL;

	free(curl_query_url);

	(*kr_api)->s_result = curl_get(curl_cmd_string);

	return 0;
}
