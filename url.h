#ifndef __url_h
#define __url_h

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "logging.h"
#include "kraken_api.h"

#define TRUE 1
#define FALSE 0

/*!
 * \file url.h 
 * \brief Inherits the functions which create the url strings.
 * 
 */

  /*!
  * \brief Creates uri-strings.
  *
  * \param kr_data = Pointer to a kraken_api structure which is not initialized yet.
  *
  * Returns 0 on success.
  */
int make_url(struct kraken_api **kr_data);
  /*!
  * \brief Creates or concatenates char arrays.
  *
  * \param dest = Pointer to the destination char array.
  * \param source = Pointer to const char array which is added.
  *
  * Returns a char pointer to the area in memory where the result is found.
  */
char *to_url(char* dest, const char *source);

#endif
