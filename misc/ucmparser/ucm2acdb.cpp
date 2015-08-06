#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define LINE_SIZE		1024
#define MAX_NAME_L		64
#define MAX_UCM_DEV_N	256

#define TOKEN_IDENTIFY(str, token) (!strncmp(str, #token, strlen(#token)))

struct UCMDeviceNode{
	char sDevName[MAX_NAME_L];
	int nACDBID;
public:
	void dump(void){
		cout<<sDevName<<'\t'<<nACDBID<< endl;
	}
};

class UCMParser{
	enum parser_state{
		Parser_Init,
		SectionDevice_Start, 
		NameIdentified,
		ACDBIDIdentified,
		SectionDevice_End
	};

public:
	UCMParser(char * sUCMFileName);
	int run();
	void dump();
private:
	bool is_ucm_sep(char ch);
	char *shrink_ucm_line(char *line);
	int parse_ucm_file(char *line);

	UCMDeviceNode *mDevList[MAX_UCM_DEV_N];
	int mCurDevIndex;
	char mUCMFileName[256];
	parser_state mState;
};

UCMParser::UCMParser(char * sUCMFileName)
{
	strcpy(mUCMFileName, sUCMFileName);
	mCurDevIndex = -1;
	mState = Parser_Init;
}

bool UCMParser::is_ucm_sep(char ch)
{
	char seps[] = { '\r', '\n', '\'', '\t', '\"'};
	for(int i=0; i<sizeof(seps); i++)
		if(ch == seps[i])return true;
	return false;
}

char* UCMParser::shrink_ucm_line(char *line)
{
	char *p, *pw;
	p = pw = line;
	bool valid_space = false;

	while(*p){
		if(*p == ' '){
			if(valid_space){ // space in line
				*pw++ = *p++;
				valid_space = false;
			}else{
				p++;
			}
		}else if (is_ucm_sep(*p)){
			p++;
		}else{
			*pw++ = *p++;
			valid_space = true;
		}
	}
	*pw = 0;
	return line;
}

int UCMParser::parse_ucm_file(char *line)
{
	char buf[LINE_SIZE] = {0};
	switch(mState){
		case Parser_Init:
		case SectionDevice_End:
			if(TOKEN_IDENTIFY(line, SectionDevice)){
				mState = SectionDevice_Start;
				mCurDevIndex ++;
				mDevList[mCurDevIndex] = new UCMDeviceNode();
			}
			/*TODO: add error process here*/
			break;
		case SectionDevice_Start:
			if(TOKEN_IDENTIFY(line, Name)){
				char * pname = strstr(line, "Name ");
				sprintf(mDevList[mCurDevIndex]->sDevName, pname + 5);
				mState = NameIdentified;
			}	
			/*TODO: add error process here*/
			break;
		case NameIdentified:
			if(TOKEN_IDENTIFY(line, ACDBID)){
				int nACDBID, nTmp;
				sscanf(line, "ACDBID%d:%d",&nACDBID, &nTmp);
				mDevList[mCurDevIndex]->nACDBID = nACDBID;
				mState = ACDBIDIdentified;
			}
			/*TODO: add error process here*/
			break;
		case ACDBIDIdentified:
			if(TOKEN_IDENTIFY(line, EndSection)){
				mState = SectionDevice_End;
			}
			/*TODO: add error process here*/
			break;
	}

	return mState;
}

int UCMParser::run()
{	
	FILE *f_input = NULL;
	f_input = fopen(mUCMFileName, "r");
	if(!f_input){
		cout <<"failed to open file" << mUCMFileName << endl;
		return -1;
	}

	size_t	len;
	char *line = NULL;

	while(getline(&line, &len, f_input) != -1){
		shrink_ucm_line(line);
		parse_ucm_file(line); 
	}

	fclose(f_input);
	return 0;

}

void UCMParser::dump(){
	for(int i =0; i<=mCurDevIndex; i++){
		mDevList[i]->dump();
	}
}

int main(int argc, char*argv[])
{
	UCMParser * parser = new UCMParser(argv[1]);
	parser->run();
	parser->dump();
	return 0;
}
