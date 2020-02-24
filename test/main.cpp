#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

#include "area-test.hpp"
#include "centroid-test.hpp"
#include "contains-test.hpp"
#include "hull-test.hpp"
#include "length-test.hpp"

int main( int argc, char* argv[] )
{
    int result = Catch::Session().run( argc, argv );

    return result;
}
