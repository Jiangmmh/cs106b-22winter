SRC := $(wildcard *.cpp)
TGT := $(patsubst %.cpp, %, $(SRC))

all: $(TGT)

%: %.cpp
	g++ -o $@ $<


.PHONY: clean
clean:
	rm -f $(TGT)