// https://github.com/graindb/graindb/blob/f82a52eb1772b37b172b8ae28f2f128b089639c8/benchmark/ldbc/ldbc_micro_k.cpp#L31

#include <filesystem>
#include <iostream>
#include <string>

#include "benchmark_runner.hpp"
#include "duckdb_benchmark_macro.hpp"

using namespace duckdb;

//////////////
//  TPC-H   //
//////////////

#define OPLQP_PATH "/home/brancaleone/Projects/optimal-physical-layout-query-processing/"

#define OPLQPBenchmark(DATASET, QUERY)             						                                                       \
	void Load(DuckDBBenchmarkState *state) override {                                                                  \
	}                                                                                                                  \
	std::string ReadFile(std::string path) {                                                                       \
		std::ifstream inputFileStream(path);                                                                          \
	  	std::string fileContent; \
		fileContent.assign ( (std::istreambuf_iterator<char>(inputFileStream) ), \
		 				     (std::istreambuf_iterator<char>()    ) );                                                           \
		return fileContent;                                                                                           \
	}\
	void RunBenchmark(DuckDBBenchmarkState *state) override {                                             \
		std::string basePath = OPLQP_PATH;                                                         \
		auto query = ReadFile(basePath + "benchmark/queries" + DATASET + "generated/" + QUERY + ".sql");\
        std::cout << query;                                                                                                        \
		state->conn.Query(query);                                                                                      \
	}                                                                                                                  \
	void Cleanup(DuckDBBenchmarkState *state) override {                                                               \
	}                                                                                                                  \
	string VerifyResult(QueryResult *result) override {                                                                \
		return string();                                                                                               \
	}                                                                                                                  \
	string BenchmarkInfo() override {                                                                                  \
		return "Benchmark partitioning technique";											                   \
	}


DUCKDB_BENCHMARK(TPCHBenchmarkQ3A, "[oplqp]")
OPLQPBenchmark("tpch", "q3a")
FINISH_BENCHMARK(TPCHBenchmarkQ3A)

DUCKDB_BENCHMARK(TaxiBenchmarkQ1A, "[oplqp]")
OPLQPBenchmark("taxi", "1a")
FINISH_BENCHMARK(TaxiBenchmarkQ1A)
