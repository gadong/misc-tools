#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <getopt.h>

#include "htmlparser.h"

static bool gShowDebugInfor = false;

#define errprint(x...)		printf("[Error]" x)
#define warnprint(x...)		printf("[Warn]" x)
#define infoprint(x...)		if(gShowDebugInfor)printf("[Info]" x)

#define html_strchr			strchr
#define html_strcmp			strcmp
#define html_strcpy			strcpy
#define html_sprintf		sprintf
#define html_strlen			strlen
#define html_strncmp		strncmp
#define html_strstr			strstr
#define html_memset			memset

const HTMLChar * HTMLTag::sSupportedTags[] = {
	"a", "aside",
	"body",
	"div",
	"figure", "footer",
	"h1", "h2", "h3", "head", "html",
	"img", "input",
	"label", "link", "li",
	"main", "meta",
	"nav",
	"p",
	"small","span",
	"title",
	"ul",
	"!--",
	NULL
	};

const HTMLChar* HTMLTag::sGlobalAttributes[] = {
	"class",
	"data-action-id",
	"id",
	"tabindex",
	NULL
	};

const HTMLChar* TAG_A::A_specificAttributes[] = {
	"href", "target", NULL
	};
const HTMLChar* TAG_BODY::BODY_specificAttributes[] = {
	"screen_capture_injected", NULL
	};
const HTMLChar* TAG_DIV::DIV_specificAttributes[] = {
	"style", NULL
	};
const HTMLChar* TAG_HTML::HTML_specificAttributes[] = {
	"lang", NULL
	};
const HTMLChar* TAG_IMG::IMG_specificAttributes[] = {
	"alt", "height", "src", "width", NULL
	};
const HTMLChar* TAG_INPUT::INPUT_specificAttributes[] = {
	"aria-haspopup", "type", NULL
	};
const HTMLChar* TAG_LABEL::LABEL_specificAttributes[] = {
	"for", NULL
	};
const HTMLChar* TAG_LINK::LINK_specificAttributes[] = {
	"href", "sizes", "rel", NULL
	};
const HTMLChar* TAG_MAIN::MAIN_specificAttributes[] = {
	"role", NULL
	};
const HTMLChar* TAG_META::META_specificAttributes[] = {
	"name", "content", "http-equiv", NULL
	};

HTMLTag * HTMLTag::makeTagByName(const HTMLChar * sTagName){
	int tagIdx = IDX_MAX;
	const HTMLChar * pNameStorage = NULL; //point to the static const area
	infoprint("try to make Tag by Name: %s\r\n", sTagName);
	for(int idx=0; sSupportedTags[idx]; idx++){
		if(!html_strcmp(sTagName, sSupportedTags[idx])){
			tagIdx = idx;
			pNameStorage = sSupportedTags[idx];
			infoprint("----identify tag: %s\r\n", sTagName);
			break;
		}
	}

	HTMLTag * pTag = NULL;
	switch(tagIdx){
		case IDX_A: pTag = new TAG_A(); break;
		case IDX_ASIDE: pTag = new HTMLTag(pNameStorage); break;
		case IDX_BODY: pTag = new TAG_BODY(); break;
		case IDX_DIV: pTag = new TAG_DIV(); break;
		case IDX_FIGURE: pTag = new HTMLTag(pNameStorage); break;
		case IDX_FOOTER: pTag = new HTMLTag(pNameStorage); break;
		case IDX_H1: pTag = new HTMLTag(pNameStorage); break;
		case IDX_H2: pTag = new HTMLTag(pNameStorage); break;
		case IDX_H3: pTag = new HTMLTag(pNameStorage); break;
		case IDX_HEAD: pTag = new HTMLTag(pNameStorage); break;
		case IDX_HTML: pTag = new TAG_HTML(); break;
		case IDX_IMG: pTag = new TAG_IMG(); break;
		case IDX_INPUT: pTag = new TAG_INPUT(); break;
		case IDX_LABEL: pTag = new TAG_LABEL(); break;
		case IDX_LI: pTag = new HTMLTag(pNameStorage); break;
		case IDX_LINK: pTag = new TAG_LINK(); break;
		case IDX_MAIN: pTag = new TAG_MAIN(); break;
		case IDX_META: pTag = new TAG_META(); break;
		case IDX_NAV: pTag = new HTMLTag(pNameStorage); break;
		case IDX_P: pTag = new HTMLTag(pNameStorage); break;
		case IDX_SMALL: pTag = new HTMLTag(pNameStorage); break;
		case IDX_SPAN: pTag = new HTMLTag(pNameStorage); break;
		case IDX_TITLE: pTag = new HTMLTag(pNameStorage); break;
		case IDX_UL: pTag = new HTMLTag(pNameStorage); break;
		case IDX_COMMENT: pTag = new HTMLTag(pNameStorage, CommentTag); break;
		default:
			errprint("Error tag idx : %d for %s\r\n" , tagIdx, pNameStorage);
			break;
	}

	return pTag;
}

