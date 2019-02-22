#ifndef __curl_h
#define __curl_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include "kraken_api.h"
#include "url.h"
#include "logging.h"
#include "crypto.h"

#define BUFFER_SIZE 65536

/*!
 * \file curl.h
 * \brief Executes the API calls.
 *
 * This function calls curl directly  - curl has to be installed.
 *
 */

/*!
 * \brief Call the curl binary
 * \param query_string = Command line arguments for curl
 *
 * Result: Char pointer which contains the result of the api call.\n
 * Usually a JSON object.
 *
 * */
char* curl_get(char* query_string);
/*!
 * \brief Creates the query string for private api calls
 * \param kraken_api = Initialized kraken_api structure.
 *
 * This functions creates the query string for private api calls.\n
 * The public and private api key must be correct.
 *
 * */
int query_private(struct kraken_api **kr_api);
/*!
 * \brief Creates the query string for public api calls
 * \param kraken_api = Initialized kraken_api structure.
 *
 * This functions creates the query string for private api calls.\n
 * The public and private api dont have to be correct.
 *
 * */
int query_public(struct kraken_api **kr_api);


#endif

