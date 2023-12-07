add_library(duckdb_benchmark_partitioning OBJECT partitioning.cpp)

set(BENCHMARK_OBJECT_FILES ${BENCHMARK_OBJECT_FILES} $<TARGET_OBJECTS:duckdb_benchmark_partitioning> PARENT_SCOPE)
