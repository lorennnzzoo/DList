#include <stdio.h>
#include <stdlib.h>
#include "DList.h"

typedef struct Person{
	int Age;
	char* Name;
} person;
int main()
{
	DList *list=malloc(sizeof(DList));
	list=Initialize(list,sizeof(person));
	if(list)
	{
		person* p=malloc(sizeof(person));
		p->Age=10;
		p->Name="Bhanu";
		Append(list,p);

		person* p2=Get(list,0);
		printf("Person Age : %d, Name : %s",p2->Age,p2->Name);
		
		Delete(&list);
	}
}

