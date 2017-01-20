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
 */
 
/*! 
 *
 * <b>Initialization</b>
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
 * <b>Setting optional arguments</b>
 *
 * \code
 * kraken_set_opt(&kr_api, "pair", "ETCXBT"); 
 * \endcode
 * \n\n
 *
 * <b>Private user trading functions</b>\n
 * Add standard oder examples:\n
 *
 * <b>market</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIR, VOLUME)\n 
 * Buy/sell assets at the best market price. 
 * \code
 * add_order(&kr_api, "buy", "market", "XXBTZEUR", "0.43");
 * \endcode
 * \n\n
 *
 * <b>limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIR, VOLUME, LIMIT-PRICE)\n 
 * Buy/sell at a fixed price.  
 * \code
 * add_order(&kr_api, "buy", "limit", "XXBTZEUR", "0.43", "702.5432");
 * \endcode
 * \n\n
 *
 * <b>stop-loss</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-PRICE)\n  
 * Buy at market once market price >= stop price.\n 
 * Sell at market once market price is <= stop price.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss", "XXBTZEUR", "0.43", "702.5432");
 * \endcode
 * \n\n
 *
 * <b>take-profit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TAKE-PROFIT-PRICE)\n
 * Buy at market once market price <= take profit price.\n
 * Sell at market once market price >= take profit price.\n 
 * \code
 * add_order(&kr_api, "buy", "take-profit", "XXBTZEUR", "0.43", "702.5432");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-profit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-PRICE, TAKE-PROFIT)\n
 * Buy at market once market price >= stop-price or <= take-profit, therefore: stop > profit.\n
 * Sell at market once market price <= stop-price or >= take-profit, therefore: stop < profit.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-profit-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-PRICE, PROFIT/LIMIT)\n
 * Buy at <em>market</em> if >= <em>stop-price</em> or at fixed price if <em>market</em> <= <em>take-profit</em>, therefore: <em>stop</em> > <em>profit</em>.\n
 * Sell at <em>market</em> if <= <em>stop-price</em> or a fixed price if <em>market</em> >= <em>limit</em>, therefore: <em>stop</em> < <em>profit</em>.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-TRIGGER, TRIGGERED-LIMIT)\n
 * Buy at fixed price once <em>market price</em> >= <em>stop price</em>, therefore <em>stop</em> < <em>limit</em>.\n
 * Sell at fixed price once <em>market price</em> <= <em>stop price</em>.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>take-profit-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TAKE-PROFIT-TRIGGER, TRIGGERED-LIMIT)\n
 * Buy at fixed price once <em>market price</em> <= <em>take profit price</em>.\n
 * Sell at fixed price once <em>market price</em> >= <em>take profit price</em>.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>trailing-stop</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TRAILING-STOP-OFFSET)\n
 * Buy at market once <em>price</em> >= <em>stop offset</em> from low.\n
 * Sell at market once <em>price</em> <= <em>stop offset</em> from high.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00");
 * \endcode
 * \n\n
 *
 * <b>trailing-stop-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TRAILING-STOP-OFFSET, TRIGGERED-LIMIT-OFFSET)\n
 * Buy at fixed price once <em>market</em> >= <em>stop offset</em> from low.\n
 * Sell at fixed price once <em>market</em> <= <em>stop offset</em> from high.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "0.4", "0.2");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-and-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-PRICE, LIMIT-PRICE)\n
 * Buy at fixed price or at <em>market</em> if >= <em>stop price</em>.\n
 * Sell at fixed price or at <em>market</em> if <= <em>stop price</em>.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "753.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>settle-position</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME)\n
 * Settle position at the original order price.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43");
 * \endcode
 * \n\n
 *
 * <b>cancel-order</b>: cancel_order(&api, "ORDER-ID")\n
 * \code
 * cancel_order(&kr_api, "OBH2CQ-KGH4B-YFF3PA");
 * \endcode
 * \n\n
 *
 *
 *
 * <b>De-Initialization</b>. 
 *
 * \code
 *
 * kraken_clean(&kr_api);
 *
 * \endcode
 *  
 *
 * <b>AddOrder</b>
 *
 */
 

/*! 
 * \brief Programm entry point.
 *
 * Here a some example of how to use this api:
 *
 * */
int main (void){


struct kraken_api *kr_api = NULL;



const char *api_key = "api_key";
const char *sec_key = "sec_key";
/* init function.... */

kraken_init(&kr_api, api_key, sec_key);

/* EXAMPLES */
#if 1
kraken_set_opt(&kr_api, "asset", "ZUSD"); 
kraken_set_opt(&kr_api, "count", "2"); 
#if 1
kraken_set_opt(&kr_api, "pair", "ETCXBT"); 
#endif
kraken_set_opt(&kr_api, "validate", "true"); 
#endif
#if 1
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

/* get-trade-balance: get_trade_balance(&kr_api, "asset-class") */
/* get-trade-balance: get_trade_balance(&kr_api)  asset class is optional */
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
#endif

#if 0
kr_api->priv_func->get_trade_volume(&kr_api);
#endif

#if 0
kr_api->pub_func->get_server_time(&kr_api);
#endif

#if 1
kr_api->pub_func->get_asset_info(&kr_api);
#endif

#if 0
kr_api->pub_func->get_tradable_asset_pairs(&kr_api);
#endif

#if 0
kr_api->pub_func->get_ticker_info(&kr_api, "XETCZEUR");
#endif

#if 0
kr_api->pub_func->get_ohlc_data(&kr_api, "XETCZEUR");
#endif

#if 0
kr_api->pub_func->get_order_book(&kr_api, "XETCZEUR");
#endif

#if 0
kr_api->pub_func->get_recent_trades(&kr_api, "XETCZEUR");
#endif

#if 0
kr_api->pub_func->get_recent_spread_data(&kr_api, "XETCZEUR");
#endif

#if 1
PTRACE("BUFFER RESULT: %s", kr_api->s_result);
#endif

/* cleanup function must be called to free allocated memory */
#if 1
kraken_clean(&kr_api);
#endif

}



