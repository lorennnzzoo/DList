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

void RemoveAt(DList* list, size_t index) {
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


void ForEach(DList* list,void (*Element)(void*))
{
	for(int i=0;i<list->Count;i++)
	{
		void* item=GetOrNull(list,i);
		if(item)
		{
			Element(item);
		}
	}
}

int Serialize(DList* list, char* file_name)
{
    FILE* file = fopen(file_name, "wb");
    if (!file)
    {
        return -1;
    }

    size_t written_count = fwrite(&list->Size, sizeof(size_t), 1, file);
    if (written_count != 1)
    {
        fclose(file);
        return 1;
    }
    written_count = fwrite(&list->type_size, sizeof(size_t), 1, file);
    if (written_count != 1)
    {
        fclose(file);
        return 1;
    }
    written_count = fwrite(&list->Count, sizeof(size_t), 1, file);
    if (written_count != 1)
    {
        fclose(file);
        return 1;
    }

    written_count = fwrite(list->Data, list->type_size, list->Count, file);
    if (written_count != list->Count)
    {
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

DList* Deserialize(char* file_name)
{
    FILE* file = fopen(file_name, "rb");
    if (!file)
    {
        return NULL;
    }

    DList* list = malloc(sizeof(DList));
    if (!list)
    {
        fclose(file);
        return NULL;
    }

    size_t read_count = fread(&list->Size, sizeof(size_t), 1, file);
    if (read_count != 1)
    {
        fclose(file);
        free(list);
        return NULL;
    }
    fread(&list->type_size, sizeof(size_t), 1, file);
    fread(&list->Count, sizeof(size_t), 1, file);

    list->Data = malloc(list->type_size * list->Count);
    if (!list->Data)
    {
        fclose(file);
        free(list);
        return NULL;
    }

    read_count = fread(list->Data, list->type_size, list->Count, file);
    if (read_count != list->Count)
    {
        fclose(file);
        free(list->Data);
        free(list);
        return NULL;
    }

    fclose(file);
    return list;
}
