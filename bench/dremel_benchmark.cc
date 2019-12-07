// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------

#include <cstdint>
#include <chrono>  // NOLINT
#include <iostream>
#include <fstream>
#include "benchmark/benchmark.h"
#include "database.h"
#include "imlab/schema.h"
#include "imlab/infra/types.h"

namespace {

void Benchmark(benchmark::State &state) {

    for (auto _ : state) {

    }

    state.SetItemsProcessed(state.iterations());
}

}  // namespace

BENCHMARK(Benchmark)
    ->Iterations(1000000);

int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}
