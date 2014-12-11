CC=g++
SRCDIR=.
BUILDDIR=../build
LIBBCM2835_DIR=../../lib/bcm2835-1.38
LIBBCM2835_INCDIR=$(LIBBCM2835_DIR)/src
LIBBCM2835_LIBDIR=$(LIBBCM2835_DIR)/src

LIBS=-lbcm2835 -L$(LIBBCM2835_LIBDIR) -I$(LIBBCM2835_INCDIR) -lrt -lpthread
CFLAGS=-c -Wall -O3 -std=c++11 -I$(LIBBCM2835_INCDIR)

TARGET := mcp23017demo
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o) ../../../build/mcp23017pi.o)
DEPS := $(OBJECTS:.o=.deps)

all $(TARGET): $(LIBBCM2835_LIBDIR)/libbcm2835.a $(OBJECTS) ../../../build/mcp23017pi.o
	@echo " Linking..."; $(CC) $^ $(LIBS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

../../../build/mcp23017pi.o: ../../controlblock/mcp23017pi.cpp
	@mkdir -p ../../../build/
	$(CC) $(CFLAGS) -c -o ../../../build/mcp23017pi.o ../../controlblock/mcp23017pi.cpp

$(LIBBCM2835_LIBDIR)/libbcm2835.a:
	cd $(LIBBCM2835_DIR) && ./configure
	cd $(LIBBCM2835_DIR) && $(MAKE)

check:
	# TO BE DONE! JUST A DUMMY FOR NOW
	@echo "*** NO TESTS IMPLEMENTED ***"

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)

install:
	install -d $(DESTDIR)$(bindir)
	install -m 0755 $(TARGET) $(DESTDIR)$(bindir)
	install -m 0755 ../supplementary/snesdev.cfg $(DESTDIR)/$(sysconfdir)

uninstall:
	-rm $(DESTDIR)$(bindir)/$(TARGET)
	-rm $(DESTDIR)/$(sysconfdir)/snesdev.cfg

.PHONY: clean install uninstall
