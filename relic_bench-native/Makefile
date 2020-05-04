include ../Makefile.my_common
#include ../Makefile.iotlab

# The following boards are known to fail or have not been tested.
BOARD_BLACKLIST :=  arduino-duemilanove \
                    arduino-leonardo \
                    arduino-mega2560 \
                    arduino-nano \
                    arduino-uno \
                    atmega256rfr2-xpro \
                    atmega328p \
                    chronos \
                    derfmega128 \
                    derfmega256 \
                    f4vi1 \
                    hifive1 \
                    hifive1b \
                    mega-xplained \
                    microduino-corerf \
                    msb-430 \
                    msb-430h \
                    msbiot \
                    redbee-econotag \
                    stm32f0discovery \
                    stm32f3discovery \
                    telosb \
                    waspmote-pro \
                    wsn430-v1_3b \
                    wsn430-v1_4 \
                    z1 \
                    #

CFLAGS += -DTHREAD_STACKSIZE_MAIN=\(15*THREAD_STACKSIZE_DEFAULT\)

USEPKG += relic

USEMODULE += embunit
USEMODULE += xtimer 
#USEMODULE += periph_hwrng

USEMODULE += ps # max threadsize in runtime
USEMODULE += schedstatistics # shows runtime per thread (extends ps)
USEMODULE += heap_cmd

FEATURE_REQUIRED += periph_hwrng
FEATURE_REQUIRED += periph_gpio

CFLAGS += -DDEVELHELP=1  # extra info in modules (shows used stack in ps)

# -DWORD=32 : 	Specifies the word width of the target system. This is
#  				currently not automatically detected so adjusted to your target
#  				platform.

# The rest of the parameters are configuration parameters for RELIC described in its documentation.
#export RELIC_CONFIG_FLAGS=-DARCH=NONE -DOPSYS=NONE -DQUIET=off -DWSIZE=32 -DFP_PRIME=255 -DWITH="BN;MD;DV;FP;EP;CP;BC;EC;PC" -DSEED=ZERO -DBN_PRECI=1024 -DBENCHMARK=10 -DOVERH=on
export RELIC_CONFIG_FLAGS=-DARCH=NONE -DOPSYS=NONE -DQUIET=off -DWSIZE=32 -DFP_PRIME=256 -DWITH="BN;MD;DV;FP;FPX;EP;EPX;CP;BC;EC;PC;PP" -DSEED=ZERO -DBN_PRECI=512 -DBENCHMARK=10 -DOVERH=on

#! in latest relic WORD is renamed to WSIZE
#export RELIC_CONFIG_FLAGS=-DARCH=NONE -DOPSYS=NONE -DQUIET=off -DWORD=32 -DFP_PRIME=256 -DWITH="BN;MD;DV;FP;EP;CP;BC;EC" -DSEED=RIOTRND -DBN_PRECI=1024 -DBENCH=0
#export RELIC_CONFIG_FLAGS=-DARCH=NONE -DOPSYS=NONE -DQUIET=off -DWORD=32 -DFP_PRIME=256 -DWITH="BN;MD;DV;FP;EP;CP;BC;EC" -DSEED=ZERO -DBN_PRECI=512

include $(RIOTBASE)/Makefile.include

include $(RIOTBASE)/dist/testbed-support/Makefile.iotlab