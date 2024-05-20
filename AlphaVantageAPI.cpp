// AlphaVantageAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AlphaVantageAPI.h"
#include <curl/curl.h>

AlphaVantageAPI::AlphaVantageAPI(const std::string& apiKey) : apiKey(apiKey) {
}

size_t AlphaVantageAPI::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

nlohmann::json AlphaVantageAPI::GetStockData(const std::string& symbol) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  // Set the callback function to handle incoming data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);  // Set the pointer to the buffer where data will be stored
        res = curl_easy_perform(curl);  // Perform the request
        curl_easy_cleanup(curl);  // Clean up the CURL handle

        if (res == CURLE_OK) {
            nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
            std::cout << "API Response: " << jsonData.dump(4) << std::endl;
            return jsonData;
        } else {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return nullptr;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
