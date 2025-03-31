#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

class Logger {
private:
    ofstream logFile;

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

    void log(const string& message) {
        if (message.empty()) {
            throw invalid_argument("ლოგის შეტყობინება ცარიელია!");
        }
        logFile << message << endl;
        cout << "ლოგი ჩაწერილია: " << message << endl;
    }
};

int main() {
    try {
        Logger logger("log.txt");

        logger.log("პროგრამა დაიწყო.");
        logger.log("მომხმარებელი შევიდა სისტემაში.");

        logger.log(""); 

    } catch (const exception& e) {
        cerr << "შეცდომა: " << e.what() << endl;
    }
}
