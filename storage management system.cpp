#include <iostream>
using namespace std;
//declaring item class

//////////////////////////////////////
//
//
//the code is a store system that takes
//input from user to add to the capacity of the
//store
//
//////////////////////////////////////


class Item
{
private:
    int ID,quantity,price;
    string name;
public:
    static int objectcount;
    Item();
    Item(string , int , int );
    Item(const Item &);
    void setName(string);
    void setQuantity(int);
    void setPrice(int);
    int getID();
    string getName();
    int getQuantity();
    int getPrice();
    static int getObjectcount();
    bool operator==(const Item&);
    void operator+=(const Item&);
    void operator-=(int q);
    friend ostream &operator<<(ostream& ,const Item&);
    friend istream &operator>>(istream&,Item&);


};
//declaring class seller
class Seller
{
private:
    string name;
    string Email;
    Item*items;
    int maxitem;
public:
    Seller(string="",string="",int=0);
    friend istream& operator>>(istream &, Seller&);

    friend ostream&operator<<(ostream &,Seller&);
    bool addItem( Item& );
    bool sellingItem(string,int);
    void printItems();
    Item findanItembyID(int);
    ~Seller();
    //copy constructor to copy the value of the seller's
    //name and Email and put it in another object
    Seller(const Seller& obj,int siz)
    {
        name=obj.name;
        Email=obj.Email;
        maxitem=siz;
        items=new Item[maxitem];
    }
};


int Item::objectcount=0;

int main()
{
    int maxNumberOfItems,choice,id,quant,pricei;
    string itemsname;
    //defining default cons
    Seller s;
    cin>>s;
    //name and email entered
    cout<<"please enter your store capacity: ";
    cin>>maxNumberOfItems;
    //initializing the object x that will be the store data
    Seller x(s,maxNumberOfItems);
    do
    {
        cout<<"Enter your choice\n";
        cout<<"1-Print my info\n";
        cout<<"2-Add An Item\n";
        cout<<"3-Sell An Item\n";
        cout<<"4-Print Items\n";
        cout<<"5-Find an Item by ID\n";
        cout<<"6-Exit\n";
        cout<<"Choice: ";
        cin>>choice;
        while(choice>6||choice<1)
        {
            cout<<"invalid please reEnter your choice: ";
            cin>>choice;
        }
        switch(choice)
        {
        case 1:
            {
                //displaying x object using the overloaded <<
                cout<<x;
            }
        break;
        case 2:
            {
                /*cout<<"Enter the item's name: ";
                cin>>itemsname;
                cout<<"Enter the item's quantity: ";
                cin>>quant;
                cout<<"Enter the item's price: ";
                cin>>pricei;*/
                //add and Item using Cin>>
                Item I;
                cin>>I;
                //putting the item in the array of items
                if(!x.addItem(I))
                {
                    cout<<"there is no space in your store\n";
                }
            }
        break;
        case 3:
            {

                // taking the name from user
                //to sell and item and taking its quantity
                string nome;
                int quan;
                cout<<"Enter the item's name: ";
                cin>>nome;
                cout<<"Enter the item's quan: ";
                cin>>quan;
                //input validating the item and quantity
                while(!x.sellingItem(nome,quan))
                {
                    cout<<"you entered invalid item or quantatity: "<<endl;
                    cout<<"reEnter the item's name: ";
                    cin>>nome;
                    cout<<"reEtner the item's quantity: ";
                    cin>>quan;
                }
            }
        break;
        case 4:
            {
                //print the array of items in x
                x.printItems();
            }
        break;
        case 5:
            {
                cout<<"Enter the ID you are searching for: ";
                cin>>id;
                x.findanItembyID(id);
            }
        }
    }
    while(choice!=6);




}


Item::Item()
{
    objectcount++;
    ID=objectcount;
    name="";
    quantity=0;
    price=0;
}
//initializing the objects members using constructor
// n stands for name and q stands for quantity , p stands for price
Item::Item(string n, int q, int p):quantity(q),price(p)
{
    name=n;
}

