#ifndef __public_functions_h
#define __public_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "kr_helper.h"
#include "logging.h"
#include "url.h"
#include "curl.h"

/*!
 * \file kr_public_functions.h
 * \brief Contains the public functions.
 *
 * The api key ist not necessary to call the functions defined
 * in here.
 * 
 */

/*! 
 * \brief Get the server time.
 * \param **kr_api Initialized API structure.
 *
 * Result: 10-digit Unix-timestamp & rfc1123 
 * See further details on <a href=https://www.kraken.com/help/api#get-server-time>kraken api description</a>
 * */
int server_time(struct kraken_api **kr_api);
/*! 
 * \brief Retrieve asset info.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>info</b>, <b>aclass</b> and <b>asset</b>\n\n 
 *
 * Result: Array of asset pair names and their info. 
 * See further details on <a href=https://www.kraken.com/help/api#get-asset-info>kraken api description</a>
 * */
int asset_info(struct kraken_api **kr_api);
/*! 
 * \brief Get tradeable asset pairs.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>info</b> and <b>pair</b> \n\n 
 *
 * Result: Array of pair names and their info. 
 * See further details on <a href=https://www.kraken.com/help/api#get-tradable-pairs>kraken api description</a>
 * */
int asset_pairs(struct kraken_api **kr_api);
int ticker_info(struct kraken_api **kr_api, const char *pair);
int ohlc_data(struct kraken_api **kr_api, const char *pair);
int order_book(struct kraken_api **kr_api, const char *pair);
int recent_trades(struct kraken_api **kr_api, const char *pair);
int spread_data(struct kraken_api **kr_api, const char *pair);




#endif
