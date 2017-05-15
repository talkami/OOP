#include "FilesListerWithSuffix.h"

//get only files we want
void FilesListerWithSuffix::refresh() {
	//calling father refresh, and then filter files
	FilesLister::refresh();
	this->filterFiles();
}

//filter files that dont end with suffix_
void FilesListerWithSuffix::filterFiles() {
	std::vector<std::string> temp = this->m_filesList; //save list of files
	this->m_filesList.clear();

	for (std::vector<std::string>::iterator itr = temp.begin(); itr != temp.end(); ++itr) {
		if (endsWith(*itr, this->m_suffix)) {
			this->m_filesList.push_back(*itr);
		}
	}
}
