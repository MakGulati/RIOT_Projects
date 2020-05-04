/*
 * Copyright (C) 2020 Max Pengrin Pengrin <max.pengrin@hft-stuttgart.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#define BENCHMARK (10) /**< set number of Benchmarks - !multible of 10!*/ 

#define SHOW_OUTPUT (1) /**< set if encoded/decoded string is displayed */
#define SHOW_EVERY_EXECUTION (1) // show times of individual executions

// set to display additional debugging information !todo
#define MY_DEBUG (1) // print keys 
//#define MY_DEBUG (2)  // print memory

#if (SHOW_OUTPUT == 1) || (MY_DEBUG == 1) 
#include <stdio.h>
#endif

#include <assert.h>
#include <stdlib.h>

#include "relic.h"
#include "riot-relic_bench.h"
#include "cp-bench.h"

int main(void) {
	if (core_init() != RLC_OK) {
		core_clean();
		return 1;
	}

	conf_print();
	util_banner("Benchmarks for the CP module:", 0);
util_print("** Benchmarking options:\n");
	util_print("   Number of times: %d\n", BENCHMARK);
#ifdef OVERH
	util_print("   Estimated overhead: ");
	bench_overhead();
#endif
	util_print("\n");

#if defined(WITH_BN)
	util_banner("Protocols based on integer factorization:\n", 0);
	rsa();
	rabin();
	benaloh();//HE
	paillier();//HE
#endif

#if defined(WITH_EC)
	util_banner("Protocols based on elliptic curves:\n", 0);
	if (ec_param_set_any() == RLC_OK) {
		ecdh();
		ecmqv();
		ecies();
		ecdsa();
		ecss();
		vbnn();
	} else {
		THROW(ERR_NO_CURVE);
	}
#endif

#if defined(WITH_PC)
	util_banner("Protocols based on pairings:\n", 0);
	if (pc_param_set_any() == RLC_OK) {
		sokaka();//IBE
		ibe();//IBE-bf
		bgn();//HE
		// bls();
		// bbs();
		// cls();
		// pss();
		// zss();
		//lhs();//linear multi key HE signature
	} else {
		THROW(ERR_NO_CURVE);
	}
#endif

	util_banner("FINISHED", 0);
	core_clean();
	return 0;
}
