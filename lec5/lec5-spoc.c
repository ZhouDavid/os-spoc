#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BLOCK_COUNT 100
#define PAGE_SIZE 1000

typedef struct Node{
	int allocated;
	int size;
	void* space;
	struct Node* next;
}Page;

Page* head;

void init(){
	if(head==NULL){
	head=sbrk(sizeof(Page));
	head->space=sbrk(PAGE_SIZE);
	head->allocated=0;
	head->size=PAGE_SIZE;
	head->next=NULL;
	}
	int i=0;
	Page* tmp=head->next;
	while(i<BLOCK_COUNT-1){
		if(tmp==NULL){
		  tmp=sbrk(sizeof(Page));
		  tmp->space=sbrk(PAGE_SIZE);
		  tmp->allocated=0;
		  tmp->size=PAGE_SIZE;
		  tmp->next=NULL;
		}
	i++;
	}
}

void* mmalloc(int size){
    Page* tmp=head;
    while(tmp!=NULL){
    	if(tmp->size >= size && tmp->allocated==0){
    		tmp->allocated=1;
    		return tmp;
    	}
    }
   	return NULL;
}
int mfree(void* p){
	Page* tmp=head;
	while(tmp!=NULL){
		if(p==tmp && tmp->allocated==1){
			tmp->allocated=0;
			return 1;
		}
		tmp=tmp->next;
	}
	return 0;
}

int main(){
  init();
  void* a=mmalloc(100);
  int b=mfree(a);
  printf("%p\n",a);
  printf("%d\n",b);
  return 0;

}
