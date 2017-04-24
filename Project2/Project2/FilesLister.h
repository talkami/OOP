#pragma once

#include "dirent.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class FilesLister{
	static std::string concatenateAbsolutePath(const std::string& dirPath, const std::string& fileName);
public:
	FilesLister(){}
	FilesLister(const std::string & basePath): m_basePath(basePath){this->refresh();}
	std::vector<std::string> getFilesList();
	virtual void refresh();

protected:
	//data member
	std::vector<std::string> m_filesList;
	std::string m_basePath;

};

