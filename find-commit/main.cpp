/*
	Author: 	Kevin, Ye
	MailBox:	kraven@foxmail.com
	Date:	26th Oct. 2014
*/

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <list>

#include <unistd.h>
#include <getopt.h>

using namespace std;

static bool gDebugEnable = false;
#define debug_print if(gDebugEnable)printf

class GitLogParser;
class Commit{
	string mSha1;
	string mTitle;
	string mAuthor;
	list<string> mBody;
	int mType;
	bool mTitleSet;

	friend class GitLogParser;
public:
	enum commit_type{
		Merge		= 0x01, 
		Revert		= 0x02, 
		CherryPick	= 0x04,
		Normal		= 0x00,
	};

	Commit(){
		mType = Normal;
		mTitleSet = false;
	}

	static int checkType(const char *sLine, int nTypeToCheck){
		const char *tag[] = {"Merge", "Revert", "(cherry picked"};
		int tag_type[] = {Merge, Revert, CherryPick};
		int type = Normal;

		for(int i=0; i<sizeof(tag_type)/sizeof(tag_type[0]); i++){
			if(!strncmp(sLine, tag[i], strlen(tag[i]))){
				type |= tag_type[i];
			}
		}
		return type & nTypeToCheck;
	}

	char * getTypename() const{
		static char name[8];
		memset(name, 0, 8);
		if(mType & Merge) strcat(name, "M ");
		if(mType & Revert) strcat(name, "R ");
		if(mType & CherryPick) strcat(name, "C");

		return name;
	}

	void setSha1(const char *sSha1){
		mSha1 = sSha1;
	}

	void setTitle(const char *sTitle){
		mType |= checkType(sTitle, Merge | Revert);
		mTitle = sTitle;
		mTitleSet = true;
	}

	void setAuthor(const char *sAuthor){
		mAuthor = sAuthor;
	}

	bool isSetTitle(){
		return mTitleSet;
	}

	void appendBody(const char *sBody){
		mType |= checkType(sBody, CherryPick);
		mBody.push_back(sBody);
	}

	void dump(){
		printf("%-.8s\t%-80.80s\t%s\r\n", mSha1.c_str(), mTitle.c_str(), getTypename());
	}
};

class GitLogParser{

	enum line_type{
		commit_line, 
		author_line,
		body_line,
		other_line
	};

	enum match_commander{
		toMatchAuthor	= 0x01, 
		toMatchType		= 0x02,
		toMatchBody		= 0x04,
		noMachRule		= 0x00,
	};

	string mInterestingAuthor;
	string mInterestingBody;
	int mInterestingType;
	int mMatchMask;
	list<Commit *> mCommits;

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
		if(mMatchMask == noMachRule)return true;

		bool bAuthorMatch=false, bBodyMatch=false, bTypeMatch=false;

		if(mMatchMask & toMatchAuthor){
			string::size_type found = pCommit->mAuthor.find(mInterestingAuthor);
			if(found != string::npos){
				debug_print("\tinteresting commit found: %s\r\n", pCommit->mAuthor.c_str());
				bAuthorMatch = true;
			}
		}

		if(mMatchMask & toMatchBody){
			for (list<string>::const_iterator it =(pCommit->mBody).begin(); it!=(pCommit->mBody).end(); it++){
				string::size_type found = (*it).find(mInterestingBody);
				if(found != string::npos){
					debug_print("\tinteresting commit found: %s\r\n", (*it).c_str());
					bBodyMatch = true;
				}
			}
		}

		if(mMatchMask & toMatchType){
			if(mInterestingType & pCommit->mType) {			
				debug_print("\tinteresting commit found: %s\r\n", pCommit->getTypename());
				bTypeMatch = true;
			}
		}

		bool bIsInteresting = true;
		if(mMatchMask){
			int toMachConds[] = {toMatchAuthor, toMatchType, toMatchBody};
			bool machResults[3];
			machResults[0] = bAuthorMatch; 
			machResults[1] = bTypeMatch; 
			machResults[2] = bBodyMatch;

			for(int i=0; i<3; i++){
				if((mMatchMask & toMachConds[i]) && !machResults[i]){
					debug_print("---toMach: %x, Result: %d----\r\n", toMachConds[i], machResults[i]);
					bIsInteresting = false;
					break;
				}
			}
		}

