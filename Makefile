EXTENSION    = dummy_data
EXTVERSION   = 1.0
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

DATA = dummy_data_test.sql
PG_CONFIG ?= pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
REGRESS      = virtual_tests

include $(PGXS)

PG_TEST_VERSION ?= $(MAJORVERSION)
TESTS        = $(wildcard test-$(VERSION)/sql/test*.sql)
REGRESS      = $(patsubst test-$(VERSION)/sql/%.sql,%,$(TESTS))
REGRESS_OPTS = --inputdir=test-$(VERSION) --load-language=plpgsql

