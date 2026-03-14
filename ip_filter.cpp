#include "ip_filter.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> parts;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delimiter);
    while (stop != std::string::npos)
    {
        parts.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(delimiter, start);
    }
    parts.push_back(str.substr(start));

    return parts;
}

IP parse_ip(const std::string &ipStr)
{
    auto octets = split(ipStr, '.');
    if (octets.size() != 4)
        throw std::invalid_argument("invalid IP: " + ipStr);
    return std::make_tuple(std::stoi(octets[0]), std::stoi(octets[1]),
                           std::stoi(octets[2]), std::stoi(octets[3]));
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
