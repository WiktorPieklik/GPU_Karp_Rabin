#include "../../main/header/RabinKarpSearch.h"
#include "../../main/header/Hash/StandardHash.h"
#include "BenchmarkCase.h"
#include <string>

int main()
{
    std::string filePath = "../test.txt", pattern = "ipsum";
    BenchmarkCase benchmarkCase = BenchmarkCase();
    RabinKarpSearch<StandardHash>* textProcessor = nullptr;
    benchmarkCase.setSameTestRepeats(10)
        ->setAllRepeats(100)
        ->beforeEach([&textProcessor, &filePath, &pattern]() -> void{
            textProcessor = new RabinKarpSearch<StandardHash>(filePath, pattern);
        })
        ->setFunctionUnderBenchmark([&textProcessor]() -> void{
            textProcessor->search();
        })
        ->afterEach([&textProcessor]() -> void{
            delete textProcessor;
        });
    std::vector<double> avgResults = benchmarkCase.run();

    for(size_t i = 0; i < avgResults.size(); ++i) {
        printf("Iteration %zu,  average time: %fs\n", i+1, avgResults[i]);
    }
        benchmarkCase.saveCaseResultsToFile("tescik");
    return 0;
}
