#pragma once
#ifndef DISPLAYSTOCKPRICES_H
#define DISPLAYSTOCKPRICES_H
#include <string>
#include <nlohmann/json.hpp>
#include <nlohmann/json.hpp>
#include "AlphaVantageAPI.h"


double CalculateAveragePrice(const nlohmann::json& timeSeries);

double CalculatePercentageDecrease(double highestPrice, double latestPrice);


void DisplayStockData(const nlohmann::json& stockData, const std::string& symbol, double buyTriggerPercentage);

#endif