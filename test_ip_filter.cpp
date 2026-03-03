#define BOOST_TEST_MODULE test_ip_filter

#include "ip_filter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_ip_filter)

// Проверяем что парсер правильно разбирает строку в октеты
BOOST_AUTO_TEST_CASE(test_parse_ip)
{
    auto ip = parse_ip("192.168.1.1");
    BOOST_CHECK_EQUAL(std::get<0>(ip), 192);
    BOOST_CHECK_EQUAL(std::get<1>(ip), 168);
    BOOST_CHECK_EQUAL(std::get<2>(ip), 1);
    BOOST_CHECK_EQUAL(std::get<3>(ip), 1);
}

// Важно: сортировка численная, а не строковая
// 1.10.x.x > 1.2.x.x > 1.1.x.x — в строковом порядке было бы наоборот
BOOST_AUTO_TEST_CASE(test_sort_reverse_numerical)
{
    std::vector<IP> ips = {
        std::make_tuple(1, 2, 0, 0),
        std::make_tuple(1, 10, 0, 0),
        std::make_tuple(1, 1, 0, 0),
    };
    sort_reverse(ips);
    BOOST_CHECK(ips[0] == std::make_tuple(1, 10, 0, 0));
    BOOST_CHECK(ips[1] == std::make_tuple(1, 2, 0, 0));
    BOOST_CHECK(ips[2] == std::make_tuple(1, 1, 0, 0));
}

// Фильтр по первому байту — должны вернуться только адреса с b1==1
BOOST_AUTO_TEST_CASE(test_filter_first_byte)
{
    std::vector<IP> ips = {
        std::make_tuple(1, 2, 3, 4),
        std::make_tuple(2, 3, 4, 5),
        std::make_tuple(1, 5, 6, 7),
    };
    auto result = filter(ips, 1);
    BOOST_REQUIRE_EQUAL(result.size(), 2u);
    BOOST_CHECK(result[0] == std::make_tuple(1, 2, 3, 4));
    BOOST_CHECK(result[1] == std::make_tuple(1, 5, 6, 7));
}

// Фильтр по двум байтам — оба должны совпасть
BOOST_AUTO_TEST_CASE(test_filter_two_bytes)
{
    std::vector<IP> ips = {
        std::make_tuple(46, 70, 225, 39),
        std::make_tuple(46, 71, 1, 1),
        std::make_tuple(47, 70, 1, 1),
    };
    auto result = filter(ips, 46, 70);
    BOOST_REQUIRE_EQUAL(result.size(), 1u);
    BOOST_CHECK(result[0] == std::make_tuple(46, 70, 225, 39));
}

// filter_any — достаточно совпадения хотя бы одного байта
BOOST_AUTO_TEST_CASE(test_filter_any)
{
    std::vector<IP> ips = {
        std::make_tuple(1, 2, 3, 46),   // совпадает 4-й байт
        std::make_tuple(46, 2, 3, 4),   // совпадает 1-й байт
        std::make_tuple(1, 2, 3, 4),    // не совпадает ни один
        std::make_tuple(5, 46, 7, 8),   // совпадает 2-й байт
    };
    auto result = filter_any(ips, 46);
    BOOST_REQUIRE_EQUAL(result.size(), 3u);
}

BOOST_AUTO_TEST_SUITE_END()
