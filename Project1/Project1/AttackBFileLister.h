#pragma once
//lister for algo B attack file
class AttackBFileLister : public FilesListerWithSuffix{
public:
	AttackBFileLister(const string & basePath) :FilesListerWithSuffix(basePath, ".attack-b") {}
};