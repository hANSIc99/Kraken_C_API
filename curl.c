#include "curl.h"
#include "kraken_api.h"


char* curl_get(char *query_string){

	FILE *curl_out;
	char *result;
	int ext_status, i_char;
	int memcount = 0;
	result = NULL;


	result = calloc(10000, sizeof(char));
	curl_out = popen(query_string, "r");
	if(curl_out == NULL)
		return NULL;	/* ERROR */

	do {
		i_char = fgetc(curl_out);

		memcount++;

		/* allocate memory for every char */

		/* skip newline chars */
		i_char == '\n' ? i_char = ' ' : i_char;  

		*(result + (memcount-1)) = (char)i_char; 
		

	}while( i_char != EOF);

	/* replace the EOF char with the terminate string char */

	*(result + (memcount-1)) = '\0';

	printf("\n\n");


	ext_status = pclose(curl_out);


	printf("Exit status: %d\n", ext_status);
	printf("ERRNO-String: %s\n",strerror(errno));
	printf("String lenght: %lu\n", strlen(result));

	printf("\nAccount query: %s \n", result);
	
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

	curl_query = malloc(sizeof(char) * 10000);
	curl_query_url = malloc(sizeof(char) * 3000);


	/* create nonce */

	sys_tz.tz_minuteswest = 0;
	sys_tz.tz_dsttime = 0;

	gettimeofday(&sys_time, &sys_tz);

	/* malloc 16 digits + '\0' */

	u64_nonce = (sys_time.tv_sec * 1000000) + sys_time.tv_usec;

	asprintf(&str_nonce, "%lu", u64_nonce); 

	PTRACE("Nonce: %s", str_nonce);

	/* baustelle */

	/*  create nonce url */

	if((curl_nonce_url = strdup(url_nonce)) == NULL)
		PDEBUG("ERROR on strdup");
	

	curl_nonce_url = to_url(curl_nonce_url, str_nonce);

	if(((*kr_api)->s_data) != NULL){
	/* add seperator to the string */
	curl_nonce_url = to_url(curl_nonce_url, url_seperator);
	/* add the rest URI-data to the url-string */
	curl_nonce_url = to_url(curl_nonce_url, (*kr_api)->s_data);
	}
	PTRACE("curl_nonce_url: %s", curl_nonce_url);


	/*  CRYPTO FUNCTIONS */
	
	/* string lenght + 17 digits for the nonce */

	s_sha256 = malloc(strlen(curl_nonce_url) + 17 );

	strcpy(s_sha256, str_nonce);
	strcat(s_sha256, curl_nonce_url);

	PTRACE("s_sha256 nonce: %s", s_sha256);

	sha256(s_sha256, digest);

	uri_length = (int)strlen((*kr_api)->tmp_query_url);

	PTRACE("uri_path: %s", (*kr_api)->tmp_query_url);
	uc_data_size =uri_length + SHA256_DIGEST_LENGTH;

	uc_data = malloc(uc_data_size);

	memcpy(uc_data, (*kr_api)->tmp_query_url, uri_length);
	memcpy(uc_data+uri_length, digest, SHA256_DIGEST_LENGTH);

	/* BASE64 decoding */

	uc_b64_decoded = base64_decode((*kr_api)->s_sec_key, uc_b64_decoded);

	/* HMAC decoding */

	uc_hmac_output = hmac_sha512(uc_data, uc_b64_decoded, uc_hmac_output, uc_data_size);

	hmac_out = base64_encode(uc_hmac_output);

	PTRACE("HMAC out: %s", hmac_out);

	/* create the curl query string */


	/* complete tmp_query_url */

	strcpy(curl_query_url, (*kr_api)->s_url);
	curl_query_url = to_url(curl_query_url, (*kr_api)->tmp_query_url);

	/* -tlsv1.3 to force TLS V1.3 support */

	strcpy(curl_query, "curl -tlsv1.3 --data ");
	strcat(curl_query, "\"");
	strcat(curl_query, curl_nonce_url);
	strcat(curl_query, "\" ");
	strcat(curl_query, "--header ");
	strcat(curl_query, "\"");
	strcat(curl_query, "API-Key: ");
        strcat(curl_query, (*kr_api)->s_api_key);
	strcat(curl_query, "\" ");
	strcat(curl_query, "--header ");
	strcat(curl_query, "\"");
	strcat(curl_query, "API-Sign: ");
	strcat(curl_query, hmac_out);
	strcat(curl_query, "\" ");
	strcat(curl_query, curl_query_url);


	if((*kr_api)->s_data != NULL)
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
