#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <list>

using namespace std;

struct Commit{
	enum commit_type{
		Merge 		= 0x01, 
		Revert 		= 0x02, 
		CherryPick 	= 0x04,
	};

	string mSha1;
	string mTitle;
	string mAuthor;
	list<string> mBody;
	int mType;
	bool mTitleSet;

	Commit(){
	}

	char * getTypename() const{
		static char name[8];
		memset(name, 0, 8);
		if(mType & Merge) strcat(name, "M ");
		if(mType & Revert) strcat(name, "R  ");
		if(mType & CherryPick) strcat(name, "C ");

		if(mType == 0)strcat(name, "N");	//nomral

		return name;
	}

	void appendBody(const char *sBody){
		const char *tag[] = {"Merge", "Revert", "(cherrypick "};
		int tag_type[] = {Merge, Revert, CherryPick};

		for(int i=0; i<sizeof(tag_type)/sizeof(tag_type[0]); i++){
			if(!strncmp(sBody, tag[i], strlen(tag[i]))){
				mType |= tag_type[i];
			}
		}

		mBody.push_back(sBody);
	}
};


#define debug_print(...)

class GitLogParser{

	enum line_type{
		commit_line, 
		author_line,
		body_line,
		other_line
	};

	list<Commit *> mCommits;
	string mInterestingAuthor;
	string mInterestingBody;

	static char * shrink_tail(char * sLine){
		for(int i=0; i<strlen(sLine); i++){
			if(sLine[i] == '\r' || sLine[i] == '\n'){
				sLine[i] = 0;
				break;
			}
		}
		return sLine;
	}

	static int identify_line_type(const char *sLine, const char **pContent){
		const char *tag[] = {"commit ", "Author: ", "    "};
		int tag_type[] = {commit_line, author_line, body_line};

		int line_type = other_line;
		*pContent = NULL;
		for(int i=0; i<sizeof(tag_type)/sizeof(tag_type[0]); i++){
			if(!strncmp(tag[i], sLine, strlen(tag[i]))){
				*pContent = sLine + strlen(tag[i]);
				line_type = tag_type[i];
				break;
			}
		}

		return line_type;
	}
	inline bool is_interesting_commit(const Commit *pCommit){
		if(!mInterestingAuthor.empty()){
			string::size_type found = pCommit->mAuthor.find(mInterestingAuthor);
			if(found != string::npos){
				debug_print("\tinteresting commit found: %s\r\n", pCommit->mAuthor.c_str());
				return true;
			}
		}

		for (list<string>::const_iterator it =(pCommit->mBody).begin(); it!=(pCommit->mBody).end(); it++){
			string::size_type found = (*it).find(mInterestingBody);
			if(found != string::npos){
				debug_print("\tinteresting commit found: %s\r\n", (*it).c_str());
				return true;
			}
		}

		return false;
	}

public:

	~GitLogParser(){
		for (list<Commit*>::iterator it =mCommits.begin(); it!=mCommits.end(); it++)
			delete (*it);
		mCommits.clear();
	}

	void setInterestingAuthor(const char *sAuthor){
		mInterestingAuthor = sAuthor;
	}

	void setInterestingBody(const char *sBody){
		mInterestingBody = sBody;
	}

	void parse(){
		Commit *pCommit = NULL;
		
		while(1){
			int line_type;
			const char *pContent = NULL;
			char *sLine=NULL;
			size_t nLen = 0;
			int nRet = 0;

			nRet = getline(&sLine, &nLen, stdin);
			if(nRet < 0)break;

			shrink_tail(sLine);
			line_type = identify_line_type(sLine, &pContent);
			
			debug_print("parsing line: %s, \t%s\r\n", sLine, pContent);
			switch(line_type){
				case commit_line:
					if(pCommit){
						if(is_interesting_commit(pCommit))
							mCommits.push_front(pCommit);
						else
							delete pCommit;
					} 
					
					debug_print("-----------------------\r\n");				
					debug_print("\tcommit found : %8s \r\n", pContent);
					pCommit = new Commit();
					if(pCommit){
						pCommit->mSha1 = pContent;
					}
					break;
				case body_line:
					if(pCommit){
						if(!pCommit->mTitleSet){
							pCommit->mTitle = pContent;
							pCommit->mTitleSet = true;
							debug_print("\ttiltle set : %s\r\n", pContent);
						}else{
							debug_print("\tbody found : %s\r\n", pContent);
							pCommit->appendBody(pContent);
						}
					}
					break;
				case author_line:
					if(pCommit){
						pCommit->mAuthor = pContent;
					}
					break;
			}
		}

		if(is_interesting_commit(pCommit))
			mCommits.push_front(pCommit);
	}

	void dumpToFile(){
		debug_print("-----------------\r\n");
		for (list<Commit*>::iterator it =mCommits.begin(); it!=mCommits.end(); it++){
			printf("\t%-.8s\t%-64.64s\t%s\r\n", (*it)->mSha1.c_str(), (*it)->mTitle.c_str(), (*it)->getTypename());
			delete (*it);
		}
		mCommits.clear();
	}
};

int main(int argc, char *argv[])
{
	/*if(argc != 2){
		printf("%s <Insteresting Token>\r\n", argv[0]);
		return 0;
	}*/

	GitLogParser *parser = new GitLogParser();
	parser->setInterestingAuthor("@gmail.com");
	parser->parse();
	parser->dumpToFile();
	delete parser;

	return 0;
}

