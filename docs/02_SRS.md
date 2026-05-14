# Software Requirements Specification (SRS)

## 1. Introduction

### 1.1 Purpose
This document describes the software requirements for a lightweight database and query engine designed to process CSV files. The system provides data ingestion, storage, query execution, and export capabilities for tabular datasets in CSV format.

### 1.2 Scope
The product is a command-line and library-based tool that loads CSV data, validates schema, executes SQL-like queries, and returns results in memory or as CSV output. It is intended for small to medium datasets and developers who need fast, portable data processing without a full database server.

### 1.3 Definitions, Acronyms, and Abbreviations
- CSV: Comma-Separated Values
- SRS: Software Requirements Specification
- Query Engine: The module that parses and executes filter, projection, aggregation, and join operations
- Schema: Definitions of columns and data types for a CSV file

### 1.4 References
- CSV file format conventions
- Project requirements from CS351 Project B

## 2. Overall Description

### 2.1 Product Perspective
The product is a standalone lightweight database engine. It does not depend on an external database server and is designed for direct processing of CSV files on local storage.

### 2.2 Product Functions
- Load CSV data into an internal table representation
- Detect and validate schema from column headers and row values
- Support SQL-like queries including SELECT, WHERE, ORDER BY, GROUP BY, and basic JOIN operations
- Export query results as CSV or display them in a console-friendly format
- Provide error handling for malformed CSV files and invalid queries

### 2.3 User Characteristics
Users are expected to be developers, data analysts, or students familiar with CSV data and basic query syntax. Users must understand column naming and simple expressions.

### 2.4 Constraints
- Input format limited to standard CSV files
- Memory usage should remain reasonable for datasets that fit in available RAM
- Query execution focused on single-node operation without distributed processing

### 2.5 Assumptions and Dependencies
- CSV files follow a header row and consistent column counts per row
- The runtime environment provides access to local filesystem storage
- The engine depends only on standard libraries or lightweight parsing utilities

## 3. Specific Requirements

### 3.1 Functional Requirements
- FR1: The system shall load a CSV file and parse its header row.
- FR2: The system shall infer or accept explicit column data types.
- FR3: The system shall support SELECT queries that project one or more columns.
- FR4: The system shall support WHERE clauses with comparison and logical operators.
- FR5: The system shall support ORDER BY for ascending and descending sorting.
- FR6: The system shall support GROUP BY with basic aggregation functions (COUNT, SUM, AVG, MIN, MAX).
- FR7: The system shall support JOIN operations between two CSV tables on one or more keys.
- FR8: The system shall export query results to a CSV file.
- FR9: The system shall report errors for invalid CSV formatting, unsupported data types, and malformed queries.

### 3.2 Nonfunctional Requirements
- NFR1: The system shall start and respond to simple queries within seconds for datasets up to tens of thousands of rows.
- NFR2: The system shall use clear and informative error messages.
- NFR3: The system shall maintain portability across Windows and Unix-like systems.
- NFR4: The system shall minimize external dependencies.

### 3.3 External Interface Requirements
- User Interface: Command-line interface accepting file paths and query strings.
- Data Interface: CSV input and output files with comma-separated fields and quoted values when required.

### 3.4 Data Requirements
- The system shall preserve column names from the CSV header.
- The system shall support string, integer, floating-point, and boolean data types.
- The system shall handle empty values as null or empty strings depending on context.

### 3.5 Performance Requirements
- The system shall process queries over datasets with up to 100,000 rows without excessive memory consumption.
- The system shall avoid unnecessary disk I/O during query execution once data is loaded.

### 3.6 Security Requirements
- The system shall not execute arbitrary code from query strings.
- The system shall validate file paths to prevent obvious path traversal in export functions.

## 4. Appendices

### 4.1 Example Use Cases
- Load a CSV file and display selected columns
- Filter rows by a numeric condition
- Generate aggregated summaries from grouped data
- Join two CSV tables on a common key

### 4.2 Revision History
- Version 1.0: Initial SRS created for CS351 Project B
