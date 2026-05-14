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

1. `employees.csv`
   - columns: `id`, `name`, `department`, `salary`, `hire_date`
2. `departments.csv`
   - columns: `department`, `manager`, `location`
3. `sales.csv`
   - columns: `order_id`, `customer_id`, `product`, `quantity`, `price`, `order_date`

## Acceptance Test Cases

### 1. Load CSV File

- Description: Verify the engine can load a CSV file and recognize columns.
- Steps:
  1. Load `employees.csv`.
  2. Inspect the schema or header.
- Expected result: The engine reports columns `id`, `name`, `department`, `salary`, `hire_date`.

### 2. Select and Filter Rows

- Description: Verify basic SELECT and WHERE operations.
- Steps:
  1. Query `employees.csv` for employees in `Sales`.
  2. Select `name` and `salary`.
- Expected result: Only rows where `department = 'Sales'` are returned, with correct `name` and `salary` values.

### 3. Arithmetic Expression

- Description: Verify arithmetic expressions in query projection.
- Steps:
  1. Query `employees.csv`.
  2. Compute `salary * 1.1` as `adjusted_salary`.
- Expected result: Each row includes `adjusted_salary` equal to the original salary multiplied by `1.1`.

### 4. Sorting Results

- Description: Verify ORDER BY support.
- Steps:
  1. Query `employees.csv`.
  2. Order by `salary DESC`.
- Expected result: Rows are sorted from highest to lowest salary.

### 5. Limit Results

- Description: Verify limit functionality.
- Steps:
  1. Query `employees.csv`.
  2. Limit to top 3 rows by salary.
- Expected result: Exactly 3 rows are returned.

### 6. Grouping and Aggregation

- Description: Verify GROUP BY and aggregate functions.
- Steps:
  1. Query `sales.csv`.
  2. Group by `product`.
  3. Compute total `quantity` and total revenue `quantity * price`.
- Expected result: One aggregated row per product with correct totals.

### 7. Join CSV Files

- Description: Verify join across files.
- Steps:
  1. Query `employees.csv` and `departments.csv`.
  2. Join on `department`.
  3. Select `name`, `department`, `manager`, `location`.
- Expected result: Each employee row is enriched with matching department manager and location.

### 8. Query with Multiple Conditions

- Description: Verify boolean logic in filters.
- Steps:
  1. Query `sales.csv`.
  2. Filter where `quantity > 5` AND `price < 100`.
- Expected result: Only rows satisfying both conditions appear.

### 9. Invalid CSV Handling

- Description: Verify the engine reports errors for malformed input.
- Steps:
  1. Load a malformed CSV with missing columns or invalid quoting.
- Expected result: The engine returns a useful error message and does not crash.

### 10. Missing Column Reference

- Description: Verify error handling for invalid references.
- Steps:
  1. Execute a query selecting a non-existent column from `employees.csv`.
- Expected result: The engine returns an error indicating the unknown column.

## Acceptance Criteria

The project is accepted when all test cases pass and the engine demonstrates correct CSV loading, query execution, result ordering, aggregation, joins, and proper error handling.
