#pragma once
class FilesListerWithSuffix : public FilesLister{
public:
	//constructor
	FilesListerWithSuffix(const string& basePath, const string& suffix)
		: FilesLister(basePath) //invokes father constructor
		, m_suffix(suffix){
		this->filterFiles();
	}

	//get only files we want
	virtual void refresh() override{
		//calling father refresh, and then filter files
		FilesLister::refresh();
		this->filterFiles();
	}

protected:
	//filter files that dont end with suffix_
	void filterFiles(){
		vector<string> temp = this->m_filesList; //save list of files
		this->m_filesList.clear();

		for (vector<string>::iterator itr = temp.begin(); itr != temp.end(); ++itr){
			if (endsWith(*itr, this->m_suffix)){
				this->m_filesList.push_back(*itr);
			}
		}
	}

	//checks if value ends with ending
	static inline bool endsWith(std::string value, std::string ending){
		if (ending.size() > value.size()){
			//basic check
			return false;
		}
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin()); //std function for checking equality of strings.
	}

	//extra data member for this class
	string m_suffix;
};
