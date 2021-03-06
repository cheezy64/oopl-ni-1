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
    --include "Copy1.c++"                    \
    --include "Copy2.c++"                    \
    --include "Transform1.c++"               \
    --include "Transform2.c++"               \
    --include "Reverse1.c++"                 \
    --include "Reverse2.c++"                 \
    --include "Selection.c++"                \
    --include "Iteration.c++"                \
    --include "Classes.c++"                  \
    --include "RangeIterator1.c++"           \
    --include "RangeIterator2.c++"           \
    --include "Range1.c++"                   \
    --include "Range2.c++"                   \
    --include "Initializations.c++"          \
    --include "InitializerList.c++"          \
    --include "Auto.c++"                     \
    --include "Arrays.c++"                   \
    --include "Vector1.c++"                  \
    --include "Vector2.c++"                  \
    --include "Vector3.c++"                  \
    --include "Vector4.c++"                  \
    --include "FunctionOverloading.c++"      \
    --include "Move.c++"                     \
    --include "Vector5.c++"                  \
    --include "Vector6.c++"                  \
    --include "FunctionDefaults.c++"         \
    --include "Memory.h"                     \
    --include "Vector7.c++"                  \
    --include "Vector8.c++"                  \
    --include "Vector9.c++"                  \
    --include "Shapes1.c++"                  \
    --include "Shapes2.c++"                  \
    --include "MethodOverriding1.c++"        \
    --include "Shapes3.c++"                  \
    --include "Shapes4.c++"                  \
    --include "MethodOverriding2.c++"        \
    --include "Shapes5.c++"                  \
    --include "Shapes6.c++"                  \
    --include "Handle1.c++"                  \
    --include "Handle2.c++"                  \
    --include "Handle3.c++"                  \
    --include "Handle4.c++"                  \
    --include "Handle5.c++"                  \
    --include "Handle6.c++"                  \
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
