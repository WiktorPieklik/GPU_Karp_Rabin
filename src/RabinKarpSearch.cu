#include "RabinKarpSearch.cuh"
#include "StandardHash.cuh"

#include <tuple>
#include "stdio.h"
#include <iostream>

namespace {
    constexpr auto PRIME = 23;
    constexpr auto BASE = 36; //input alphabet's length
}

RabinKarpSearch::RabinKarpSearch(std::string file, std::string pattern, std::unique_ptr<Hash> hash): file(std::move(file)), pattern(std::move(pattern)), hash(std::move(hash))
{
    init();
}

void RabinKarpSearch::init()
{
    reader = TextReaderFactory::forText(file);
    if(!reader)
        throw std::runtime_error("Couldn't create a reader!");
    text = reader->read();
    calculateHashes();
    for(size_t i = 1; i < pattern.length(); ++i)
    {
        mostSignificantWeight *= BASE;
    }
}

void RabinKarpSearch::calculateHashes()
{
    if(!hash)
        throw std::runtime_error("Hash not initialized.");

    std::tuple<long long, long long> hashes = hash
            ->forBase(BASE)
            .getPolyValues(pattern, text.substr(currentWindowPosition, pattern.length()));
    patternHash = std::get<0>(hashes) % PRIME;
    windowHash = std::get<1>(hashes) % PRIME;
}

void RabinKarpSearch::calculateRollingHash()
{
    windowHash = (windowHash - mostSignificantWeight * text[currentWindowPosition - 1]) * BASE + text[currentWindowPosition + pattern.length() - 1];
    windowHash = windowHash % PRIME;

    if(windowHash < 0)
    {
        windowHash = windowHash + PRIME;
    }
}

void RabinKarpSearch::moveWindow()
{
    ++currentWindowPosition;
}

std::vector<size_t> RabinKarpSearch::search()
{
    std::vector<size_t> matches;
    auto windows_count = text.length() - pattern.length();
    while(currentWindowPosition <= windows_count)
    {
        if(windowHash == patternHash)
        {
            if(pattern == text.substr(currentWindowPosition, pattern.length()))
            {
                //match found
                matches.push_back(currentWindowPosition);
            }
        }
        moveWindow();
        calculateRollingHash();
    }
    return matches;
}

std::string RabinKarpSearch::getText() {
    return text;
}

std::string RabinKarpSearch::getPattern() {
    return pattern;
}