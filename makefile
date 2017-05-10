CVER = g++
WFLAGS = -Wall -Werror -ansi -pedantic
ODIR = bin

all: rshell

rshell: ; mkdir -p $(ODIR) ; $(CVER) src/main.cpp src/And.cpp src/Cmd.cpp src/Connector.cpp src/Semi.cpp src/Or.cpp $(WFLAGS) -o $(ODIR)/rshell

clean: ; rm -rf bin