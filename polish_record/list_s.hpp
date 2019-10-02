#ifndef LIST_H
#define LIST_H

// List
// Stores integer values inside
template<typename Data>
struct ListItem
{
	Data item;
	ListItem<Data>* Next;
};

template<typename Data>
class List 
{
	ListItem<Data>* first_e;
public:
	// Creates new list
	List();
	// Destroys the list and frees the memory
	~List();
	// Retrieves the first item from the list
	ListItem<Data>* first();
	// Extracts data from the list item
	Data item_data(const ListItem<Data>* item);
	// Returns list item following after the specified one
	ListItem<Data>* item_next(ListItem<Data>* item);
	// Returns previous element for the specified item.
	// Not applicable for the singly linked lists.
	//ListItem* item_prev(ListItem* item);
	// Inserts new list item into the beginning
	ListItem<Data>* insert(Data data);
	// Inserts new list item after the specified item
	ListItem<Data>* insert_after(ListItem<Data>* item, Data data);
	// Deletes the specified list item.
	// Not applicable for the singly linked lists.
	// Should be O(1)
	//ListItem* erase(ListItem* item);
	// Deletes the list item following the specified one
	// Should be O(1)
	ListItem<Data>* erase_next(ListItem<Data>* item);
};

template<typename Data>
List < Data > ::List()
{
	first_e = nullptr;
}

template<typename Data>
List < Data > ::~List()
{
	ListItem<Data>* next = first_e;
	while (next != nullptr)
	{
		next = item_next(first_e);
		delete first_e;
		first_e = next;
	}
}

template<typename Data>
ListItem< Data >* List < Data > ::first()
{
	return first_e;
}

template<typename Data>
Data List< Data > ::item_data(const ListItem<Data>* item)
{
	return item->item;
}

template<typename Data>
ListItem<Data>* List< Data > ::item_next(ListItem<Data>* item)
{
	return item->Next;
}

/*template<typename Data>
ListItem<Data>* List< Data > ::item_prev(ListItem<Data>* item)
{

}*/

template<typename Data>
ListItem<Data>* List< Data > ::insert(Data data)
{
	ListItem<Data>* next = first_e;
	first_e = new ListItem<Data>;
	first_e->item = data;
	first_e->Next = next;
	return first_e;
}

template<typename Data>
ListItem<Data>* List< Data > ::insert_after(ListItem<Data>* item, Data data)
{
	ListItem<Data>* next = item_next(item);
	item->Next = new ListItem<Data>;
	item->Next->item = data;
	item->Next->Next = next;
	return item->Next;
}

/*template<typename Data>
ListItem<Data>* List< Data > ::erase(ListItem<Data>* item)
{

}*/

template<typename Data>
ListItem<Data>* List< Data > ::erase_next(ListItem<Data>* item)
{
	ListItem<Data>* next = item_next(item_next(item));
	delete item_next(item);
	item->Next = next;
	return item->Next;
}

#endif