unsigned HTMLTag::sizeOfSource()
{
	unsigned length = 0;

	//length for tag attributes
	for (map<const HTMLChar *,const HTMLChar *>::iterator it=mAttributes.begin();
		it!=mAttributes.end();
		++it){
		length += html_strlen(it->first);
		length += html_strlen(it->second);
		length += 4; // ="" and a prefix-blank
	}

	//lenght of text
	if(mText)length += html_strlen(mText);

	//length for tag starting/closing tag
	if(mFlag & CommentTag) {
		length += 7; //<!--, -->
	}else if(mFlag & SingleLineTag){
		length += (html_strlen(mName) + 5 + 4*mDepth); //<name/>\r\n, and count of prefix-spaces 
	}else{
		length += (2*html_strlen(mName) + 8*mDepth + 11); //<name>\r\n</name>\r\n, and prefix-spaces
	}

	//length of nested tags
	for (list<HTMLTag *>::iterator it=mNestedTags.begin(); it != mNestedTags.end(); ++it){
		length += (*it)->sizeOfSource();
	}

	return length;
}

HTMLChar * HTMLTag::toSource(HTMLChar * saveTo, unsigned & size){
	HTMLChar * pSave = saveTo;
	HTMLChar * pStart;

	if(!pSave){
		if(!mSource) mSource=new HTMLChar[sizeOfSource()];
		pSave = mSource;
	}
	pStart = pSave;

	//starting-tag 1:
	if(mDepth){
		HTMLChar pPrefix[128]={0};
		html_memset(pPrefix, ' ', (mDepth*4<128)?mDepth*4:127);
		pSave += html_sprintf(pSave, "%s", pPrefix);
	}
	pSave += html_sprintf(pSave, "<%s", mName);

	//format attributes
	for (map<const HTMLChar *,const HTMLChar *>::iterator it=mAttributes.begin();
		it!=mAttributes.end();
		++it){
		pSave += html_sprintf(pSave, " %s=\"%s\"", it->first, it->second);
	}

	//starting-tag 2 or closing-tag
	if(mFlag & CommentTag){
		pSave += html_sprintf(pSave, "%s-->\r\n", mText);
	}else if(mFlag & SingleLineTag){
		pSave += html_sprintf(pSave, "/>\r\n");
	}else{
		//starting-tag 2:
		pSave += html_sprintf(pSave, ">");
		if(!mNestedTags.empty())pSave += html_sprintf(pSave, "\r\n");

		//nested tags
		unsigned size;
		 for (list<HTMLTag *>::iterator it=mNestedTags.begin(); it != mNestedTags.end(); ++it){
			(*it)->toSource(pSave, size);
			pSave = (char*)pSave+ size;
		}

		// Text
		if (mText){
			pSave += html_sprintf(pSave, "%s\r\n", mText);
		}

		if(mDepth){
			HTMLChar pPrefix[128]={0};
			html_memset(pPrefix, ' ', (mDepth*4<128)?mDepth*4:127);
			pSave += html_sprintf(pSave, "%s", pPrefix);
		}

		//closing-tag
		pSave += html_sprintf(pSave, "</%s>\r\n", mName);
	}
	size = (pSave-pStart)*sizeof(HTMLChar);

	return pStart;
}

void HTMLTag::updateDepth(){
	mDepth = mParent->mDepth + 1;
	for (list<HTMLTag *>::iterator it=mNestedTags.begin(); it != mNestedTags.end(); ++it){
		HTMLTag * pTag =*it;
		pTag->updateDepth();
	}
}

void HTMLTag::setText(const HTMLChar * sText){
	mText = new HTMLChar[html_strlen(sText)];
	html_strcpy(mText, sText);
}

HTMLTag::HTMLTag(const HTMLChar * sName, unsigned flag){
	mName = sName;
	mFlag = flag;
	mText = NULL;
	mSource = NULL;
	mDepth = 0;
}

HTMLTag::~HTMLTag(){
	for (list<HTMLTag *>::iterator it=mNestedTags.begin(); it != mNestedTags.end(); ++it){
		HTMLTag * pTag =*it;
		delete pTag;
	}
	mNestedTags.clear();

	for (map<const HTMLChar *,const HTMLChar *>::iterator it=mAttributes.begin();
		it!=mAttributes.end();
		++it){
		const HTMLChar * pVal = it->second;
		delete []pVal;
	}
	mAttributes.clear();

	if(mText)delete []mText;
	if(mSource)delete []mSource;
}

