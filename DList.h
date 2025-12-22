#ifndef DLIST_H
#define DLIST_H

typedef struct
{
	void* Data;
	size_t Count;
	size_t Size;
	size_t type_size;
} DList;

//Iteration
void ForEach(DList* list,void (*Element)(void*));

//Creation
DList* Initialize(DList* list,size_t type_size);

//Accessing and Modifying items in List
int Append(DList* list,void* item);
void RemoveAt(DList* list,size_t index);
void* GetOrNull(DList* list,size_t index);
void* FirstOrNull(DList* list);
void* LastOrNull(DList* list);

//Clearing the items from List
void Clear(DList* list);

//Deleting the entire List
void Delete(DList** list);

//Binary Serialization
int Serialize(DList* list,char* file_name);

//Binary Deserialization
DList* Deserialize(char* file_name);

#endif
