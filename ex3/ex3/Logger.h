#pragma once
#include <string>
#include <fstream>
#include <vector>


class Logger {
	std::ofstream logFile;
public:
	Logger(){}
	~Logger();	
	void InitLog(std::string& path);
	void logMessage(const std::string& msg);
	void logResults(std::vector<std::tuple<int, int, int, int, std::string>>& results, size_t nameBuffer, int round);
};