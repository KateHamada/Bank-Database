/******************************************************************/
//  NAME:        Kate Hamada
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 15, 2025
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This contains the methods/constructors from the llist class.
//
/****************************************************************/

#include <iostream>
#include <ostream>
#include <fstream>
#include <cstring>
#include "llist.h"
#include "record.h"

using namespace std;

/******************************************************************/
//  Function name: llist
//
//  DESCRIPTION:   This is the default constructor for llist.
//
//  Parameters:    N/A
//                 
//  Return values:  N/A
//
/****************************************************************/
llist::llist()
{
    strcpy(filename, "testfile.txt");
    start = NULL;
    readfile();
}

/******************************************************************/
//  Function name: llist
//
//  DESCRIPTION:   This is a constructor for llist with parameter.
//
//  Parameters:    given_name (char[]) : An array of the name of a file
//
//  Return values:  N/A
//
/****************************************************************/
llist::llist(char given_name[])
{
     strcpy(filename, given_name);
     start = NULL;
     readfile(); 
}

/******************************************************************/
//  Function name: ~llist
//  
//  DESCRIPTION:   This is the deconstructor for llist.
//
//  Parameters:    N/A
//
//  Return values:  N/A
//
/****************************************************************/
llist::~llist()
{
    writefile();
    cleanup();
}

/******************************************************************/
//  Function name: llist
//
//  DESCRIPTION:   This method...
//                 to manage their customer's information.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : The function ended
// 
/****************************************************************/
llist::llist(const llist& other)
{
    start = NULL;
    strcpy(filename, other.filename);
    record* current = other.start;
  
    while (current != NULL)
    {
        addRecord(current->accountno, current->name, current->address);
        current = current->next;
    }
}

/******************************************************************/
//  Function name: operator=
//
//  DESCRIPTION:   This method overloads the assignment (=) operator 
//                 so that it can set a llist to another llist.
//
//  Parameters:    other (const llist&) : Reference to the llist
//                                        being copied to a different
//                                        llist.
//
//  Return values: llist& : A reference to the llist being copied.
//  
/****************************************************************/
llist& llist::operator=(const llist& other)
{
    // avoid self assignment
    if (this != &other)
    {
        // prevent memory leak incase the one being assigned the llist already has a linked list that you'd need to get rid of
        cleanup();

        strcpy(filename, other.filename);
        record* current = other.start;
        while (current != NULL)
        {
            addRecord(current->accountno, current->name, current->address);
            current = current->next;
        }   
    }
    return *this;
}

/******************************************************************/
//  Function name: operator<<
//
//  DESCRIPTION:   This method overloads the << operator which prints
//                 all of the records from the linked list.
//
//  Parameters:    os (ostream&) : A reference of ostream (output 
//                                 stream) to be able to print for 
//                                 the llist object.
//
//                 list (const llist&) : A reference of the list of 
//                                       records being printed.
//
//  Return values:  ostream& : A refernce of ostream to allow
//                             chaining of << operator
//  
/****************************************************************/
ostream& operator<<(ostream& os, const llist& list)
{
    record* current = list.start;

    if (current == NULL)
    {
        os << "\nThere are no records" << endl;
    }

    while (current != NULL)
    {
        os << "\nAccount Number: " << current->accountno << endl;
        os << "Account Holder Name: " << current->name << endl;
        os << "Holder's Address: " << current->address << endl;
        current = current->next;
    }

    return os;
}

/******************************************************************/
//  Function name: cleanup
//
//  DESCRIPTION:   This method deallocates the records from the 
//                 linked list to prevent memory leaks.
//  
//  Parameters:    N/A
//
//  Return values:  N/A
//
/****************************************************************/
void llist::cleanup()
{
    struct record* temp;
    while (start != NULL)
    {
        temp = start;
        start = start->next;
        delete temp;
    }
}

/******************************************************************/
//  Function name: readfile
//
//  DESCRIPTION:   This function reads the file and takes the info
//                 and creates records from it.
//
//  Parameters:    N/A
//
//  Return values:  0 : The file was able to be opened/read.
//                 -1 : The file wasn't able to be opened.
//  
/****************************************************************/
int llist::readfile()
{
    ifstream infile(filename);
    int acc_num;
    string name;
    string address;
    
    if (!infile)
    {
        #ifdef DEBUG
        cout << "---Error could not open file in readmode---" << endl;
        #endif
        return -1;
    }

    while (infile >> acc_num)
    {
        infile.ignore();
        getline(infile, name);
        getline(infile, address);
        this->addRecord(acc_num, (char*)name.c_str(), (char*)address.c_str());           
    }

    infile.close();
    return 0; 
}

/******************************************************************/
//  Function name: writefile
//
//  DESCRIPTION:   This function writes in the file the info from
//                 the records list. 
//
//  Parameters:    N/A
//
//  Return values:  0 : The file was able to be opened/written.
//                 -1 : The file wasn't able to be opened.
//
/****************************************************************/
int llist::writefile()
{
    ofstream outfile(filename);
    struct record *current = start;
    
    if (!outfile)
    {
        #ifdef DEBUG
        cout << "---Error couldn't open file in write mode---" << endl;
        #endif 
        return -1;
    }

    while (current != NULL)
    {
        outfile << current->accountno << endl;
        outfile << current->name << endl;
        outfile << current->address << endl;
        current = current->next;
    }

    outfile.close();
    return 0;
}

