#include "BenchmarkCase.h"
#include <chrono>
#include <utility>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace {
    constexpr auto outputFileExtension = ".csv";
    constexpr auto outputFolder = "results";
}

/**
 * Tells how many times function under benchmark will be executed for single pattern
 */
BenchmarkCase* BenchmarkCase::setTestRepeats(size_t i)
{
    testRepeats = i;
    return this;
}

/**
 * Enables exact benchmarking (results for specific pattern) and tells whole Benchmark class
 * how many times (collectively) tests should be executed.
 */
BenchmarkCase* BenchmarkCase::setPatterns(const std::vector<std::string>& patterns)
{
    for(const auto& pattern : patterns) {                               //avg time, found count
        results.emplace_back(std::make_pair(pattern, std::make_pair(0.0, 0)));
    }
    resultIterator = results.begin();
    return this;
}

/**
 * This method is executed before every single test.
 * It can be also interpreted as setup function for single test.
 */
BenchmarkCase* BenchmarkCase::beforeEach(std::function<void()> function)
{
    beforeEachFunction = std::move(function);
    return this;
}

/**
 *  This method is executed after every single test.
 *  It can be also interpreted as tear down function for single test.
 */
BenchmarkCase* BenchmarkCase::afterEach(std::function<void()> function)
{
    afterEachFunction = std::move(function);
    return this;
}

/**
 * This method is executed after ${testRepeats} tests on single pattern
 */
BenchmarkCase* BenchmarkCase::afterTest(std::function<void()> function)
{
    afterTestFunction = std::move(function);
    return this;
}

BenchmarkCase* BenchmarkCase::setFunctionUnderBenchmark(std::function<size_t()> function)
{
    functionUnderBenchmark = std::move(function);
    return this;
}

double BenchmarkCase::runSingle()
{
    beforeEachFunction();

    auto start = std::chrono::high_resolution_clock::now();
    resultIterator->second.second = functionUnderBenchmark(); //saving pattern occurrence count
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> benchmarkTime = end - start;

    afterEachFunction();

    return benchmarkTime.count();
}

double BenchmarkCase::repeatSingle()
{
    double timesSum = 0.0;
    double averageTime = 0.0;
    for(size_t i = 0; i < testRepeats; ++i) {
        timesSum += runSingle();
    }
    afterTestFunction();
    resultIterator++;
    averageTime = timesSum / testRepeats;

    return averageTime;
}

/**
 * It is assumed that textProcessor searches text for patterns in patterns order given in setPatterns().
 * That's why this method iterates over results and saves time (iterator->second.first) and found count (iterator->second.second).
 * to corresponding pattern.
 */
std::vector<BenchmarkCase::BenchmarkResult> BenchmarkCase::test()
{
    std::cout << "BENCHMARK STARTED" << std::endl;
    for(auto iterator = results.begin(); iterator != results.end(); ++iterator) {
        iterator->second.first = repeatSingle(); //saving average processing time
    }
    printResults();

    return results;
}

void BenchmarkCase::printResults()
{
    for(auto iterator = results.begin(); iterator != results.end(); ++iterator) {
        printf("Pattern: %s,  found count: %lu, average time: %fs\n",
               iterator->first.c_str(), iterator->second.second, iterator->second.first);
    }
}

/**
 * Saves benchmark results to ./benchmark/results/${testRepeats}${fileName}.csv (e.g 10small_test.csv)
 * Do not provide file extension, it is already configured - by default .csv
 */
void BenchmarkCase::saveResultsToFile(const std::string& fileName)
{
    std::filesystem::path projectDir = std::filesystem::current_path().parent_path();
    std::filesystem::path outputFile = projectDir
            .append("benchmark")
            .append(outputFolder)
            .append(std::to_string(testRepeats) + fileName + outputFileExtension);
    std::ofstream resultsFile;
    resultsFile.open(outputFile, std::fstream::out);
    resultsFile << "pattern,found count,time" << std::endl;
    for(auto iterator = results.begin(); iterator != results.end(); ++iterator) {
        resultsFile
        << iterator->first << ","
        << iterator->second.second << ","
        << iterator->second.first << std::endl;
    }
    resultsFile.close();
    std::cout<<"Results are saved in " << outputFile << std::endl;
}
