#ifndef __crypto_h
#define __crypto_h

/*!
 * \file crypto.h
 * \brief Inherits the crypto functions.
 */

#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

#include "logging.h"

#define BIO_DECODE_SIZE 64
#define WRITE_LENGHT 64
#define KEY_LENGHT 64

  /*!
  * \brief SHA256 hashing function
  *
  * \param data = Const char array; data to be encoded.
  * \param digest = Unsigned char array; the result is written to it.
  *
  * Returns the result in an unsigned char array.
  */
int sha256(const char* data, unsigned char digest[SHA256_DIGEST_LENGTH]);
  /*!
  * \brief Base64 decoding.
  *
  * \param data = Const char array; data to be encoded.
  * \param output = Pointer to an unsigned char array which gets the result.
  *
  * Returns the result in an unsigned char array.
  */
unsigned char* base64_decode(const char* data, unsigned char* output);
  /*!
  * \brief Base64 encoding.
  *
  * \param data = Unsigned const char array.
  *
  * Returns the encoded string.
  */
char* base64_encode(unsigned char* data);
  /*!
  * \brief HMAC SHA 512 Function
  *
  * \param data = Unsigned char pointer; the data to be hashed.
  * \param key = Unsigned char pointer; key for the hash function.
  * \param output = Unsigned char pointer; contains the output of the hash function.
  * \param data_size = Int; lenght in bytes of <em>data</em>.
  *
  * The function returns the hashed value as an pointer to an unsigned char array.
  */
unsigned char* hmac_sha512(unsigned char* data, unsigned char* key, unsigned char* output, int data_size);
#endif
