#include "../../main/header/RabinKarpSearch.h"
#include "../../main/header/Hash/StandardHash.h"
#include "BenchmarkCase.h"
#include <string>
#include <iostream>

int main()
{
    std::string filePath = "../small_test.txt", pattern = "student";
    BenchmarkCase benchmarkCase = BenchmarkCase();
    RabinKarpSearch<StandardHash>* textProcessor = nullptr;
    benchmarkCase.setSameTestRepeats(2)
        ->setAllRepeats(5)
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
        printf("Iteration %zu,  average time: %fs\n", i, avgResults[i]);
    }

    return 0;
}
