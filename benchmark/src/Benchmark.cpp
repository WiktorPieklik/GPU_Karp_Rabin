#include "../../main/header/RabinKarpSearch.h"
#include "../../main/header/Hash/StandardHash.h"
#include "BenchmarkCase.h"
#include <vector>

int main()
{
    std::string filePath = "../test.txt";
    std::vector<std::string> patterns = {"ipsum", "turpis", "lorem", "eros", "amet", "purus", "ex", "ac"};
    auto patternsIterator = patterns.begin();

    RabinKarpSearch* textProcessor;
    BenchmarkCase benchmarkCase = BenchmarkCase();
    benchmarkCase.setTestRepeats(100)
            ->setPatterns(patterns)
            ->beforeEach([&textProcessor, &filePath, &patternsIterator]() -> void {
                textProcessor = new RabinKarpSearch(filePath, *patternsIterator, std::make_unique<StandardHash>());
            })
            ->setFunctionUnderBenchmark([&textProcessor]() -> size_t {
                return textProcessor->search().size();
            })
            ->afterEach([&textProcessor]() -> void {
                delete textProcessor;
            })
            ->afterTest([&patternsIterator]() -> void{
                patternsIterator++;
            });
    auto results = benchmarkCase.test();
    benchmarkCase.saveResultsToFile("test");

    return 0;
}
