#include <iostream>
#include "AlphaVantageAPI.h"
#include "DisplayStockPrices.h"
#include <curl/curl.h>
#include <string>

double CalculateAveragePrice(const nlohmann::json& timeSeries) {
	double sum = 0;
	int count = 0;
	for (auto date = timeSeries.begin(); date != timeSeries.end(); ++date) {
		if (date.value().contains("4. close")) {
			sum += std::stod(date.value().at("4. close").get<std::string>());
			count++;
		}
	}

	return (count > 0) ? (sum / count) : 0;
}

double CalculatePercentageDecrease(double highestPrice, double latestPrice) {
	if (highestPrice == 0) return 0;

	double percentDecrease = ((highestPrice - latestPrice) / highestPrice) * 100;

	return percentDecrease;
}


void DisplayStockData(const nlohmann::json& stockData, const std::string& symbol, double buyTriggerPercentage) {
	if (!stockData.contains("Time Series (Daily)")) {
		std::cerr << "Error: Time Series (Daily) not found in JSON data\n";
		return;
	}

	const auto& timeSeries = stockData["Time Series (Daily)"];
	double latestPrice = 0.0;
	double highestPrice = 0.0;
	double sum = 0.0;
	int count = 0;

	//latest price calculations
	try {
		auto lastEntry = timeSeries.end();
		--lastEntry;  // Move to the last entry
		if (lastEntry.value().contains("4. close")) {
			latestPrice = std::stod(lastEntry.value().at("4. close").get<std::string>());
		}
		else {
			throw std::runtime_error("Latest price '4. close' not found");
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error parsing latest price: " << e.what() << std::endl;
		return;
	}


	//highest price calculations
	for (auto it = timeSeries.begin(); it != timeSeries.end(); ++it) {
		try {
			double closePrice = std::stod(it.value().at("4. close").get<std::string>());
			if (closePrice > highestPrice) {
				highestPrice = closePrice;
			}
			sum += closePrice;
			++count;
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing close price: " << e.what() << std::endl;
		}
	}

	double averagePrice = CalculateAveragePrice(timeSeries);
	double percentDecrease = CalculatePercentageDecrease(highestPrice, latestPrice);

	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Latest stock price for " << symbol << ": " << latestPrice << "\n";
	std::cout << "Average stock price for " << symbol << ": " << averagePrice << "\n";
	std::cout << "Highest stock price for " << symbol << ": " << highestPrice << "\n";
	std::cout << "Percentage decrease from highest: " << percentDecrease << "%\n";

	if (percentDecrease >= buyTriggerPercentage) {
		std::cout << "The stock has decreased by " << buyTriggerPercentage << "% or more. Consider buying.\n";
	}
	else {
		std::cout << "The stock has not decreased by " << buyTriggerPercentage << "%.\n";
	}
}


