CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++20 -g -fstandalone-debug -fsanitize=address,null -fno-omit-frame-pointer
exec: bin/exec
	bin/exec

tests: bin/tests
	bin/tests

bin/exec: ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

bin/tests: ./tests/tests.cc ./src/illini_book.cc ./src/utilities.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*