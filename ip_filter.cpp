#include "ip_filter.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));

    return r;
}

IP parse_ip(const std::string &s)
{
    auto parts = split(s, '.');
    if (parts.size() != 4)
        throw std::invalid_argument("invalid IP: " + s);
    return std::make_tuple(std::stoi(parts[0]), std::stoi(parts[1]),
                           std::stoi(parts[2]), std::stoi(parts[3]));
}

void print_ip(const IP &ip)
{
    std::cout << std::get<0>(ip) << "."
              << std::get<1>(ip) << "."
              << std::get<2>(ip) << "."
              << std::get<3>(ip) << "\n";
}

void sort_reverse(std::vector<IP> &ips)
{
    std::sort(ips.begin(), ips.end(), [](const IP &a, const IP &b) {
        return a > b;
    });
}

std::vector<IP> filter(const std::vector<IP> &ips, int b1)
{
    std::vector<IP> result;
    std::copy_if(ips.cbegin(), ips.cend(), std::back_inserter(result),
                 [b1](const IP &ip) { return std::get<0>(ip) == b1; });
    return result;
}

std::vector<IP> filter(const std::vector<IP> &ips, int b1, int b2)
{
    std::vector<IP> result;
    std::copy_if(ips.cbegin(), ips.cend(), std::back_inserter(result),
                 [b1, b2](const IP &ip) {
                     return std::get<0>(ip) == b1 && std::get<1>(ip) == b2;
                 });
    return result;
}

std::vector<IP> filter_any(const std::vector<IP> &ips, int val)
{
    std::vector<IP> result;
    std::copy_if(ips.cbegin(), ips.cend(), std::back_inserter(result),
                 [val](const IP &ip) {
                     return std::get<0>(ip) == val || std::get<1>(ip) == val ||
                            std::get<2>(ip) == val || std::get<3>(ip) == val;
                 });
    return result;
}
