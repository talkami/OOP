#pragma once

#include "FilesListerWithSuffix.h"

//lister for algo A attack file
class AttackAFileLister : public FilesListerWithSuffix {
public:
	AttackAFileLister() {}
	AttackAFileLister(const std::string & basePath) :FilesListerWithSuffix(basePath, ".attack-a") {}
};