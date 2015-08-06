#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE		256
#define FIELD_SIZE		256

enum parser_state{
	Parser_Init,
	SectionDevice_Start, 
	NameIdentified,
	EnableSequence_Start,
	EnableSequence_End,
	SectionDevice_End
};

#define error_printf 	printf
#define warn_printf 	printf
#define info_printf 	printf

#define dump_printf(buf, fmt...) {\
		sprintf(buf,fmt);		\
		info_printf(fmt);			\
	}

#define TOKEN_IDENTIFY(str, token) (!strncmp(str, #token, strlen(#token)))

bool is_ucm_sep(char ch)
{
	char seps[] = { '\r', '\n', '\'', '\t', '\"'};
	for(int i=0; i<sizeof(seps); i++)
		if(ch == seps[i])return true;
	return false;
}

char *shrink_ucm_line(char *line)
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

bool convert_ucm_line(char *ucm_line, FILE *flp){
	char *pname = NULL;
	char *pvalue = NULL;
	char *psubvalue, *pval;
	int type;
	int i = 0;
	static char buf[LINE_SIZE] = {0};

	pval = ucm_line;
	while(psubvalue = strsep(&pval, ":")){
		if(i==0)pname = psubvalue;
		else if(i==1) type = atoi(psubvalue);
		else if(i==2) pvalue = psubvalue;

		i++;
	}

	if(i!=3){
		//printf("invalid ucm line: %s\r\n", ucm_line);
		return false;
	}

	switch(type){
		case 0:
		case 1:
			dump_printf(buf, "        <ctl name=\"%s\" value=\"%s\" />\r\n", pname, pvalue);
			if(flp)fwrite(buf, sizeof(char), strlen(buf), flp);
			break;
		case 2:
			pval = pvalue;
			i = 0;
			while(psubvalue = strsep(&pval, " ")){
				dump_printf(buf, "        <ctl name=\"%s\" id=\"%d\" value=\"%s\" />\r\n", pname, i, psubvalue);
				if(flp)fwrite(buf, sizeof(char), strlen(buf), flp);
				i++;
			}
			break;
		default:
			warn_printf("invalid ucm dev type %d\r\n", type);
			return false;
	}

	return true;
}



static int parse_ucm_file(char *line, int &state, FILE** p_flp)
{
	char buf[LINE_SIZE] = {0};
	switch(state){
		case Parser_Init:
		case SectionDevice_End:
			if(TOKEN_IDENTIFY(line, SectionDevice))
				state = SectionDevice_Start;
			/*TODO: add error process here*/
			break;
		case SectionDevice_Start:
			if(TOKEN_IDENTIFY(line, Name)){
				char * pname = strstr(line, "Name ");
				sprintf(buf, "%s.txt", pname+5);
				*p_flp = fopen(buf, "w+");
				dump_printf(buf, "    <path name=\"%s\">\r\n", pname + 5);
				state = NameIdentified;
				if(*p_flp){
					fwrite(buf, sizeof(char), strlen(buf), *p_flp);
				}
			}	
			/*TODO: add error process here*/
			break;
		case NameIdentified:
			if(TOKEN_IDENTIFY(line,EnableSequence))
				state = EnableSequence_Start;
			/*TODO: add error process here*/
			break;
		case EnableSequence_Start:
			if(TOKEN_IDENTIFY(line, EndSequence))
				state = EnableSequence_End;
			else
				convert_ucm_line(line, *p_flp);
			break;
		case EnableSequence_End:
			if(TOKEN_IDENTIFY(line, EndSection)){
				state = SectionDevice_End;
				dump_printf(buf, "    </path>\r\n");
				
				if(*p_flp){
					fwrite(buf, sizeof(char), strlen(buf), *p_flp);
					fclose(*p_flp);
					*p_flp = NULL;
				}
			}
			/*TODO: add error process here*/
			break;
	}

	return state;
}

int main(int argc, char*argv[])
{
	FILE * f_input;
	FILE * f_output = NULL;
	f_input = fopen(argv[1], "r");
	if(!f_input){
		error_printf("failed to open file %s\r\n", argv[1]);
		return -1;
	}

	size_t	len;
	char *line = NULL;
	int state = Parser_Init;

	while(getline(&line, &len, f_input) != -1){
		shrink_ucm_line(line);
		parse_ucm_file(line, state, &f_output);
	}

	fclose(f_input);

	return 0;
}
