#ifndef __logging_h
#define __logging_h

/*
 * __FUNCTION__ -> __func__
 * * see: https://gcc.gnu.org/gcc-5/porting_to.html
 *https://gcc.gnu.org/gcc-5/porting_to.html
 */

#include <stdio.h>

#undef PDEBUGX
#ifdef API_DEBUG
#    define PDEBUGX(fmt, ...)	do{ \
					fprintf(stderr, "%s(): ", __func__); \
					fprintf(stderr, fmt, ##__VA_ARGS__); \
					fprintf(stderr, "\n"); \
				} while(0)
/* The do - while loop allows several statements in the macro
 * and reuires semicolon after the marco: PDEBUG("%s.\n", some_var);
 * This makes PDEBUG to looke a function.
 * do - while will probably be eliminated by the compiler optmisation.
 */
#else
#  define PDEBUGX(fmt, ...)
#endif

#undef PDEBUG
#ifdef API_DEBUG
#    define PDEBUG(fmt)	do{ \
					fprintf(stderr, "%s(): ", __func__); \
					fprintf(stderr, fmt); \
					fprintf(stderr, "\n"); \
				} while(0)
#else
#  define PDEBUG(fmt)
#endif

#undef PTRACEX
#ifdef API_TRACE
#    define PTRACEX(fmt, ...)	do{ \
					fprintf(stderr, "%s(): ", __func__); \
					fprintf(stderr, fmt, ##__VA_ARGS__); \
					fprintf(stderr, "\n"); \
				} while(0)
#else
#  define PTRACEX(fmt, ...)
#endif

#undef PTRACE
#ifdef API_TRACE
#    define PTRACE(fmt)	do{ \
					fprintf(stderr, "%s(): ", __func__); \
					fprintf(stderr, fmt); \
					fprintf(stderr, "\n"); \
				} while(0)
#else
#  define PTRACE(fmt)
#endif

#undef PERRORX
#ifdef API_ERROR
#    define PERRORX(fmt, ...)	do{ \
					fprintf(stderr, "%s(): ", __func__); \
					fprintf(stderr, fmt, ##__VA_ARGS__); \
					fprintf(stderr, "\n"); \
				} while(0)
#else
#  define PERRORX(fmt, ...) /* not debugging: nothing */
#endif

#undef PERROR
#ifdef API_ERROR
#    define PERROR(fmt)	do{ \
					fprintf(stderr, "%s(): ", __func__); \
					fprintf(stderr, fmt); \
					fprintf(stderr, "\n"); \
				} while(0)
#else
#  define PERROR(fmt) /* not debugging: nothing */
#endif

#endif
