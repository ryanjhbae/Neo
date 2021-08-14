CXX=g++
CXXFLAGS=-std=c++14 -g -Werror=vla -MMD
OBJECTS=main.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=biquadris

${EXEC}: ${OBJECTS}
        ${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
