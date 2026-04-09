# CSV Mini Database and Query Engine

A lightweight database and query engine for processing CSV files.

## Features

- Load and parse CSV files
- Execute queries on CSV data
- Filter, sort, and aggregate data
- Export results

## Getting Started

### Prerequisites

- Python 3.8+

### Installation

```bash
git clone <https://github.com/henrystitch-debug/11402_CS351_ProjectB.git>
cd 11402_CS351_ProjectB
```

### Usage

```python
from csv_engine import Database

db = Database()
db.load_csv('data.csv')
results = db.query('SELECT * WHERE condition')
```

## Project Structure

```
├── README.md
├── src/
│   └── csv_engine.py
└── tests/
    └── test_engine.py
```

## License

MIT License
