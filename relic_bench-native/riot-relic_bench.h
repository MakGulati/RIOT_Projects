
#ifndef RIOT_RELIC_BENCH_H
#define RIOT_RELIC_BENCH_H

#ifndef BENCHMARK
#define BENCHMARK (10) //default
#endif

#include "xtimer.h"
#include "periph/gpio.h"
#include "board.h"

#include <stdio.h>
#include <string.h>

#include "relic_core.h"
#include "relic_conf.h"
#include "relic_label.h"
#include "relic_util.h"

#ifdef CLOCK_CORECLOCK
#define DELAY_SHORT         (CLOCK_CORECLOCK / 50)
#else
#define DELAY_SHORT         (500000UL)
#endif
#define DELAY_LONG          (DELAY_SHORT * 4)

void dumb_delay(uint32_t delay)
{
    for (uint32_t i = 0; i < delay; i++) {
        __asm__("nop");
    }
}

/*============================================================================*/
/* Macro definitions                                                          */
/*============================================================================*/

/**
 * Runs a new benchmark once.
 *
 * @param[in] LABEL			- the label for this benchmark.
 * @param[in] FUNCTION		- the function to benchmark.
 */
#define BENCHMARK_ONCE(LABEL, FUNCTION)											\
	bench_reset();															\
	util_print("BENCH: " LABEL "%*c = ", (int)(32 - strlen(LABEL)), ' ');	\
	bench_before();															\
	FUNCTION;																\
	bench_after();															\
	bench_compute(1);														\
	bench_print();															\

/**
 * Runs a new benchmark a small number of times.
 *
 * @param[in] LABEL			- the label for this benchmark.
 * @param[in] FUNCTION		- the function to benchmark.
 */
#define BENCHMARK_SMALL(LABEL, FUNCTION)										\
	bench_reset();															\
	util_print("BENCH: " LABEL "%*c = ", (int)(32 - strlen(LABEL)), ' ');	\
	bench_before();															\
	for (int i = 0; i < BENCHMARK; i++)	{									\
		FUNCTION;															\
	}																		\
	bench_after();															\
	bench_compute(BENCHMARK);												\
	bench_print();															\

#ifdef SHOW_EVERY_EXECUTION				
	#define AVERAGE_LABEL_BEGINN(LABEL) 
	#define AVERAGE_LABEL_END(N) util_print("#AVERAGE %-37c /%d= "," ",N);
	#define PRINT_SUBBBENCH subbench_print();
	#define LABEL_SUBBENCH(LABEL,BENCHMARK)	util_print("BENCH(%0*i/%*d): %-32s = ", 2,_b+1,2, BENCHMARK, LABEL);	
#else
	#define AVERAGE_LABEL_BEGINN(LABEL) util_print("BENCH: " LABEL "%*c = ", (int)(32 - strlen(LABEL)), ' '); 
	#define AVERAGE_LABEL_END 
	#define PRINT_SUBBBENCH 
	#define LABEL_SUBBENCH(LABEL,BENCHMARK) 
#endif

/**
 * Runs a new benchmark.
 *
 * @param[in] LABEL			- the label for this benchmark.
 */
#define BENCHMARK_BEGIN(LABEL)										\
	bench_reset();													\
	AVERAGE_LABEL_BEGINN(LABEL)										\
	for (int _b = 0; _b < BENCHMARK; _b++)	{						\
	LABEL_SUBBENCH(LABEL,BENCHMARK)									\
	
/**
 * Prints the average timing of each execution in the chosen metric.
 */
#define BENCHMARK_END							\
	}											\
	AVERAGE_LABEL_END(BENCHMARK)							\
	bench_compute(BENCHMARK);					\
	bench_print();								\

/**
 * Prints the average timing of each execution amortized by N.
 *
 * @param N				- the amortization factor.
 */
#define BENCHMARK_DIV(N)						\
	}											\
	AVERAGE_LABEL_END(N)						\
	bench_compute(N);				\
	bench_print()								\

/**
 * Measures the time of one execution and adds it to the benchmark total.
 *
 * @param[in] FUNCTION		- the function executed.
 */
#define BENCHMARK_ADD(FUNCTION)													\
	bench_before();								\
		FUNCTION;								\
	bench_after();								\
	PRINT_SUBBBENCH								\

