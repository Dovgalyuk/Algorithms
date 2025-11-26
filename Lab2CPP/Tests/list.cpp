#include <iostream>
#include "list.h"

int main()
{
    List listA = List();
    List listB = List();

    listA.insert(1);
    listA.insert(2);
    listA.insert(3);

    listB = List(listA); 
    
    if(listB.first()->data() != listA.first()->data())
    {
        std::cout <<"list_copy error"<< std::endl;
        return 1;
    }

    listB.insert(5);
    listB.insert(6);
    listB.insert(7);

    listB = listA;
    
    if(listB.first()->data() != listA.first()->data())
    {
        std::cout <<"list_argumment_operation error"<< std::endl;
        return 1;
    }
}
