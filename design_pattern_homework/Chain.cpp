#include <iostream>
#include <string>

// Base Handler class
class SupportHandler {
protected:
    SupportHandler *nextHandler;

public:
    SupportHandler(SupportHandler *next = nullptr) : nextHandler(next) {}

    virtual void HandleRequest(const std::string &issue, int severity) {
        if (nextHandler) {
            nextHandler->HandleRequest(issue, severity);
        } else {
            std::cerr << "Issue could not be resolved. Please escalate further." << std::endl;
        }
    }
};

// Concrete Handler 1: Tier 1 Support
class Tier1Support : public SupportHandler {
public:
    using SupportHandler::SupportHandler;

    void HandleRequest(const std::string &issue, int severity) override {
        if (severity <= 2) {
            std::cout << "Tier 1 Support resolved: " << issue << std::endl;
        } else {
            std::cout << "Tier 1 Support cannot handle: " << issue << ". Escalating to Tier 2..." << std::endl;
            SupportHandler::HandleRequest(issue, severity);
        }
    }
};

// Concrete Handler 2: Tier 2 Support
class Tier2Support : public SupportHandler {
public:
    using SupportHandler::SupportHandler;

    void HandleRequest(const std::string &issue, int severity) override {
        if (severity <= 4) {
            std::cout << "Tier 2 Support resolved: " << issue << std::endl;
        } else {
            std::cout << "Tier 2 Support cannot handle: " << issue << ". Escalating to Tier 3..." << std::endl;
            SupportHandler::HandleRequest(issue, severity);
        }
    }
};

// Concrete Handler 3: Tier 3 Support
class Tier3Support : public SupportHandler {
public:
    using SupportHandler::SupportHandler;

    void HandleRequest(const std::string &issue, int severity) override {
        if (severity <= 6) {
            std::cout << "Tier 3 Support resolved: " << issue << std::endl;
        } else {
            std::cout << "Tier 3 Support cannot handle: " << issue << ". Issue remains unresolved." << std::endl;
        }
    }
};

int main() {
    // Create the chain of responsibility
    SupportHandler *support = new Tier1Support(new Tier2Support(new Tier3Support()));

    std::cout << "Issue 1: Login issue (Severity 1)" << std::endl;
    support->HandleRequest("Login issue", 1);
    std::cout << std::endl;

    std::cout << "Issue 2: Database outage (Severity 3)" << std::endl;
    support->HandleRequest("Database outage", 3);
    std::cout << std::endl;

    std::cout << "Issue 3: Server crash (Severity 5)" << std::endl;
    support->HandleRequest("Server crash", 5);
    std::cout << std::endl;

    std::cout << "Issue 4: Critical data breach (Severity 7)" << std::endl;
    support->HandleRequest("Critical data breach", 7);

    // Clean up
    delete support;
    return 0;
}