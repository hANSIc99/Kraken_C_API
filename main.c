#include "main_header.h"


int main (void){


struct kraken_api *kr_api = NULL;


const char *api_key = "api-key";
const char *sec_key = "sec-key";

/* init function.... */

kraken_init(&kr_api, api_key, sec_key);

/* AVAILABLE ORDERS */

/* market: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIR, VOLUME) */
/* buy/sell assets at the best market price */
/* market: add_order(&kr_api, "buy", "market", "XXBTZEUR", "0.43") */

/* limit: add_order(&api, TYPE, ORDERTYPE, ASSET-PAIT, VOLUME, LIMIT-PRICE)  */
/* buy/sell at a fixed price  */
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


#if 1
kraken_set_opt(&kr_api, "AClass", "hi"); 
kraken_set_opt(&kr_api, "expireTM", "hi2"); 
#endif

/* add_order returns 0 on success */
#if 0
kr_api->priv_func->add_order(&kr_api, "buy", "trailing-stop-limit", "XXBTZEUR", "10.0", "755.00", "758.00");
#endif

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
PTRACE("BUFFER RESULT: %s", kr_api->s_result);
#endif

/* cleanup function must be called to free allocated memory */
#if 1
kraken_clean(&kr_api);
#endif

}



