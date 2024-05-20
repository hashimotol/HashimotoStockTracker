#pragma once
#ifndef ALPHAADVANTAGEAPI_H
#define ALPHAADVANTAGEAPI_H
#include <string>
#include <nlohmann/json.hpp>

class AlphaVantageAPI {
public:
    AlphaVantageAPI(const std::string& apiKey);
    nlohmann::json GetStockData(const std::string& symbol);

private:
    std::string apiKey;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};








#endif // !ALPHAADVANTAGEAPI_H
