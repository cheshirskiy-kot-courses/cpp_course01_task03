#pragma once

#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>

#include <range/v3/all.hpp>


using IP = std::array<uint8_t, 4>;
using IP_Pool = std::vector<IP>;


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string & str, char d);

IP parse_ip(const std::string & str);

void rsort_lexicographically(IP_Pool & ip_pool);


template<class ...Bytes>
IP_Pool filter(IP_Pool ip_pool, Bytes... bytes)
{
    static_assert(sizeof...(bytes) <= 4, "Wrong bytes size");
    auto b = std::array< uint8_t, sizeof...(bytes) >{ static_cast<uint8_t>(bytes)... };
    
    IP_Pool res;

    using namespace ranges;
    ranges::for_each(ip_pool | ranges::views::filter(
        [&b](const IP & ip)
            {
                return equal(ip | views::take(b.size()), b | views::take(b.size()));
            }),
        [&res](const IP & ip) { res.push_back(ip); });

    return res;
}


IP_Pool filter_any(IP_Pool ip_pool, uint8_t byte);
