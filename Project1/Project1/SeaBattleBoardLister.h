#pragma once
//lister for sea battle boards
class SeaBattleBoardLister : public FilesListerWithSuffix{
public:
	SeaBattleBoardLister(const string & basePath):FilesListerWithSuffix(basePath, ".sboard"){}
};