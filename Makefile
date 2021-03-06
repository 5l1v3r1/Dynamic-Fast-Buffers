BASEDIR=.
OUTDIR= $(BASEDIR)/output
CC=gcc
CPP=g++
LN=g++
AR=ar
CP=cp
LNK=ln


-include $(EPROSIMADIR)/building/makefiles/eProsima.mk
-include $(BASEDIR)/building/makefiles/dfb.mk

.PHONY: all

all: dfb

clean:
	@rm -f $(OBJS)
	@rm -f $(DEPS)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif
