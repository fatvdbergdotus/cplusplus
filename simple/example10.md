# Simple example

## Library string functionality
```cpp
// STLString - demonstrates just a few of the features
//             
of the string class which is part of the
//             
Standard Template Library
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
// removeSpaces - remove any spaces within a string
string removeSpaces(const string& source)
{
    // make a copy of the source string so that we don't
    // modify it
    string s = source;
    // find the offset of the first space;
    // search the string until no more spaces found
    size_t offset;
    while((offset = s.find(" ")) != string::npos)
    {
        // remove the space just discovered
        s.erase(offset, 1);
    }
    return s;
}
// insertPhrase - insert a phrase in the position of
//                <ip> for insertion point
string insertPhrase(const string& source)
{
    string s = source;
    size_t offset = s.find("<ip>");
    if (offset != string::npos)
    {
        s.erase(offset, 4);
        s.insert(offset, "Randall");
    }
    return s;
}
int main(int argc, char* pArgs[])
{
    // create a string that is the sum of two strings
    cout << "string1 + string2 = "
         << (string("string 1") + string("string 2"))
         << endl;
    // create a test string and then remove all spaces
    // from it using simple string methods
    string s2("This is a test string");
    cout << "<" << s2 << "> minus spaces = <"
         << removeSpaces(s2) << ">" << endl;
    // insert a phrase within the middle of an existing
    // sentence (at the location of "<ip>")
    string s3 = "Stephen <ip> Davis";
    cout << s3 + " -> " + insertPhrase(s3) << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/*
    string1 + string2 = string1string2
    <this is a test string> minus spaces = <thisisateststring>
    Stephen <ip> Davis -> Stephen Randall Davis
    Press Enter to continue...
*/
```

## Sort a list
```cpp
// STLListStudents - use a list to contain and sort a
//                   
user defined class
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
using namespace std;
// Student - some example user defined class
class Student
{
public:
Student(const char* pszS, int id) : sName(pszS), ssID(id) {}
string sName;
int ssID;
};
// the following function is required to support the
// sort operation
bool operator<(const Student& s1, const Student& s2)
{
    return s1.ssID < s2.ssID;
}
// displayStudents - iterate through the list displaying
//                   
each element
void displayStudents(list<Student>& students)
{
// allocate an iterator that points to the first
// element in the list
    // list<Student>::iterator iter = students.begin();
    auto iter = students.begin();
    // continue to loop through the list until the
    // iterator hits the end of the list
    while(iter != students.end())
    {
        // retrieve the Student the iterator points at
        Student& s = *iter;
        cout << s.ssID << " - " << s.sName << endl;
        // now move the iterator over to the next element
        // in the list
        iter++;
    }
}
int main(int argc, char* pArgs[])
{
    // define a collection of students
    list<Student> students;
    // add three student objects to the list
    students.push_back(Student("Marion Haste", 10));
    students.push_back(Student("Dewie Cheatum", 5));
    students.push_back(Student("Stew Dent", 15));
    // display the list
    cout << "The original list:" << endl;
    displayStudents(students);
    // now sort the list and redisplay
    students.sort();
    cout << "\nThe sorted list:" << endl;
    displayStudents(students);
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT
The original list:
10 - Marion Haste
5 - Dewie Cheatum
15 - Stew Dent
The sorted list:
5 - Dewie Cheatum
10 - Marion Haste
15 - Stew Dent
Press Enter to continue...
*/
```

## Hacker proof: Buffer overflow
```cpp
// BufferOverflow - this program demonstrates how a 
//                  program that reads data into a fixed 
//                  length buffer without checking can be
//                  hacked
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
// getString - read a string of input from the user prompt
//             and return it to the caller
char* getString(istream& cin)
{
    char buffer[64];
    // now input a string from the file
    char* pB;
    for(pB = buffer;*pB = cin.get(); pB++)
    {
        if (cin.eof())
        {
            break;
        }
    }
    *pB = '\0';
    // return a copy of the string to the caller
    pB = new char[strlen(buffer) + 1];
    strcpy(pB, buffer);
    return pB;
}
int main(int argc, char* pArgv[])
{
    // get the name of the file to read
    cout <<"This program reads input from an input file\n"
           "Enter the name of the file:";
    string sName;
    cin >> sName;
    // open the file
    ifstream c(sName.c_str());
    if (!c)
    {
        cout << "\nError opening input file" << endl;
        exit(-1);
    }
    // read the file's content into a string
    char* pB = getString(c);
    // output what we got
    cout << "\nWe successfully read in:\n" << pB << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    printf("Done!");
    exit(0);
    return 0;
}

/* POSSIBLE OUTPUT:
This program reads input from an input file
Enter the name of the file:OK_File.txt
We successfully read in:
This is benign input.
Press Enter to continue..
*/
```