		return bIsInteresting;
	}

public:
	GitLogParser(){
		mInterestingType = Commit::Normal;
		mMatchMask = noMachRule;
	}

	~GitLogParser(){
		for (list<Commit*>::iterator it =mCommits.begin(); it!=mCommits.end(); it++)
			delete (*it);
		mCommits.clear();
	}

	void setInterestingAuthor(const char *sAuthor){
		mInterestingAuthor = sAuthor;
		if(!mInterestingAuthor.empty()) mMatchMask |= toMatchAuthor;
	}

	void setInterestingBody(const char *sBody){
		mInterestingBody = sBody;
		if(!mInterestingBody.empty()) mMatchMask |= toMatchBody;
	}

	void setInterestingType(int nType){
		mInterestingType = nType;
		if(mInterestingType) mMatchMask |= toMatchType;
	}

	void parse(){
		Commit *pCommit = NULL;
		bool loop = true;
		
		while(loop){
			int line_type;
			const char *pContent = NULL;
			char *sLine=NULL;
			size_t nLen = 0;
			int nRet = 0;

			nRet = getline(&sLine, &nLen, stdin);
			if(nRet < 0)break;

			shrink_tail(sLine);
			line_type = identify_line_type(sLine, &pContent);
			
			switch(line_type){
				case commit_line:
					if(pCommit){
						if(is_interesting_commit(pCommit))
							mCommits.push_front(pCommit);
						else
							delete pCommit;
					} 
					
					debug_print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\n");				
					debug_print("\tcommit found : %-.8s \r\n", pContent);
					pCommit = new Commit();
					if(pCommit){
						pCommit->setSha1(pContent);
					}else{
						loop = false;
					}
					break;
				case body_line:
					if(pCommit){
						if(!pCommit->isSetTitle()){
							pCommit->setTitle(pContent);
							debug_print("\ttiltle set : %s\r\n", pContent);
						}

						//debug_print("\tbody found : %s\r\n", pContent);
						pCommit->appendBody(pContent);
					}
					break;
				case author_line:
					if(pCommit){
						pCommit->setAuthor(pContent);
					}
					break;
			}
		}

		if(pCommit && is_interesting_commit(pCommit)){
			pCommit->dump();
			delete pCommit;
		}
	}

	void dumpToFile(){
		debug_print("---------------------------------------------------------\r\n");
		for (list<Commit*>::iterator it =mCommits.begin(); it!=mCommits.end(); it++){
			(*it)->dump();
			delete (*it);
		}
		mCommits.clear();
	}
};

static void print_usage(){
	printf("Usage:\r\n");
	printf("\t-a/--author : author infor\r\n");
	printf("\t-b/--body   : body infor\r\n");
	printf("\t-a/--type   : M C R, M(Merge), C(Cherry-Pick), R(Revert)\r\n");
	printf("\t-a/--verbose: debug info\r\n");
}

int main(int argc, char *argv[])
{
	struct option long_options[] =
	{
		{"author", 1, NULL, 'a'},
		{"body",1, NULL, 'b'},
		{"type", 1, NULL, 't'},
		{"verbose", 0, NULL, 'v'},      
		{0, 0, 0, 0},      
	};
	char* const short_options = "a:b:t:v";
	int opt;
	char *opt_arg;

	GitLogParser *parser = new GitLogParser();

	while((opt = getopt_long (argc, argv, short_options, long_options, NULL)) != -1) {
		switch(opt){
			case 'a':
				parser->setInterestingAuthor(optarg); 
				break;
			case 'b':
				parser->setInterestingBody(optarg); 
				break;
			case 't':
				/*M C R*/
				if(*optarg != 'C' && *optarg != 'R' && *optarg != 'M')
					print_usage();
				else{
					if(*optarg == 'C')parser->setInterestingType(Commit::CherryPick);
					else if(*optarg == 'R')parser->setInterestingType(Commit::Revert);
					else parser->setInterestingType(Commit::Merge);
				}
				break;
			case 'v':
				gDebugEnable = true;
				break;
			case ':':
			case '?':
				print_usage();
				return 0;
			default:
				break;
		}
	}

	parser->parse();
	parser->dumpToFile();
	delete parser;

	return 0;
}

