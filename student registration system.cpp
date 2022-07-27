#include <iostream>
#include <fstream>
using namespace std;

//the class stores data
class Student
{
private:
    int rollNo;
    char name[50];
    int OOP_mark,mathMark,sci_mark,net_mark;
    float average;
    char grade;
public:
    void calculateAVG()
    {
        average=(OOP_mark+mathMark+sci_mark+net_mark)/4;
        if(average>90)
        grade='A';
        else if(average>75)
        grade='B';
        else if(average>50)
        grade='C';
        else
        grade='F';
    }
    void setdata()
    {
        cout<<"enter student rollno: ";
        cin>>rollNo;
        cout<<"enter student name: ";
        cin.ignore();
        cin.getline(name,50,'\n');
        cout<<"all marks should be out of 100\n";
        cout<<"enter the oop mark: ";
        cin>>OOP_mark;
        cout<<"enter the mathMark: ";
        cin>>mathMark;
        cout<<"enter the science mark: ";
        cin>>sci_mark;
        cout<<"enter the networks mark: ";
        cin>>net_mark;
        calculateAVG();
    }
    void showData()const
    {
        cout<<"\nRoll number of student : "<<rollNo;
        cout<<"\nName of student : "<<name;
        cout<<"\nMaths : "<<mathMark;
        cout<<"\nScience : "<<sci_mark;
        cout<<"\nComputer Science :"<<OOP_mark;
        cout<<"\nNetwork: "<<net_mark;
        cout<<"\nAverage Marks :"<<average;
        cout<<"\nGrade of student is :"<<grade;
    }
    int retRollNO()
    {
        return rollNo;
    }
};
void create_student();
void display_sp(int);
void display_all();
void delete_student(int);
void change_student(int);
void delete_all();


int main()
{
int anynumber;
    int enrollNO;
    Student stud;
    char choice;
    do
    {
        cout<<"\nPress 1 to add student";
        cout<<"\nPress 2 to display specific student";
        cout<<"\nPress 3 to display all students";
        cout<<"\nPress 4 to delete student";
        cout<<"\nPress 5 to change student";
        cout<<"\nPress 6 to delete all content";
        cout<<"\nPress 7 to exit";
        cout<<"\nYour choice: ";
        cin>>choice;
        switch(choice)
        {
            case '1':create_student();
            break;
            case '2':
                {
                    cout<<"\nEnter the ID of the student: ";
                    cin>>enrollNO;
                    display_sp(enrollNO);
                }
            break;
            case '3':display_all();
            break;
            case '4':
                {
                    cout<<"\nEnter the ID of the student: ";
                    cin>>enrollNO;
                    delete_student(enrollNO);
                }
            break;
            case '5':
                {
                    cout<<"\nEnter the ID of the student: ";
                    cin>>enrollNO;
                    change_student(enrollNO);
                }
            break;
            case '6':delete_all();
            break;
            case '7':cout<<"exitingggg";exit(0);
            default:cout<<"reEnter your choice: ";
            break;
        }
    }
    while(choice!='7');

    return 0;
}
void create_student()
{
    Student stud;
    ofstream ofile("student.dat",ios::binary|ios::app);
    stud.setdata();
    ofile.write(reinterpret_cast<const char*>(&stud),sizeof(Student));
    ofile.close();
}
void display_sp(int rollN)
{
    Student stud;
    bool found=false;
    ifstream ifile("student.dat",ios::binary);
    if(ifile.fail())
    {
        cout<<"\n this file is failed to open: ";
        return;
    }
    while(!ifile.eof())
    {
        //try to remove the char after ending
        ifile.read(reinterpret_cast<char*>(&stud),sizeof(Student));
        if(stud.retRollNO()==rollN)
        {
            stud.showData();
            found=true;
            break;
        }
    }
    if(!found)
    {
        cout<<"\nThis student is not registered: ";
    }
    ifile.close();
}
void display_all()
{
    Student stud;
    ifstream ifile("student.dat",ios::binary);
    ifile.read(reinterpret_cast<char*>(&stud),sizeof(Student));
    while(!ifile.eof())
    {
        stud.showData();
        ifile.read(reinterpret_cast<char*>(&stud),sizeof(Student));
    }
    ifile.close();
}
void delete_student(int rollN)
{
    bool found=false;
    Student stud;
    ofstream ofile("temp.dat",ios::binary);
    ifstream ifile("student.dat",ios::binary);
    while(ifile.read(reinterpret_cast<char*>(&stud),sizeof(Student)))
    {

        if(rollN==stud.retRollNO())
        {
            found=true;
            continue;
        }
        ofile.write(reinterpret_cast<const char*>(&stud),sizeof(Student));
    }
    if(!found)
    {
        cout<<"\nThis student is not registered";
    }
    ifile.close();
    ofile.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
}
void change_student(int rollN)
{
    bool found=false;
    Student stud;
    int pos=(-1)*static_cast<int>(sizeof(Student));
    fstream file("student.dat",ios::in|ios::out|ios::binary);
    while(!file.eof())
    {
        file.read(reinterpret_cast<char*>(&stud),sizeof(Student));
        if(rollN==stud.retRollNO())
        {
            //try to change this to seekg
            file.seekp(pos,ios::cur);
            stud.setdata();
            file.write(reinterpret_cast<char*>(&stud),sizeof(Student));
            found=true;
            break;
        }
    }
    if(!found)
    {
        cout<<"\nThis student is not registered";
    }
    file.close();
}
void delete_all()
{
    fstream dfile("student.dat",ios::out|ios::trunc);
    dfile.close();
}
