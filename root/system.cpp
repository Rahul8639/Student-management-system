#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std; 

// Initialising the class that stores data
class student
{
    int rollno;
    char name[20];
    int eng_marks, math_marks, sci_marks, cs_marks;
    double average;
    char grade;
    
    public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
}; 

// Calculating the average and grade
void student::calculate()
{
    average = (eng_marks + math_marks + sci_marks + cs_marks) / 4.0;
    if (average >= 90)
        grade = 'A';
    else if (average >= 75)
        grade = 'B';
    else if (average >= 50)
        grade = 'C';
    else
        grade = 'F';
}

// Getting the data from the user
void student::getdata()
{
    cout << "-----------------> REGISTER STUDENT DETAILS <-----------------" << endl;

    cout << "Enter student's roll number: ";
    cin >> rollno;
    
    cout << "Enter student's name: ";
    cin.ignore();
    cin.getline(name, 20);

    cout << "\n\nEnter Student's Marks (out of 100)" << endl;

    cout << "\n\nEnter marks in English: ";
    cin >> eng_marks;
    
    cout << "Enter marks in Math: ";
    cin >> math_marks;

    cout << "Enter marks in Science: ";
    cin >> sci_marks;
    
    cout << "Enter marks in Computer Science: ";
    cin >> cs_marks;
    calculate();
}

void student::showdata() const
{
    cout << "\nRoll number of student is: " << rollno;
    cout << "\nName of student is: " << name;
    cout << "\nEnglish marks is: " << eng_marks;
    cout << "\nMaths marks is: " << math_marks;
    cout << "\nScience marks is: " << sci_marks;
    cout << "\nComputer Science marks is: " << cs_marks;
    cout << "\nAverage Marks is: " << average;
    cout << "\nGrade of student is: " << grade;
}

int student::retrollno() const
{
    return rollno;
}

// Function declarations
void create_student();
void display_sp(int); // Display particular record of student
void display_all(); // Display all records of student
void delete_student(int); // Delete particular record of student
void change_student(int); // Edit particular record of student

int main()
{
    char ch;
    cout << setprecision(2) << fixed;
    
    do
    {
        int num;
        system("cls");
        cout << "Welcome to Student Registration Management System created by Rahul Prasad" << endl;
        cout << "\n-------------> SELECT MENU <-------------" << endl;
        cout << "\n1. Create a new student record" << endl;
        cout << "2. Search student record" << endl;
        cout << "3. Display all records" << endl;
        cout << "4. Delete student record" << endl;
        cout << "5. Modify student record" << endl;
        cout << "6. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> ch;
        
        system("cls");
            
        switch(ch)
        {
            case '1': create_student(); break;
            case '2': 
                cout << "\n\n\tEnter The roll number: "; 
                cin >> num;
                display_sp(num); 
                break;
            case '3': display_all(); break;
            case '4':     
                cout << "\n\n\tEnter The roll number: ";
                cin >> num;
                delete_student(num);
                break;
            case '5':     
                cout << "\n\n\tEnter The roll number: "; 
                cin >> num;
                change_student(num);
                break;
            case '6':     
                cout << "Exiting, Thank you!";
                exit(0);
        }
    
    } while(ch != '6');
    return 0;
}

// Creating the student record
void create_student()
{
    student stud;
    ofstream oFile("student.dat", ios::binary | ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char*>(&stud), sizeof(student));
    oFile.close();
    cout << "\nStudent's record has been created ";
    cin.ignore();
    cin.get();
}

// Displaying all the records of student
void display_all()
{
    student stud;
    ifstream inFile("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "No Record Found";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\n\n\t\t-----------------> DISPLAYING ALL RECORDS <-----------------\n\n";
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(student)))
    {
        stud.showdata();
        cout << "\n\n****************************************************\n";
    }

    inFile.close();
    cin.ignore();
    cin.get();
}

// Displaying the particular record of student
void display_sp(int n)
{
    student stud;
    ifstream iFile("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "No Record Found";
        cin.ignore();
        cin.get();
        return;
    }
    
    bool flag = false;
    while (iFile.read(reinterpret_cast<char*>(&stud), sizeof(student)))
    {
        if (stud.retrollno() == n)
        {
            stud.showdata();
            flag = true;
        }
    }
    
    iFile.close();
    if (!flag)
        cout << "\n\nRecord does not exist";
    cin.ignore();
    cin.get();
}

// Modifying the record of student
void change_student(int n)
{
    bool found = false;
    student stud;
    fstream fl("student.dat", ios::binary | ios::in | ios::out);
    if (!fl)
    {
        cout << "No Record Found";
        cin.ignore();
        cin.get();
        return;
    }
    
    while (!fl.eof() && !found)
    {
        fl.read(reinterpret_cast<char*>(&stud), sizeof(student));
        if (stud.retrollno() == n)
        {
            stud.showdata();
            cout << "\nEnter new student details:" << endl;
            stud.getdata();
            int pos = (-1) * static_cast<int>(sizeof(stud));
            fl.seekp(pos, ios::cur);
            fl.write(reinterpret_cast<char*>(&stud), sizeof(student));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    
    fl.close();
    if (!found)
        cout << "\n\n Record Not Found ";
    cin.ignore();
    cin.get();
}

// Deleting the record of student
void delete_student(int n)
{
    student stud;
    ifstream iFile("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "No Record Found";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile("Temp.dat", ios::out);
    iFile.seekg(0, ios::beg);
    while (iFile.read(reinterpret_cast<char*>(&stud), sizeof(student)))
    {
        if (stud.retrollno() != n)
        {
            oFile.write(reinterpret_cast<char*>(&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}