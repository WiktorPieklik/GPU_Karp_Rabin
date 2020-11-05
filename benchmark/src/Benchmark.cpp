#include "../../main/header/RabinKarpSearch.h"
#include "../../main/header/Hash/StandardHash.h"
#include "BenchmarkCase.h"
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
            ->setFunctionUnderBenchmark([&textProcessor]() -> size_t {
                return textProcessor->search().size();
            })
            ->afterEach([&textProcessor]() -> void {
                delete textProcessor;
            })
            ->afterTest([&it]() -> void{
                it++;
            });
    auto avgResults = benchmarkCase.test();
    benchmarkCase.saveResultsToFile("test");

    return 0;
}
