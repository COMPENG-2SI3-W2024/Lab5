#include "objPosDoubleHashing.h"
#include "MacUILib.h"

#include <iostream>
using namespace std;

objPosDoubleHashing::objPosDoubleHashing()
{
    myHashTable = new objPos[TABLE_SIZE];
}

objPosDoubleHashing::~objPosDoubleHashing()
{
    delete[] myHashTable;
}

int objPosDoubleHashing::calculateHashing(int prefix, int number) const  // hashing function
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

// 5 - sum of all digits of the first hashing index mod 5.
int objPosDoubleHashing::calculateSecondaryHashing(int input) const
{
    int sum = 0;

    while(input != 0)
    {
        sum += (input % 10);
        input /= 10;
    }

    return 5 - (sum % 5);
}

bool objPosDoubleHashing::insert(const objPos &thisPos)
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
    for(int i = 1; myHashTable[hashIndex].getSym() != 0; i++)
    {
        hashIndex = (originalIndex + i * calculateSecondaryHashing(originalIndex)) % TABLE_SIZE;
        if(hashIndex == originalIndex) break;
    }    

    // Then check if insertion is possible
    if(hashIndex != originalIndex)
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

bool objPosDoubleHashing::remove(const objPos &thisPos)  // lazy delete 
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

        hashIndex = (originalIndex + i * calculateSecondaryHashing(originalIndex)) % TABLE_SIZE;        
        if(hashIndex == originalIndex) break;
    }

    return false;  // only reaches here if matches not found
}

bool objPosDoubleHashing::isInTable(const objPos &thisPos) const
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
            return true;
        }

        hashIndex = (originalIndex + i * calculateSecondaryHashing(originalIndex)) % TABLE_SIZE;        
        if(hashIndex == originalIndex) break;
    }

    return false;  // only reaches here if matches not found
}

double objPosDoubleHashing::getLambda() const
{
    int count = 0;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(myHashTable[i].getSym() != 0)    
            count++;
    }

    return (double)count / TABLE_SIZE;
}

void objPosDoubleHashing::printMe() const
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        cout << "[" << i << "]  " << myHashTable[i].getPF() << myHashTable[i].getNum() << " " << myHashTable[i].getSym() << endl;     
    }
}