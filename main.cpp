#include <iostream>
#include "AlphaVantageAPI.h"
#include "DisplayStockPrices.h"


int main() {
    std::string apiKey = "HUSEYM6KZZBIB9XZ";
    std::string symbol = "NVDA";  // Example stock symbol for Apple
    double buyTriggerPercentage = 10.0;

    AlphaVantageAPI api(apiKey);


    auto stockData = api.GetStockData(symbol);

    if (!stockData.is_null()) {
        DisplayStockData(stockData, symbol, buyTriggerPercentage);
    }
    else {
        std::cerr << "Failed to fetch stock data." << std::endl;
    }

    return 0;
}