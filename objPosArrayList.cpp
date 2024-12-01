#include "objPosArrayList.h"
#include "MacUILib.h"
// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.


//constructor
objPosArrayList::objPosArrayList()
{
    aList = new objPos [ARRAY_MAX_CAP]; //allocate array
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP; 

}

//deconstructor
objPosArrayList::~objPosArrayList()
{
    delete [] aList; //freeing array list

}

//get the current size of list
int objPosArrayList::getSize() const
{
    return listSize; 
}

//inster a new element at the head of the list
void objPosArrayList::insertHead(objPos thisPos)
{
    
    
    if (listSize >= arrayCapacity) 
        return; //list is full

    //shifting elements by one postion
    for (int i = listSize; i>0; i--){
        aList[i] = aList[i-1];
    }

    //inserting new element at index 0 (which is at head)
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity)
        return; //list full

    //new element at current size which is tail
    aList[listSize] = thisPos;
    listSize++;
    
}

//remove the element ta the head of the list
void objPosArrayList::removeHead()
{
    if (listSize <= 0)
        return; //empty list

//shifting elements by one position to the left
    for (int i = 0; i < listSize - 1; i++){
        aList[i] = aList[i+1];
    }

    listSize--;

}

//remove the element at the tail (end) of the list
void objPosArrayList::removeTail()
{
    if (listSize <= 0) // empty list
        return;
    
    listSize--;//decrease size but no shift

}

//get the element at the head of the list
objPos objPosArrayList::getHeadElement() const
{
    if (listSize <= 0) //check if list is empty
        return objPos(); //return default objPos

    return aList[0]; //return first element
}

//get the element at the tail -->last index
objPos objPosArrayList::getTailElement() const
{
    if (listSize <= 0) //check if the list is empty
        return objPos(); //return default objPos 
    return aList[listSize - 1]; //return the last element
}

//get the element at a specific index in the list
objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= arrayCapacity) //check for index out of bounds
        return objPos(); 
    
    return aList[index]; //reutrn element at the specified index
}

