#include "FilesLister.h"

//get all files
void FilesLister::refresh() {
	//directory handling
	DIR* dir;
	struct dirent * ent;

	this->m_filesList.clear();

	if ((dir = opendir(this->m_basePath.c_str())) != NULL) {
		/* read all the files and directories within directory, one-by-one */
		while ((ent = readdir(dir)) != NULL) {
			this->m_filesList.push_back(concatenateAbsolutePath(this->m_basePath, ent->d_name));
		}
		//ending dir operations
		closedir(dir);
	}
	else {
		std::cout << "Wrong path: " << this->m_basePath << std::endl;
		return;
	}
	//sort our vector
	std::sort(this->m_filesList.begin(), this->m_filesList.end());
}

//getter for files
std::vector<std::string> FilesLister::getFilesList() {
	return this->m_filesList;
}

//concatenating relative path to dir path
std::string FilesLister::concatenateAbsolutePath(const std::string& dirPath, const std::string& fileName) {
	if (dirPath.empty()) { //no dir path is given
		return fileName;
	}
	if (dirPath.back() == '/') { //dir path includes '/'
		return dirPath + fileName;
	}

	return dirPath + "/" + fileName;
}

