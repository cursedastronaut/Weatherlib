#pragma once
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

struct weather {
	using string = std::string;
	double	temperatureCelsius;
	float	temperatureFahrenheit;
	float	windMph;
	float	windKph;
	int		windDegree;
	string	windDirection;
	float	pressureMillibars;
	float	pressureInches;
	float	precipitationMillimeters;
	float	precipitationInches;
	int		humidity;
	int		cloudCoverage;
	bool	isDay;
	int		uv;
};

class CPPWeather {
	using string = std::string;
	public:
		CPPWeather(const string &);
		void RefreshUserIP();
		void Refresh();
		weather GetWeather();
		string GetUserIP();

	private:
		string token;
		std::string ip = "";
		string apiAnswer;


		static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
};