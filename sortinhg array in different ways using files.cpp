//used library are iostream and fstream and iomanip
#include <bits/stdc++.h>

using namespace std;
//declaring class float array
class floatarray
{
protected:
    //declaring the array size member function and the dynamic array of floats
    int arrsize;
    float *arrOfFloats;
public:
    //constructor to the array of floats
    floatarray(int Size)
    {
        arrsize=Size;
        arrOfFloats=new float[arrsize];
        //initializing elements of arr of float to a very large number
        for(int i=0;i<arrsize;i++)
        {
            arrOfFloats[i]=100000;
        }

    }
    //prototype for function that adds element to arrray
    //we used virtual because it will be overrided in the derived classes
    virtual void addItem(float );
    friend ofstream& operator<<(ofstream&,floatarray*);
    friend ifstream& operator>>(ifstream&,floatarray*);
    ~floatarray()
    {
        delete[]arrOfFloats;
    }
};
//declaring the class sorted array that inherits from float array
class SortedArray:public floatarray
{
public:
    //sorted array constructor and the overrided additem function prototype
    SortedArray(int s):floatarray(s){}
    virtual void addItem(float );
};

class FrontArray:public floatarray
{
public:
    FrontArray(int s):floatarray(s){}
    //overriding addItem function in float array so that
    //it adds element to the front of the array
    void addItem(float fitem)
    {
        //reversed loop to shift elements of the array one slot forward
        for(int j=arrsize-1;j>0;j--)
        {
            arrOfFloats[j]=arrOfFloats[j-1];
        }
        // the parameter is assigned to the first element of the array
        arrOfFloats[0]=fitem;
    }
};
//declaring positive array class that inherits from sorter array
class PositiveArray:public SortedArray
{
public:
    PositiveArray(int sizE):SortedArray(sizE){}
    //overriding the addItem function in sorted array
    //the function checks whether the parameter is positive
    //if so it use the function addItem in class sorted array to add it
    //to the array
    //does the name of the parameter affect the overriding mechanism?????
    void addItem(float Item)
    {
        if(Item>0)
        {
            SortedArray::addItem(Item);
        }
    }
};
class NegativeArray:public SortedArray
{
public:
    NegativeArray(int sizE):SortedArray(sizE){}
    //declaring a new function that called Additem
    //that uses the addItem inherited from sorted array class
    void Additem(float Item)
    {
        if(Item<0)
        {
            addItem(Item);
        }
    }
};