/*============================================================================*/
/* Type definitions                                                           */
/*============================================================================*/

/**
 * Timer type.
 */
#if OPSYS == DUINO && TIMER == HREAL

typedef uint32_t bench_t;

#elif TIMER == HREAL || TIMER == HPROC || TIMER == HTHRD

#include <sys/time.h>
#include <time.h>
typedef struct timespec bench_t;

#elif TIMER == ANSI

#include <time.h>
typedef clock_t bench_t;

#elif TIMER == POSIX

#include <sys/time.h>
typedef struct timeval bench_t;

#elif TIMER == CYCLE

typedef unsigned long long bench_t;

#else

typedef unsigned long long bench_t;

#endif

bench_t oldTotal=0;

#if OPSYS == DUINO && TIMER == HREAL
/*
 * Prototype for Arduino timing function.
 *
 * @return The time in microseconds since the program began running.
 */
uint32_t micros();
#endif

/*============================================================================*/
/* Private definitions                                                        */
/*============================================================================*/

#if defined(OVERH) && defined(TIMER) && BENCHMARK > 1

/**
 * Dummy function for measuring benchmarking overhead.
 *
 * @param a				- the dummy parameter.
 */
static void empty(int *a) {
	(*a)++;
}

#endif /* OVER && TIMER && BENCHMARK_NUM > 1 */

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

#if defined(OVERH) && defined(TIMER) && BENCHMARK > 1

void bench_overhead(void) {
	ctx_t *ctx = core_get();
	int a[BENCHMARK + 1];
	int *tmpa;

	do {
		ctx->over = 0;
		for (int l = 0; l < BENCHMARK; l++) {
			ctx->total = 0;
			/* Measure the cost of (n^2 + over). */
			bench_before();
			for (int i = 0; i < BENCHMARK; i++) {
				tmpa = a;
				for (int j = 0; j < BENCHMARK; j++) {
					empty(tmpa++);
				}
			}
			bench_after();
			/* Add the cost of (n^2 + over). */
			ctx->over += ctx->total;
		}
		/* Overhead stores the cost of n*(n^2 + over) = n^3 + n*over. */
		ctx->total = 0;
		/* Measure the cost of (n^3 + over). */
		bench_before();
		for (int i = 0; i < BENCHMARK; i++) {
			for (int k = 0; k < BENCHMARK; k++) {
				tmpa = a;
				for (int j = 0; j < BENCHMARK; j++) {
					empty(tmpa++);
				}
			}
		}
		bench_after();
		/* Subtract the cost of (n^3 + over). */
		ctx->over -= ctx->total;
		/* Now overhead stores (n - 1)*over, so take the average to obtain the
		 * overhead to execute BENCHMARK operations inside a benchmark. */
		ctx->over /= (BENCHMARK - 1);
		/* Divide to obtain the overhead of one operation pair. */
		ctx->over /= BENCHMARK;
	} while (ctx->over < 0);
	ctx->total = ctx->over;
	bench_print();
}

#endif /* OVER && TIMER && BENCHMARK > 1 */

void bench_reset(void) {
#if defined(MODULE_XTIMER)
xtimer_init();
#endif
#ifdef TIMER
puts("right bench reset");
	core_get()->total = 0;
	core_get()->after = 0;
	core_get()->before = 0;
#elif
	total = 0;
	after = 0;
	before = 0;
#endif
	oldTotal = 0;
}

void bench_before(void) {
#if defined(MODULE_XTIMER)
	core_get()->before = xtimer_now_usec();
#elif OPSYS == DUINO && TIMER == HREAL
	core_get()->before = micros();
#elif TIMER == HREAL || TIMER == HPROC || TIMER == HTHRD
	clock_gettime(CLOCK, &(core_get()->before));
#elif TIMER == ANSI
	core_get()->before = clock();
#elif TIMER == POSIX
	gettimeofday(&(core_get()->before), NULL);
#elif TIMER == CYCLE
	core_get()->before = arch_cycles();
#endif
}

