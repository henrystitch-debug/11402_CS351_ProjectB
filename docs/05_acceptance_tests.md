# Acceptance Tests

## Overview

This document defines acceptance tests for the lightweight database and query engine for processing CSV files. The goal is to verify that the system can ingest CSV data, execute queries, and produce correct results for typical use cases.

## Scope

Acceptance tests cover the following capabilities:

- loading CSV files into the engine
- selecting columns and filtering rows
- performing arithmetic and comparison operations
- sorting and limiting result sets
- grouping and aggregation
- joining data across CSV files
- handling invalid input and error conditions

## Test Environment

Assumptions:

- CSV files are available locally in a known data directory
- The query engine can be invoked from a command line or API
- Results may be returned as rows, tables, or exported CSV output

## Test Data

Sample data sets used for tests:

- products.csv (columns: productId, name, price, material, quantity, color)

## Acceptance Test Cases

### 1. Load and Reset Functions

- Description: Verify the engine can load a CSV file and reset it.
- Steps:
  1. Load `products.csv`.
  2. Inspect the schema or header.
  3. Reset the engine.
- Expected result: The engine successfully loads `products.csv` with columns `productId`, `name`, `price`, `material`, `quantity`, and `color`. Reset clears the loaded data.

### 2. Select a Specific Column

- Description: Verify basic SELECT operations on a specific column.
- Steps:
  1. Load `products.csv`.
  2. Query and select only the `name` column.
- Expected result: Only the `name` column is returned for all products.

### 3. Filter Rows by Price

- Description: Verify filtering capabilities.
- Steps:
  1. Load `products.csv`.
  2. Filter rows where `price > 50`.
- Expected result: Only rows with price greater than 50 are returned with all columns intact.

### 4. Sorting Rows Alphabetically

- Description: Verify ORDER BY support for alphabetical sorting.
- Steps:
  1. Load `products.csv`.
  2. Order by `name` alphabetically (ASC).
- Expected result: Rows are sorted alphabetically by product name from A to Z.

### 5. Aggregate Functions - MIN

- Description: Verify MIN aggregate function.
- Steps:
  1. Load `products.csv`.
  2. Compute the minimum `price`.
- Expected result: The lowest price value from all products is returned.

### 6. Aggregate Functions - MAX

- Description: Verify MAX aggregate function.
- Steps:
  1. Load `products.csv`.
  2. Compute the maximum `price`.
- Expected result: The highest price value from all products is returned.

### 7. Aggregate Functions - AVG

- Description: Verify AVG aggregate function.
- Steps:
  1. Load `products.csv`.
  2. Compute the average `price`.
- Expected result: The mean price value from all products is returned.

### 8. Invalid CSV Handling

- Description: Verify the engine reports errors for malformed input.
- Steps:
  1. Load a malformed CSV with missing columns or invalid quoting.
- Expected result: The engine returns a useful error message and does not crash.

### 9. Missing Column Reference

- Description: Verify error handling for invalid references.
- Steps:
  1. Execute a query selecting a non-existent column from `products.csv`.
- Expected result: The engine returns an error indicating the unknown column.

## Acceptance Criteria

The project is accepted when all test cases pass and the engine demonstrates correct CSV loading, query execution, result ordering, aggregation, joins, and proper error handling.
