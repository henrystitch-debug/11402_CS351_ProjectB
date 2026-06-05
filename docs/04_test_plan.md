# Test Plan

## 1. Introduction
This document defines the test plan for the lightweight database and query engine for processing CSV files. The purpose is to verify functionality, correctness, and stability for ingesting, querying, and exporting CSV data.

## 2. Objectives
- Confirm that the engine correctly reads and parses CSV files.
- Verify query operations return accurate results.
- Validate filter, projection, aggregation, and join behaviors.
- Ensure error handling is appropriate for malformed input and invalid queries.
- Confirm performance is acceptable for small to medium-sized CSV datasets.

## 3. Scope
In scope:
- CSV file ingestion and parsing
- Query parsing and execution
- Result formatting and export
- Error reporting for invalid CSV and queries
- Basic performance for representative data sizes

Out of scope:
- Distributed query processing
- Advanced SQL features beyond the supported query subset
- Large-scale benchmarking on datasets larger than 1 million rows

## 4. Test Items
- CSV reader module
- Query parser module
- Query execution engine
- Result formatter/exporter
- Error handling and validation logic

## 5. Test Approach
- Unit tests for individual modules and components
- Integration tests that cover end-to-end CSV load, query execution, and output
- Regression tests for previously identified edge cases
- Manual test cases for complex query scenarios when automated coverage is insufficient

## 6. Test Cases
1. CSV ingestion
   - Read valid CSV with headers and verify field values.
   - Read CSV with quoted fields and commas inside values.
   - Detect missing fields or inconsistent column count.

2. Query execution
   - Select all columns from a loaded CSV.
   - Select specified columns.
   - Apply filters using equality, inequality, and numeric comparisons.
   - Execute aggregate queries such as count, sum, average if supported.
   - Perform simple joins between two CSV datasets if supported.

3. Error handling
   - Reject malformed CSV files with clear error messages.
   - Reject invalid query syntax.
   - Reject queries referencing missing columns.

4. Output verification
   - Confirm query results match expected rows.
   - Confirm output format is valid CSV or specified format.

5. Performance
   - Load and query datasets of varying sizes (small, medium).
   - Measure execution time for basic queries.

## 7. Test Data
- Small CSV dataset (10-50 rows) with mixed data types.
- Medium CSV dataset (500-1000 rows) with repeated values.
- Edge case CSV files: empty file, no results.
- Sample join datasets with common key columns.

## 8. Pass/Fail Criteria
- Pass: Test case executes and results match expected values.
- Fail: Actual output differs from expected output, or system crashes/returns invalid errors.
- Critical failures include incorrect parsing, incorrect query results, or unhandled exceptions.

