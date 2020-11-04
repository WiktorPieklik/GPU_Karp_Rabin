#include "../../main/header/RabinKarpSearch.h"
#include "../../main/header/Hash/StandardHash.h"
#include "BenchmarkCase.h"
#include <string>
#include <vector>

int main()
{
    std::string filePath = "../test.txt";
    std::vector<std::string> patterns = {"ipsum", "turpis", "lorem", "eros", "amet", "purus", "ex", "ac"};
    auto it = patterns.begin();

    RabinKarpSearch* textProcessor;
    BenchmarkCase benchmarkCase = BenchmarkCase();
    benchmarkCase.setTestRepeats(100)
            ->setPatterns(patterns)
            ->beforeEach([&textProcessor, &filePath, &it]() -> void {
                textProcessor = new RabinKarpSearch(filePath, *it, std::make_unique<StandardHash>());
            })
            ->setFunctionUnderBenchmark([&textProcessor]() -> void {
                textProcessor->search();
            })
            ->afterEach([&textProcessor]() -> void {
                delete textProcessor;
            })
            ->afterTest([&it]() -> void{
                it++;
            });
    std::vector<std::pair<std::string, double>> avgResults = benchmarkCase.test();
    benchmarkCase.saveResultsToFile("small_test");

    return 0;
}
