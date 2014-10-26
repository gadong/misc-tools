/*
	Author: 	Kevin, Ye
	MailBox:	kraven@foxmail.com
	Date:	26th Oct. 2014
*/


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
	
	char mSha1[64];
	char mTitle[128];
	int mType;
	bool mIsInteresting;
	bool mTitleSet;

	Commit(){
		memset(mSha1, 0, 64);
		memset(mTitle, 0, 128);
	}

	char * getTypename(){
		static char name[8];
		memset(name, 0, 8);
		if(mType & Merge) strcat(name, "M ");
		if(mType &  Revert) strcat(name, "R  ");
		if(mType & CherryPick) strcat(name, "C ");

		if(mType == 0)strcat(name, "N");
		
		return name;
	}

	void checkType(const char *sBody){
		const char *tag[] = {"Merge", "Revert", "(cherrypick "};
		int tag_type[] = {Merge, Revert, CherryPick};

		for(int i=0; i<sizeof(tag_type)/sizeof(tag_type[0]); i++){
			if(!strncmp(sBody, tag[i], strlen(tag[i]))){
				mType |= tag_type[i];
			}
		}
	}
};


#define debug_print(...)

class GitLogParser{
	list<Commit *> mCommits;
public:

	enum line_type{
		commit_line, 
		author_line,
		body_line,
		other_line
	};

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
	
	static inline bool is_interesting_author(const char *sAuthor, const char * sInteresting){
		return strstr(sAuthor, sInteresting) != NULL;
	}
	
	void parse(){
		Commit *pCommit = NULL;
		
		while(1){
			int line_type;
			const char *pContent = NULL;
			char *sLine = NULL;
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
						if(pCommit->mIsInteresting)
							mCommits.push_front(pCommit);
						else
							delete pCommit;
					} 
					debug_print("-----------------------\r\n");
					pCommit = new Commit();
					
					debug_print("\tcommit found : %8s \r\n", pContent);
					strncpy(pCommit->mSha1, pContent, 64);

					break;
				case body_line:
					if(pCommit && !pCommit->mTitleSet){
						strncpy(pCommit->mTitle, pContent, 128);
						pCommit->mTitleSet = true;
						debug_print("\ttiltle set : %s\r\n", pContent);
					}
					if(pCommit){
						debug_print("\tbody found : %s\r\n", pContent);
						pCommit->checkType(sLine);
					}
					break;
				case author_line:
					if(is_interesting_author(sLine,"@gmail.com") && pCommit){
						pCommit->mIsInteresting = true;
						debug_print("\tinteresting commit found: %s\r\n", sLine);
					}
					break;
			}
		}

		if(pCommit->mIsInteresting)
			mCommits.push_front(pCommit);
	}
	
	void dumpToFile(){
		debug_print("-----------------\r\n");
		for (list<Commit*>::iterator it =mCommits.begin(); it!=mCommits.end(); it++){
			printf("\t%-.8s\t%-64.64s\t%s\r\n", (*it)->mSha1, (*it)->mTitle, (*it)->getTypename());
			delete (*it);
		}
	}
};

int main(int argc, char *argv[])
{
	GitLogParser *parser = new GitLogParser();
	parser->parse();
	parser->dumpToFile();
	delete parser;
	
	return 0;
}
