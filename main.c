#include "main_header.h"

/*!
 * \file main.c
 * \brief API How To
 *
 * Contains examples of how to use this api.
 */

/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *  
 * etc...
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
 * Buy at market if >= stop-price or a fixed price is market <= take-profit, therefore: stop > profit.\n
 * Sell at market if <= stop or a fixed price if market >= limit, therefore: stop < profit.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
 *
 * <b>stop-loss-limit</b>: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-TRIGGER, TRIGGERED-LIMIT)\n
 * buy at fixed price once market price >= stop price, therefore stop < limit.\n
 * sell at fixed price once market price <= stop price.\n
 * \code
 * add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00");
 * \endcode
 * \n\n
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

#if 1
kraken_set_opt(&kr_api, "assetbla", "asset"); 
kraken_set_opt(&kr_api, "interval", "21600"); 
kraken_set_opt(&kr_api, "count", "2"); 
#if 0
kraken_set_opt(&kr_api, "pair", "ETCXBT"); 
#endif
kraken_set_opt(&kr_api, "aclass", "hellokitti"); 
kraken_set_opt(&kr_api, "trades", "trades"); 
kraken_set_opt(&kr_api, "validate", "true"); 
#endif
#if 1
kraken_set_opt(&kr_api, "end", "1482998660"); 
kraken_set_opt(&kr_api, "ofs", "ofs"); 
kraken_set_opt(&kr_api, "closetime", "1482999660"); 
#endif



/* AVAILABLE ORDERS */

/* PRIVATE USER TRADING */

/* add_order returns 0 on success */
#if 0
kr_api->priv_func->add_order(&kr_api, "buy", "trailing-stop-limit", "XXBTZEUR", "10.0", "755.00", "758.00");
#endif
/* market: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIR, VOLUME) */
/* buy/sell assets at the best market price */
/* market: add_order(&kr_api, "buy", "market", "XXBTZEUR", "0.43") */

/* limit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, LIMIT-PRICE)  */
/* limit: add_order(&kr_api, "buy", "limit", "XXBTZEUR", "0.43", "702.5432") */

/* stop-loss: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-PRICE)  */
/* buy at market once market price >= stop price */
/* sell at market once market price is <= stop price */
/* stop-loss: add_order(&kr_api, "buy", "stop-loss", "XXBTZEUR", "0.43", "702.5432") */

/* take-profit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TAKE-PROFIT-PRICE)  */
/* buy at market once market price <= take profit price */
/* sell at market once market price >= take profit price */
/* take-profit: add_order(&kr_api, "buy", "take-profit", "XXBTZEUR", "0.43", "702.5432") */

/* stop-loss-profit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-PRICE, TAKE-PROFIT)  */
/* buy at market once market price >= STOP-PRICE or <= TAKE-PROFIT, therefore: STOP > PROFIT */
/* sell at market once market price <= STOP-PRICE or >= TAKE-PROFIT, therefore: STOP < PROFIT */
/* stop-loss-profit: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00") */

/* stop-loss-profit-limit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-PRICE, PROFIT/LIMIT)  */
/* buy at market if >= STOP-PRICE or a fixed price is market <= TAKE-PROFIT, therefore: STOP > PROFIT */
/* sell at market if <= stop or a fixed price if market >= limit, therefore: STOP < PROFIT */
/* stop-loss-profit-limit: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00") */

/* stop-loss-limit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-TRIGGER, TRIGGERED-LIMIT) */
/* buy at fixed price once market price >= stop price, therefore STOP < LIMIT */
/* sell at fixed price once market price <= stop price */
/* stop-loss-limit: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00") */

/* take-profit-limit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TAKE-PROFIT-TRIGGER, TRIGGERED-LIMIT) */
/* buy at fixed price once market price <= take profit price */
/* sell at fixed price once market price >= take profit price */
/* take-profit-limit: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00", "755.00") */

/* trailing-stop: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TRAILING-STOP-OFFSET) */
/* buy at market once price >= stop offset from low */
/* sell at market once price <= stop offset from high  */
/* trailing-stop: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "758.00") */

/* trailing-stop-limit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, TRAILING-STOP-OFFSET, TRIGGERED-LIMIT-OFFSET) */
/* buy at fixed price once market >= stop offset from low */
/* sell at fixed price once market <= stop offset from high */
/* trailing-stop-limit: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "0.4", "0.2") */

/* stop-loss-and-limit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, STOP-LOSS-PRICE, LIMIT-PRICE) */
/* buy at fixed price or at market if >= stop price */
/* sell at fixed price or at market if <= stop price */
/* stop-loss-and-limit: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43", "753.00", "755.00") */

/* settle-position: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME) */
/* Settle position at the original order price */
/* settle-position: add_order(&kr_api, "buy", "stop-loss-profit", "XXBTZEUR", "0.43") */

/* cancel-order: cancel_order(&api, "ORDER-ID"); */
/* cancel-order: cancel_order(&kr_api, "OBH2CQ-KGH4B-YFF3PA") */

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
kr_api->priv_func->get_trade_balance(&kr_api, "ZEUR");
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

#if 1
kr_api->pub_func->get_server_time(&kr_api);
#endif

#if 0
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



