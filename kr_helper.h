#ifndef __kr_helper_h
#define __kr_helper_h

#include "logging.h"
#include "kraken_api.h"
#include "url.h"

/*!
 * \file kr_helper.h
 * \brief Helper functions for private API calls. 
 * This file contains helper functions used by private trading and user functions.
 *
 * Currently switch_opt(struct kraken_api **kr_api) is used by both parts; the private trading and user functions.
 *
 * \file kr_helper.c
 * \var u8_opt_count
 * \brief API wide variable
 *
 * This variable is the by every functions that corresponds
 * to an API call that accept optionals.
 *
 * */



/*! 
 * \brief Set the optional arguments in API calls
 *
 * \param **kr_api Initialized API structure.
 *
 * This functions checks if options flags are set. Possible options are defined
 * in #options_listen_table[] in kraken_api.c
 *
 * The functions sets the appropriate content so the s_data variable. When
 * no content was found, the flag will be set to FALSE again.
 *
 * After this procedure the function calls itself again till all possible
 * options were checked.
 *
 * */

void switch_opt(struct kraken_api **kr_api);

#endif
