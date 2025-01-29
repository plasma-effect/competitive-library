.PHONY: default
default: test_all

WARNINGS = -Wall -Wextra -Werror=return-type
INCLUDES = -Iinclude \
	-I$(HOME)/boost_1_82_0/include \
	-I$(HOME)/ac-library \
	-Igoogletest/googletest/include \
	-Igoogletest/googlemock/include
CXXFLAGS = -std=c++20 -O3  -DLOCAL_DEBUG $(INCLUDES) $(WARNINGS)
GTEST_LIBS = \
	googletest/build/lib/libgtest_main.a \
	googletest/build/lib/libgtest.a


%.o: %.cpp
	g++ -MMD -MP -c $< $(CXXFLAGS) -o $@

-include tests/utility.d

test_all: tests/utility.o $(GTEST_LIBS)
	g++ $^ $(CXXFLAGS) -o $@
