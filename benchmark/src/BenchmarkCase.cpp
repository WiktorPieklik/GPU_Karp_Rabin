#include "BenchmarkCase.h"
#include <chrono>
#include <utility>

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
    for(size_t i = 0; i < allRepeats; ++i) {
        results.push_back(repeatSingle());
    }

    return results;
}