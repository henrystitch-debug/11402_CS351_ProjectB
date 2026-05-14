#include <iostream>;
#include <fstream>;
#include <vector>;
#include <string>;
#include <sstream>;
#include <algorithm>;
#include <numeric>;
#include <cctype>;

class CSVProcessor {
private:
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> data;

    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    bool loadCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string line;
        if (std::getline(file, line)) {
            headers = split(line, ',');
        }

        while (std::getline(file, line)) {
            data.push_back(split(line, ','));
        }

        file.close();
        return true;
    }

    void executeQuery(const std::string& query) {
        // Simple query parser: assume format like "SELECT column WHERE column op value SORT BY column AGGREGATE func column"
        // This is a basic implementation; extend as needed.
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
            std::string by;
            iss >> by >> by; // skip "BY"
            iss >> by;
            sortBy(by);
        } else if (command == "AGGREGATE") {
            std::string func, col;
            iss >> func >> col;
            aggregate(func, col);
        }
    }

    void selectColumn(const std::string& col) {
        auto it = std::find(headers.begin(), headers.end(), col);
        if (it == headers.end()) return;
        size_t idx = it - headers.begin();

        std::cout << col << std::endl;
        for (const auto& row : data) {
            if (idx < row.size()) std::cout << row[idx] << std::endl;
        }
    }

    void filter(const std::string& col, const std::string& op, const std::string& val) {
        auto it = std::find(headers.begin(), headers.end(), col);
        if (it == headers.end()) return;
        size_t idx = it - headers.begin();

        std::vector<std::vector<std::string>> filtered;
        for (const auto& row : data) {
            if (idx >= row.size()) continue;
            std::string cell = row[idx];
            bool match = false;
            if (op == "==") match = (cell == val);
            else if (op == "!=") match = (cell != val);
            else if (op == ">") match = (std::stod(cell) > std::stod(val));
            else if (op == "<") match = (std::stod(cell) < std::stod(val));
            if (match) filtered.push_back(row);
        }
        data = filtered;
    }

    void sortBy(const std::string& col) {
        auto it = std::find(headers.begin(), headers.end(), col);
        if (it == headers.end()) return;
        size_t idx = it - headers.begin();

        std::sort(data.begin(), data.end(), [idx](const std::vector<std::string>& a, const std::vector<std::string>& b) {
            if (idx >= a.size() || idx >= b.size()) return false;
            return a[idx] < b[idx];
        });
    }

    void aggregate(const std::string& func, const std::string& col) {
        auto it = std::find(headers.begin(), headers.end(), col);
        if (it == headers.end()) return;
        size_t idx = it - headers.begin();

        std::vector<double> values;
        for (const auto& row : data) {
            if (idx < row.size()) {
                try {
                    values.push_back(std::stod(row[idx]));
                } catch (...) {}
            }
        }

        if (func == "SUM") {
            double sum = std::accumulate(values.begin(), values.end(), 0.0);
            std::cout << "Sum: " << sum << std::endl;
        } else if (func == "AVG") {
            if (!values.empty()) {
                double sum = std::accumulate(values.begin(), values.end(), 0.0);
                std::cout << "Average: " << sum / values.size() << std::endl;
            }
        } else if (func == "COUNT") {
            std::cout << "Count: " << values.size() << std::endl;
        }
    }

    void exportResults(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        // Write headers
        for (size_t i = 0; i < headers.size(); ++i) {
            file << headers[i];
            if (i < headers.size() - 1) file << ",";
        }
        file << std::endl;

        // Write data
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) file << ",";
            }
            file << std::endl;
        }

        file.close();
    }
};

int main() {
    CSVProcessor processor;
    if (processor.loadCSV("data.csv")) {
        processor.executeQuery("FILTER age &gt; 25");
        processor.executeQuery("SORT BY name");
        processor.exportResults("output.csv");
    }
    return 0;
}