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

class CurrencyExchangeService {
private:
    ExchangeRateService* exchangeRateService;

public:
    CurrencyExchangeService(ExchangeRateService* service) : exchangeRateService(service) {}

    vector<pair<string, string>> convert(const string& source, const string& target, const string& amount_str) {
        vector<pair<string, string>> result;
        string amount_str_no_comma = "";
        for (char c : amount_str) {
           if (isdigit(c)) {
                amount_str_no_comma += c;
            } else if (c == ',') {
                continue;
            } else {
                result.push_back(make_pair("msg", "Invalid amount"));
                return result;
            }
        }
        double amount;
        string error = "";
        try {
            amount = stod(amount_str_no_comma); // convert string to double data type
        } catch (...) {
            result.push_back(make_pair("msg", "Invalid amount"));
            return result;
        }

        if (exchangeRateService == nullptr) {
            result.push_back(make_pair("msg", "Invalid exchange rate service"));
            return result;
        }

        double rate = exchangeRateService->getExchangeRate(source, target);
        double converted_amount = amount * rate;
        double rounded_amount = round(converted_amount * 100) / 100;

        string formatted_amount = to_string(rounded_amount);
        size_t pos = formatted_amount.find('.');
        if (pos != string::npos && formatted_amount.length() - pos > 3) {
            formatted_amount = formatted_amount.substr(0, pos + 3);
        }

        // add ','
        for (int i = formatted_amount.length() - 6; i > 0; i -= 3) {
            formatted_amount.insert(i, ",");
        }
        
        result.push_back(make_pair("msg", "success"));
        result.push_back(make_pair("amount", formatted_amount));

        return result;
    }
};

int main() {
    cout << "hello world" << endl;

    return 0;
}