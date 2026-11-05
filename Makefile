CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Werror -O2 -Isrc
.PHONY: all test clean
all: build/procspine build/test_proc
build:
	mkdir -p build
build/procspine: src/main.cpp src/proc_status.hpp | build
	$(CXX) $(CXXFLAGS) -o $@ src/main.cpp
build/test_proc: tests/test_proc.cpp src/proc_status.hpp | build
	$(CXX) $(CXXFLAGS) -o $@ tests/test_proc.cpp
test: all
	./build/test_proc
	./build/procspine tests/fixtures/status.txt | grep -q 'ad=procspine-test'
	./build/procspine /proc/self/status
clean:
	rm -rf build
