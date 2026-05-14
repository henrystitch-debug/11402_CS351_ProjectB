cmake_minimum_required(VERSION 3.14)
project(CSVMiniDatabase CXX)

# ── Standard ──────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Compiler warnings ─────────────────────────────────────────────────────────
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ── Shared library (core logic reused by main and tests) ──────────────────────
add_library(csv_core STATIC
    src/csv_processor.cpp
)
target_include_directories(csv_core PUBLIC include)

# ── Main executable ───────────────────────────────────────────────────────────
add_executable(csv_db src/main.cpp)
target_link_libraries(csv_db PRIVATE csv_core)

# ── Tests ─────────────────────────────────────────────────────────────────────
enable_testing()

add_executable(run_tests tests/test_csv_processor.cpp)
target_link_libraries(run_tests PRIVATE csv_core)

target_compile_definitions(run_tests PRIVATE
    TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data"
)

# Register with CTest
add_test(
    NAME CSVProcessorTests
    COMMAND run_tests
)