BINDIR := ./Bin
SOURCE := ./Main.cpp ../Library/Server.cpp ../Library/Measure.cpp ../Library/BinaryWrapper.cpp
BINARY := $(addprefix $(BINDIR)/, collector)

$(BINARY): $(SOURCE)
	g++ -g -o $(BINARY) $(SOURCE)

$(BINARY): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)
