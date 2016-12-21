#ifndef __crypto_h
#define __crypto_h

#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

#include "logging.h"

#define BIO_DECODE_SIZE 64

unsigned char* sha256(const char* data, unsigned char digest[SHA256_DIGEST_LENGTH]);
unsigned char* base64_decode(const char* data, unsigned char* output); 
char* base64_encode(unsigned char* data);
unsigned char* hmac_sha512(unsigned char* data, unsigned char* key, unsigned char* output, int data_size);
#endif
