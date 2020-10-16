//
// Created by Wiktor Pieklik on 16/10/2020.
//

#include "RabinKarpSearch.h"
#include "../header/StandardHash.h"

#include <utility>

template <typename Hash>
RabinKarpSearch<Hash>::RabinKarpSearch(std::string file, std::string pattern): file(std::move(file)), pattern(std::move(pattern)){}

template <typename Hash>
int RabinKarpSearch<Hash>::calculateHash()
{
    Hash hash = Hash();
    int hashVal = hash
            .forX(3)
            .getPolyValue(std::vector<int>{2,4,-10,0,0,3});

    return hashVal % this->prime;

}

template <typename Hash>
std::vector<int> RabinKarpSearch<Hash>::search()
{
    return std::vector<int>{calculateHash()};
}

template class RabinKarpSearch<StandardHash>;