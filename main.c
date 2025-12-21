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
		p->Name="loren";
		Append(list,p);


		person* p2=malloc(sizeof(person));
		p2->Age=23;
		p2->Name="lorenzo";
		Append(list,p2);

		
		person* p3=malloc(sizeof(person));
		p3->Age=22;
		p3->Name="lore";
		Append(list,p3);

		person* p_at=GetOrNull(list,1);
		printf("2nd position Person Age : %d, Name : %s\n",p_at->Age,p_at->Name);
		
		person* first_person=FirstOrNull(list);
		if(first_person)
		{
			printf("first position Person Age : %d, Name : %s\n",first_person->Age,first_person->Name);
		}
		else{
			printf("Null returned");
		}

		
		person* last_person=LastOrNull(list);
		if(last_person)
		{
			printf("last position Person Age : %d, Name : %s\n",last_person->Age,last_person->Name);
		}
		else{
			printf("Null returned");
		}
		Clear(list);
		printf("List count : %zu\n",list->Count);
		printf("List size : %zu\n",list->Size);
		Delete(&list);
	}
}

