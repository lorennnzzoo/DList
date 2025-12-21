#include <stdio.h>
#include <stdlib.h>
#include "DList.h"

DList* Initialize(DList* list,size_t type_size)
{
        if(!list)
                //user passed NULL pointer
                return NULL;
        list->Size=1;
	list->type_size=type_size;
        list->Count=0;
        list->Data=malloc(type_size*list->Size);
        if(!list->Data)
        {
                //malloc failed to allocate memory for Data
                free(list); //free the list cause we dont need it anymore
                return NULL;
        }
	return list;
}

int Append(DList* list,void* item)
{
	if(list->Count==list->Size)
	{
		list->Size++;
		int* temporary=realloc(list->Data,list->type_size*list->Size);
		if(!temporary)
		{
			//Unable to allocate new memory for list
			list->Size--;
			return -1;
		}
		list->Data=temporary;
	}
	memcpy((char*)list->Data + list->type_size * list->Count, item, list->type_size);
	list->Count++;
	return 0;
}

void Delete(DList** list)
{
	if(*list)
	{
		free((*list)->Data);
		free(*list);
		*list=NULL;
	}
}

void Remove(DList* list, size_t index) {
    printf("Removing at %zu\n", index);

    if (index >= list->Count) {
        printf("Index is greater than or equal to list Count\n");
        return;
    }

    for (size_t position = index + 1; position < list->Count; position++) {
        memcpy((char*)list->Data + (position - 1) * list->type_size,
               (char*)list->Data + position * list->type_size,
               list->type_size);
    }

    list->Count--;

    void* shrink = realloc(list->Data, list->type_size * list->Size - 1);
    if (shrink) {
        list->Size--;
        list->Data = shrink;
    }

    printf("Count after removing: %zu\n", list->Count);
    return;
}

void* GetOrNull(DList* list,size_t index)
{
	if(index>=list->Count)
		return NULL;
	return (char*)list->Data + list->type_size * index;
}

void* FirstOrNull(DList* list)
{
	if(list->Count==0)
		return NULL;
	return (char*)list->Data+list->type_size*0;
}

void* LastOrNull(DList* list)
{
	if(list->Count==0)
		return NULL;
	return (char*)list->Data+(list->type_size*(list->Count-1));
}

void Clear(DList* list)
{
	if(realloc(list->Data,list->type_size*1)){
		list->Size=1;
		list->Count=0;
	}
}
