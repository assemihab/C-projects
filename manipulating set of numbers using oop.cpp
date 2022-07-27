#include <iostream>

using namespace std;

const int noOfElement=100;
//declaring class to store the sets
class IntegerSet
{

private:
    int Set[noOfElement];
public:
    //default constructor initializing all elements by zero
    IntegerSet()
    {
        for(int i=0;i<noOfElement;i++)
        {
            Set[i]=0;
        }
    }
    //method that return IntegerSet object which contain elements of two sets(union of them)
    IntegerSet unionOfSets(IntegerSet& obj)
    {
        IntegerSet temp;
        for(int i=0;i<noOfElement;i++)
        {
            if(Set[i]==1||obj.Set[i]==1)
                temp.Set[i]=1;
        }
        return temp;
    }
    //method that return IntegerSet object which
    //contain the common elements of two sets(intersection of them)
    IntegerSet intersectionOfSets (IntegerSet& obj)
    {
        IntegerSet temp;
        for(int i=0;i<noOfElement;i++)
        {
            if(Set[i]==1&& obj.Set[i]==1)
                temp.Set[i]=1;
        }
        return temp;
    }
    void insertElement (int k)
    {
        Set[k]=1;
    }
    void deleteElement (int m)
    {
        Set[m]=0;
    }
    //method that prints all elements in the object(set) called with
    void printSet ()
    {
        for (int j=0;j<noOfElement;j++)
        {
            cout<<' ';
            if(Set[j])
                cout<<j;
            else
                cout<<"---";
            if(!((j+1)%25))
                cout<<endl;
        }
            cout<<endl;
    }
    //method that compare if two sets are equal or not
    bool isEqualTo(IntegerSet& obj)
    {
        for(int i=0;i<noOfElement;i++)
        {
            if(Set[i]!=obj.Set[i])
                return false;
        }
        return true;
    }
    //constructor that initializes elements in the set using array
    IntegerSet(int arr[],int Size)
    {
        for(int i=0;i<Size;i++)
            Set[i]=1;
        for(int i=Size;i<noOfElement;i++)
            Set[i]=0;
    }
    //operator that subtract the elements of two sets from each other
    IntegerSet operator-(IntegerSet& obj)
    {
        IntegerSet temp;
        for(int i=0;i<noOfElement;i++)
        {
            temp.Set[i]=Set[i]-obj.Set[i];
            if(temp.Set[i]<0)
                temp.Set[i]=0;
        }
        return temp;
    }
    //operator that return the complement of a set
    IntegerSet operator!()
    {
        IntegerSet temp;
        for(int i=0;i<noOfElement;i++)
            temp.Set[i]=!Set[i];
        return temp;
    }
};

int main()
{
    int halfArr[50];
    bool status=true;
    IntegerSet setEven, setOdd, fullSet,emptySet;
    IntegerSet twoElementSet,halfEvenOddSet;
    IntegerSet halfOddSet,halfEvenFullSet;
    //inseting even and odd numbers to two sets
    for(int i=0;i<noOfElement;i++)
    {
        if(status)
        {
            setEven.insertElement(i);
            if(i<50)
                {
                    halfArr[i]=1;
                    halfEvenOddSet.insertElement(i);
                }
        }
        if(!status)
        {
            setOdd.insertElement(i);
            if(i>50)
                halfEvenOddSet.insertElement(i);
        }
        status=!status;
        if(i<2)
            twoElementSet.insertElement(i);

    }
    cout<<"testing the insertion method and printing method by \n"<<
          "printing a sets with even, odd elements respectevly: \n";

    setEven.printSet();
    setOdd.printSet();
    cout<<"testing the union method on the even and odd sets so we \n"
        <<"we should get a set with all elements initialized in it:\n";

    fullSet=setEven.unionOfSets(setOdd);
    fullSet.printSet();
    cout<<"testing the intersection method will result in empty set:\n";

    emptySet=setEven.intersectionOfSets(setOdd);
    emptySet.printSet();
    twoElementSet.printSet();
deleteElement:
    cout<<"enter the index of the element you want to delete from the set above until it's empty: ";

    int index;
    cin>>index;
    twoElementSet.deleteElement(index);
    twoElementSet.printSet();
    if(!emptySet.isEqualTo(twoElementSet))
        goto deleteElement;
    cout<<"testing the delete method and the equality method on the above sets\n"
        <<"by modify two element set until it's empty so the code can complete execution\n\n";

    cout<<"testing the constructor to see if it would\n"
        <<" accept the input to the set as array or not:\n";

    IntegerSet halfSet(halfArr,50);
    halfSet.printSet();
    cout<<"testing the subtraction operator on the set:\n";

    halfOddSet=setOdd-halfEvenOddSet;
    halfOddSet.printSet();
    cout<<"testing the complement operator on the set above:\n";

    halfEvenFullSet=!halfOddSet;
    halfEvenFullSet.printSet();
    return 0;
}
