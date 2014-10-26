/*
	Author: 	Kevin, Ye
	MailBox:	kraven@foxmail.com
	Date:	26th Oct. 2014
*/

#include <stdio.h>
#include <stdlib.h>

#define debugprint(...)		//printf

struct Int{
	int mVal;

	Int(int val=0){
		mVal = val;
	}
	Int(const Int & copy){
		mVal = copy.mVal;
	}
	Int & operator=(int val){
		mVal = val;
	};
	operator int() const{
		return mVal;
	}
	void dump()
	{
		printf("%4d ", mVal);
	}
};

typedef struct matrix_region{
	int left;
	int right;
	int top;
	int bottom;
}matrix_region_t;

template <typename Element>
class Matrix{
	Element *mStorage;
	int mHeight;
	int mWidth;
	
	Element *mTraverseResult;
	Element *mTmpTraversePtr;
	int mResultSize;
	bool mTraversed;
	
	enum GraphFlag{
		original,
		available, 
		settled, 
	};	
	int * mTmpMaskGraph;
	int mRecursionDepth;

	void _trapezoidTraverse(const matrix_region_t *pregion);
	void _swap(int i, int j);
	
public:
	Matrix(Element * pStorage, int nHeight, int nWidth);
	~Matrix();

	void dump(const char * sTitle);
	void convert();
	bool getTraverseResult(int * pResultSize, Element **pResult);
	void trapezoidTraverse(const matrix_region_t *pregion);
};

template<typename Element>
Matrix<Element>::Matrix(Element *pStorage, int nHeight, int nWidth)
{
	mStorage = pStorage;
	mHeight = nHeight;
	mWidth = nWidth;
	mRecursionDepth = 0;
	
	mTraversed = false;
}

template<typename Element>
Matrix<Element>::~Matrix()
{
	delete []mTraverseResult;
}

template<typename Element>
void Matrix<Element>::_swap(int row, int col)
{
	int srcLoc = row * mWidth + col;
	int dstLoc = col* mHeight + row;

	Element *pelement  = new Element();
	*pelement = mStorage[srcLoc];
	mTmpMaskGraph[srcLoc] = available;
	
	if(srcLoc != dstLoc) {
		if(mTmpMaskGraph[dstLoc] == settled)
			debugprint("FATAL Error: %d %d is mapped to %d\r\n", row, col, dstLoc);
		if(mTmpMaskGraph[dstLoc] == original){
			int i, j;
			i = dstLoc /mWidth;
			j = dstLoc % mWidth;
			_swap(i, j);
		}
		mStorage[dstLoc] = *pelement;
		delete pelement;
	}
	
	mTmpMaskGraph[dstLoc] = settled;
}

template<typename Element>
void Matrix<Element>::convert()
{
	mTmpMaskGraph = (int*)new Int[mHeight*mWidth];

	for(int i=0; i<mHeight*mWidth; i++)
		mTmpMaskGraph[i] = original;
	
	for(int row = 0; row < mHeight; row ++){
		for(int col = 0; col < mWidth; col ++){
			//all ready handled
			if(mTmpMaskGraph[row*mWidth + col] == settled)continue;
			_swap(row, col);
		}
	}

	mTraversed = false;

	int nTmp = mHeight;
	mHeight = mWidth;
	mWidth = nTmp;
	delete []mTmpMaskGraph;
}

template<typename Element>
bool Matrix<Element>::getTraverseResult(int * pResultSize, Element ** pResult)
{

	if(!mTraversed)return false;
	
	*pResultSize = mResultSize;
	*pResult = mTraverseResult;
	
	return true;
}

template<typename Element>
void Matrix<Element>::dump(const char *sTitle)
{
	printf("\r\n::%s\r\n", sTitle);
	printf("------------------------\r\n");
	for(int i=0; i<mHeight; i++){
		for(int j=0; j<mWidth; j++){
			Element *pelement = &mStorage[i*mWidth + j];
			pelement->dump();
		}
		printf("\r\n");
	}
	printf("-----------End----------\r\n");
}

template<typename Element>
void Matrix<Element>::_trapezoidTraverse(const matrix_region_t *pregion)
{
	int i, j;
	int left, right, top, bottom;
	int wmatrix, hmatrix;
	int wregion, hregion;

	left = pregion->left;
	right = pregion->right;
	top = pregion->top;
	bottom = pregion->bottom;

	wregion = right-left + 1;
	hregion = bottom-top + 1;
	
	// To Right
	for( i=left; i<=right; i++){
		*mTmpTraversePtr ++ = mStorage[top*mWidth+i];
	}
 
	// To Left-Down
	i=right - 1; j=top + 1;
	for(; i>=left && j<=bottom; i--, j++){
		*mTmpTraversePtr ++ = mStorage[j*mWidth+i];
	}
	
	// To Left
	for(; i>=left; i--){
		*mTmpTraversePtr ++ = mStorage[(j-1)*mWidth+i];
	}

	// To Up
	int rbottom = (wregion>hregion) ? bottom : top+wregion-1;
	for(j=rbottom-1;j>top; j--){
		*mTmpTraversePtr ++ = mStorage[j*mWidth+left];
	}
	
	// To the Embedded-Sub-Matrix
	if(wregion>3 && hregion>2){

		matrix_region_t sub_region;
		sub_region.left = left +1;
		sub_region.right = right -2;
		sub_region.top = top + 1;
		sub_region.bottom = bottom -1;
		_trapezoidTraverse(&sub_region);
	}
}

template<typename Element>
void Matrix<Element>::trapezoidTraverse(const matrix_region_t *pregion)
{
	if(!mTraversed){
		if(mWidth>=mHeight){
			mResultSize= (mWidth * mHeight) - (mHeight-1)*mHeight/2;
		}else{
			mResultSize= (mWidth +1)*mWidth/2;
		}

		mTraverseResult = new Element[mResultSize*sizeof(int)];
		debugprint("Traverse Summary: %d @ %p\r\n", mResultSize, mTraverseResult);

		mTmpTraversePtr = mTraverseResult;
		_trapezoidTraverse(pregion);
		mTmpTraversePtr = NULL;
		
		mTraversed = true;
	}
}

void  convertMatrix(int width, int height, int* matrix, int *result_size, int** result) {
	Matrix<Int> *pMatrix = new Matrix<Int>((Int*)matrix, height, width);

	matrix_region_t sub_region;
	sub_region.left = 0;
	sub_region.right = width-1;
	sub_region.top = 0;
	sub_region.bottom = height -1;
	pMatrix->dump("Original Matrix");
	pMatrix->trapezoidTraverse(&sub_region);
	pMatrix->getTraverseResult(result_size, (Int**)result);

	pMatrix->convert();
	pMatrix->dump("After Converted");
}

int main() {
    int res_size;
    int* res;
    int _width;
    scanf("%d", &_width);
    
    int _height;
    scanf("%d", &_height);
    
    int *_matrix = (int*) malloc(_width * _height * sizeof(int));
    int _matrix_i;
    for(_matrix_i = 0; _matrix_i < _width * _height; _matrix_i++) { 
        int _matrix_item;
        scanf("%d", &_matrix_item);
        
        _matrix[_matrix_i] = _matrix_item;
    }

    convertMatrix(_width, _height, _matrix, &res_size, &res);
    int res_i;
    for(res_i=0; res_i < res_size; res_i++) {
    
        printf("%d ", res[res_i]);
        
    }
    
    return 0;
}

