#include <filesystem>
#include <iostream>
#include <string>

#include "benchmark_runner.hpp"
#include "duckdb_benchmark_macro.hpp"

using namespace duckdb;

#define QUERY_FILE_PATH "query.sql"
#define VERIFY_FILE "verify.sql"

//////////////
// DuckDBPartitionState //
//////////////
struct DuckDBPartitionState : public DuckDBBenchmarkState {
	string query;

	DuckDBPartitionState(string path) : DuckDBBenchmarkState(path) {	                                               \
		string queryPath = QUERY_FILE_PATH;																			   \
		std::ifstream inputFileStream(queryPath);                                                                      \
		std::string fileContent;                                                                                       \
		fileContent.assign ( (std::istreambuf_iterator<char>(inputFileStream) ),                                       \
		                   (  std::istreambuf_iterator<char>()    ) );                                                 \
		query = fileContent;
	}
	virtual ~DuckDBPartitionState() {
	}
};

#define OPLQPBenchmark(QUERY_FILE) 																					   \
	duckdb::unique_ptr<DuckDBBenchmarkState> CreateBenchmarkState() override {   									   \
		auto result = make_uniq<DuckDBPartitionState>(GetDatabasePath());                                              \
		return std::move(result);                                                                                      \
    }                                                                                                                  \
	void Load(DuckDBBenchmarkState *state_p) override {  															   \
    	state_p->conn.Query("PRAGMA enable_object_cache");                                                             \
	}                                                                                                                  \
	void RunBenchmark(DuckDBBenchmarkState *state_p) override {                                                        \
        auto state = (DuckDBPartitionState *)state_p;                                                                  \
	    auto query = state->query;                                                                                     \
	    state->result = state->conn.Query(query);                                                                      \
	}                                                                                                                  \
	void Cleanup(DuckDBBenchmarkState *state) override {                                                               \
	}                                                                                                                  \
	string VerifyResult(QueryResult *result) override {                                                                \
		if (result->HasError()) {                                                                                      \
			return result->GetError();                                                                                 \
		}                                                                                                              \
		return string();    																						   \
    }                                                                                                                  \
	string BenchmarkInfo() override {                                                                                  \
		return "Benchmark partitioning technique for dataset";											               \
	}           																									   \
	size_t Timeout() override {                                                                                        \
		return 60;                                                                                                     \
	}


DUCKDB_BENCHMARK(PartitioningBenchmark, "[oplqp]")
OPLQPBenchmark("query.sql")
FINISH_BENCHMARK(PartitioningBenchmark)
