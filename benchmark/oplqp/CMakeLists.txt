add_library(
  duckdb_benchmark_olpqp OBJECT
  tpch.cpp)

set(BENCHMARK_OBJECT_FILES
    ${BENCHMARK_OBJECT_FILES} $<TARGET_OBJECTS:duckdb_benchmark_olpqp>
    PARENT_SCOPE)
