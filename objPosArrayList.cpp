#include "objPosArrayList.h"
#include "MacUILib.h"
// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.



objPosArrayList::objPosArrayList()
{
    aList = new objPos [ARRAY_MAX_CAP]; //allocate array
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;

}

objPosArrayList::~objPosArrayList()
{
    delete [] aList; //freeing array list

}

int objPosArrayList::getSize() const
{
    return listSize; 
}

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

void objPosArrayList::removeTail()
{
    if (listSize <= 0) // empty list
        return;
    
    listSize--;//decrease size but no shift

}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize <= 0)
        return objPos();

    // MacUILib_printf("Data: %c, %d, %d\n", aList[0].symbol, aList[0].pos->x, aList[0].pos->y);
    // MacUILib_Delay(999999);
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize <= 0)
        return objPos();
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= arrayCapacity)
        return objPos();
    
    return aList[index];
}

