#include <iostream>

using namespace std;

class ExchangeRateService {
public:
    virtual double getExchangeRate(const string& source, const string& target) = 0;
    virtual ~ExchangeRateService() {}
};

int main() {
    cout << "hello world" << endl;

    return 0;
}