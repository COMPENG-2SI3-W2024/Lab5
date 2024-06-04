#include "objPosDoubleHashing.h"
//#include "MacUILib.h"

#include <iostream>
using namespace std;

objPosDoubleHashing::objPosDoubleHashing()
{
<<<<<<< HEAD
    myHashTable = new objPos[TABLE_SIZE];
    tableSize = TABLE_SIZE;
=======
    // Instantiate the objPos Hash Table of the default size TABLE_SIZE defined in the objPosHashTable abstract class
    // Should also initialize tableSize field with the default size TABLE_SIZE
>>>>>>> 7839822f6863a99ce656626b336181744a258eee
}

objPosDoubleHashing::objPosDoubleHashing(int size)
{
<<<<<<< HEAD
    myHashTable = new objPos[size];
    tableSize = size;
=======
    // Instantiate the objPos Hash Table of the specified size
    // Should also initialize tableSize field with specified size
>>>>>>> 7839822f6863a99ce656626b336181744a258eee
}

objPosDoubleHashing::~objPosDoubleHashing()
{
    // delete the Hash Table
}

int objPosDoubleHashing::calculateHashing(int prefix, int number) const  // hashing function
{    
    // Implementing the primary hashing function

    // Add all the decimal integer digits of the Prefix ASCII char and the Number together

    // For example, given objPos.prefix = 'A' (65) and objPos.number = 98, then...
    //  h(x) = sum of all decimal digits of prefix and number = 6 + 5 + 9 + 8 = 28

    // return the sum as the hashing key. 
}

int objPosDoubleHashing::calculateSecondaryHashing(int input) const
{
    // Implementing the secondary hashing function

    // 1. Sum up all digits of input
    // 2. return 5 - (sum mod 5)

    // e.g.  input = 18
    //       sum = 1 + 8 = 9
    //       return value = 5 - (9 % 5) = 5 - 4 = 1
    
}

bool objPosDoubleHashing::insert(const objPos &thisPos)
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    //  2. Check symbol field to see whether the indexed slot is empty
    //      If yes, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      Otherwise, proceed to collision resolution
    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    //  4. For every newly calculated key using quadratic probing, check for empty slot for insertion
    //      If empty slot is found, insert data, set symbol to 'v', then return true (indicating successful insertion)
    //      If element is already inserted, return false (indicating failed insertion)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

<<<<<<< HEAD
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
        hashIndex = (originalIndex + i * calculateSecondaryHashing(originalIndex)) % tableSize;
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
=======
>>>>>>> 7839822f6863a99ce656626b336181744a258eee

}

bool objPosDoubleHashing::remove(const objPos &thisPos)  // lazy delete 
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    //  2. Check if the data at the slot matches thisPos (prefix and number)
    //      If yes, perform lazy delete by setting symbol to 0, then return true (indicating successful removal)
    //      Otherwise, proceed to collision resolution
    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
    //      If match found, perform lazy delete by setting symbol to 0, then return true (indicating successful removal)
    //      If empty slot encountered, the probing chain reaches the end, hence return false (indicating failed removal)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)

<<<<<<< HEAD
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

        hashIndex = (originalIndex + i * calculateSecondaryHashing(originalIndex)) % tableSize;        
        if(hashIndex == originalIndex) break;
    }

    return false;  // only reaches here if matches not found
=======
>>>>>>> 7839822f6863a99ce656626b336181744a258eee
}

bool objPosDoubleHashing::isInTable(const objPos &thisPos) const
{
    // Algorithm similar to the one discussed in class
    //  1. Calculate the initial hashing key using calculateHashing() private helper function (i.e. the h1(x))
    //  2. Check if the data at the slot matches thisPos (prefix and number) 
    //      If matched, further chech whether symbol != 0 (data not deleted yet)
    //          If yes, return true (indicating successfully found)
    //          Otherwise, return false (indicating failed to find)
    //     If no match is found, proceed to collision resolution
    //  3. Collision resolution strategy - Double Probing
    //      h(x) = (h1(x) + i*h2(x)) mod tableSize  (i is the probing count)
    //      where h2(x) = 5 - (sum of all digits of h1(x)) mod 5)
    //  4. For every newly calculated key using quadratic probing, check for data matching (identical prefix and number)
    //      If matched, further chech whether symbol != 0 (data not deleted yet)
    //          If yes, return true (indicating successfully found)
    //          Otherwise, return false (indicating failed to find)
    //      If probing count exceeds MAX_PROBING_COUNT defined in objPosHash.h, return false
    //          (too many probing attempts, may lead to integer overflow)


<<<<<<< HEAD
        if(myHashTable[hashIndex].getPF() == thisPos.getPF() &&
           myHashTable[hashIndex].getNum() == thisPos.getNum())
        {   
            return (myHashTable[hashIndex].getSym() != 0);
        }

        hashIndex = (originalIndex + i * calculateSecondaryHashing(originalIndex)) % tableSize;        
        if(hashIndex == originalIndex) break;
    }

    return false;  // only reaches here if matches not found
=======
>>>>>>> 7839822f6863a99ce656626b336181744a258eee
}

double objPosDoubleHashing::getLambda() const
{
<<<<<<< HEAD
    int count = 0;

    for(int i = 0; i < tableSize; i++)
    {
        if(myHashTable[i].getSym() != 0)    
            count++;
    }

    return (double)count / tableSize;
=======
    // Calculate the Load Factor of the Hash Table
    // Check lecture code for examples
>>>>>>> 7839822f6863a99ce656626b336181744a258eee
}

void objPosDoubleHashing::printMe() const
{
<<<<<<< HEAD
    for(int i = 0; i < tableSize; i++)
    {
        cout << "[" << i << "]  " << myHashTable[i].getPF() << myHashTable[i].getNum() << " " << myHashTable[i].getSym() << endl;     
    }
=======
    // Recommended Format:
    //  [Key] Prefix Number  Symbol

    // e.g. ...
    //      [20] A 9  v
    //      [21] 0 
    //      [22] E 7  v
    //      ... 
 


    // Provided Code for Model Code Integration
    ////////////////////////////////////////////////

    // MacUILib_printf("[ ");
    // for(int i = 0; i < TABLE_SIZE; i++)
    // {
    //     if(myHashTable[i].getSym() != 0)
    //         MacUILib_printf("%c%d ", myHashTable[i].getPF(), myHashTable[i].getNum());     
    // }
    // MacUILib_printf("] L=%.2f", getLambda());

    // You will also need to #include "MacUILib.h" when integrating with the model code.
>>>>>>> 7839822f6863a99ce656626b336181744a258eee
}