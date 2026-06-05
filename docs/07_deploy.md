# Deployment

This document describes how to deploy the lightweight database and query engine for processing CSV files.

## Requirements

- C++
- Git (optional, for cloning the repository)
- Access to the CSV dataset files

## Setup

  Clone the repository (if needed):
   ```bash
   git clone https://henrystitch-debug/11402_CS351/ProjectB.git
   cd 11402_CS351_ProjectB
   ```


## Configuration

- Place CSV files in the configured data directory, typically `data/`.
- Update any runtime configuration settings in the project configuration file if available.
- Ensure file paths and permissions allow read access for the application.

## Running the Engine

To start the query engine, run the main entry point for the project. From the repository root:

```bash
g++ src/main.cpp src/csv_processor.cpp -o build/csv_db -Iinclude -Wall -Wextra -std=c++17   
```

or run the tests:

```bash
g++ tests/test_csv_processor.cpp src/csv_processor.cpp -o run_tests -Iinclude -Wall -Wextra -std=c++17
>> ./run_tests.exe

```

## Deployment Notes

- For local deployment, ensure the virtual environment is activated before running the application.
- For production deployment, consider packaging the project as a container or using a lightweight process manager.
- Monitor application logs and ensure CSV inputs are updated in a controlled way.

## Testing Deployment

- Verify the engine can load and parse CSV files.
- Run sample queries against the loaded dataset.
- Confirm output matches expected results.

## Maintenance

- Keep dependencies up to date.
- Back up CSV data files before making changes.
- Review performance for large CSV datasets and adjust memory or file handling settings as needed.
