#include "curl.h"
#include "kraken_api.h"


char* curl_get(char *query_string){

	FILE *curl_out;
	char *result;
	int ext_status, i_char;
	int memcount = 0;
	result = NULL;


	result = calloc(BUFFER_SIZE, sizeof(char));
	curl_out = popen(query_string, "r");

	if(curl_out == NULL)

		return NULL;	/* ERROR */

	do {
		i_char = fgetc(curl_out);

		memcount++;

		/* skip newline chars */
		i_char == '\n' ? i_char = ' ' : i_char;  

		*(result + (memcount-1)) = (char)i_char; 
		

	}while(i_char != EOF);

	/* replace the EOF char with the terminate string char */

	*(result + (memcount-1)) = '\0';


	if((ext_status = pclose(curl_out)) != 0){
		PERROR("ERROR on pclose");
		PERROR("ERRNO-String: %s\n",strerror(errno));
	}


	/* free memory allocated in query_private() */

	free(query_string);

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
	char* curl_query = NULL;
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


	u64_nonce = (sys_time.tv_sec * 1000000) + sys_time.tv_usec;

	/* create string from nonce */

	asprintf(&str_nonce, "%lu", u64_nonce); 

	PTRACE("Nonce: %s", str_nonce);

	/*  create nonce url with the nonce + the specific data */

	/* set the "nonce=" to the string */
	curl_nonce_url = to_url(curl_nonce_url, url_nonce);
	/* append the nonce string to the url */
	curl_nonce_url = to_url(curl_nonce_url, str_nonce);

	/* e.g. curl_nonce_url = "nonce=1234567890123456" */

	if(((*kr_api)->s_data)){

		/* add seperator to the string */

		curl_nonce_url = to_url(curl_nonce_url, url_seperator);

		/* add the rest URI-data to the url-string */

		curl_nonce_url = to_url(curl_nonce_url, (*kr_api)->s_data);
	}

	PTRACE("curl_nonce_url: %s", curl_nonce_url);


	/*  CRYPTO FUNCTIONS */
	

	/* s_sha256 = "1234567890123456nonce=12332.....pair=XBT.."  */

	s_sha256 = to_url(s_sha256, str_nonce);
	s_sha256 = to_url(s_sha256, curl_nonce_url);

	PTRACE("s_sha256 nonce: %s", s_sha256);

	/* execute SHA256 hash-algorithm */

	if((sha256(s_sha256, digest)) != 0){
		PDEBUG("Error calling SHA256"); 
		return -1;
	}

	uri_length = (int)strlen((*kr_api)->tmp_query_url);

	PTRACE("uri_path: %s", (*kr_api)->tmp_query_url);
	uc_data_size =uri_length + SHA256_DIGEST_LENGTH;


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

	PTRACE("HMAC out: %s", hmac_out);

	/* create the curl query string:
	 * complete tmp_query_url */

	curl_query_url = strdup((*kr_api)->s_url);
	curl_query_url = to_url(curl_query_url, (*kr_api)->tmp_query_url);

	/* GENERATE THE CURL COMMAND LINE ARGUMENT STRING */

	/* -tlsv1.3 to force TLS V1.3 support */

	curl_query = strdup("curl -tlsv1.3 --data ");
	curl_query = to_url(curl_query, "\"");
	curl_query = to_url(curl_query, curl_nonce_url);
	curl_query = to_url(curl_query, "\" ");
	curl_query = to_url(curl_query, "--header ");
	curl_query = to_url(curl_query, "\"");
	curl_query = to_url(curl_query, "API-Key: ");
	curl_query = to_url(curl_query, (*kr_api)->s_api_key);
	curl_query = to_url(curl_query, "\" ");
	curl_query = to_url(curl_query, "--header ");
	curl_query = to_url(curl_query, "\"");
	curl_query = to_url(curl_query, "API-Sign: ");
	curl_query = to_url(curl_query, hmac_out);
	curl_query = to_url(curl_query, "\" ");
	curl_query = to_url(curl_query, curl_query_url);



	/* free s_data only if it was used */
	if((*kr_api)->s_data)
		free((*kr_api)->s_data);

	free(curl_query_url);
	free(curl_nonce_url);
	free((*kr_api)->tmp_query_url);
	free(str_nonce);
	free(s_sha256);
	free(uc_data);
	free(uc_b64_decoded);
	free(hmac_out);
	free(uc_hmac_output);

	PTRACE("\n%s\n", curl_query);
	
	(*kr_api)->s_result = curl_get(curl_query);

	return 0;
}


int query_public(struct kraken_api **kr_api){


	char* curl_query_url	= NULL;
	char* curl_query	= NULL;

	/* create the curl query string:
	 * complete tmp_query_url */

	curl_query_url = strdup((*kr_api)->s_url);
	curl_query_url = to_url(curl_query_url, (*kr_api)->tmp_query_url);

	/* GENERATE THE CURL COMMAND LINE ARGUMENT STRING */

	/* -tlsv1.3 to force TLS V1.3 support */

	curl_query = strdup("curl -tlsv1.3 ");


	PTRACE("curl query: %s", (*kr_api)->s_data);

	if((*kr_api)->s_data){
		curl_query = to_url(curl_query, "--data ");
		curl_query = to_url(curl_query, "\"");
	        curl_query = to_url(curl_query, (*kr_api)->s_data);	
		curl_query = to_url(curl_query, "\" ");
	}

	curl_query = to_url(curl_query, "\"");
	curl_query = to_url(curl_query, curl_query_url);
	curl_query = to_url(curl_query, "\"");

	PTRACE("curl query: %s", curl_query);

	/* free s_data only if it was used */
	if((*kr_api)->s_data)
		free((*kr_api)->s_data);
	free((*kr_api)->tmp_query_url);
	free(curl_query_url);

	(*kr_api)->s_result = curl_get(curl_query);

	return 0;
}
