#pragma once

#include "FilesLister.h"

class FilesListerWithSuffix : public FilesLister {
public:
	FilesListerWithSuffix(){}
	//constructor
	FilesListerWithSuffix(const std::string& basePath, const std::string& suffix)
		: FilesLister(basePath) //invokes father constructor
		, m_suffix(suffix){
		this->filterFiles();
	}

	//get only files we want
	virtual void refresh() override; 

protected:
	//filter files that dont end with suffix_
	void filterFiles();
	
	//checks if value ends with ending
	static inline bool endsWith(std::string value, std::string ending) {
		if (ending.size() > value.size()) {
			//basic check
			return false;
		}
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin()); //std function for checking equality of strings.
	}

	//extra data member for this class
	std::string m_suffix;
};
