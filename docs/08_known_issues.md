# Known Issues

This project is a lightweight CSV-based database and query engine. The implementation is intentionally simple, and the following limitations are known.

## CSV Parsing

- Only standard comma-separated CSV files are supported.
- Quoted fields with embedded newlines are not fully supported.
- Escaped delimiters and custom quote characters may not be handled correctly.
- Inconsistent row lengths can cause parsing failures or misaligned output.

## Query Engine

- SQL support is limited. Most queries are restricted to basic `SELECT`, `FROM`, and `WHERE` operations.
- Joins are not supported or are only partially implemented.
- Aggregate functions, grouping, ordering, and subqueries are not available.
- Complex expressions and advanced query optimizations are not implemented.

## Performance and Scalability

- The engine is single-threaded and does not scale to very large CSV files.
- Memory usage can be high for large datasets since file content may be loaded into memory.
- There is no indexing support, so filtering and scanning are often full-table operations.

## Data Types and Schema

- Column type inference is basic and may treat values as strings when numeric or date types are expected.
- Schema evolution or column type changes are not supported.
- Missing values and null handling are limited.

## Concurrency and Reliability

- Concurrent read/write access is not supported.
- There is no transaction support, rollback, or crash recovery.
- Error reporting is minimal and may not always identify the root cause.

## Recommended Workarounds

- Use well-formed CSV files with consistent rows and simple formatting.
- Keep datasets small to avoid memory and performance issues.
- Use this engine for lightweight analysis rather than production workloads.
