#include "csv_processor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string inputFile  = (argc > 1) ? argv[1] : "../data/products.csv";
    std::string outputFile = (argc > 2) ? argv[2] : "output.csv";

    CSVProcessor processor;

    if (!processor.loadCSV(inputFile)) {
        std::cerr << "Failed to open: " << inputFile << std::endl;
        return 1;
    }

    std::cout << "=== Loaded " << processor.getRowCount() << " rows ===\n\n";

    // Example 1: filter expensive items, then sort
    std::cout << "--- Items over $50, sorted by price ---\n";
    processor.executeQuery("FILTER price > 50");
    processor.executeQuery("SORT BY price");
    processor.executeQuery("SELECT name");

    processor.reset(); // back to full dataset

    // Example 2: aggregate
    std::cout << "\n--- Price stats (full catalogue) ---\n";
    processor.executeQuery("AGGREGATE AVG price");
    processor.executeQuery("AGGREGATE MIN price");
    processor.executeQuery("AGGREGATE MAX price");
    processor.executeQuery("AGGREGATE SUM quantity");

    processor.reset();

    // Example 3: filter by material then export
    std::cout << "\n--- Wool items exported to " << outputFile << " ---\n";
    processor.executeQuery("FILTER material == Wool");
    processor.exportResults(outputFile);
    std::cout << processor.getRowCount() << " rows written.\n";

    return 0;
}