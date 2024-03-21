BINDIR := ./Bin
BINARY := $(addprefix $(BINDIR)/, collector)

LIB_SIGNALS := ../Library/Measure.cpp ../Library/CommTerm.cpp
LIB_NETWORK := ../Library/Server.cpp
SOURCE := ./Main.cpp \
		  $(LIB_NETWORK) \
		  $(LIB_SIGNALS) \
          ./CollectorService.cpp \

$(BINARY): $(SOURCE)
	g++ -g -o $(BINARY) $(SOURCE)

$(BINARY): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)
