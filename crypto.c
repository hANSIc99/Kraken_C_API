#include "crypto.h"

static size_t calcDecodeLength(const char* b64input) { //Calculates the length of a decoded string
	size_t len = strlen(b64input),
		padding = 0;

	if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len-1] == '=') //last char is =
		padding = 1;

	return (len*3)/4 - padding;
}

unsigned char* sha256(const char* data, unsigned char digest[SHA256_DIGEST_LENGTH]){
	

	printf("\nsha256 in: %s\n", data);

	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, data, strlen(data));
	SHA256_Final(digest, &ctx);


	printf("\nsha256 digest lenght: %d\n", SHA256_DIGEST_LENGTH);
	return digest;
}


unsigned char* base64_decode(const char* data, unsigned char* output){ 
//Decodes a base64 encoded string

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

	printf("\nb64 decoded_lenght: %d\n", decode_lenght);	

	if (decoded_size < 0)
		PDEBUG("ERROR in decoding");
	else
		PTRACE("b64 decoding successfull; decoded_size: %d", decoded_size);
	return output;
}	

char* base64_encode(unsigned char* data){


	BIO *b64, *bio_mem;
	char* output;	/*!< description */	
	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	bio_mem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bio_mem);


	/* hier eventuell size anpassen */
	BIO_write(b64, data, 64);
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
	HMAC_Init_ex(&ctx, key, 64, EVP_sha512(), NULL);

	HMAC_Update(&ctx, data, data_size);
	HMAC_Final(&ctx, output, &lenght);

	HMAC_CTX_cleanup(&ctx);

	return output;

}


