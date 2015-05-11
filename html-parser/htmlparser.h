#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <list>
#include <map>

using namespace std;

typedef char 				HTMLChar;

class BitMap{
};

class HTMLTag{
public:
	enum TagFlag{
		Normal			= 0, //<tag-name ...> ...</tag-name>
		VisibleTag		= 0x01U<<0, // for tags would invovle a UI drawing
		SingleLineTag	= 0x01U<<1, // <input .../>
		CommentTag		= 0x01U<<2, // for comment tag, <!--...-->
		TextTag			= 0x01U<<3, // <tag-name...>...Text...</tag-name>
	};

	unsigned flag() const {return mFlag;}
	unsigned depth() const {return mDepth;}
	const HTMLChar * name() const {return mName;}
	virtual void drawOn(BitMap & bitmap){}
	unsigned sizeOfSource();
	HTMLChar * toSource(HTMLChar * saveTo, unsigned & size);
	void addNestedTag(HTMLTag *pNestedTag);
	bool addAttribute(const HTMLChar *sName, const HTMLChar *sValue );
	void setParent(HTMLTag * parent) {mParent = parent; updateDepth();}
	void setText(const HTMLChar * sText);

	static HTMLTag * makeTagByName(const HTMLChar * sTagName);
	static void releaseTag(HTMLTag * pTag){delete pTag;}

protected:
	enum TagIndex{
		IDX_A, IDX_ASIDE,
		IDX_BODY,
		IDX_DIV,
		IDX_FIGURE, IDX_FOOTER,
		IDX_H1, IDX_H2, IDX_H3, IDX_HEAD, IDX_HTML,
		IDX_IMG, IDX_INPUT,
		IDX_LABEL, IDX_LINK, IDX_LI,
		IDX_MAIN, IDX_META,
		IDX_NAV,
		IDX_P,
		IDX_SMALL,IDX_SPAN,
		IDX_TITLE,
		IDX_UL,
		IDX_COMMENT,
		IDX_MAX};

	static const HTMLChar * sSupportedTags[];
	static const HTMLChar * sGlobalAttributes[];

	HTMLTag *mParent;
	const HTMLChar *mName;
	HTMLChar *mText;
	HTMLChar *mSource;
	short mDepth;
	unsigned mFlag;

	map<const HTMLChar *, const HTMLChar *> mAttributes;
	list<HTMLTag *> mNestedTags;

	HTMLTag(const HTMLChar * sName, unsigned flag = TextTag);
	virtual ~HTMLTag();

	void updateDepth();
	virtual const HTMLChar ** getSpecificAttributes(){
		return NULL;
	}
};

class TAG_A: public HTMLTag{
	static const HTMLChar *A_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return A_specificAttributes;
	}
public:
	TAG_A(): HTMLTag(sSupportedTags[IDX_A], TextTag){}
	virtual ~TAG_A(){}
};

class TAG_BODY: public HTMLTag{
	static const HTMLChar *BODY_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return BODY_specificAttributes;
	}
public:
	TAG_BODY(): HTMLTag(sSupportedTags[IDX_BODY]){}
	virtual ~TAG_BODY(){};
};

class TAG_DIV: public HTMLTag{
	static const HTMLChar *DIV_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return DIV_specificAttributes;
	}
public:
	TAG_DIV(): HTMLTag(sSupportedTags[IDX_DIV]){}
	virtual ~TAG_DIV(){};
};

class TAG_HTML: public HTMLTag{
protected:
	static const HTMLChar *HTML_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return HTML_specificAttributes;
	}
public:
	TAG_HTML(): HTMLTag(sSupportedTags[IDX_HTML]){}
	virtual ~TAG_HTML(){};
};

class TAG_IMG: public HTMLTag{
	static const HTMLChar *IMG_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return IMG_specificAttributes;
	}
public:
	TAG_IMG(): HTMLTag(sSupportedTags[IDX_IMG], SingleLineTag){}
	virtual ~TAG_IMG(){};
};

class TAG_INPUT: public HTMLTag{
	static const HTMLChar *INPUT_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return INPUT_specificAttributes;
	}
public:
	TAG_INPUT(): HTMLTag(sSupportedTags[IDX_INPUT], SingleLineTag){}
	virtual ~TAG_INPUT(){};
};

class TAG_LABEL: public HTMLTag{
	static const HTMLChar *LABEL_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return LABEL_specificAttributes;
	}
public:
	TAG_LABEL(): HTMLTag(sSupportedTags[IDX_LABEL]){}
	virtual ~TAG_LABEL(){};
};

class TAG_LINK: public HTMLTag{
	static const HTMLChar *LINK_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return LINK_specificAttributes;
	}
public:
	TAG_LINK(): HTMLTag(sSupportedTags[IDX_LINK], SingleLineTag){}
	virtual ~TAG_LINK(){};
};

class TAG_MAIN: public HTMLTag{
	static const HTMLChar *MAIN_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return MAIN_specificAttributes;
	}
public:
	TAG_MAIN(): HTMLTag(sSupportedTags[IDX_MAIN]){}
	virtual ~TAG_MAIN(){};
};

class TAG_META: public HTMLTag{
	static const HTMLChar *META_specificAttributes[];
	virtual const HTMLChar ** getSpecificAttributes(){
		return META_specificAttributes;
	}
public:
	TAG_META(): HTMLTag(sSupportedTags[IDX_META], SingleLineTag){}
	virtual ~TAG_META(){};
};

class HTMLParser{
	char * mBuffer;
	list<HTMLTag *> mTopLevelTags;

	HTMLChar * skipBlank(HTMLChar *str);
	HTMLTag * probeHTMLTag(HTMLChar *sSource, HTMLChar **psSave);
	HTMLTag * probeCommentTag(HTMLChar *sSource, HTMLChar **psSave);

public:
	bool loadHTML(const char * fromFile);
	bool saveAs(const char * toFile);
	bool parse();
};
#endif
