#include "BenchmarkCase.h"
#include <chrono>
#include <utility>
#include <filesystem>
#include <fstream>
#include <iostream>

/**
 * Tells how many times function under benchmark will be executed
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
BenchmarkCase * BenchmarkCase::setPatterns(const std::vector<std::string>& patterns)
{
    for(const auto& pattern : patterns) {
        testResults.emplace_back(std::make_pair(pattern, 0.0));
    }
    return this;
}

/**
 * This method is executed before every single test.
 * It can be also interpreted as setup function for single test.
 */
BenchmarkCase* BenchmarkCase::beforeEach(std::function<void ()> function)
{
    beforeEachFunction = std::move(function);
    return this;
}

/**
 *  This method is executed after every single test.
 *  It can be also interpreted as tear down function for single test.
 */
BenchmarkCase* BenchmarkCase::afterEach(std::function<void ()> function)
{
    afterEachFunction = std::move(function);
    return this;
}

/**
 * This method is executed after ${testRepeats} tests on single pattern
 */
BenchmarkCase * BenchmarkCase::afterTest(std::function<void()> function)
{
    afterTestFunction = std::move(function);
    return this;
}

BenchmarkCase* BenchmarkCase::setFunctionUnderBenchmark(std::function<void ()> function)
{
    functionUnderBenchmark = std::move(function);
    return this;
}

double BenchmarkCase::runSingle()
{
    beforeEachFunction();

    auto start = std::chrono::high_resolution_clock::now();
    functionUnderBenchmark();
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
    averageTime = timesSum / testRepeats;

    return averageTime;
}

std::vector<std::pair<std::string, double>> BenchmarkCase::test()
{
    std::cout << "BENCHMARK STARTED" << std::endl;
    for(auto iterator = testResults.begin(); iterator != testResults.end(); ++iterator) {
        iterator->second = repeatSingle();
    }
    printResults();

    return testResults;
}

void BenchmarkCase::printResults()
{
    for(auto iterator = testResults.begin(); iterator != testResults.end(); ++iterator) {
        printf("Pattern: %s,  average time: %fs\n", iterator->first.c_str(), iterator->second);
    }
}

/**
 * Saves benchmark results to ./benchmark/results/${testRepeats}${fileName}.csv (e.g 10small_test.csv)
 * Do not provide file extension, it it already configured - by default .csv
 */
void BenchmarkCase::saveResultsToFile(const std::string& fileName)
{
    std::filesystem::path projectDir = std::filesystem::current_path().parent_path();
    std::filesystem::path outputFile = projectDir
            .append("benchmark")
            .append(outputFolder)
            .append(std::to_string(testRepeats) + fileName + fileExtension);
    std::ofstream resultsFile;
    resultsFile.open(outputFile, std::fstream::out);
    resultsFile << "pattern, time" << std::endl;
    for(auto iterator = testResults.begin(); iterator != testResults.end(); ++iterator) {
        resultsFile << iterator->first << "," << iterator->second << std::endl;
    }
    resultsFile.close();
    std::cout<<"Results are saved in " << outputFile << std::endl;
}