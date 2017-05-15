#pragma once

#include "FilesListerWithSuffix.h"

//lister for algo A attack file
class AttackFileLister : public FilesListerWithSuffix {
public:
	AttackFileLister() {}
	AttackFileLister(const std::string & basePath) : FilesListerWithSuffix(basePath, ".attack") { 
		std::sort(this->m_filesList.begin(), this->m_filesList.end()); }
};