#include "objPosQuadHashing.h"
#include "MacUILib.h"

#include <iostream>
using namespace std;

objPosQuadHashing::objPosQuadHashing()
{
    myHashTable = new objPos[TABLE_SIZE];
    tableSize = TABLE_SIZE;
}

objPosQuadHashing::objPosQuadHashing(int size)
{
    myHashTable = new objPos[size];
    tableSize = size;
}

objPosQuadHashing::~objPosQuadHashing()
{
    delete[] myHashTable;
}

int objPosQuadHashing::calculateHashing(int prefix, int number) const  // hashing function
{    
    int sum = 0;

    while(prefix != 0)
    {
        sum += (prefix % 10);
        prefix /= 10;
    }

    while(number != 0)
    {
        sum += (number % 10);
        number /= 10;
    }

    return sum;
}

bool objPosQuadHashing::insert(const objPos &thisPos)
{
    int hashIndex = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int originalIndex = hashIndex;

    // If hashing index location is empty, insert
    if(myHashTable[hashIndex].getSym() == 0)
    {
        myHashTable[hashIndex] = thisPos;
        myHashTable[hashIndex].setSym('v'); // representing taken
        return true;
    }

    // Otherwise, start probing until another empty position is found
    // OR the last hashing index is at the original index (for foolproofing)
    int i;
    for(i = 1; myHashTable[hashIndex].getSym() != 0; i++)
    {
        hashIndex = (originalIndex + i * i) % tableSize;
        if(hashIndex == originalIndex || i > MAX_PROBING_COUNT) 
            break;
    }    

    // Then check if insertion is possible
    if(hashIndex != originalIndex && i <= MAX_PROBING_COUNT)
    {
        myHashTable[hashIndex] = thisPos;   
        myHashTable[hashIndex].setSym('v'); // representing taken     
        return true;
    }
    else
    {
        //cout << "failed to insert!" << endl;
        return false;
    }

}

bool objPosQuadHashing::remove(const objPos &thisPos)  // lazy delete 
{
    int hashIndex = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int originalIndex = hashIndex;    

    for(int i = 1; myHashTable[hashIndex].getSym() != 0; i++)
    {
        if(myHashTable[hashIndex].getPF() == thisPos.getPF() &&
           myHashTable[hashIndex].getNum() == thisPos.getNum())
        {
            myHashTable[hashIndex].setSym(0);  // lazy delete
            //cout << "deleted at index " << hashIndex << ": ";
            //myHashTable[hashIndex].printObjPos();
            return true;
        }

        hashIndex = (originalIndex + i * i) % tableSize;        
        if(hashIndex == originalIndex) break;
    }

    return false;  // only reaches here if matches not found
}

bool objPosQuadHashing::isInTable(const objPos &thisPos) const
{
    int hashIndex = calculateHashing(thisPos.getPF(), thisPos.getNum());
    int originalIndex = hashIndex;
    
    //cout << "calculated index: " << hashIndex << endl;

    for(int i = 1; myHashTable[hashIndex].getSym() != 0; i++)
    {
        //myHashTable[hashIndex].printObjPos();
        //thisPos.printObjPos();        
        //cout << "at Index = " << hashIndex << endl;

        if(myHashTable[hashIndex].getPF() == thisPos.getPF() &&
           myHashTable[hashIndex].getNum() == thisPos.getNum())
        {   
            return (myHashTable[hashIndex].getSym() != 0);
        }

        hashIndex = (originalIndex + i * i) % tableSize;        
        if(hashIndex == originalIndex) break;
    }

    return false;  // only reaches here if matches not found
}

double objPosQuadHashing::getLambda() const
{
    int count = 0;

    for(int i = 0; i < tableSize; i++)
    {
        if(myHashTable[i].getSym() != 0)    
            count++;
    }

    return (double)count / tableSize;
}

void objPosQuadHashing::printMe() const
{
    MacUILib_printf("[ ");
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(myHashTable[i].getSym() != 0)
            MacUILib_printf("%c%d ", myHashTable[i].getPF(), myHashTable[i].getNum());     
    }
    MacUILib_printf("] L=%.2f", getLambda());
}