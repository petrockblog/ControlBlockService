CC=g++
SRCDIR=.
BUILDDIR=../../build
LIBWIRINGPI_DIR=../lib/wiringPi/wiringPi
LIBWIRINGPI_INCDIR=$(LIBWIRINGPI_DIR)
LIBWIRINGPI_LIBDIR=$(LIBWIRINGPI_DIR)
LIBJSONCPP_DIR=../lib/jsoncpp
LIBJSONCPP_INCDIR=$(LIBJSONCPP_DIR)/include
LIBJSONCPP_LIBDIR=$(LIBJSONCPP_DIR)/build/release/lib
LIBS=-lwiringPi -ljsoncpp -L$(LIBWIRINGPI_LIBDIR) -I$(LIBWIRINGPI_INCDIR) -L$(LIBJSONCPP_LIBDIR) -I$(LIBJSONCPP_INCDIR) -lrt -lpthread
CFLAGS=-c -Wall -O3 -std=c++11 -I$(LIBWIRINGPI_INCDIR) -I$(LIBJSONCPP_INCDIR)
# CFLAGS=-c -Wall -O3 -Weffc++ -std=c++11 -I$(LIBWIRINGPI_INCDIR) -I$(LIBJSONCPP_INCDIR)

TARGET := $(BUILDDIR)/controlblock
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

all $(TARGET): $(LIBWIRINGPI_LIBDIR)/libwiringPi.a $(LIBJSONCPP_LIBDIR)/libjsoncpp.a $(OBJECTS)
	@echo " Linking..."; $(CC) $^ $(LIBS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

$(LIBWIRINGPI_LIBDIR)/libwiringPi.a:
	cd ../lib/wiringPi/wiringPi/ && $(MAKE) static
	
$(LIBJSONCPP_LIBDIR)/libjsoncpp.a:
	cd ../lib/jsoncpp/ && mkdir -p build/release
	cd ../lib/jsoncpp/build/release && cmake -DCMAKE_BUILD_TYPE=release -DJSONCPP_LIB_BUILD_SHARED=OFF -G "Unix Makefiles" ../..
	cd ../lib/jsoncpp/build/release && make	

check:
	# TO BE DONE! JUST A DUMMY FOR NOW
	@echo "*** NO TESTS IMPLEMENTED ***"

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)

install:
	install -d $(DESTDIR)$(bindir)
	install -m 0755 $(TARGET) $(DESTDIR)$(bindir)
	install -m 0755 ../../supplementary/controlblockconfig.cfg $(DESTDIR)/$(sysconfdir)

uninstall:
	-rm $(DESTDIR)$(bindir)/$(TARGET)
	-rm $(DESTDIR)/$(sysconfdir)/controlblockconfig.cfg

.PHONY: clean install uninstall
