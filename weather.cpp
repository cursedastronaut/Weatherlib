#include "weather.hpp"

using std::string;
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


weather CPPWeather::GetWeather() {
	RefreshUserIP();
	CURL *curl;
	CURLcode res;
	std::string request = "https://api.weatherapi.com/v1/current.json?key=";
	request += token;
	request +="&q=";
	request += ip;
	request += "&aqi=no/current.json";
	const char * tempRequest = request.c_str();
	curl = curl_easy_init();
	if(!curl)
		return weather();
	curl_easy_setopt(curl, CURLOPT_URL, tempRequest);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiAnswer);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	json temp = json::parse(apiAnswer);
	weather currentWeather;
	currentWeather.temperatureCelsius =			temp["current"]["temp_c"];
	currentWeather.temperatureFahrenheit =		temp["current"]["temp_f"];
	currentWeather.windMph =					temp["current"]["wind_mph"];
	currentWeather.windKph =					temp["current"]["wind_kph"];
	currentWeather.windDegree =					temp["current"]["wind_degree"];
	currentWeather.windDirection =				temp["current"]["wind_dir"];
	currentWeather.pressureMillibars =			temp["current"]["pressure_mb"];
	currentWeather.pressureInches =				temp["current"]["pressure_in"];
	currentWeather.precipitationMillimeters =	temp["current"]["precip_mm"];
	currentWeather.precipitationInches =		temp["current"]["precip_in"];
	currentWeather.humidity =					temp["current"]["humidity"];
	currentWeather.cloudCoverage =				temp["current"]["cloud"];
	int isDayTemp =								temp["current"]["is_day"];
	currentWeather.uv =							temp["current"]["uv"];
	currentWeather.isDay = isDayTemp == 1;
	return currentWeather;

}