# CPPWeather
A simple C++ library to get user local weather.
## Requires
- A [WeatherAPI key](https://www.weatherapi.com/).
- C++17
- Linux
- [cURL library](https://github.com/curl/curl)
## How to compile ?
Execute the following:
```sh
	g++ -o weather.o -c weather.cpp -std=c++17 -lcurl -Iinclude
	ar -crs libweather.a weather.o
	#Your program:
	g++ your_program.cpp -Lpath/to/lib -lweather -std=c++17 -lcurl -Iinclude
```
Don't forget to include weather.hpp.

## Examples
```cpp
#include "weather.hpp"

int main() {
	using std::cout, std::endl;
	CPPWeather api(my_key);
	weather currentWeather = api.GetWeather();
	
	cout << currentWeather.temperatureCelsius		<< '\n'; //Temperature in Celsius
	cout << currentWeather.temperatureFahrenheit	<< '\n'; //Temperature in Fahrenheit
	cout << currentWeather.windMph					<< '\n'; //Wind in Miles per Hour
	cout << currentWeather.windKph					<< '\n'; //Wind in Kilometers per Hours
	cout << currentWeather.windDegree				<< '\n'; //Wind direction (in degree)
	cout << currentWeather.windDirection			<< '\n'; //Wind direction (N, S, SW...)
	cout << currentWeather.pressureMillibars		<< '\n'; //Pressure in millibars
	cout << currentWeather.pressureInches			<< '\n'; //Pressure in inches
	cout << currentWeather.precipitationMillimeters	<< '\n'; //Precipitations in mm
	cout << currentWeather.precipitationInches 		<< '\n'; //Precipitations in inches
	cout << currentWeather.humidity					<< '\n'; //Humidity percentage
	cout << currentWeather.cloudCoverage			<< '\n'; //Cloud coverage percentage
	cout << currentWeather.isDay					<< '\n'; //Boolean, is it day or not
	cout << currentWeather.uv						<< endl; //UV index (endl flushes)
	return 0;
}
```

See CPPWeather class declaration, and weather struct declaration in [weather.hpp](weather.hpp)

## Thanks
To:
- [WeatherAPI](https://www.weatherapi.com/) for their API.
- cURL for their [library](https://github.com/curl/curl) for downloading stuff online.
- [@nlohmann](https://github.com/nlohmann/) for his [JSON library](https://github.com/nlohmann/json).