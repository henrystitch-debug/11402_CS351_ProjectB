# Traceability

## Purpose

This document records the relationships between project requirements, design decisions, implementation, and verification activities for the lightweight CSV database and query engine.

## Key Requirements

- Import CSV files and validate basic file structure.
- Store rows and columns in a memory-efficient representation.
- Execute simple SQL-like queries including SELECT, WHERE, and JOIN operations.
- Support projection, filtering, and aggregation over CSV data.
- Produce query results in tabular format.
- Handle errors gracefully and report invalid queries.

## Design Components

- CSV Parser: reads CSV input and converts it into an internal table representation.
- Table Model: defines rows, columns, and data types for query processing.
- Query Engine: parses and executes SQL-like queries against tables.
- Execution Planner: maps query clauses to operations such as selection, projection, and join.
- Result Formatter: converts query output back into a human-readable table.

## Traceability Matrix

- Requirement: Import CSV files and validate basic file structure.
  - Design: CSV Parser
  - Implementation: parser module and CSV reader routines
  - Verification: parser tests for valid and malformed CSV inputs

- Requirement: Store rows and columns in a memory-efficient representation.
  - Design: Table Model
  - Implementation: in-memory table structures with row/column indexing
  - Verification: unit tests for table creation and data access

- Requirement: Execute simple SQL-like queries including SELECT, WHERE, and JOIN operations.
  - Design: Query Engine and Execution Planner
  - Implementation: query parser, filter evaluator, and join operator
  - Verification: integration tests for SELECT, WHERE, and JOIN queries

- Requirement: Support projection, filtering, and aggregation over CSV data.
  - Design: Query Engine and Result Formatter
  - Implementation: expression evaluation, projection logic, aggregation functions
  - Verification: tests covering projection, filter conditions, and grouped results

- Requirement: Produce query results in tabular format.
  - Design: Result Formatter
  - Implementation: output formatting module or printer
  - Verification: tests checking formatted output

- Requirement: Handle errors gracefully and report invalid queries.
  - Design: error handling in parser and execution engine
  - Implementation: validation logic and user-facing error messages
  - Verification: tests for invalid CSV input and malformed queries

## Notes

Traceability is maintained by linking each requirement to the corresponding design component and test coverage. Any future changes to requirements should update this document and the related implementation and verification artifacts.
