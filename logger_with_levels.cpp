
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger {
private:
    ofstream logFile;

    string levelToString(LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARN: return "WARN";
            case ERROR: return "ERROR";
            case FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

public:
    Logger(const string& filename) {
        logFile.open(filename, ios::app);
        if (!logFile.is_open()) {
            throw runtime_error("ფაილის გახსნა ვერ მოხერხდა!");
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(LogLevel level, const string& message) {
        if (message.empty()) {
            throw invalid_argument("ლოგის შეტყობინება ცარიელია!");
        }

        string fullMessage = "[" + levelToString(level) + "] " + message;
        logFile << fullMessage << endl;
        cout << "ლოგი ჩაწერილია: " << fullMessage << endl;
    }
};

int main() {
    try {
        Logger logger("log.txt");

        logger.log(INFO, "პროგრამა დაიწყო.");
        logger.log(DEBUG, "დაწყებულია მონაცემების ჩატვირთვა.");
        logger.log(INFO, "მომხმარებელი შევიდა სისტემაში.");
        logger.log(WARN, "მომხმარებელს არა აქვს სრული წვდომა.");
        logger.log(ERROR, "მონაცემების ჩატვირთვა ვერ მოხერხდა.");
        logger.log(FATAL, "სისტემა იშლება!");

        // ცარიელი
        logger.log(INFO, ""); 

    } catch (const exception& e) {
        cerr << "შეცდომა: " << e.what() << endl;
    }
}
