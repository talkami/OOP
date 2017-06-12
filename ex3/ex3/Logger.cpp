#include "Logger.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <map>

void Logger::InitLog(std::string& path) {
	this->logFile.open(path);
}

Logger::~Logger() {
	if (this->logFile.is_open()){
		this->logFile.close();
	}
}

void Logger::logMessage(const std::string& msg) {
	if (this->logFile.is_open()){
		time_t now = time(0);
		tm currTime;
		localtime_s(&currTime, &now);
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_mday << "/";
		this->logFile << std::setfill('0') << std::setw(2) << 1 + currTime.tm_mon << "/";
		this->logFile << 1900 + currTime.tm_year << " ";
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_hour << ":";
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_min << ":";
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_sec << " - ";
		this->logFile << msg << "\n";
	}
}	

void Logger::logResults(std::vector<std::tuple<int, int, int, int, std::string>>& results, size_t nameBuffer, int round) {
	if (this->logFile.is_open()) {
		this->logFile << std::left << "Results for round " << round << "are: ";
		this->logFile << std::setw(8) << "#" << std::setw(nameBuffer) << "Team Name";
		this->logFile << std::setw(8) << "Wins" << std::setw(8) << "Losses" << std::setw(8) << "%";
		this->logFile << std::setw(8) << "Pts For" << std::setw(8) << "Pts Against" << std::endl;

		for (int i = 0; i < results.size(); i++) {
			this->logFile << std::setw(8) << std::to_string(i + 1) + '.';
			this->logFile << std::setw(nameBuffer) << std::get<4>(results.at(i));
			this->logFile << std::setw(8) << std::get<0>(results.at(i));
			this->logFile << std::setw(8) << std::get<2>(results.at(i));
			this->logFile << std::setw(8) << std::setprecision(2) << (double)std::get<0>(results.at(i)) / round;
			this->logFile << std::setw(8) << std::get<1>(results.at(i));
			this->logFile << std::setw(8) << std::get<3>(results.at(i)) << std::endl;
		}
	}
}