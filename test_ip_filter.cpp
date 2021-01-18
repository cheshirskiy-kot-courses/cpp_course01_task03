#define BOOST_TEST_MODULE ip_filter_test_module

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

using namespace std;

BOOST_AUTO_TEST_CASE(test_parse_ip)
{
    auto in = "113.162.145.156\t111\t0"s;
    auto out = parse_ip(in);
    auto res = IP{ 113, 162, 145, 156 };
    BOOST_CHECK(out == res);
}

BOOST_AUTO_TEST_CASE(test_rsort)
{
    auto ip_pool = IP_Pool{
        IP{222, 173, 235, 64},
        IP{1, 70, 44, 170},
        IP{1, 1, 234, 8},
        IP{222, 82, 198, 61},
        IP{1, 70, 168, 152},
        IP{222, 173, 235, 246}
    };

    rsort_lexicographically(ip_pool);
    auto res = IP_Pool{
        IP{222, 173, 235, 246},
        IP{222, 173, 235, 64},
        IP{222, 82, 198, 61},
        IP{1, 70, 168, 152},
        IP{1, 70, 44, 170},
        IP{1, 1, 234, 8}
    };

    BOOST_CHECK(ip_pool == res);
}

BOOST_AUTO_TEST_CASE(test_filter_1_arg)
{
    auto ip_pool = IP_Pool{
        IP{222, 173, 235, 246},
        IP{222, 173, 235, 64},
        IP{222, 82, 198, 61},
        IP{1, 70, 168, 152},
        IP{1, 70, 44, 170},
        IP{1, 1, 234, 8}
    };

    auto out = filter(ip_pool, 1);
    auto res = IP_Pool{
        IP{1, 70, 168, 152},
        IP{1, 70, 44, 170},
        IP{1, 1, 234, 8}
    };

    BOOST_CHECK(out == res);
}

BOOST_AUTO_TEST_CASE(test_filter_2_args)
{
    auto ip_pool = IP_Pool{
        IP{222, 173, 235, 246},
        IP{222, 173, 235, 64},
        IP{222, 82, 198, 61},
        IP{46, 70, 225, 39},
        IP{46, 70, 147, 26},
        IP{46, 70, 113, 73},
        IP{46, 70, 29, 76},
        IP{1, 70, 168, 152},
        IP{1, 70, 44, 170},
        IP{1, 1, 234, 8}
    };

    auto out = filter(ip_pool, 46, 70);
    auto res = IP_Pool{
        IP{46, 70, 225, 39},
        IP{46, 70, 147, 26},
        IP{46, 70, 113, 73},
        IP{46, 70, 29, 76}
    };

    BOOST_CHECK(out == res);
}

BOOST_AUTO_TEST_CASE(test_filter_any)
{
    auto ip_pool = IP_Pool{
        IP{222, 173, 235, 46},
        IP{222, 82, 198, 61},
        IP{186, 204, 34, 46},
        IP{185, 46, 85, 78},
        IP{68, 46, 218, 208},
        IP{46, 161, 60, 92},
        IP{39, 46, 86, 85},
        IP{5, 189, 203, 46},
        IP{1, 70, 168, 152},
        IP{1, 1, 46, 8}
    };

    auto out = filter_any(ip_pool, 46);
    auto res = IP_Pool{
        IP{222, 173, 235, 46},
        IP{186, 204, 34, 46},
        IP{185, 46, 85, 78},
        IP{68, 46, 218, 208},
        IP{46, 161, 60, 92},
        IP{39, 46, 86, 85},
        IP{5, 189, 203, 46},
        IP{1, 1, 46, 8}
    };

    BOOST_CHECK(out == res);
}

BOOST_AUTO_TEST_SUITE_END()