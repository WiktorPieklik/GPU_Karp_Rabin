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
    BenchmarkCase* setFunctionUnderBenchmark(std::function<void()> function);
    BenchmarkCase* setSameTestRepeats(int i);
    BenchmarkCase* setAllRepeats(int i);
    std::vector<double> run();
    void saveCaseResultsToFile(const std::string& fileName);
private:
    int sameTestRepeats = 1;
    int allRepeats = 1;
    std::vector<double> results;
    const std::string fileExtension = ".csv";
    const std::string outputFolder = "results";

    std::function<void()> functionUnderBenchmark = [](){};
    std::function<void()> beforeEachFunction = [](){};
    std::function<void()> afterEachFunction = [](){};

    double runSingle();
    double repeatSingle();
};


#endif //GPU_KARP_RABIN_BENCHMARKCASE_H
