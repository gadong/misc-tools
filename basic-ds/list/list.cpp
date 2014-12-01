#include <stdio.h>
#include <stdlib.h>

typedef struct list_node{
	void * data;
	struct list_node * next;
}ln_t;

void inverse_list(list_node ** pplist){
	list_node *pOldHead = *pplist;
	list_node *pNewHead = NULL;
	list_node *pTmp;

	for(;pOldHead;){
		pTmp = pOldHead;
		pOldHead = pOldHead->next;
		pTmp->next = pNewHead;
		pNewHead = pTmp;
	}

	*pplist = pNewHead;
}

void recursive_inverse_list(list_node **ppOldList, list_node **ppNewList){
	list_node *pOldHead = *ppOldList;
	list_node *pNewHead = *ppNewList;
	list_node *pTmp;

	if(pOldHead){
		pTmp = pOldHead;
		pOldHead = pOldHead->next;
		pTmp->next = pNewHead;
		pNewHead = pTmp;
		*ppOldList = pOldHead;
		*ppNewList = pNewHead;

		recursive_inverse_list(ppOldList, ppNewList);
	}
}



