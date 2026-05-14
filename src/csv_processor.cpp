#include "csv_processor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <climits>
#include <cstdint>

// ── Private helpers ──────────────────────────────────────────────────────────

std::vector<std::string> CSVProcessor::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

std::string CSVProcessor::trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// ── Accessors ────────────────────────────────────────────────────────────────

const std::vector<std::string>& CSVProcessor::getHeaders() const { return headers; }
const std::vector<std::vector<std::string>>& CSVProcessor::getData() const { return data; }
int CSVProcessor::getRowCount() const { return static_cast<int>(data.size()); }

size_t CSVProcessor::getColumnIndex(const std::string& col) const {
    auto it = std::find(headers.begin(), headers.end(), col);
    return (it == headers.end()) ? SIZE_MAX : static_cast<size_t>(it - headers.begin());
}

// ── Loading ──────────────────────────────────────────────────────────────────

bool CSVProcessor::loadCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    headers.clear();
    data.clear();

    std::string line;
    if (std::getline(file, line)) {
        headers = split(line, ',');
    }

    while (std::getline(file, line)) {
        if (!line.empty()) {
            data.push_back(split(line, ','));
        }
    }

    originalData = data; // snapshot for reset()
    return true;
}

void CSVProcessor::reset() {
    data = originalData;
}

// ── Query dispatcher ─────────────────────────────────────────────────────────

void CSVProcessor::executeQuery(const std::string& query) {
    std::istringstream iss(query);
    std::string command;
    iss >> command;

    if (command == "SELECT") {
        std::string col;
        iss >> col;
        selectColumn(col);
    } else if (command == "FILTER") {
        std::string col, op, val;
        iss >> col >> op >> val;
        filter(col, op, val);
    } else if (command == "SORT") {
        std::string skip, col;
        iss >> skip;          // consume "BY"
        iss >> col;
        sortBy(col);
    } else if (command == "AGGREGATE") {
        std::string func, col;
        iss >> func >> col;
        aggregate(func, col);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}

// ── Operations ───────────────────────────────────────────────────────────────

void CSVProcessor::selectColumn(const std::string& col) {
    size_t idx = getColumnIndex(col);
    if (idx == SIZE_MAX) {
        std::cerr << "Column not found: " << col << std::endl;
        return;
    }
    std::cout << col << "\n";
    for (const auto& row : data) {
        if (idx < row.size()) std::cout << row[idx] << "\n";
    }
}

void CSVProcessor::filter(const std::string& col, const std::string& op, const std::string& val) {
    size_t idx = getColumnIndex(col);
    if (idx == SIZE_MAX) {
        std::cerr << "Column not found: " << col << std::endl;
        return;
    }

    std::vector<std::vector<std::string>> filtered;
    for (const auto& row : data) {
        if (idx >= row.size()) continue;
        const std::string& cell = row[idx];
        bool match = false;
        try {
            if (op == "==")       match = (cell == val);
            else if (op == "!=")  match = (cell != val);
            else if (op == ">")   match = (std::stod(cell) > std::stod(val));
            else if (op == "<")   match = (std::stod(cell) < std::stod(val));
            else if (op == ">=")  match = (std::stod(cell) >= std::stod(val));
            else if (op == "<=")  match = (std::stod(cell) <= std::stod(val));
            else std::cerr << "Unknown operator: " << op << std::endl;
        } catch (...) {
            // non-numeric cell with numeric operator → skip
        }
        if (match) filtered.push_back(row);
    }
    data = filtered;
}

void CSVProcessor::sortBy(const std::string& col) {
    size_t idx = getColumnIndex(col);
    if (idx == SIZE_MAX) {
        std::cerr << "Column not found: " << col << std::endl;
        return;
    }

    std::stable_sort(data.begin(), data.end(),
        [idx](const std::vector<std::string>& a, const std::vector<std::string>& b) {
            if (idx >= a.size() || idx >= b.size()) return false;
            // Try numeric sort first
            try {
                return std::stod(a[idx]) < std::stod(b[idx]);
            } catch (...) {
                return a[idx] < b[idx]; // fall back to lexicographic
            }
        });
}

void CSVProcessor::aggregate(const std::string& func, const std::string& col) {
    size_t idx = getColumnIndex(col);
    if (idx == SIZE_MAX) {
        std::cerr << "Column not found: " << col << std::endl;
        return;
    }

    std::vector<double> values;
    for (const auto& row : data) {
        if (idx < row.size()) {
            try { values.push_back(std::stod(row[idx])); } catch (...) {}
        }
    }

    if (func == "SUM") {
        std::cout << "Sum: " << std::accumulate(values.begin(), values.end(), 0.0) << "\n";
    } else if (func == "AVG") {
        if (!values.empty()) {
            std::cout << "Average: "
                      << std::accumulate(values.begin(), values.end(), 0.0) / values.size()
                      << "\n";
        }
    } else if (func == "COUNT") {
        std::cout << "Count: " << values.size() << "\n";
    } else if (func == "MIN") {
        if (!values.empty())
            std::cout << "Min: " << *std::min_element(values.begin(), values.end()) << "\n";
    } else if (func == "MAX") {
        if (!values.empty())
            std::cout << "Max: " << *std::max_element(values.begin(), values.end()) << "\n";
    } else {
        std::cerr << "Unknown aggregate function: " << func << std::endl;
    }
}

// ── Export ───────────────────────────────────────────────────────────────────

void CSVProcessor::exportResults(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open output file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < headers.size(); ++i) {
        file << headers[i];
        if (i < headers.size() - 1) file << ",";
    }
    file << "\n";

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}