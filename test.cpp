#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                    "4 1\n"
                    "11 1 12 2\n"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "2\n"
            "1 1 2 2 "
    );
}

TEST_CASE("test 2, zero D", ""){
    std::stringstream input(
            "4 0\n"
            "11 1 12 2"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "1\n"
                    "1 1 1 1 "
    );
}

TEST_CASE("all tickets", ""){
    std::stringstream input(
            "4 4\n"
            "1 2 3 4"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "4\n"
                    "1 2 3 4 "
    );
}
