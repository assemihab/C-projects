//TD means testing data formyself
//comments between/**/ are notes for myself
#include<string>
#include <iostream>
#include<iomanip>
using namespace std;
//class declaration
class MyPhoneBook
{
private:
    string*names,*phones;
    int phoneBookSize;
public:
    MyPhoneBook(int);
    MyPhoneBook(const MyPhoneBook&);
    bool addEntry(string,string);
    bool displayEntryAtIndex(int);
    void displayEntryAtIndex(int*);
    void displayAll();
    int *findbyName(string);
    int *findByPhone(string);
    bool updateNameAt(string,int);
    bool updatePhoneAt(string,int);
    ~MyPhoneBook();
};



int main()
{
    //int arr[3]={1,0,1};
    int booksize,choice,entryIndex,updateIndex;
    string name,phone,desiredName,desiredPhone,updatedName,updatedNumber;
    cout<<"Enter the size of your phone book: ";
    cin>>booksize;
    MyPhoneBook r(booksize);
    cin.ignore();
    for(int i=0;i<booksize;i++)
    {
        cout<<"Enter name "<<i+1<<": ";
        getline(cin,name);
        cout<<"Enter phone "<<i+1<<": ";
        cin>>phone;
        while(!r.addEntry(name,phone))
        {
            cout<<"invalid phone number, please reEnter: ";
            cin>>phone;

        }
        cin.ignore();
    }
    //prompt the user to enter his choice
    //is the choice is number 8 the program will exit
    do
    {
        cout<<"Enter your choice: \n";
        cout<<"1- Display all phone book\n";
        cout<<"2- Search for entry/entries by name\n";
        cout<<"3- Search for entry/entries by phone\n";
        cout<<"4- Find an entry by index\n";
        cout<<"5- Update name by index\n";
        cout<<"6- Update phone by index\n";
        cout<<"7- Copy phone book to another and display entries of the new phone book\n";
        cout<<"8- Exit\n";
        cout<<"choice: ";
        cin>>choice;
        while(choice>8||choice<1)
        {
            cout<<"wrong entery please reenter your choice: ";
            cin>>choice;
        }
        switch(choice)
        {
        case 1:
            {
                r.displayAll();
            }
        break;
        case 2:
            {
                cout<<"Enter the name you are searching for: ";
                cin.ignore();
                getline(cin,desiredName);
                //displaying the array returned from method
                //(find by name) using for loop
                for(int i=0;i<booksize;i++)
                    {
                        if(r.findbyName(desiredName)[i]==1)
                            cout<<"the name exists here: ";
                        else
                            cout<<"the name isn't here:  ";

                        cout<<*(r.findbyName(desiredName)+i)<<endl;
                    }
            }
        break;
        case 3:
            {
                cout<<"Enter the number you are searching for: ";
                cin>>desiredPhone;
                //displaying the array returned from method
                //(find by phonne) using for loop
                for(int i=0;i<booksize;i++)
                    {
                        if(r.findByPhone(desiredPhone)[i]==1)
                            cout<<"the number exists here: ";
                        else
                            cout<<"the number isn't here:  ";
                        cout<<*(r.findByPhone(desiredPhone)+i)<<endl;
                    }
            }
        break;
        case 4:
            {
                cout<<"enter the index of slots you need to check (starting from zero): ";
                cin>>entryIndex;
                // validating user's input using while loop
                while(!r.displayEntryAtIndex(entryIndex))
                {
                    cout<<"invalid index please reEnter: ";
                    cin>>entryIndex;
                }
            }
        break;
        case 5:
            {
                cout<<"enter the new name: ";
                cin.ignore();
                getline(cin,updatedName);
                cout<<"enter the index of the new name: ";
                cin>>updateIndex;
                //validating user's input using while loop
                while(!r.updateNameAt(updatedName,updateIndex))
                {
                    cout<<"invalid index please reEnter: ";
                    cin>>updateIndex;
                }
            }
        break;
        case 6:
            {
                cout<<"enter the new number: ";
                cin>>updatedNumber;
                cout<<"enter the index of the new number: ";
                cin>>updateIndex;
                while(!r.updatePhoneAt(updatedNumber,updateIndex))
                {
                    cout<<"please reEnter the new number: ";
                    cin>>updatedNumber;
                    cout<<"please reEnter the index of the new number: ";
                    cin>>updateIndex;
                }
            }
        break;
        case 7:
            {
                MyPhoneBook k(r);
                k.displayAll();
            }
        }
    }
    while(choice!=8);


    return 0;
}

//assigning value to the phone book size using constructor

MyPhoneBook::MyPhoneBook(int PBsize):phoneBookSize(PBsize)
{
    names=new string[phoneBookSize];
    phones=new string[phoneBookSize];
}

