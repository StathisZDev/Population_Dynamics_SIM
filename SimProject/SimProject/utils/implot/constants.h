#pragma once
#include <vector>

// ==========================================
// CONSTANTS FOR THE U_IMPLOT.CPP FILE
// ==========================================

namespace UImPlot {

    inline std::vector<double> time_vec;
    inline std::vector<double> food_vec;
    inline std::vector<double> temperature_vec;
    inline std::vector<double> populationSize_vec;

    inline int currentFood;
	inline int currentTemperature;
	inline int currentPopulationSize;

    inline constexpr double timeMin = 0.0;
    inline constexpr double timeMax = 60.0;
    inline constexpr double foodMin = 0.0;
    inline constexpr double foodMax = 3000000.0;
    inline constexpr double temperatureMin = -100.0;
    inline constexpr double temperatureMax = 100.0;
    inline constexpr double populationMin = 0;
    inline constexpr double populationMax = 50000;

	inline constexpr double windowSize = 300.0;
}
