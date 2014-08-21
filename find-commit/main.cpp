#include <iostream>

using namespace std;

class Commit{

public:
	char mSha1[64];
	char mTitle[128];

	enum commit_type{
		Merge 		= 0x01, 
		Revert 		= 0x02, 
		CherryPick 	= 0x04,
	};

	commit_type mType;

	Commit(const char *sSha1, const char *sTitle, commit_type type){
		if(sSha1)	strncpy(mSha1, sSha1, 63);
		if(sTitle)strncpy(mTitle, sTitle, 127);
		mType = type;
	}
	Commit(){}
};

class GitLogParser{
	char mLogFile[256];
public:
	GitLogParser(const char *sFile){
		strncpy(mLogFile, sFile, 255);
	}
	bool parse();
	bool dump();
};

int main(int argc, char *argv[])
{


}
