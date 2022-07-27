#include <iostream>
#include <cmath>
//#include "Node.h>
using namespace std;

template<class T>
class Node
{
    T info;
    Node* next;
public:
    Node (T value, Node*n=0):info(value),next(n){}
    Node*getNext()
    {
        return next;
    }
    void setNext(Node*n)
    {
        next=n;
    }
    T getInfo()
    {
        return info;
    }
    void setInfo(T value)
    {
        info= value;
    }
};

template <class T>
class SLL
{
    Node<T>*head,*tail;
public:
    SLL()
    {
        head=tail=0;
    }
    void addToHead(T value)
    {
        Node<T>*new_node=new Node<T>(value,head);
        head=new_node;
        if(tail==0)
            tail=head;
    }
    void addToTail(T value)
    {
        Node<T>*new_node=new Node<T>(value);
        if(tail==0)
            {
                addToHead(value);
                return;
            }
        tail->setNext(new_node);
        tail=tail->getNext();
    }
    T removeFromHead()
    {
        T value=head->getInfo();
        if(head==tail)
        {
            delete head;
            head=tail=0;
            return value;
        }
        Node<T>*ptrToHead=head;
        head=head->getNext();
        delete ptrToHead;
        return value;
    }
    T removeFromTail()
    {
        if(head==tail)
        {
            T value =removeFromHead();
            return value;
        }
        Node<T>*traversePtr=head;
        while(traversePtr->getNext()!=tail)
            {
                traversePtr=traversePtr->getNext();
            }
        T value=tail->getInfo();
        delete tail;
        tail=traversePtr;
        tail->setNext(0);
        return value;
    }
    T getValueAtHead()
    {
        return head->getInfo();
    }
    bool isEmpty()
    {
        return head==0;
    }
    void clear()
    {
        Node<T>*deletingPtr;
        while(head!=0)
        {
            deletingPtr=head;
            head=head->getNext();
            delete deletingPtr;
        }
    }
    template<class T1>
    friend ostream&operator<<(ostream&,const SLL<T1>&);
};
template<class T>
ostream&operator<<(ostream& insertion,const SLL<T>&sll)
{
    Node<T>*traverse=sll.head;
    while(traverse!=0)
    {
        insertion<<traverse->getInfo()<<"\t";
        traverse=traverse->getNext();
    }
    return insertion;
}

template<class T>
class StackSLL
{
    SLL<T> Stack;
public:
    void push(T elem)
    {
        Stack.addToHead(elem);
    }
    T pop()
    {
        return Stack.removeFromHead();
    }
    T top()
    {
        return Stack.getValueAtHead();
    }
    bool isEmpty()
    {
        return Stack.isEmpty();
    }
    void clear()
    {
        Stack.clear();
    }
};
template<class T>
class QueueSLL
{
    SLL<T>Queue;
public:
    void enqueue(T value)
    {
        Queue.addToTail(value);
    }
    T dequeue()
    {
        return Queue.removeFromHead();
    }
    T Front()
    {
        return Queue.getValueAtHead();
    }
    bool isEmpty()
    {
        return Queue.isEmpty();
    }
    void clear()
    {
        Queue.clear();
    }

};

bool comparingDelimiters(char c, StackSLL<char>&st)
{
        if(st.isEmpty())
        {
            return false;
        }
        char openDelimiter=st.pop();
        if(openDelimiter!=c)
        {
            return false;
        }
        return true;
}
bool chkBalanced(string str)
{
    char openDelimiter;
    bool Balanced=true;
    StackSLL<char> S;
    for(int i=0;str[i]!='\0';i++)
    {
        char c=str[i];
        if(c=='{'||c=='<'||c=='['||c=='(')
            {
                S.push(c);
            }
        switch(c)
        {
        case '}':
            {
                if(!comparingDelimiters('{',S))
                    return false;
            }
        break;
        case '>':
            {
                if(!comparingDelimiters('<',S))
                    return false;
            }
        break;
        case ']':
            {
                if(!comparingDelimiters('[',S))
                    return false;
            }
        break;
        case')' :
            {
                if(!comparingDelimiters('(',S))
                    return false;
            }
        break;
        }

    }
    if(!S.isEmpty())
    {
        Balanced=false;
    }
    return Balanced;
}
string convertToBinary(int number)
{
    StackSLL<char>S;
    string result;
    while(number!=0)
    {

        S.push((number%2)+48);
        number/=2;
    }
    while(!S.isEmpty())
    {
        result+=S.pop();

    }
    return result;
}

bool isPrior(char k,char h)
{
    int precedence1,precedence2;
    if (k == '^')
        precedence1= 3;
    else if (k == '/' || k == '*')
        precedence1= 2;
    else if (k == '+' || k == '-')
        precedence1= 1;
    else
        precedence1= -1;
    if (h == '^')
        precedence2= 3;
    else if (h == '/' || h == '*')
        precedence2= 2;
    else if (h == '+' || h == '-')
        precedence2= 1;
    //if there is closed parenthesis we assume that it has very low precedence
    else
        precedence2= -1;
    //the power is evaluated from right to left 2^3^2 will be 2^9 which will be 512 not 8^2 which will be 64
    if(precedence2==3&&precedence1==3)
        return false;
    return precedence1<=precedence2;
}
string convertInfixToPostfix(string str)
{
    string result;
    StackSLL<char>S;
    for(int i=0;str[i]!='\0';i++)
    {
        char c=str[i];
        if(c==' ')
            continue;
        if((c>'a'&&c<'z')||(c>'A'&&c<'Z')||(c>'0'&&c<'9'))
            result+=c;
        else if(c=='(')
        {
            S.push(c);
        }
        else if(c==')')
        {
            char k=S.pop();
            while (k!='(')
            {
                result+=k;
                k=S.pop();
            }
        }
        else
        {
            while(!S.isEmpty()&&isPrior(c,S.top()))
            {
                result+=S.pop();
            }
            S.push(c);
        }
    }
    while(!S.isEmpty())
    {
        result+=S.pop();
    }
    return result;
}

