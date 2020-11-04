#include "BenchmarkCase.h"
#include <chrono>
#include <utility>
#include <filesystem>
#include <fstream>
#include <iostream>

BenchmarkCase* BenchmarkCase::setAllRepeats(int i)
{
    allRepeats = i;
    return this;
}

BenchmarkCase* BenchmarkCase::setSameTestRepeats(int i)
{
    sameTestRepeats = i;
    return this;
}

BenchmarkCase* BenchmarkCase::beforeEach(std::function<void ()> function)
{
    beforeEachFunction = std::move(function);
    return this;
}

BenchmarkCase* BenchmarkCase::afterEach(std::function<void ()> function)
{
    afterEachFunction = std::move(function);
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
    for(size_t i = 0; i < sameTestRepeats; ++i) {
        timesSum += runSingle();
    }
    averageTime = timesSum / sameTestRepeats;

    return averageTime;
}

std::vector<double> BenchmarkCase::run()
{
    std::cout << "BENCHMARK STARTED" << std::endl;
    for(size_t i = 0; i < allRepeats; ++i) {
        results.push_back(repeatSingle());
    }

    return results;
}

/**
 * Prints benchmark results to ./benchmark/results/${fileName}.csv
 * Do not provide file extension, it it already configured - by default .csv
 */
void BenchmarkCase::saveCaseResultsToFile(const std::string& fileName)
{
    std::filesystem::path projectDir = std::filesystem::current_path().parent_path();
    std::filesystem::path outputFile = projectDir
            .append("benchmark")
            .append(outputFolder)
            .append(fileName + fileExtension);
    std::ofstream resultsFile;
    resultsFile.open(outputFile, std::fstream::out);
    resultsFile << "iteration, time" << std::endl;
    for(size_t i = 0; i < results.size(); ++i) {
        resultsFile << std::to_string(i + 1) << "," << results[i] << std::endl;
    }
    resultsFile.close();
    std::cout<<"Results are saved in " << outputFile << std::endl;
}