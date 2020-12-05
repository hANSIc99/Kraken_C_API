#include "kraken_api.h"
/*!
 * \file main.c
 * \brief <b>Open me! I'm full of examples!</b>
 *
 * Contains examples of how to use this api.
 */

/*! \mainpage Application interface for Kraken.com written in C
 *
 * \section intro_sec Introduction
 *
 * This API ist intended for use in Linux/Unix-like systems.\n\n
 *
 * The API depends on <em>Curl</em>.\n
 * On the most distributions, <em>Curl</em> is installed by default, if not, you can get it here:
 * <a href=https://curl.haxx.se/>https://curl.haxx.se/</a>.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Include kraken_api.h to your project.
 * Set/unset *DEBUG* or *TRACE* in the makefile to get trace/debug information
 * printed to stdout.
 * \subsection step2 Step 2: Look into the documentation of main.c for exaples.
 *
 * Find examples of all API calls in the documentation of main.c.
 * \n\n
 * If you have any suggestions feel free to contact me on s.avenwedde@gmail.com
 *
 *
 */



/*!
 *
 * <h3>Initialization</h3>
 * See the description of <em>kraken_init()</em>.\n
 * Memory which is allocated here is freed in <em>kraken_clean()</em>.
 * \code
 *
 * struct kraken_api *kr_api = NULL;
 *
 * const char *api_key = "api_key";
 * const char *sec_key = "sec_key";
 *
 * kraken_init(&kr_api, api_key, sec_key);
 *
 * \endcode
 * \n\n
 *
 * <h3>Setting optional arguments</h3>\n
 * Possible arguments found at the description of <em>kraken_set_opt()</em>,\n
 * or at <a href=https://www.kraken.com/help/api>kraken api description</a>.
 *
 * \code
 * kraken_set_opt(&kr_api, "pair", "ETCXBT");
 * \endcode
 * \n\n
 *
 * <h3>Private user trading examples:\n</h3>
 *
 * <b>market</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIR, VOLUME)\n
 * Buy/sell assets at the best market price.
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "market", "XXBTZEUR", "0.43");
 * \endcode
 * \n\n
 *
 * <b>limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIR, VOLUME, LIMIT-PRICE)\n
 * Buy/sell at a fixed price.
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "limit", "XXBTZEUR", "0.43", "702.5432");
 * \endcode
 * \n\n
 *
 * <b>stop-loss</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-PRICE)\n
 * Buy at market once market price >= stop price.\n
 * Sell at market once market price is <= stop price.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss", "XXBTZEUR", "0.43", "702.5432");
 * \endcode
 * \n\n
 *
 * <b>take-profit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TAKE-PROFIT-PRICE)\n
 * Buy at market once market price <= take profit price.\n
 * Sell at market once market price >= take profit price.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "take-profit", "XXBTZEUR", "0.43", "702.5432");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-profit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-PRICE, TAKE-PROFIT)\n
 * Buy at market once market price >= stop-price or <= take-profit, therefore: stop > profit.\n
 * Sell at market once market price <= stop-price or >= take-profit, therefore: stop < profit.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-profit-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-PRICE, PROFIT/LIMIT)\n
 * Buy at <em>market</em> if >= <em>stop-price</em> or at fixed price if <em>market</em> <= <em>take-profit</em>, therefore: <em>stop</em> > <em>profit</em>.\n
 * Sell at <em>market</em> if <= <em>stop-price</em> or a fixed price if <em>market</em> >= <em>limit</em>, therefore: <em>stop</em> < <em>profit</em>.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-TRIGGER, TRIGGERED-LIMIT)\n
 * Buy at fixed price once <em>market price</em> >= <em>stop price</em>, therefore <em>stop</em> < <em>limit</em>.\n
 * Sell at fixed price once <em>market price</em> <= <em>stop price</em>.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>take-profit-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TAKE-PROFIT-TRIGGER, TRIGGERED-LIMIT)\n
 * Buy at fixed price once <em>market price</em> <= <em>take profit price</em>.\n
 * Sell at fixed price once <em>market price</em> >= <em>take profit price</em>.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>trailing-stop</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TRAILING-STOP-OFFSET)\n
 * Buy at market once <em>price</em> >= <em>stop offset</em> from low.\n
 * Sell at market once <em>price</em> <= <em>stop offset</em> from high.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00");
 * \endcode
 * \n\n
 *
 * <b>trailing-stop-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TRAILING-STOP-OFFSET, TRIGGERED-LIMIT-OFFSET)\n
 * Buy at fixed price once <em>market</em> >= <em>stop offset</em> from low.\n
 * Sell at fixed price once <em>market</em> <= <em>stop offset</em> from high.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "0.4", "0.2");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-and-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-PRICE, LIMIT-PRICE)\n
 * Buy at fixed price or at <em>market</em> if >= <em>stop price</em>.\n
 * Sell at fixed price or at <em>market</em> if <= <em>stop price</em>.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "753.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>settle-position</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME)\n
 * Settle position at the original order price.\n
 * \code
 * kr_api->priv_func->add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43");
 * \endcode
 * \n\n
 *
 * <b>cancel-order</b>: cancel_order(&api, "ORDER-ID")\n
 * \code
 * kr_api->priv_func->cancel_order(&kr_api, "OBH2CQ-KGH4B-YFF3PA");
 * \endcode
 * \n\n
 *
 * <h3>Private user data examples:\n</h3>
 *
 * <b>get account balance</b>: get_account_balance(&api)\n
 * \code
 * kr_api->priv_func->get_account_balance(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get trade balance</b>: get_trade_balance(&api)\n
 * The function takes the optionals <b>aclass</b> and <b>asset</b> into account.\n
 * \code
 * kr_api->priv_func->get_trade_balance(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get open orders</b>: get_open_orders(&api)\n
 * The function takes the optionals <b>trades</b> and <b>userref</b> into account.\n
 * \code
 * kr_api->priv_func->get_open_orders(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get closed orders</b>: get_closed_orders(&api)\n
 * The function takes the optionals <b>trades</b>, <b>userref</b>, <b>start</b>, <b>end</b>, <b>ofs</b> and <b>closetime</b> into account.\n
 * \code
 * kr_api->priv_func->get_closed_orders(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>query orders info</b>: query_order_info(&api, TXID)\n
 * TXID = Comma delimited list of transaction ids to qury info about (20 maximum).\n
 * The function takes the optionals <b>trades</b> and <b>userref</b> into account.\n
 * \code
 * kr_api->priv_func->query_order_info(&kr_api, "TR7S3C-HQA5K-H65IMX");
 * \endcode
 * \n\n
 *
 * <b>get trades history</b>: get_trades_history(&api)\n
 * The function takes the optionals <b>type</b>, <b>trades</b>, <b>start</b>, <b>end</b>, <b>ofs</b> into account.\n
 * \code
 * kr_api->priv_func->get_trades_history(&api);
 * \endcode
 * \n\n
 *
 * <b>query trades info</b>: query_trades_info(&api, TXID)\n
 * TXID = Comma delimited list of transaction ids to qury info about (20 maximum).\n
 * The function takes the optional <b>trades</b> into account.\n
 * \code
 * kr_api->priv_func->query_trades_info(&kr_api, "TR7S3C-HQA5K-H65IMX");
 * \endcode
 * \n\n
 *
 * <b>get open positions</b>: get_open_positions(&api, TXID)\n
 * TXID = Comma delimited list of transaction ids to restrict output to.\n
 * The function takes the optional <b>docalcs</b> into account.\n
 * \code
 * kr_api->priv_func->get_open_positions(&kr_api, "TR7S3C-HQA5K-H65IMX");
 * \endcode
 * \n\n
 *
 * <b>get ledgers info</b>: get_ledgers_info(&api)\n
 * The function takes the optionals <b>acalss</b>, <b>asset</b>, <b>type</b>, <b>start</b>, <b>end</b>, <b>ofs</b> into account.\n
 * \code
 * kr_api->priv_func->get_ledgers_info(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>query ledgers</b>: query_ledgers(&api, ID)\n
 * ID = Comma delimited list of ids to query info about.\n
 * \code
 * kr_api->priv_func->query_ledgers(&kr_api, "123");
 * \endcode
 * \n\n
 *
 * <b>get trade volume</b>: get_trades_history(&api)\n
 * The function takes the optionals <b>pair</b> and <b>fee-info</b> into account.\n
 * \code
 * kr_api->priv_func->get_trades_history(&kr_api, "123");
 * \endcode
 * \n\n
 *
 * <h3>Public function examples</h3>
 *
 * <b>get server time</b>: get_server_time(&api)\n
 * \code
 * kr_api->pub_func->get_server_time(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get system status</b>: get_system_status(&api)\n
 * \code
 * kr_api->pub_func->get_system_status(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get asset info</b>: get_asset_info(&api)\n
 * \code
 * kr_api->pub_func->get_asset_info(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get asset info</b>: get_asset_info(&api)\n
 * The function takes the optionals <b>info</b>, <b>aclass</b> and <b>asset</b> into account.\n
 * \code
 * kr_api->pub_func->get_asset_info(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get tradeable asset pairs</b>: get_tradable_asset_pairs(&api)\n
 * The function takes the optionals <b>info</b> and <b>pair</b> into account.\n
 * \code
 * kr_api->pub_func->get_tradable_asset_pairs(&kr_api);
 * \endcode
 * \n\n
 *
 * <b>get ticker information</b>: get_ticker_info(&api, PAIR)\n
 * PAIR = Comma delimited list of asset pairs to get info on.\n
 * \code
 * kr_api->pub_func->get_ticker_info(&kr_api, "XETCZEUR");
 * \endcode
 * \n\n
 *
 * <b>get OHLC data</b>: get_ohlc_data(&api, PAIR)\n
 * PAIR = Asset pair to get OHLC data for.\n
 * \code
 * kr_api->pub_func->get_ohlc_data(&kr_api, "XETCZEUR");
 * \endcode
 * \n\n
 *
 * <b>get order book</b>: get_order_book(&api, PAIR)\n
 * PAIR = Asset pair to get market depth for.\n
 * The function takes the optional <b>count</b> into account.\n
 * \code
 * kr_api->pub_func->get_order_book(&kr_api, "XETCZEUR");
 * \endcode
 * \n\n
 *
 * <b>get recent trades</b>: get_recent_trades(&api, PAIR)\n
 * PAIR = Asset pair to get trade data depth for.\n
 * The function takes the optional <b>since</b> into account.\n
 * \code
 * kr_api->pub_func->get_recent_trades(&kr_api, "XETCZEUR");
 * \endcode
 * \n\n
 *
 * <b>get recent spread data</b>: get_recent_spread_data(&api, PAIR)\n
 * PAIR = Asset pair to get spread data depth for.\n
 * The function takes the optional <b>since</b> into account.\n
 * \code
 * kr_api->pub_func->get_recent_spread_data(&kr_api, "XETCZEUR");
 * \endcode
 * \n\n
 *
 * <h3>De-Initialization</h3>
 * Freeing the memory that was allocated in <em>kraken_init()</em>.
 * \code
 * kraken_clean(&kr_api);
 * \endcode
 * \n
 *
 *
 *
 */


