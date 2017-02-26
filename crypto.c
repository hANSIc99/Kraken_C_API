#include "crypto.h"

/* Helper function to calculate of a b64 decoded string */

static size_t calcDecodeLength(const char* b64input) { 
	size_t len = strlen(b64input),
		padding = 0;

	/* the last two chars are '=' */
	if (b64input[len-1] == '=' && b64input[len-2] == '=') 
		padding = 2;
	else if (b64input[len-1] == '=') 
		/* the last char is '=' */
		padding = 1;

	return (len*3)/4 - padding;
}

int sha256(const char* data, unsigned char digest[SHA256_DIGEST_LENGTH]){
	
	PTRACE("SHA256 input data: %s", data);

	SHA256_CTX ctx;
	if((SHA256_Init(&ctx)) != 1){
		PDEBUG("SHA256_Init failed");
		return -1;
	}

	if((SHA256_Update(&ctx, data, strlen(data))) != 1){
		PDEBUG("SHA256_Update failed");
		return -1;
	}

	if((SHA256_Final(digest, &ctx)) != 1){
		PDEBUG("SHA256_Final failed");
		return -1;
	}

	PTRACE("SHA256 digest lenght: %d", SHA256_DIGEST_LENGTH);

	return 0;
}


unsigned char* base64_decode(const char* data, unsigned char* output){ 

	BIO *bio_mem, *b64;
	int decode_lenght, decoded_size;
        decode_lenght = calcDecodeLength(data);


	output = malloc(BIO_DECODE_SIZE);

	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	bio_mem = BIO_new_mem_buf((void*)data, strlen(data));

	bio_mem = BIO_push(b64, bio_mem);
	
	decoded_size = BIO_read(bio_mem, output, strlen(data));

	BIO_free_all(bio_mem);

	PTRACE("B64 decoded_lenght: %d", decode_lenght);

	if (decoded_size < 0)
		PDEBUG("ERROR in decoding");
	else{
		PTRACE("b64 decoding successfull; decoded_size: %d", decoded_size);
	}
	return output;
}	

char* base64_encode(unsigned char* data){

	BIO *b64, *bio_mem;
	char* output;

	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	bio_mem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bio_mem);

	BIO_write(b64, data, WRITE_LENGHT);
	BIO_flush(b64);

	BUF_MEM* bptr = NULL;
	BIO_get_mem_ptr(b64, &bptr);

	output = malloc((bptr->length) +1);
	memcpy(output, bptr->data, bptr->length);
	output[bptr->length] = '\0' ;

	BIO_free_all(b64);

	return output;
}

unsigned char* hmac_sha512(unsigned char* data, unsigned char* key, unsigned char* output, int data_size){
	
	unsigned int lenght = EVP_MAX_MD_SIZE; 

	output = malloc(lenght);

	HMAC_CTX ctx;
	HMAC_CTX_init(&ctx);

	/* 64 = decoded size of base64 key decoding */
	HMAC_Init_ex(&ctx, key, KEY_LENGHT, EVP_sha512(), NULL);

	HMAC_Update(&ctx, data, data_size);
	HMAC_Final(&ctx, output, &lenght);

	HMAC_CTX_cleanup(&ctx);

	return output;
}


