#ifndef __kr_private_trading_functions_h
#define __kr_private_trading_functions_h

#include <stdarg.h>
#include <stdint.h>
#include "kraken_api.h"
#include "logging.h"
#include "url.h"
#include "curl.h"
#include "kr_helper.h"

#define MARKET			0
#define LIMIT			1
#define STOP_LOSS		2
#define TAKE_PROFIT		3
#define STOP_LOSS_PROFIT	4
#define STOP_LOSS_PROFIT_LIMIT	5
#define STOP_LOSS_LIMIT		6
#define TAKE_PROFIT_LIMIT	7
#define TRAILING_STOP		8
#define TRAILING_STOP_LIMIT	9
#define STOP_LOSS_AND_LIMIT	10
#define SETTLE_POSITION		11
#define BADARG			-1

/*!
 * \file kr_private_trading_functions.h
 * \brief Contains private user trading functions.
 *
 * The file inherits the functions reffering to
 * <a href=https://www.kraken.com/help/api#private-user-trading>Kraken Api: Private user trading</a>.
 */

/*!
 * \brief Add standard order.
 * \param **kr_api Initialized API structure.
 * \param *type String: Type ("buy"/"sell").
 * \param *order String: Order type; possible order types are listed below.
 * \param *asset String: Asset pair.
 * \param *volume String: Volume in lots.
 * \param *... String: Argument depending upon ordertype.
 *
 * Optionals: <b>leverage</b>, <b>oflags</b>, <b>starttm</b>, <b>expiretm</b>, <b>userref</b>, <b>validate</b>,
 * <b>close-type</b>, <b>close-pc-1</b>, <b>close-pc-2</b>\n\n
 *
 * Available order types (passed as <b>String</b>):\n
 * <b>market</b>\n
 * <b>limit</b> (price = limit price)\n
 * <b>stop-loss</b> (price = stop loss price)\n
 * <b>take-profit</b> (price = take profit price)\n
 * <b>stop-loss-profit</b> (price-1 = stop loss price, price-2 = take profit price)\n
 * <b>stop-loss-profit-limit</b> (price-1 = stop loss price, price-2 = take profit price)\n
 * <b>stop-loss-limit</b> (price-1 = stop loss trigger price, price-2 = triggered limit price)\n
 * <b>take-profit-limit</b> (price-1 = take profit trigger price, price-2 = triggered limit price)\n
 * <b>trailing-stop</b> (price = trailing stop offset)\n
 * <b>trailing-stop-limit</b> (price-1 = trailing stop offset, price-2 = triggered limit offset)\n
 * <b>stop-loss-and-limit</b> (price-1 = stop loss price, price-2 = limit price)\n
 * <b>setttle-position</b>\n
 *
 * Example orders can be found in the dokumentation of main.c
 *
 * Result: See further details on <a href=https://www.kraken.com/help/api#add-standard-order>kraken api description</a>.
 * */
int addOrder(struct kraken_api **kr_api,
		const char *type,
		const char *order,
		const char *asset,
		const char* volume,
		...);

int cancelOrder(struct kraken_api **kr_api, const char *txid);


#endif
