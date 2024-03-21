BINDIR := ./Bin
BINARY := $(addprefix $(BINDIR)/, collector)

LIB_SIGNALS := ../Library/Measure.cpp ../Library/CommTerm.cpp
LIB_NETWORK := ../Library/Server.cpp
LIB_LOGGING := ../Library/ELog/easylogging++.cc
SOURCE := ./Main.cpp \
		  $(LIB_LOGGING) \
		  $(LIB_NETWORK) \
		  $(LIB_SIGNALS) \
          ./CollectorService.cpp \

$(BINARY): $(SOURCE)
	g++ -g -o $(BINARY) $(SOURCE)

$(BINARY): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)