int main()
{
    //iIword is the variable that will hold the name of the class
    //that will be taken from the input file
    //iiinputfile,oooutputfile variables that hold the names of files
    string iIword,iiinputfile,oooutputfile;
    //numelements hold the the number of elements in each array in the input file
    float numelements;
    //declaring if and of stream objects
    ifstream infile;
    ofstream outfile;
    //the subscribt is set to 10 according to number of lines
    //parr meaning pointer to array
    //consider it as array of 10 dynamically allocated  objects
    floatarray*parr[10];
    floatarray*ptr;
    //prompt the user to enter the name of input and output files
    cout<<"Enter the name of the input file:\n";
    cin>>iiinputfile;
    cout<<"Enter the name of the output file:\n";
    cin>>oooutputfile;
    //opening the input and output files
    infile.open(iiinputfile);
    outfile.open(oooutputfile);
    //using counter to loop over the parr arrays
    //the loop will end when we reach the end of the file
    int counter=0;
    while(!infile.eof())
    {
        //entering the type of the array in the iIword vriable
        //and number of elements that will be in the array
        infile>>iIword;
        infile>>numelements;
        //using if/else if to determine which class will be this dynamically allocated array
        if(iIword=="Sorted")
        {
            //parr[counter] means the object at this counter will be of class sortedarray
            parr[counter]=new SortedArray(numelements);
            //filling the array in object parr[counter] using the overloaded extraction operator
            infile>>parr[counter];
        }
        else if(iIword=="Array")
        {
            parr[counter]=new floatarray(numelements);
            infile>>parr[counter];
        }
        else if(iIword=="Front")
        {
            parr[counter]=new FrontArray(numelements);
            infile>>parr[counter];
        }
        //is this condition we used different method in filling the array in the object
        else if(iIword=="Positive")
        {
            //we first declared element variable to store the value taken from the input file
            //and declared and empty array of floats of maximum size 100
            float element=0;
            float arr[100];
            for(int i=0;i<100;i++)
            {
                arr[i]=0;
            }
            //declaring cccounter that will store the number of positive numbers in the array
            int cccounter=0;
            //enter the element in the positive array in the file to our empty array arr[100]
            for(int i=0;i<numelements;i++)
            {
                infile>>element;
                arr[i]=element;
            }
            for(int i=0;i<numelements;i++)
            {
                if(arr[i]>0)
                {
                    //incrementing the cccounter with every positive element we find in the array
                    cccounter++;
                }
            }
            //the object parr[counter] will be dynamically allocated to class positive array
            //and the array inside this object will be of size cccounter
            parr[counter]=new PositiveArray(cccounter);
            //looping over arr[100] to add the positive values inside it to our object's array
            for(int i=0;i<100;i++)
            {
                parr[counter]->addItem(arr[i]);
            }
        }
        else if(iIword=="Negative")
        {
            float element=0;
            float arr[20];
            for(int i=0;i<20;i++)
            {
                arr[i]=0;
            }
            int ccounter=0;
            //used while loop to fill out empty arr[20]
            while(ccounter<numelements)
            {
                infile>>element;
                arr[ccounter]=element;
                ccounter++;
            }
            int cccounter=0;
            for(int i=0;i<20;i++)
            {
                if(arr[i]<0)
                    cccounter++;
            }
            //the object parr[counter] will be dynamically allocated to class negative array
            parr[counter]=new NegativeArray(cccounter);
            for(int i=0;i<20;i++)
            {
                //we are here taking the negative values inside the arr[20]
                //and put in the array in the object parr[counter] using the Additem method in negative array class
                // since this method is not in float array class we will then type cast our pointer to object to negative array class
                ((NegativeArray*)parr[counter])->Additem(arr[i]);
            }
        }
        counter++;

    }
    //here we will loop over the array of dynamically allocated objects
    //to put the values inside their arrays in the output file
    //using the overloaded insertion operator "<<"
    for(int i=0;i<10;i++)
    {
        outfile<<parr[i];
    }
    outfile.close();
    infile.close();
    return 0;
}
//the overloaded if ifstream extraction operator will take the input file object
//and a pointer to the object we want to fill the array inside it as parameters
ifstream& operator>>(ifstream& iinfile,floatarray* arrr)
{
    //declaring variables and enter in infinite loop until we reach the end of the line the loop
    //will break
    char v;
    float element=0;
    while(1)
    {
        iinfile>>element;
        //dereference the pointer to object and use the dot operator to access the function add item
        //inside the class of this object
        (*arrr).addItem(element);
        iinfile.get(v);
        if(v=='\n')
        {
            break;
        }
    }
}
//the overloaded insertion operator will take parameters
//the output file object and a pointer to the object we want to fill the array inside it
ofstream& operator<<(ofstream& oofile,floatarray* arrr)
{
    //accessing the size of the array through pointer to the object using the arrow operator
    oofile<<setw(3)<<arrr->arrsize<<"|";
    for(int i=0;i<arrr->arrsize;i++)
    {
        oofile<<"\t"<<arrr->arrOfFloats[i];
    }
    //put new line character in the file using the method put
    oofile.put('\n');
}
// overrided addItem function in sorted array class it take one float element
// as a parameter
  void SortedArray::addItem(float fitem)
{
    //here we used for loop to loop over the array of the object
    //to see the first element greater than the element we take as parameter "fitem"
    for(int i=0;i<arrsize;i++)
    {
        if(arrOfFloats[i]>fitem)
        {
            //if so and we find element greater than fitem in the array let's call it greatelement
            // we use reversed loop to shift greatelement and all elements after it to the next slot
            for(int j=arrsize-1;j>i;j--)
            {
            arrOfFloats[j]=arrOfFloats[j-1];
            }
            //the formerly great slot element will be the new element which is tha parameter taken "fitem"
            arrOfFloats[i]=fitem;
            //then we break from the large loop so that not element greater than fitem become fitem
            break;
        }
    }
}
//the addItem method in float array class
void floatarray::addItem(float fitem)
{
    //looping over the array to make shift every slot except the last slot
    //to the right
    for(int i=0;i<arrsize-1;i++)
    {
        //assign float to the end of the array
        arrOfFloats[i]=arrOfFloats[i+1];
    }
    //assing the parameter named "fitem" to the last slot
    arrOfFloats[arrsize-1]=fitem;
}