/******************************************************************/
//  Function name: addRecord
//
//  DESCRIPTION:   This method adds a record to the linked list 
//                 from the given parameters.
//
//  Parameters:    acc_num (int) : The account number.
//                 name (char[]) : An array of characters of the
//                                 account holder's name.
//                 address (char[]) : An array of characters of the
//                                    holder's address.
//
//  Return values:  0 : The method was able to add the record.
//                 -1 : The given account number is a duplicate
//                      and so won't add the record.
//
/****************************************************************/
int llist::addRecord(int acc_num, char name[], char address[])
{
     struct record* current = start;
     struct record* previous = NULL;

     // if the list of records is empty
     if (current == NULL)
     {
         record* temp = new record;
         temp->accountno = acc_num;
         strcpy(temp->name, name);
         strcpy(temp->address, address);
         temp->next = current;
         start = temp;
         return 0;
     }
     
     while (current != NULL && current->accountno < acc_num)
     {
         previous = current;
         current = current->next;
     }

     // if the account number already exists
     if (current != NULL && current ->accountno == acc_num)
     {
         cout << "The account number you entered already exists, account won't be added." << endl;
         #ifdef DEBUG
         cout << "\n\n****Debug Function Info****";
         cout << "\nFunction name: addRecord";
         cout << "\nParameters passed: acc_num = " << acc_num << " name = " << name << " and address = " << address;
         cout << "\nReturn value : -1" << endl;
         #endif
         return -1;
     }

     struct record* temp = new record;
     temp->accountno = acc_num;
     strcpy(temp->name, name);
     strcpy(temp->address, address);
     temp->next = current;

     // account number is smaller than the start record
     if (previous == NULL)
     {
         start = temp;
         #ifdef DEBUG
         cout << "\n\n****Debug Function Info****";
         cout << "\nFunction name: addRecord";
         cout << "\nParameters passed: acc_num = " << acc_num << " name = " << name << " and address = " << address;
         cout << "\nReturn value : 0" << endl;
         #endif
         return 0;
     }
     else
     {
         previous->next = temp;
         #ifdef DEBUG
         cout << "\n\n****Debug Function Info****";
         cout << "\nFunction name: addRecord";
         cout << "\nParameters passed: acc_num = " << acc_num << " name = " << name << " and address = " << address;
         cout << "\nReturn value : 0" << endl;
         #endif

         return 0;
     }
}


/******************************************************************/
//  Function name: findRecord
//
//  DESCRIPTION:   This method finds the account in records given
//                 an account number.
//
//  Parameters:    acc_num (int) : The given account number.
//
//  Return values:  0 : The account was found.
//                 -1 : The account wasn't found or doesn't exist.
//  
/****************************************************************/
int llist::findRecord(int acc_num)
{
    struct record *current = start;
    if (start == NULL)
    {
        return -1;
    }
   
    while (current != NULL)
    {
        if (current->accountno == acc_num)
        {
            cout << "\n***Success Account Found***" << endl;
            cout << "\nAccount Number: " << current->accountno << endl;
            cout << "\nAccount Holder Name: " << current->name << endl;
            cout << "\nHolder's Address: " << current->address << endl;
            return 0;
        }
        else
        {
            current = current->next;
        }
    }
    return -1;
}


/******************************************************************/
//  Function name: printAllRecords
//
//  DESCRIPTION:   This method prints all of the records in the
//                 linked list or prints that there are no records.
//
//  Parameters:    N/A
//
//  Return values:  N/A
// 
/****************************************************************/
void llist::printAllRecords()
{
    struct record *current = start;
    
    if (current == NULL)
    {
        cout << "\nThere are no records" << endl;
    }

    while(current != NULL)
    {
        cout << "\nAccount Number: " << current->accountno << endl;
        cout << "\nAccount Holder Name: " << current->name << endl;
        cout << "\nHolder's Address: " << current->address << endl;
        current = current->next;
    }
}


/******************************************************************/
//  Function name: deleteRecord
//
//  DESCRIPTION:   This method delets the record of the given
//                 account number if it exists.
//
//  Parameters:    acc_num (int) : The give account number.
//
//  Return values:  0 : The method was able to delete the record.
//                 -1 : The method was unable to delete the record
//                      because it doesn't exist.
//  
/****************************************************************/
int llist::deleteRecord(int acc_num)
{
    struct record *current = start;
    struct record *previous = NULL;
    if (start == NULL)
    {
        #ifdef DEBUG
        cout << "\n\n****Debug Function Info****";
        cout << "\nFunction name: addRecord";
        cout << "\nParameters passed: acc_num = " << acc_num;
        cout << "\nReturn value : -1" << endl;
        #endif
        return -1;
    }

    while (current != NULL)
    {
        if (current->accountno == acc_num)
        {
            if (previous == NULL)
            {
                start = current->next;
            }
            else
            {
                previous->next = current->next;
            }
      
            #ifdef DEBUG
            cout << "\n\n****Debug Function Info****";
            cout << "\nFunction name: deleteRecord";
            cout << "\nParameters passed: acc_num = " << acc_num;
            cout << "\nReturn value : 0" << endl;

            cout << "\n--Deleted Account Info--";
            cout << "\nAccount Number: " << current->accountno;
            cout << "\nAccount Holder Name: " << current->name;
            cout << "\nHolder's Address: " << current->address << endl;
            #endif
            return 0;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
   
    #ifdef DEBUG
    cout << "\n\n****Debug Function Info****";
    cout << "\nFunction name: addRecord";
    cout << "\nParameters passed: acc_num = " << acc_num;
    cout << "\nReturn value : -1" << endl;
    #endif 
    return -1;
}
