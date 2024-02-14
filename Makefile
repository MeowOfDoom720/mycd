CXX = g++

#CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field
CXXFLAGS = -std=c++11 -ggdb -O0	-Wextra -Wno-unused-parameter -Wno-unused-private-field

BINARIES = mycd

all: ${BINARIES}

mycd: mycd.o	
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o
