# Deployment

This document describes how to deploy the lightweight database and query engine for processing CSV files.

## Requirements

- Python 3.11 or later
- pip
- Git (optional, for cloning the repository)
- Access to the CSV dataset files

## Setup

1. Clone the repository (if needed):
   ```bash
   git clone https://your-repo-url.git
   cd 11402_CS351_ProjectB
   ```

2. Create and activate a virtual environment:
   ```bash
   python -m venv .venv
   .venv\Scripts\activate
   ```

3. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```

## Configuration

- Place CSV files in the configured data directory, typically `data/`.
- Update any runtime configuration settings in the project configuration file if available.
- Ensure file paths and permissions allow read access for the application.

## Running the Engine

To start the query engine, run the main entry point for the project. From the repository root:

```bash
python -m src.main
```

or use the provided script if one exists:

```bash
python run.py
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
