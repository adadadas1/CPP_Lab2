#pragma once

#include <string>
#include <tuple>
#include <vector>

// IP-адрес как кортеж из 4 целых чисел (октетов)
using IP = std::tuple<int, int, int, int>;

// Разбить строку по разделителю
std::vector<std::string> split(const std::string &str, char d);

// Распарсить строку вида "1.2.3.4" в IP
IP parse_ip(const std::string &s);

// Вывести IP в stdout в виде "1.2.3.4"
void print_ip(const IP &ip);

// Отсортировать пул IP в обратном лексикографическом порядке (численном)
void sort_reverse(std::vector<IP> &ips);

// Фильтр по первому байту
std::vector<IP> filter(const std::vector<IP> &ips, int b1);

// Фильтр по первому и второму байтам
std::vector<IP> filter(const std::vector<IP> &ips, int b1, int b2);

// Фильтр: любой байт равен val
std::vector<IP> filter_any(const std::vector<IP> &ips, int val);
