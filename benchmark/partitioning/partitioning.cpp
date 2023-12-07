#include <filesystem>
#include <iostream>
#include <string>

#include "benchmark_runner.hpp"
#include "duckdb_benchmark_macro.hpp"

using namespace duckdb;

#define OPLQP_PATH "/home/brancaleone/Projects/optimal-physical-layout-query-processing/benchmark/temp"

#define OPLQPBenchmark(QUERY_FILE)             						                                                       \
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
		auto query = ReadFile(basePath + QUERY_FILE);\
        std::cout << query;                                                                                                        \
		state->conn.Query(query);                                                                                      \
	}                                                                                                                  \
	void Cleanup(DuckDBBenchmarkState *state) override {                                                               \
	}                                                                                                                  \
	string VerifyResult(QueryResult *result) override {                                                                \
		return string();                                                                                               \
	}                                                                                                                  \
	string BenchmarkInfo() override {                                                                                  \
		return "Benchmark partitioning technique for dataset";											                   \
	}


DUCKDB_BENCHMARK(PartitioningBenchmark, "[oplqp]")
OPLQPBenchmark("query.sql")
FINISH_BENCHMARK(PartitioningBenchmark)
