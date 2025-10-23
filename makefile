VER=2.2
DIST=qubic$(VER)
PROGS=qubic
CXX_SRCS=struct.cpp read_array.cpp make_graph.cpp get_options.cpp write_block.cpp cluster.cpp main.cpp expand.cpp
OBJS=$(CXX_SRCS:.cpp=.o)

LDFLAGS+=-lm -fopenmp
CXXFLAGS+=-O3 -Wall -ansi -std=c++0x -fopenmp -DVER=$(VER)

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    # Windows settings
    SHARED_LIB=qubic.dll
    CXX=cl
    CXXFLAGS=/O2 /EHsc /DVER=$(VER) /I.
    LDFLAGS=
    LINK_SHARED=/DLL /OUT:$(SHARED_LIB)
else
    # Linux/macOS settings
    SHARED_LIB=qubic.so
    CXX=g++
    CXXFLAGS+=-fPIC
    LINK_SHARED=-shared -o $(SHARED_LIB)
endif

all: $(PROGS)

${PROGS}: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

shared: mathematica_wrapper.o $(OBJS)
	$(CXX) $^ $(LINK_SHARED) $(LDFLAGS)

mathematica_wrapper.o: mathematica_wrapper.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGS)
	rm -f *.o
	rm -f data/*.rules
	rm -f data/*.chars
	rm -f data/*.blocks
	rm -f data/*.expansion
	rm -f $(SHARED_LIB)

dist:
	$(MAKE) clean
	cd .. && tar czvf $(DIST).tar.gz $(DIST)/

test: 
	$(MAKE)
	./${PROGS} -i data/example 