//copy constructor
MyPhoneBook::MyPhoneBook(const MyPhoneBook& obj)
{
    //copying the values and dynamically allocating the arrays
    phoneBookSize=obj.phoneBookSize;
    names=new string[phoneBookSize];
    phones=new string[phoneBookSize];

    for(int i=0;i<phoneBookSize;i++)
    {
        names[i]=obj.names[i];
        phones[i]=obj.phones[i];
    }
}
// function to add elements to arrays
//N stands for name and P stands for phone, to be added
bool MyPhoneBook::addEntry(string N,string P)
{
    bool status=false;
    int index;
    //declaring empty array to compare the data i could have
    //used just empty quotations
    string arr[1];
    if(P.length()==11)
    {
        status=true;
    }
    if (status)
    {
        for(int j=0;j<11;j++)
        {
            //checking that number is valid by looping over it
            //changing the string to int using ASCII table
            if(P[j]-48>=0 && P[j]-48<=9)
            {
                status=true;

            }
            else
            {
                status=false;
                break;
            }
        }
    }

    //looping over the array to find empty slot
    if(status)
    {
        for(index=0;index<phoneBookSize;index++)
        {
        //checking the empty slot using if
        //and assign the parameters to the desired slot
            if(names[index]==arr[0] && phones[index]==arr[0])
            {
                names[index]=N;
                phones[index]=P;
                status=true;
                break;
            }
            else
                status=false;
        }
    }
    return status;
}
bool MyPhoneBook::displayEntryAtIndex(int index)
{
    bool status;

    if(index>=phoneBookSize)
    {
        status=false;
    }
    /*remember to use stew for displaying aesthetic shape*/
    else
    {
        cout<<setw(15)<<names[index];
        cout<<setw(17)<<phones[index]<<endl;
        status=true;

    }
    return status;
}
//we will send binary array to the function (biarr)
void MyPhoneBook::displayEntryAtIndex(int*biarr)
{
    for(int i=0;i<phoneBookSize;i++)
    {
        if(biarr[i]==1)
        {
            cout<<setw(15)<<names[i];
            cout<<setw(17)<<phones[i]<<endl;

        }
    }
}
void MyPhoneBook::displayAll()
{
    for(int i=0;i<phoneBookSize;i++)
    {
        cout<<setw(15)<<names[i];
        cout<<setw(17)<<phones[i]<<endl;

    }
}
//trying to find if name exist
//from the whole name or just part of it without
// using find built-in function we taken in structured programming
int* MyPhoneBook::findbyName(string name)
{
    //variable to save the value returned from function find
    int found;
    //array(pointer to be returned)(p)
    int*p;
    p= new int[phoneBookSize];
    for(int i=0;i<phoneBookSize;i++)
    {
        p[i]=0;
    }
    for(int i=0;i<phoneBookSize;i++)
    {
        found=names[i].find(name);
        if(found!=-1)
            p[i]=1;
    }
    return p;
}
//trying to find if phone number exists
//using built in function (find)

int* MyPhoneBook::findByPhone(string number)
{
    int found;
    //array to be returned(p)
    int*p;
    p=new int[phoneBookSize];
    for(int i=0;i<phoneBookSize;i++)
    {
        p[i]=0;
    }

    for(int i=0;i<phoneBookSize;i++)
    {
        found=phones[i].find(number);
        if(found!= -1)
            p[i]=1;
    }
    return p;

}
//changing the name with the index(i)
//of slot of the array with new name(Nname)
bool MyPhoneBook::updateNameAt(string Nname,int ind)
{
    bool status=false;
    if(ind>=0 && ind<phoneBookSize)
    {
        names[ind]=Nname;
        status=true;
    }
    else
        status=false;
    return status;
}

//changing the name with the index(i)
//of slot of the array with new name(Nname)
bool MyPhoneBook::updatePhoneAt(string Nphone,int ind)
{
    bool status= false;
    if(Nphone.length()==11)
    {
        status=true;
    }
    else
    {
        status=false;
        cout<<"invalid number of digits\n";
    }
    if (status)
    {
        for(int j=0;j<11;j++)
        {
            //checking that number is valid by looping over it
            //changing the string to int using ASCII table
            if(Nphone[j]-48>=0 && Nphone[j]-48<=9)
            {
                status=true;

            }
            else
            {
                status=false;
                cout<<"you entered invalid phone number\n";
                break;
            }
        }
    }
    if(status)
    {
        if(ind>=0 && ind<phoneBookSize)
        {
            phones[ind]=Nphone;
            status=true;
        }
        else
        {
            status=false;
            cout<<"you entered wrong index\n";
        }
    }
    return status;

}
MyPhoneBook::~MyPhoneBook()
{
    delete [] names;
    delete [] phones;
}
