#include <iostream>
using namespace std;

#define SUCCESS 0
#define FAILURE -1
#define NEWLINE cout<<endl

struct linkedListElement{
    int value;
    linkedListElement* nextElement;
};

linkedListElement* create_linkedListElement(int value){

    linkedListElement *list = (struct linkedListElement *)malloc(sizeof(linkedListElement));
    list->value = value;
    list->nextElement = NULL;

    return list;
}

//FIXME: ist der next pointer des elements NULL?
linkedListElement* append_linkedList(linkedListElement* list,linkedListElement* element){
    //check if list pointer is empty aka there is no list. 
    if (list == NULL){
        list = element;
        return list;
    }
    //if list exists traverse list until last element is found, then change current last element next ptr to new element
    linkedListElement *temp = list;
    while(temp->nextElement != NULL){
        temp = temp->nextElement;
    }
    temp->nextElement = element;
    element->nextElement = NULL; //set last next pointer to NULL to indicate end of list
    return list;
}

linkedListElement* prefix_linkedList(linkedListElement* list,linkedListElement* element){
    //check if list is NULL
    if(list == NULL){
        element->nextElement == NULL;
        return element;
    }
    element->nextElement = list;
    return element;
}

int delete_linkedListElement(linkedListElement* list,linkedListElement* element_to_delete){
    //TODO: Return pointer for new first element.
    linkedListElement* temp = list;
    //check if element to delete is first element
    if(list == element_to_delete){
        temp = list->nextElement;
        delete element_to_delete;
        list = temp;
        return SUCCESS;
    }
    while(temp != NULL){
        if(temp->nextElement == element_to_delete){
            temp->nextElement = element_to_delete->nextElement;
            delete element_to_delete;
            return SUCCESS;
        }
        temp = temp->nextElement;
    }
    return FAILURE;
}

linkedListElement* delete_list_completely(linkedListElement* list){
    linkedListElement* temp1 = list;
    linkedListElement* temp2 = temp1->nextElement;
    while (temp1)
    {
        temp2 = temp1->nextElement;
        delete temp1;
        temp1 = temp2;
    }
    return temp1;
    
    
}


int print_listelements(linkedListElement* list){
    linkedListElement* tempptr = list;
    int i=0;
    while(tempptr != NULL){
        cout<<"Element "<<i<<" : "<<tempptr->value<<"";
        tempptr = tempptr->nextElement;
        i++;
    }
    return 0;
}

linkedListElement* find_first_value(linkedListElement* list, int value){
    linkedListElement* tempptr = list;
    while (tempptr){
        if (tempptr->value == value){
            return tempptr;
        }
        tempptr = tempptr->nextElement;
    }
    return NULL;
}

int main(){
    linkedListElement* element1 = create_linkedListElement(101);
    linkedListElement* element2 = create_linkedListElement(102);
    static linkedListElement* List1;

    for (int i = 0; i < 100; i++)
    {
        List1 = append_linkedList(List1,create_linkedListElement(i));
    }
    List1 = append_linkedList(List1,element2);
    List1 = append_linkedList(List1,element1);

    List1 = prefix_linkedList(List1,create_linkedListElement(999999));

    print_listelements(List1);
    linkedListElement* element17 =  find_first_value(List1,17);
    delete_linkedListElement(List1,element17);
    cout << endl;
    cout << endl;
    print_listelements(List1);
    NEWLINE;
    NEWLINE;
    delete_linkedListElement(List1,List1);
    print_listelements(List1);
    

    // linkedListElement* Liste1 = append_linkedList(NULL,element1);
    // linkedListElcoutement* Liste2 = append_linkedList(Liste1,element2);
    // linkedListElement* Liste3 = append_linkedList(Liste2,create_linkedListElement(33));
}