void bench_after(void) {
	ctx_t *ctx = core_get();
	long long result;

#if defined(MODULE_XTIMER)
	core_get()->after = xtimer_now_usec();
	result = (ctx->after - ctx->before);
	util_print("after result: %09" PRIu32 " microsec", result);
#elif OPSYS == DUINO && TIMER == HREAL
	core_get()->after = micros();
	result = (ctx->after - ctx->before);
#elif TIMER == HREAL || TIMER == HPROC || TIMER == HTHRD
	clock_gettime(CLOCK, &(ctx->after));
	result = ((long)ctx->after.tv_sec - (long)ctx->before.tv_sec) * 1000000000;
	result += (ctx->after.tv_nsec - ctx->before.tv_nsec);
#elif TIMER == ANSI
	ctx->after = clock();
	result = (ctx->after - ctx->before) * 1000000 / CLOCKS_PER_SEC;
#elif TIMER == POSIX
	gettimeofday(&(ctx->after), NULL);
	result = ((long)ctx->after.tv_sec - (long)ctx->before.tv_sec) * 1000000;
	result += (ctx->after.tv_usec - ctx->before.tv_usec);
#elif TIMER == CYCLE
	ctx->after = arch_cycles();
  	result = (ctx->after - ctx->before);
#endif

#ifdef TIMER
	ctx->total += result;
#else
	(void)result;
	(void)ctx;
#endif
}

void bench_compute(int benches) {
	ctx_t *ctx = core_get();
#ifdef TIMER
	ctx->total = ctx->total / benches;
#ifdef OVERH
	ctx->total = ctx->total - ctx->over;
#endif /* OVERH */
#else
	(void)benches;
	(void)ctx;
#endif /* TIMER */
}

/*
* prints ellapsed time since last messured
*/
void subbench_print(void) {
	ctx_t *ctx = core_get();

#if TIMER == POSIX || TIMER == ANSI || (OPSYS == DUINO && TIMER == HREAL)
//	util_print("%lld microsec", ctx->total - oldTotal);
	util_print("%09" PRIu32 " microsec", ctx->total-oldTotal);
	oldTotal = ctx->total;
#elif TIMER == CYCLE
	util_print("%lld cycles", total - after);
#else
	util_print("%lld nanosec", total - after);
#endif
	if (ctx->total < 0) {
		util_print(" (overflow or bad overhead estimation)\n");
	} else {
		util_print("\n");
	}
}

void bench_print(void) {
	ctx_t *ctx = core_get();

#if TIMER == POSIX || TIMER == ANSI || (OPSYS == DUINO && TIMER == HREAL)
	//util_print("%lld microsec", ctx->total);
	util_print("%09" PRIu32 " microsec", ctx->total);
#elif TIMER == CYCLE
	util_print("%lld cycles", total);
#else
	util_print("%lld nanosec", total);
#endif
	if (ctx->total < 0) {
		util_print(" (overflow or bad overhead estimation)\n");
	} else {
		util_print("\n"); 
		#ifdef SHOW_EVERY_EXECUTION	
		util_print("\n");
		#endif
	}
}

ull_t bench_total(void) {
	return core_get()->total;
}


/*============================================================================*/
/*  Helper functions for debugging                                            */
/*============================================================================*/
#if ( MY_DEBUG > 2 )

/**
 * prints a hexdump of the given memory
 * 
 * @param *addr         - pointer to memory to be dumped
 * @param len           - size of addr
 */
void hexdump_mem(void *addr, int len)
{
    int i;
    unsigned char buff[17];
    const unsigned char *pc = (const unsigned char *)addr;

    // Length checks.

    if (len == 0)
    {
        printf("  ZERO LENGTH\n");
        return;
    }
    else if (len < 0)
    {
        printf("  NEGATIVE LENGTH: %d\n", len);
        return;
    }

    // Process every byte in the data.

    for (i = 0; i < len; i++)
    {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0)
        {
            // Don't print ASCII buffer for the "zeroth" line.

            if (i != 0)
                printf("  %s\n", buff);

            // Output the offset.

            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", pc[i]);

        // And buffer a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.

    while ((i % 16) != 0)
    {
        printf("   ");
        i++;
    }

    // And print the final ASCII buffer.

    printf("  %s\n\n", buff);
MD_LEN}
#else
#define print_mem(x, y)		/*empty*/
#endif

#endif /* !RELIC_BENCH_H */