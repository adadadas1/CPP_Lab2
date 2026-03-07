#pragma once

#include <string>
#include <tuple>
#include <vector>

using IP = std::tuple<int, int, int, int>;

std::vector<std::string> split(const std::string &str, char d);
IP parse_ip(const std::string &s);
void print_ip(const IP &ip);
void sort_reverse(std::vector<IP> &ips);
std::vector<IP> filter(const std::vector<IP> &ips, int b1);
std::vector<IP> filter(const std::vector<IP> &ips, int b1, int b2);
std::vector<IP> filter_any(const std::vector<IP> &ips, int val);
