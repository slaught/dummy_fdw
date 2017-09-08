EXTENSION    = dummy_data
EXTVERSION   = 2.0
MODULE_big   = dummy_data
OBJS         =  dummy_data.o 
DOCS         = $(wildcard *.md)

BUILD_DIR = $(shell pwd)

all: $(EXTENSION)--$(EXTVERSION).sql

install: 

clobber: clean 
	-rm $(EXTENSION)--$(EXTVERSION).sql

# this doesn't
$(EXTENSION)--$(EXTVERSION).sql: $(EXTENSION).sql
	cat $< | sed 's@BUILD_DIR@$(BUILD_DIR)@' > $@

DATA = $(EXTENSION)--$(EXTVERSION).sql
PG_CONFIG ?= pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
REGRESS      = dummy_data_test dummy_data_test2

include $(PGXS)

PG_TEST_VERSION ?= $(MAJORVERSION)
REGRESS_OPTS = --inputdir=sql --load-language=plpgsql --dbname=regression

