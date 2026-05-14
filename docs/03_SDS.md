# Software Design Specification (SDS)

## 1. Overview

This document describes the detailed design of a lightweight database and query engine for processing CSV files. The system allows users to load CSV data, execute SQL-like queries, and retrieve results efficiently.

## 2. System Architecture

### 2.1 High-Level Components

- **CSV Loader**: Reads and parses CSV files into in-memory data structures
- **Query Parser**: Parses SQL-like query syntax
- **Query Engine**: Executes parsed queries against loaded data
- **Result Manager**: Formats and returns query results

### 2.2 Data Flow

```
CSV File → CSV Loader → Data Store → Query Parser → Query Engine → Results
```

## 3. Detailed Design

### 3.1 CSV Loader Module

**Responsibility**: Load CSV files and convert them into in-memory table structures

**Key Functions**:
- `loadCSV(filepath)`: Reads CSV file and creates table
- `parseRow(line)`: Parses individual CSV row
- `validateData()`: Ensures data integrity

**Data Structures**:
- Table: In-memory representation of CSV data
- Row: Collection of column values
- Column: Metadata including name and type

### 3.2 Data Store Module

**Responsibility**: Store and manage loaded CSV data

**Key Structures**:
- `Table`: Contains rows and column metadata
- `Database`: Collection of loaded tables
- `Schema`: Column definitions and types

### 3.3 Query Parser Module

**Responsibility**: Parse SQL-like query strings into executable structures

**Supported Operations**:
- SELECT: Column projection
- WHERE: Row filtering
- ORDER BY: Result sorting
- GROUP BY: Data aggregation
- JOIN: Multi-table operations

**Key Functions**:
- `parse(queryString)`: Convert query to AST
- `validate(ast)`: Verify query validity
- `optimize(ast)`: Optimize query execution plan

### 3.4 Query Engine Module

**Responsibility**: Execute parsed queries against data store

**Key Functions**:
- `execute(query)`: Run query and return results
- `filter(rows, condition)`: Apply WHERE clause
- `project(rows, columns)`: Apply SELECT clause
- `sort(rows, order)`: Apply ORDER BY clause
- `aggregate(rows, groupBy)`: Apply GROUP BY clause

### 3.5 Result Manager Module

**Responsibility**: Format and return query results

**Key Functions**:
- `formatResults(data)`: Convert to output format
- `toJSON()`: JSON output format
- `toCSV()`: CSV output format
- `toTable()`: Human-readable table format

## 4. Class Diagram

```
Database
├── Table[]
│   ├── Column[]
│   └── Row[]
│
QueryEngine
├── Parser
├── Executor
└── ResultManager
```

## 5. Data Structures

### 5.1 Column
- `name`: String
- `type`: DataType (STRING, INTEGER, FLOAT, BOOLEAN)
- `nullable`: Boolean

### 5.2 Row
- `values`: Array of values
- `parentTable`: Reference to table

### 5.3 Table
- `name`: String
- `columns`: Column[]
- `rows`: Row[]
- `schema`: Schema metadata

## 6. Algorithm Descriptions

### 6.1 CSV Parsing Algorithm

```
1. Read file line by line
2. Parse first line as header
3. For each subsequent line:
   a. Split by delimiter (comma)
   b. Handle quoted fields
   c. Create Row with parsed values
   d. Add to Table
```

### 6.2 Query Execution Algorithm

```
1. Parse query string
2. Validate query structure
3. Load relevant table(s)
4. Apply WHERE clause (filter)
5. Apply GROUP BY if present
6. Apply ORDER BY if present
7. Apply SELECT (projection)
8. Format and return results
```

## 7. Design Patterns

- **Builder Pattern**: For query construction
- **Strategy Pattern**: For different output formats
- **Visitor Pattern**: For AST traversal during execution
- **Facade Pattern**: Simple interface to complex query engine

## 8. Performance Considerations

- In-memory storage for fast access
- Column indexing for optimized WHERE clause evaluation
- Lazy evaluation where applicable
- Query optimization before execution

## 9. Error Handling

- Invalid CSV format detection
- Query syntax validation
- Type mismatch detection
- File I/O error handling
- Meaningful error messages

## 10. Dependencies

- No external libraries for core functionality
- Standard library utilities for file I/O
- Standard collections for data structures
