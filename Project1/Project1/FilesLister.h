#pragma once
#include <dirent.h>
#include <iostream>
#include <vector>
#include <algorithm>

class FilesLister{
	static string concatenateAbsolutePath(const string& dirPath, const string& fileName)
public:
	FilesLister(const string & basePath): m_basePath(basePath){this->refresh();}
	virtual void refresh();

protected:
	//data member
	vector<string> m_filesList;
	string m_basePath;

private:
	static string concatenateAbsolutePath(const string& dirPath, const string& fileName);
};

