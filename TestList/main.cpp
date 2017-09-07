#include <iostream>
#include "list.h"

int main()
{
    List *list = list_create();
    
    list_delete(list);
}
