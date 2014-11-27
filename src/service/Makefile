CC=g++
SRCDIR=.
BUILDDIR=../../build
LIBWIRINGPI_DIR=/usr/local
LIBWIRINGPI_INCDIR=$(LIBWIRINGPI_DIR)/include
LIBWIRINGPI_LIBDIR=$(LIBWIRINGPI_DIR)/lib
LIBS=-lwiringPi -L$(LIBWIRINGPI_LIBDIR) -I$(LIBWIRINGPI_INCDIR) -lrt -lpthread
CFLAGS=-c -Wall -O3 -std=c++11 -I$(LIBWIRINGPI_INCDIR)

TARGET := $(BUILDDIR)/controlblock
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

all $(TARGET): $(LIBWIRINGPI_LIBDIR)/libwiringPi.a $(OBJECTS)
	@echo " Linking..."; $(CC) $^ $(LIBS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

$(LIBWIRINGPI_LIBDIR)/libwiringPi.a:
	cd ../lib/wiringPi/wiringPi/ && $(MAKE) static
	cd ../lib/wiringPi/wiringPi/ && $(MAKE) install-static
	cd ../lib/wiringPi/wiringPi/ && $(MAKE) install-headers

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