int evaluatePostfix(string str)
{
    int first,second;
    StackSLL<int>s;
    for(int i=0;i<str.length();i++)
    {

        char c=str[i];
        if(c>='0'&&c<='9')
        {
            s.push(c-48);
        }
        else if((c>='*'&&c<='/')||c=='^')
        {
            first=s.pop();
            second=s.pop();
            switch(c)
            {
                case '*': s.push((first*second));
                break;
                case '/': s.push((second/first));
                break;
                case '+': s.push((first+second));
                break;
                case '-': s.push((first-second));
                break;
                case '^': s.push(pow(second,first));
                break;
            }
        }
        else
            return false;
    }
    return s.pop();
}
template<class T>
void movingElemFromQtoAnother(QueueSLL<T>&Q1,QueueSLL<T>&Q2)
{
    while(!Q1.isEmpty())
        Q2.enqueue(Q1.dequeue());
}
template<class T>
bool moveNthElem(QueueSLL<T>&Q,int n)
{
    QueueSLL<T> Q2;
    for(int i=1;i<n;i++)
    {
        if(Q.isEmpty())
        {
            movingElemFromQtoAnother(Q2,Q);
            return false;
        }
        Q2.enqueue(Q.dequeue());
    }
    if(Q.isEmpty())
    {
        movingElemFromQtoAnother(Q2,Q);
        return false;
    }
    T value=Q.dequeue();
    movingElemFromQtoAnother(Q,Q2);
    Q.enqueue(value);
    movingElemFromQtoAnother(Q2,Q);
    return true;
}
template<class T>
void reverseQueue(QueueSLL<T> &Q)
{
    StackSLL<T>s;
    while(!Q.isEmpty())
    {
        s.push(Q.dequeue());
    }
    while(!s.isEmpty())
    {
        Q.enqueue(s.pop());
    }
}

int main()
{

    char choice;
    string userEntry,output;
    int userEntryNum,position;
    double userEntrydoube;
    do
    {
    system("cls");
        cout<<"\n1- Check for balanced brackets.";
        cout<<"\n2- Convert to binary.";
        cout<<"\n3- Convert infix to postfix expression and evaluate.";
        cout<<"\n4- Move Nth element to front in a queue of strings.";
        cout<<"\n5- Reverse elements of a queue of doubles.";
        cout<<"\nEnter your choice: ";
invalidchoice:
        cin>>choice;
        switch(choice)
        {
        case '1':
            {
                cout<<"\nEnter the expression you want to test: ";
                cin.ignore();
                getline(cin, userEntry);
                if(chkBalanced(userEntry))
                    cout<<"\nThe expression is balanced\n";
                else
                    cout<<"\nThe expression is not balanced\n";
            }
        break;
        case '2':
            {
                cout<<"\nEnter the decimal number you want to convert: ";
                while(!(cin>>userEntryNum))
                {
                        cout<<"\nEnter a valid number: ";
                        cin.clear();
                        cin.ignore(1000000,'\n');
                }
                output=convertToBinary(userEntryNum);
                cout<<endl<<output;

            }
        break;
        case '3':
            {
                cout<<"\nEnter the infix expression: ";
                cin.ignore();
                getline(cin,userEntry);
                output=convertInfixToPostfix(userEntry);
                cout<<endl<<"Output: "<<output;
                cout<<"\nResult: "<<evaluatePostfix(output);
            }
        break;
        case '4':
            {
                QueueSLL<string>Q1;
                string condition;
                int counter=0;
                while(!(condition=="Exit"||condition=="exit"))
                {
                    cin.ignore();
                    cout<<"\nEnter the "<<counter+1<<" value: ";
                    getline(cin,userEntry);
                    Q1.enqueue(userEntry);
                    cout<<"\nPress any key to continue or write exit to Stop: ";
                    cin>>condition;
                    counter ++;
                }
                cout<<"\nEnter the position of the element you want to move"
                    <<"\nTo the front of the queue: ";

                while(!(cin>>position))
                {
                    cin.clear();
                    cin.ignore(100000000,'\n');
                    cout<<"\nEnter an integer position: ";
                }
                while(!moveNthElem(Q1,position))
                {
                    cout<<"\nThe position you have entered is out of range "
                        <<"\nReEnter the position you need to move to the front: ";
                    cin>>position;
                }
                cout<<"\nNewly ordered Queue: ";
                while(!Q1.isEmpty())
                {
                    cout<<Q1.dequeue()<<"  ";
                }
            }
        break;
        case '5':
            {
                QueueSLL<double>Q1;
                cout<<"\nEnter the queue elements and to stop press on any letter: ";

                while(cin>>userEntrydoube)
                {
                    Q1.enqueue(userEntrydoube);
                    cout<<"\nEnter the next value or Enter any letter to stop: ";
                }
                cin.clear();
                cin.ignore(100000000,'\n');
                reverseQueue(Q1);
                cout<<"\nReversed Queue elements : ";
                while(!Q1.isEmpty())
                {
                    cout<<Q1.dequeue()<<"  ";
                }

            }
        break;
        default:cout<<"\nReEnter your choice: ";cin.ignore(10000000,'\n');goto invalidchoice;
        }
    system("pause");
    cin>>choice;
    if(choice=='6')
        exit(0);
    else
        continue;


    system("cls");
    }
    while(choice!='6');
    return 0;
}
