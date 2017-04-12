#pragma once
#include "FilesListerWithSuffix.h"

//lister for sea battle boards
class SeaBattleBoardLister : public FilesListerWithSuffix{
public:
	SeaBattleBoardLister(const std::string & basePath):FilesListerWithSuffix(basePath, ".sboard"){}
};