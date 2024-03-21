BINDIR := ./Bin
BINARY := $(addprefix $(BINDIR)/, emitter)

LIB_SIGNALS := ../Library/Measure.cpp ../Library/CommTerm.cpp ../Library/BinaryWrapper.cpp
LIB_NETWORK := ../Library/Client.cpp
SOURCE := ./Main.cpp \
		  $(LIB_NETWORK) \
		  $(LIB_SIGNALS) \

$(BINARY): $(SOURCE)
	g++ -g -o $(BINARY) $(SOURCE)

$(BINARY): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)