int print_n_reset(struct kraken_api *kr_api);

int print_n_reset(struct kraken_api *kr_api){
	if ( kr_api->s_result == NULL ) {
		PERROR("Failed to get the data");
		printf("Failed to get the data\n");
		return -1;
	}
	printf("RESULT BUFFER: %s\n\n", kr_api->s_result);
	free(kr_api->s_result);
	kr_api->s_result=NULL;
	return 0;
}

int main (void){
	struct kraken_api *kr_api = NULL;
	const char *api_key = "api_key";
	const char *sec_key = "sec_key";

	/* We need to call the init function: */
	kraken_init(&kr_api, api_key, sec_key);

/* EXAMPLES */
#if 0
	kraken_set_opt(&kr_api, "asset", "ZUSD");
	kraken_set_opt(&kr_api, "count", "2");
#endif
#if 0
	kraken_set_opt(&kr_api, "pair", "ETCXBT");
	kraken_set_opt(&kr_api, "validate", "true");
#endif
#if 0
	kraken_set_opt(&kr_api, "end", "1482998660");
	kraken_set_opt(&kr_api, "ofs", "ofs");
	kraken_set_opt(&kr_api, "closetime", "1482999660");
#endif

	/* PRIVATE USER TRADING */
	/* add_order returns 0 on success */
#if 0
	kr_api->priv_func->add_order(&kr_api, "buy", "trailing-stop-limit", "XXBTZEUR", "10.0", "755.00", "758.00");
#endif
#if 0
	kr_api->priv_func->cancel_order(&kr_api, "OBH2CQ-KGH4B-YFF3PA");
#endif

	/* PRIVATE USER DATA */

	/* get open orders: get_open_orders(&kr_api) */
	/* the function takes the optionals USERREF and TRADES into account (if given) */

	/* get-account-balance: get_account_balance(&api) - no further arguments or optionals */
	/* get-account-balance: get_account_balance(&kr_api) */

#if 0
	kr_api->priv_func->get_account_balance(&kr_api);
#endif

	/* the result is stored in the buffer: kr_api->s_result */
#if 0
	kr_api->priv_func->get_trade_balance(&kr_api);
#endif

#if 0
	kr_api->priv_func->get_open_orders(&kr_api);
#endif

#if 0
	kr_api->priv_func->get_closed_orders(&kr_api);
#endif

#if 0
	kr_api->priv_func->query_order_info(&kr_api, "122343445");
#endif

#if 0
	kr_api->priv_func->get_trades_history(&kr_api);
#endif

#if 0
	kr_api->priv_func->query_trades_info(&kr_api, "TR7S3C-HQA5K-H65IMB");
#endif

#if 0
	kr_api->priv_func->get_open_positions(&kr_api, "TR7S3C-HQA5K-H65IMB");
#endif

#if 0
	kr_api->priv_func->get_ledgers_info(&kr_api);
#endif

#if 0
	kr_api->priv_func->query_ledgers(&kr_api, "123");
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->priv_func->get_trade_volume(&kr_api);
	print_n_reset(kr_api);
#endif

#if 1
	kr_api->pub_func->get_server_time(&kr_api);
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_system_status(&kr_api);
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_asset_info(&kr_api);
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_tradable_asset_pairs(&kr_api);
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_ticker_info(&kr_api, "XETCZEUR");
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_ohlc_data(&kr_api, "XETCZEUR");
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_order_book(&kr_api, "XETCZEUR");
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_recent_trades(&kr_api, "XETCZEUR");
	print_n_reset(kr_api);
#endif

#if 0
	kr_api->pub_func->get_recent_spread_data(&kr_api, "XETCZEUR");
	print_n_reset(kr_api);
#endif

#if 0
	PTRACEX("BUFFER RESULT: %s", kr_api->s_result);
	free(kr_api->s_result);
	kr_api->s_result=NULL;
#endif

	/* Simple test */
#if 0
	/* asset_info with not compatible option */
	kraken_set_opt(&kr_api, "pair", "XETHZEUR,XETHZUSD");
	kr_api->pub_func->get_asset_info(&kr_api);
	print_n_reset(kr_api);
	/* tradable_asset_pairs with some options */

	kraken_set_opt(&kr_api, "pair", "XETHZEUR,XETHZUSD");
	kraken_set_opt(&kr_api, "info", "info");
	kr_api->pub_func->get_tradable_asset_pairs(&kr_api);
	print_n_reset(kr_api);
#endif
	/* cleanup function must be called to free allocated memory */
	kraken_clean(&kr_api);
}



