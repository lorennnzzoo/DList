#ifndef DLIST_H
#define DLIST_H

typedef struct DList
{
	void* Data;
	size_t Count;
	size_t Size;
	size_t type_size;
} DList;


DList* Initialize(DList* list,size_t type_size);
int Append(DList* list,void* item);
void Delete(DList** list);
void Remove(DList* list,size_t index);
void* Get(DList* list,size_t index);

#endif
