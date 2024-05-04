#include <iostream>
#include <unordered_map>

using namespace std;

class ExchangeRateService {
public:
    virtual double getExchangeRate(const string& source, const string& target) = 0;
    virtual ~ExchangeRateService() {}
};

class SimpleExchangeRateService : public ExchangeRateService {
private:
    unordered_map<string, unordered_map<string, double>> rates;

public:
    SimpleExchangeRateService(unordered_map<string, unordered_map<string, double>> rates) : rates(rates) {}

    double getExchangeRate(const string& source, const string& target) override {
        return rates[source][target];
    }
};

int main() {
    cout << "hello world" << endl;

    return 0;
}