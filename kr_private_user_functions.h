#ifndef __kr_private_user_functions_h
#define __kr_private_user_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "logging.h"
#include "curl.h"
#include "kr_helper.h"

/*!
 * \file kr_private_user_functions.h
 * \brief Contains private user functions.
 *
 * Further description 
 * 
 */

/*! 
 * \brief Get account balance
 * \param **kr_api Initialized API structure.
 *
 * Result: array of asset names and balance amount.
 *
 * */
int account_balance(struct kraken_api **kr_api);
/*! 
 * \brief Get trade balance
 * \param **kr_api Initialized API structure.
 * \param ... <b>char*</b>: Asset: default = <b>ZUSD</b>, can be omitted.
 *
 * Result: array of trade balance info
 * 
 * eb = equivalent balance (combined balance of all currencies)\n
 * tb = trade balance (combined balance of all equity currencies)\n
 * m = margin amount of open positions\n
 * n = unrealized net profit/loss of open positions\n
 * c = cost basis of open positions\n
 * v = current floating valuation of open positions\n
 * e = equity = trade balance + unrealized net profit/loss\n
 * mf = free margin = equity - initial margin (maximum margin available to open new positions)\n
 * ml = margin level = (equity / initial margin) * 100*\n
 *
 * */
int trade_balance(struct kraken_api **kr_api, ...);
/*! 
 * \brief Get open orders
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>trades</b> and <b>userref</b>\n\n 
 *
 * Result: array of order info in open array with txid as the key.\n
 * See further details on <a href=https://www.kraken.com/help/api#get-open-orders>kraken api description</a>
 *
 * */
int open_orders(struct kraken_api **kr_api);
/*! 
 * \brief Get closed orders
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>trades</b>, <b>userref</b>, <b>start</b>, <b>end</b>, <b>ofs</b>, <b>closetime</b>\n\n 
 *
 * Result: array of order info
 * See further details on <a href=https://www.kraken.com/help/api#get-closed-orders>kraken api description</a>
 *
 * */
int closed_orders(struct kraken_api **kr_api);
/*! 
 * \brief Query orders info
 * \param **kr_api Initialized API structure.
 * \param txid Comma delimited list of transaction ids to query info about (20 maximum)
 *
 * Optionals: <b>trades</b> and <b>userref</b>
 *
 * Result: associative array of orders info
 * <order_txid> = order info.  See Get open_orders() / closed_orders()
 *
 * */
int query_orders(struct kraken_api **kr_api, const char* txid);
/*! 
 * \brief Get trades history
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>type</b>, <b>trades</b>, <b>start</b>, <b>end</b>, <b>ofs</b>
 *
 * Result: array of trade info
 * See further details on <a href=https://www.kraken.com/help/api#get-trades-history>kraken api description</a>
 *
 * */
int trades_history(struct kraken_api **kr_api);
/*! 
 * \brief Query trades info
 * \param **kr_api Initialized API structure.
 * \param txid Comma delimited list of transaction ids to query info about (20 maximum)
 *
 * Optionals: <b>trades</b>
 *
 * Result: associative array of trades ingo
 * <trade_txid> = trade info.  See Get trades_history()
 *
 * */
int trades_info(struct kraken_api **kr_api, const char* txid);
/*! 
 * \brief Query trades info
 * \param **kr_api Initialized API structure.
 * \param txid Comma delimited list of transaction ids to query info about (20 maximum)
 *
 * Optionals: <b>docalcs</b>
 *
 * Result: associative array of open positions
 * See further details on <a href=https://www.kraken.com/help/api#get-open-positions>kraken api description</a>
 *
 * */
int open_positions(struct kraken_api **kr_api, const char* txid);
int ledgers_info(struct kraken_api **kr_api);
int query_ledgers(struct kraken_api **kr_api, const char* id);
int trade_volume(struct kraken_api **kr_api);





#endif
