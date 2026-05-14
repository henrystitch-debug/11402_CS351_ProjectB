#pragma once

#include <string>
#include <vector>

class CSVProcessor {
private:
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> data;
    std::vector<std::vector<std::string>> originalData; // preserved for reset

    std::vector<std::string> split(const std::string& s, char delimiter);
    std::string trim(const std::string& s);

public:
    // Loading
    bool loadCSV(const std::string& filename);
    void reset();  // restores data to originalData

    // Query execution (dispatch)
    void executeQuery(const std::string& query);

    // Individual operations
    void selectColumn(const std::string& col);
    void filter(const std::string& col, const std::string& op, const std::string& val);
    void sortBy(const std::string& col);
    void aggregate(const std::string& func, const std::string& col);

    // Export
    void exportResults(const std::string& filename);

    // Accessors (used by tests)
    const std::vector<std::string>& getHeaders() const;
    const std::vector<std::vector<std::string>>& getData() const;
    size_t getColumnIndex(const std::string& col) const; // returns SIZE_MAX if not found
    int getRowCount() const;
};