bool HTMLTag::addAttribute(const HTMLChar * sName,const HTMLChar * sValue){
	bool isValid = false;
	bool isGlobal = false;
	const HTMLChar * pName;

	for(int i=0; sGlobalAttributes[i]; i++){
		if(!html_strcmp(sName, sGlobalAttributes[i])){
			isValid =  true;
			pName = sGlobalAttributes[i];
			break;
		}
	}

	if(!isValid){
		const HTMLChar **pSpecificAttributes = getSpecificAttributes();
		if(pSpecificAttributes){
			for(int i=0; pSpecificAttributes[i]; i++){
				if(!html_strcmp(sName, pSpecificAttributes[i])){
					isValid = true;
					pName = pSpecificAttributes[i];
					break;
				}
			}
		}
	}

	if(isValid){
		// should be deleted in destructor
		HTMLChar * pValue = new HTMLChar[html_strlen(sValue)+1];
		html_strcpy(pValue, sValue);
		map<const HTMLChar *, const HTMLChar *>::iterator it = mAttributes.begin();
		mAttributes.insert (it, pair<const HTMLChar *, const HTMLChar *>(pName,pValue));
	}

	return isValid;
}

void HTMLTag::addNestedTag(HTMLTag * pNestedTag){
	if(pNestedTag){
		pNestedTag->setParent(this);
		mNestedTags.push_back(pNestedTag);
	}
}

HTMLChar * HTMLParser::skipBlank(HTMLChar * str){
	while(*str == ' ' || *str == '\r' || *str == '\n') str++;
	return str;
}

HTMLTag * HTMLParser::probeHTMLTag(HTMLChar *sSource, HTMLChar **psSave){
	HTMLTag *pTag = NULL;
	HTMLChar *pStart = skipBlank(sSource);
	HTMLChar *pTmp, *pTmp1, *pTmp2;

	// check whether it's a valid starting-tag or not, and create a new Tag if it's valid
	if(!html_strncmp("<!--", pStart, 4)){
		pTag = HTMLTag::makeTagByName("!--");
		pTmp = pStart+4;
	}else if(*pStart == '<'){
		pTmp1 = html_strchr(pStart, ' ');
		pTmp2 = html_strchr(pStart, '>');
		if(pTmp1 || pTmp2){
			pTmp = (pTmp1<pTmp2 && pTmp1)? pTmp1:pTmp2;
			*pTmp = 0;
			pTag = HTMLTag::makeTagByName(pStart+1);
			*pTmp = (pTmp == pTmp1)?' ':'>';
		}else{
			errprint("can't identify tagName");
			goto err1;
		}
	}else{
		infoprint("it's not a valid staring-tag: \r\n\t%s\r\n", pStart);
		goto err1;
	}

	if(!pTag) {
		errprint("can't make a tag by name : \r\n", pStart+1);
		goto err1;
	}

	pStart = pTmp;

	// to probe the attribues for the tag
	if(!(pTag->flag() & HTMLTag::CommentTag)){
		while(*pStart && *pStart!='>'){

			HTMLChar *pNameStart=NULL, *pValStart=NULL, *pValEnd=NULL;
			pNameStart = skipBlank(pStart);
			pValStart = html_strstr(pNameStart, "=\"");
			if(pValStart)pValEnd = html_strchr(pValStart+2, '\"');

			if(pNameStart && pValStart && pValEnd && pValStart > pNameStart){
				*pValStart = 0;
				*pValEnd = 0;
				pValStart += 2; // skip ="
				if(!pTag->addAttribute(pNameStart, pValStart)){
					errprint("invalid tag-attr: %s=\"%s\"\r\n", pNameStart, pValStart);
					goto err2;
				}

				pStart = pValEnd+1; //move to next
			}
		}
	}

	// to do further check
	//		1, try to close the tag if it's a single-line tag
	//		2, a more complicate case, which includes Text or nested-tags, or closig-tag
	pStart = skipBlank(pStart);
	if(pTag->flag() & HTMLTag::SingleLineTag){
		if(*pStart == '>' || !html_strncmp("/>", pStart, 2)){
			if(*pStart == '>') *psSave = pStart + 1;
			else *psSave = pStart + 2;
			//*psSave = pStart + (*pStart == '>')?1:2;
			infoprint("single-line tag was successfully closed\r\n");
		}else{
			errprint("didn't find a closing-brace\r\n");
			goto err2;
		}
	}else if(pTag->flag() & HTMLTag::CommentTag){
		pTmp = html_strstr(pStart, "-->"); //from the pos after <!--
		if(pTmp){
			*pTmp = 0;
			if(pTmp > pStart){
				pTag->setText(pStart);
			}else{
				warnprint("didn't find any comment\r\n");
			}
			*psSave = pTmp + 3;
			infoprint("comment tag was succesfully closed\r\n");
		}else{
			errprint("didn't fid the closing-tag --> for comment tag\r\n");
			goto err2;
		}
	}else{
		//came to the closing-brace
		pTmp = html_strchr(pStart, '>');
		if(!pTmp){
			errprint("can't find the closing-brace for the tag: %s\r\n", pTag->name());
			goto err2;
		}
		pStart += 1;

		while(*pStart){
			pStart = skipBlank(pStart);
			if (!html_strncmp(pStart, "</", 2)){ // it came to the closig-tag
				pTmp = html_strchr(pStart, '>');
				if(pTmp){
					*pTmp = 0;
				}else{
					errprint("didn't find a closing-brace\r\n");
					goto err2;
				}

				if(html_strcmp(pStart+2, pTag->name())){
					errprint("closing-tag not match\r\n");
					goto err2;
				}else{
					infoprint("complicated tag was successfully closed: %s\r\n", pTag->name());
					*psSave = pTmp + 1;
					break;//exit the loop
				}
			}else if(*pStart == '<'){ //a nested tag founded
				HTMLTag * pSon= probeHTMLTag(pStart, &pTmp);
				if(pSon){
					pTag->addNestedTag(pSon);
					pStart = pTmp;
				}else{
					errprint("fail to extend a nested-tag\r\n");
					goto err2;
				}
			}else if(pTag->flag() & HTMLTag::TextTag){ //text for tag
				pTmp = html_strchr(pStart, '<');
				if(pTmp && pTag){
					*pTmp = 0;
					pTag->setText(pStart);
					*pTmp = '<';
					pStart = pTmp;
				}else{
					errprint("naked text found\r\n");
					goto err2;
				}
			}else{
				errprint("text part found for no-text tag\r\n");
				goto err2;
			}
		}
	}

okay:
	return pTag;

//error handling
err2:
	HTMLTag::releaseTag(pTag);
err1:
	return NULL;
}

