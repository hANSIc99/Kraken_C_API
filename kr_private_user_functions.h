#ifndef __kr_private_user_functions_h
#define __kr_private_user_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "curl.h"
#include "kr_helper.h"

/*!
 * \file kr_private_user_functions.h
 * \brief Contains private user functions.
 *
 * The file inherits the functions reffering to
 * <a href=https://www.kraken.com/help/api#private-user-data>Kraken Api: Private user data</a>.
 */

/*!
 * \brief Get account balance.
 * \param **kr_api Initialized API structure.
 *
 * Result: Array of asset names and balance amount.
 *
 * */
int account_balance(struct kraken_api **kr_api);
/*!
 * \brief Get trade balance.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>asset</b> (default = "ZUSD")\n\n
 *
 * Result: Array of trade balance info.\n
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
int trade_balance(struct kraken_api **kr_api);
/*!
 * \brief Get open orders.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>trades</b> and <b>userref</b>\n\n
 *
 * Result: Array of order info in open array with txid as the key.\n
 * See further details on <a href=https://www.kraken.com/help/api#get-open-orders>kraken api description</a>.
 *
 * */
int open_orders(struct kraken_api **kr_api);
/*!
 * \brief Get closed orders.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>trades</b>, <b>userref</b>, <b>start</b>, <b>end</b>, <b>ofs</b>, <b>closetime</b>\n\n
 *
 * Result: Array of order info.\n
 * See further details on <a href=https://www.kraken.com/help/api#get-closed-orders>kraken api description</a>.
 *
 * */
int closed_orders(struct kraken_api **kr_api);
/*!
 * \brief Query orders info.
 * \param **kr_api Initialized API structure.
 * \param txid Comma delimited list of transaction ids to query info about (20 maximum)
 *
 * Optionals: <b>trades</b> and <b>userref</b>
 *
 * Result: Associative array of orders info.\n
 * <order_txid> = order info.  See Get open_orders() / closed_orders()
 *
 * */
int query_orders(struct kraken_api **kr_api, const char* txid);
/*!
 * \brief Get trades history.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>type</b>, <b>trades</b>, <b>start</b>, <b>end</b>, <b>ofs</b>
 *
 * Result: Array of trade info.\n
 * See further details on <a href=https://www.kraken.com/help/api#get-trades-history>kraken api description</a>.
 *
 * */
int trades_history(struct kraken_api **kr_api);
/*!
 * \brief Query trades info.
 * \param **kr_api Initialized API structure.
 * \param txid Comma delimited list of transaction ids to query info about (20 maximum)
 *
 * Optionals: <b>trades</b>
 *
 * Result: Associative array of trades info.\n
 * <trade_txid> = trade info.  See Get trades_history()
 *
 * */
int trades_info(struct kraken_api **kr_api, const char* txid);
/*!
 * \brief Query trades info.
 * \param **kr_api Initialized API structure.
 * \param txid Comma delimited list of transaction ids to query info about (20 maximum)
 *
 * Optionals: <b>docalcs</b>
 *
 * Result: Associative array of open positions.\n
 * See further details on <a href=https://www.kraken.com/help/api#get-open-positions>kraken api description</a>.
 *
 * */
int open_positions(struct kraken_api **kr_api, const char* txid);
/*!
 * \brief Get ledgers info.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>aclass</b>, <b>asset</b>, <b>type</b>, <b>start</b>, <b>end</b> and <b>ofs</b>
 *
 * Result: Associative array of ledgers info.\n
 * See further details on <a href=https://www.kraken.com/help/api#get-ledgers-info>kraken api description</a>.
 *
 * */
int ledgers_info(struct kraken_api **kr_api);
/*!
 * \brief Query ledgers info.
 * \param **kr_api Initialized API structure.
 * \param *id Comma delimited list of ledger ids to query info about (20 maximum).
 *
 *
 * Result: Associative array of ledgers info.\n
 * See further details on <a href=https://www.kraken.com/help/api#query-ledgers>kraken api description</a>.
 *
 * */
int query_ledgers(struct kraken_api **kr_api, const char* id);
/*!
 * \brief Get trade volume.
 * \param **kr_api Initialized API structure.
 *
 * Optionals: <b>pair</b> and <b>fee-info</b>
 *
 * Result: Associative array.\n
 * See further details on <a href=https://www.kraken.com/help/api#get-trade-volume>kraken api description</a>.
 *
 * */
int trade_volume(struct kraken_api **kr_api);





#endif
