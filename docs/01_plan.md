# Project Plan: Lightweight CSV Database and Query Engine

## Overview
This project develops a lightweight database and query engine for processing CSV files. It enables loading CSV data, executing SQL-like queries, and exporting results efficiently.

## Objectives
- Create an efficient tool for querying large CSV files without full memory loading.
- Support essential SQL operations
- Ensure fast performance for typical CSV processing tasks.
- Provide a simple command-line interface.

## Key Features
- **CSV Loading**: Parse and load CSV files into internal data structures.
- **Query Support**: Implement a subset of SQL for querying data.
- **Export Functionality**: Output query results to CSV or other formats.
- **Optimization**: Basic query planning and indexing for performance.

## Architecture
- **Parser Module**: Handles CSV reading, parsing, and schema inference.
- **Storage Module**: Manages data in memory or on disk with indexing.
- **Query Engine**: Parses SQL queries, executes them, and returns results.
- **CLI Module**: Provides the interface for user commands.

## Implementation Phases
1. **Phase 1: Design and Setup**
   - Define data structures (e.g., tables, columns).
   - Set up project structure and dependencies.

2. **Phase 2: Core Components**
   - Implement CSV parser.
   - Build basic storage and query execution.

3. **Phase 3: Advanced Features**
   - Add SELECT, aggregation, and sorting.
   - Implement query optimization.

4. **Phase 4: Testing**
   - Comprehensive testing and bug fixes.

5. **Phase 5: Documentation and Finalization**
   - Write user documentation.
   - Performance tuning and release preparation.

## Technologies
- Language: C++
- Libraries: csv

