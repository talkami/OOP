#pragma once
#include "FilesListerWithSuffix.h"

//lister for algo B attack file
class AttackBFileLister : public FilesListerWithSuffix{
public:
	AttackBFileLister(){}
	AttackBFileLister(const std::string & basePath) :FilesListerWithSuffix(basePath, ".attack-b") {}
};