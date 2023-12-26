		#include <iostream>
#include "weather.hpp"

using std::string, std::cout, std::endl, std::cerr;
using json = nlohmann::json;

CPPWeather::CPPWeather(const string &tokenUser) {
	token = tokenUser;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void CPPWeather::RefreshUserIP() {
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org?format=json");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ip);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		
		ip = json::parse(ip)["ip"];
	}
}

string CPPWeather::GetUserIP() {
	return ip;
}


void CPPWeather::GetWeather() {
	RefreshUserIP();
	CURL *curl;
	CURLcode res;
	std::string request = "https://api.CPPWeather.com/v1/current.json?key=";
	request += token;
	request +="&q=";
	request += ip;
	request += "&aqi=no/current.json";
	
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiAnswer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		json temp = json::parse(apiAnswer);
		temperatureCelsius =		temp["current"]["temp_c"];
		temperatureFahrenheit =		temp["current"]["temp_f"];
		windMph =					temp["current"]["wind_mph"];
		windKph =					temp["current"]["wind_kph"];
		windDegree =				temp["current"]["wind_degree"];
		windDirection =				temp["current"]["wind_dir"];
		pressureMillibars =			temp["current"]["pressure_mb"];
		pressureInches =			temp["current"]["pressure_in"];
		precipitationMillimeters =	temp["current"]["precip_mm"];
		precipitationInches =		temp["current"]["precip_in"];
		humidity =					temp["current"]["humidity"];
		cloudCoverage =				temp["current"]["cloud"];
		int isDayTemp =				temp["current"]["is_day"];
		uv =						temp["current"]["uv"];
		isDay = isDayTemp == 1;
	}

}