#include "ip_filter.h"

#include <iostream>

int main(int, char const *[])
{
    try
    {
        std::vector<IP> ip_pool;

        // Читаем строки из stdin, каждая строка — "ip\tN\tN"
        // Берём только первый столбец (сам IP)
        for (std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            decltype(ip_pool)::value_type ip = parse_ip(v.at(0));
            ip_pool.push_back(ip);
        }

        // Сортируем весь пул в обратном порядке и выводим
        sort_reverse(ip_pool);
        for (const auto &ip : ip_pool)
            print_ip(ip);

        // Фильтр: первый байт == 1
        for (const auto &ip : filter(ip_pool, 1))
            print_ip(ip);

        // Фильтр: первый байт == 46, второй == 70
        for (const auto &ip : filter(ip_pool, 46, 70))
            print_ip(ip);

        // Фильтр: любой байт == 46
        for (const auto &ip : filter_any(ip_pool, 46))
            print_ip(ip);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
