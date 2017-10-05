.DEFAULT_GOAL := all

ifeq ($(shell uname), Darwin)                                           # Apple
    CXX          := g++
    INCLUDE      := /usr/local/include
    CXXFLAGS     := -pedantic -std=c++14 -Wall -Weffc++
    LIBB         := /usr/local/lib
    LIBG         := /usr/local/lib
    LDFLAGS      := -lgtest -lgtest_main
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format
else ifeq ($(CI), true)                                                 # Travis CI
    CXX          := g++-5
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++14 -Wall -Weffc++
    LIBB         := /usr/lib/x86_64-linux-gnu/
    LIBG         := $(PWD)/gtest
    LDFLAGS      := -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov-5
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format
else ifeq ($(shell uname -p), unknown)                                  # Docker
    CXX          := g++
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++14 -Wall -Weffc++
    LIBB         := /usr/lib/x86_64-linux-gnu/
    LIBG         := /usr/lib
    LDFLAGS      := -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format-3.5
else                                                                    # UTCS
    CXX          := g++
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++14 -Wall -Weffc++
    LIBB         := /usr/lib/x86_64-linux-gnu
    LIBG         := /usr/local/lib
    LDFLAGS      := -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format-3.8
endif

all:
	cd examples; make all

clean:
	cd examples; make clean

config:
	git config -l

docker:
	docker run -it -v $(PWD):/usr/oopl-ni -w /usr/oopl-ni gpdowning/gcc

init:
	touch README
	git init
	git add README
	git commit -m 'first commit'
	git remote add origin git@github.com:gpdowning/oopl-ni.git
	git push -u origin master

pull:
	make clean
	@echo
	git pull
	git status

push:
	make clean
	@echo
	git add .gitignore
	git add .travis.yml
	git add examples
	git add makefile
	git add notes
	git commit -m "another commit"
	git push
	git status

run:
	cd examples; make run

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

sync:
	@rsync -r -t -u -v --delete              \
    --include "Docker.txt"                   \
    --include "Dockerfile"                   \
    --include "Hello.c++"                    \
    --include "Assertions.c++"               \
    --include "UnitTests1.c++"               \
    --include "UnitTests2.c++"               \
    --include "UnitTests3.c++"               \
    --include "Coverage1.c++"                \
    --include "Coverage2.c++"                \
    --include "Coverage3.c++"                \
    --include "IsPrime1.c++"                 \
    --include "IsPrime2.c++"                 \
    --include "Exceptions.c++"               \
    --include "StrCmp1.c++"                  \
    --include "StrCmp2.c++"                  \
    --include "Types.c++"                    \
    --include "Representations.c++"          \
    --include "Operators.c++"                \
    --include "Variables.c++"                \
    --include "Arguments.c++"                \
    --include "Equal1.c++"                   \
    --include "Equal2.c++"                   \
    --include "Consts.c++"                   \
    --include "Iterators.c++"                \
    --include "Factorial1.c++"               \
    --include "Factorial2.c++"               \
    --include "Fill1.c++"                    \
    --include "Fill2.c++"                    \
    --include "Iota1.c++"                    \
    --include "Iota2.c++"                    \
    --include "Accumulate1.c++"              \
    --include "Accumulate2.c++"              \
    --include "Cache.c++"                    \
    --include "Returns.c++"                  \
    --include "Selection.c++"                \
    --include "Iteration.c++"                \
    --include "Classes.c++"                  \
    --exclude "*"                            \
    ../../examples/c++/ examples

travis:
	cd examples; make travis

versions:
	which cmake
	cmake --version
	@echo
	which make
	make --version
	@echo
	which git
	git --version
	@echo
	which $(CXX)
	$(CXX) --version
	@echo
	ls -adl $(INCLUDE)/boost
	@echo
	ls -adl $(INCLUDE)/gtest
	@echo
	ls -al $(LIBB)/libboost_serialization.a
	@echo
	ls -al $(LIBG)/libgtest.a
	ls -al $(LIBG)/libgtest_main.a
	@echo
	which $(CLANG-CHECK)
	$(CLANG-CHECK) --version
	@echo
	which $(GCOV)
	$(GCOV) --version
	@echo
	which $(VALGRIND)
	$(VALGRIND) --version
	@echo
	which $(DOXYGEN)
	$(DOXYGEN) --version
	@echo
	which $(CLANG-FORMAT)
	$(CLANG-FORMAT) --version
