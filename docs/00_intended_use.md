# Intended Use

This project is a lightweight database and query engine designed for processing CSV files.

## Purpose

The intended use of this project is to provide a simple, efficient tool for:
- loading CSV data
- executing basic queries and filters
- performing aggregations and projections

## Use Cases

Typical use cases include:
- analyzing CSV datasets for small to medium-sized projects
- teaching or learning query processing concepts
- automating CSV-based data workflows

## Scope

The project is intended for:
- local CSV files
- simple query operations over one or more CSV tables
- lightweight, in-memory computation
- developers and analysts who need a compact alternative to relational databases

It is not intended for:
- large-scale distributed database workloads
- replacing enterprise database systems
- complex transactions or multi-user concurrency control

## Workflow

1. Provide one or more CSV files as input.
2. Define the query or transformation to execute.
3. Run the engine to process the CSV data.
4. Review the output, which can be returned as a query result or saved as a CSV.

## Goals

The primary goals are:
- easy setup and usage
- predictable CSV processing behavior
- clear query semantics
- portability across environments
