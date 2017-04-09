#pragma once

class FilesLister{
public:
	FilesLister(const string & basePath): m_basePath(basePath){
		this->refresh();
	}

	//get all files
	virtual void refresh(){
		//directory handling
		DIR * dir;
		struct dirent * ent;

		this->m_filesList.clear();

		if ((dir = opendir(this->m_basePath.c_str())) != NULL){
			/* read all the files and directories within directory, one-by-one */
			while ((ent = readdir(dir)) != NULL){
				this->m_filesList.push_back(concatenateAbsolutePath(this->m_basePath, ent->d_name));
			}
			//ending dir operations
			closedir(dir);
		}
		else{
			/* could not open directory
			Remark: IN YOUR CODE, handle this error as well (e.g. throw an exception)... */
			//cout << "Error: could not open directory: " <<  this->m_basePath << endl;
			return;
		}
		//sort our vector
		std::sort(this->m_filesList.begin(), this->m_filesList.end());
	}

	//getter for files
	vector<string> getFilesList(){
		return this->m_filesList;
	}

protected:
	//data member
	vector<string> m_filesList;
	string m_basePath;

private:
	//concatenating relative path to dir path
	static string concatenateAbsolutePath(const string& dirPath, const string& fileName){
		if (dirPath.empty()){ //no dir path is given
			return fileName;
		}
		if (dirPath.back() == '/'){ //dir path includes '/'
			return dirPath + fileName;
		}

		return dirPath + "/" + fileName;
	}
};

