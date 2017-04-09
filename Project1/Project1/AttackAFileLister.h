#pragma once
//lister for algo A attack file
class AttackAFileLister : public FilesListerWithSuffix{
public:
	AttackAFileLister(const string & basePath) :FilesListerWithSuffix(basePath, ".attack-a") {}
};