#ifndef GPU_KARP_RABIN_BENCHMARKCASE_H
#define GPU_KARP_RABIN_BENCHMARKCASE_H

#include <functional>
#include <vector>
#include <string>

class BenchmarkCase
{
using BenchmarkResult = std::pair<std::string, std::pair<double, size_t>>;
public:
    BenchmarkCase() = default;
    BenchmarkCase* beforeEach(std::function<void()> function);
    BenchmarkCase* afterEach(std::function<void()> function);
    BenchmarkCase* afterTest(std::function<void()> function);
    BenchmarkCase* setFunctionUnderBenchmark(std::function<size_t()> function);
    BenchmarkCase* setTestRepeats(size_t i);
    BenchmarkCase* setPatterns(const std::vector<std::string>& patterns);
    std::vector<BenchmarkResult> test();
    void saveResultsToFile(const std::string& fileName);
private:
    size_t testRepeats = 1;

    std::vector<BenchmarkResult> results; //pattern : (avg processing time : found count)
    std::vector<BenchmarkResult>::iterator resultIterator;

    std::function<size_t()> functionUnderBenchmark = [](){ return 0;};
    std::function<void()> beforeEachFunction = [](){};
    std::function<void()> afterEachFunction = [](){};
    std::function<void()> afterTestFunction = [](){};

    double runSingle();
    double repeatSingle();
    void printResults();
};


#endif //GPU_KARP_RABIN_BENCHMARKCASE_H