//copy constructor of Item class
Item::Item(const Item &obj)
{
    //see if you need to increment the static variable or not
    name=obj.name;
    quantity=obj.quantity;
    price=obj.price;
}
//setter for name
void Item::setName(string n)
{
    name=n;
}
//setter for quantity
void Item::setQuantity(int q)
{
    quantity=q;
}
//setter for price
void Item::setPrice(int p)
{
    price=p;
}
//notice we don't need setter for the id
//because it initialized automatically
//getting the id
int Item::getID()
{
    return ID;
}
//getting the name
string Item::getName()
{
    return name;
}
//getter function for the quantity
int Item::getQuantity()
{
    return quantity;
}
//getter function for the price
int Item::getPrice()
{
    return price;
}
//static function to get the static variable of class item
// which is object count
int Item::getObjectcount()
{
    return objectcount;
}
//overloading == operator to compare the names of
// an items
bool Item::operator==(const Item& Right)
{
    bool status=false;
    if(name==Right.name)
        status=true;
    return status;
}
//overloading the += operator to add value of
//quantity to the main obj's quantity
void Item::operator+=(const Item& Right)
{
    quantity+=Right.quantity;
}
//overloading the -= operator to subtract value
// from quantity
void Item::operator-=(int q)
{
    quantity-=q;
}


//overloading ostream operators in item class//

ostream &operator<<(ostream& extract,const Item&obj)
{
    extract<<"Name: "<<obj.name<<endl;
    extract<<"ID: "<<obj.ID<<endl;
    extract<<"quantity: "<<obj.quantity<<endl;
    extract<<"Price: "<<obj.price<<endl;
}
//////////////////////////////////////////////////
//overloading the istream operatorfor class item//
//////////////////////////////////////////////////

istream &operator>>(istream&ins,Item&obj)
{
    cout<<"Enter the item's name: ";
    ins>>obj.name;
    cout<<"Enter the item's quantity: ";
    ins>>obj.quantity;
    cout<<"Enter the item's price: ";
    ins>>obj.price;
}

//parametarized constructo for class seller
Seller::Seller(string n, string e,int s)
{
    name=n;
    Email=e;
    maxitem=s;
    items=new Item[maxitem];
}
/////////////////////////////////////////////
//overloading the is and os tream operators//
/////////////////////////////////////////////
ostream&operator<<(ostream &ext,Seller&obj)
{
    ext<<"seller's name is:  "<<obj.name<<endl;
    ext<<"seller's Email is: "<<obj.Email<<endl;
}
istream& operator>>(istream &ins, Seller&obj)
{
    cout<<"please enter your name: ";
    //using getline to enter the name
    getline(ins,obj.name);
    cout<<"please enter your Email: ";
    ins>>obj.Email;

}


bool Seller::addItem( Item& obj)
{
    bool status=false;
    for(int i=0;i<maxitem;i++)
    {
        if (items[i]==obj)
        {
            items[i]+=obj;
            status=true;
            break;
        }
    }
    if(!status)
    {
        for(int i=0;i<maxitem;i++)
        {
            if(items[i].getName()=="")
            {
                //used the setters and getters
                items[i].setName(obj.getName());
                items[i].setPrice(obj.getPrice());
                items[i].setQuantity(obj.getQuantity());
                status=true;
                break;
            }
        }
    }
    return status;
}
//n is stands for name and q stands for quantity
bool Seller::sellingItem(string n,int q)
{
    bool status=false;
    int i;
    for(i=0;i<maxitem;i++)
    {
        //looping over the items to find the requested item
        //checking if the name of the comdity to be sold is in the array
        //of items
        if(items[i].getName()==n)
        {
            status=true;
            break;
        }
    }
    //if the name is available then check if the quantity is vaild
    if(status)
    {
        if(items[i].getQuantity()>=q)
        {
            items[i]-=q;
        }
        else
            status=false;
    }
    //returning status if the name and quantity is vaild
    //it will be true
    return status;
}
void Seller::printItems()
{
    //looping over array of items and print it using << overloaded operator
    for(int i=0;i<maxitem;i++)
    {
        cout<<items[i]<<endl;
    }
}
//change the void to Item
Item Seller:: findanItembyID(int id)
{
    for(int i=0;i<maxitem;i++)
    {
        if(items[i].getID()==id)
        {
            //change the cout to return
            cout<<items[i];
            return items[i];
        }
    }
}
Seller::~Seller()
{
    delete []items;
}






