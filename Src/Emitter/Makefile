BINDIR := ./Bin
BINARY := $(addprefix $(BINDIR)/, emitter)

LIB_SIGNALS := ../Library/Measure.cpp ../Library/CommTerm.cpp ../Library/BinaryWrapper.cpp
LIB_NETWORK := ../Library/Client.cpp
LIB_LOGGING := ../Library/ELog/easylogging++.cc

SOURCE := ./Main.cpp \
		  $(LIB_LOGGING) \
		  $(LIB_NETWORK) \
		  $(LIB_SIGNALS) \

DEF :=
DEF += -DELPP_NO_DEFAULT_LOG_FILE

$(BINARY): $(SOURCE)
	g++ $(DEF) -g -o $(BINARY) $(SOURCE)

$(BINARY): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)
