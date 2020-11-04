#ifndef GPU_KARP_RABIN_BENCHMARKCASE_H
#define GPU_KARP_RABIN_BENCHMARKCASE_H

#include <functional>
#include <vector>
#include <string>

class BenchmarkCase
{
public:
    BenchmarkCase() = default;
    BenchmarkCase* beforeEach(std::function<void()> function);
    BenchmarkCase* afterEach(std::function<void()> function);
    BenchmarkCase* afterTest(std::function<void()> function);
    BenchmarkCase* setFunctionUnderBenchmark(std::function<void()> function);
    BenchmarkCase* setTestRepeats(size_t i);
    BenchmarkCase* setPatterns(const std::vector<std::string>& patterns);
    std::vector<std::pair<std::string, double>> test();
    void saveResultsToFile(const std::string& fileName);
private:
    size_t testRepeats = 1;
    const std::string fileExtension = ".csv";
    const std::string outputFolder = "results";

    std::vector<std::pair<std::string, double>> testResults;

    std::function<void()> functionUnderBenchmark = [](){};
    std::function<void()> beforeEachFunction = [](){};
    std::function<void()> afterEachFunction = [](){};
    std::function<void()> afterTestFunction = [](){};

    double runSingle();
    double repeatSingle();
    void printResults();
};


#endif //GPU_KARP_RABIN_BENCHMARKCASE_H