bool HTMLParser::loadHTML(const char * fromFile){
	ifstream is (fromFile, ifstream::binary);

	if (is) {
		// get length of file:
		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		mBuffer = new char [length+1];
		is.read (mBuffer,length);
		is.close();

		return true;
	}
	return false;
}

bool HTMLParser::saveAs(const char * toFile){
	ofstream of (toFile,ofstream::binary);

	if(of){
		unsigned size;
		HTMLChar * pStart;
		 for (list<HTMLTag *>::iterator it=mTopLevelTags.begin(); it != mTopLevelTags.end(); ++it){
			 pStart = (*it)->toSource(NULL, size);
			 of.write(pStart, size);
		 }

		 of.close();
	}

	return true;
}

bool HTMLParser::parse()
{
	HTMLChar * pStart;
	HTMLTag * pTag;

	pStart = skipBlank(mBuffer);
	pStart = html_strstr(pStart, "<!DOCTYPE html>");
	if(pStart){
		pStart += 15;
	}else{
		pStart=mBuffer;
		warnprint("didn't find doc-type declaration\r\n");
	}
	while(*pStart){
		pTag = probeHTMLTag(pStart, &pStart);
		if(pTag) {
			mTopLevelTags.push_back(pTag);
		}else {
			break;
		}
	}

	return (*pStart == 0);
}

static void print_usage(const char * sCmd){
	printf("\tUsage:%s -i <in-html> -o <save to html>\r\n", sCmd);
	printf("\t\t-i/--input: load from HTML\r\n");
	printf("\t\t-o/--output: save to HTML\r\n");
	printf("\t\t-v/--verbose: show debug infor\r\n");
}

int main(int argc, char * argv[])
{
	struct option long_options[] =
	{
		{"input", 1, NULL, 'i'},
		{"output",1, NULL, 'o'},
		{"verbose",1, NULL, 'v'},
		{0, 0, 0, 0},
	};
	const char*  short_options = "i:o:v";

	int opt;

	char * infile=NULL, *outfile=NULL;
	while((opt = getopt_long (argc, argv, short_options, long_options, NULL)) != -1) {
		switch(opt){
			case 'i':
				infile = optarg;
				break;
			case 'o':
				outfile = optarg;
				break;
			case 'v':
				gShowDebugInfor= true;
				break;
			case ':':
			case '?':
				print_usage(argv[0]);
				return 0;
			default:
				break;
		}
	}

	if(infile){
		HTMLParser * parser = new HTMLParser();
		if(parser){
			parser->loadHTML(infile);
			parser->parse();
			if(outfile)parser->saveAs(outfile);
			delete parser;
		}
	}else{
		print_usage(argv[0]);
	}
	return 0;
}
