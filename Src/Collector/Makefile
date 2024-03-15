BINDIR := ./Bin
SOURCE := ./Main.cpp ./CollectorService.cpp ../Library/Server.cpp ../Library/Measure.cpp ../Library/CommTerm.cpp ../Library/BinaryWrapper.cpp
BINARY := $(addprefix $(BINDIR)/, collector)

$(BINARY): $(SOURCE)
	g++ -g -o $(BINARY) $(SOURCE)

$(BINARY): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)
