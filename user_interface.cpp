/******************************************************************/
//  NAME:        Kate Hamada
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 15, 2025
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This is the c++ file where the it gets the input from the user
//   and then based off of what they input uses methods from llist
//   to do what the user wants.
//  
/****************************************************************/

#include <iostream>
#include <ostream>
#include <string>
#include <cstring>
#include "llist.h"
#include "record.h"

using namespace std;

/******************************************************************/
//  Function name: enter_acc_num
//  
//  DESCRIPTION:   This function gets input from the user and if they
//                 inputed a valid number (postive & no non-digits)
//                 then it will set the number from the user into the
//                 num variable.
//
//  Parameters:    num (int *) : The pointer of the variable that
//                               is being set to a number from the
//                               user input.
//
//  Return values:  N/A
//  
/****************************************************************/
void enter_acc_num (int *num)
{
    cin.ignore(1000, '\n');

    string input;
    int result;
    *num = 0;
    int once_through = 0;
    bool is_digit = true;
    char ch;
    
    while (*num <= 0)
    {
        is_digit = true;
        result = 0;
        if (once_through != 0)
        {
            cout << "\nYou've typed an invalid account number please try again." << endl;
        }

        cout << "\n\nType the account number: " << endl;
        getline(cin, input);

        for (size_t i = 0; i < input.size(); ++i)
        {
            ch = input[i];
            if (!isdigit(ch))
            {
                is_digit = false;

            }
        }

        if (is_digit && !input.empty()) 
        {
            for (size_t i = 0; i < input.size(); ++i)
            {
                ch = input[i];
                result = result * 10 + (ch - '0');
            }
            
            if (result <= 0)
            {
                is_digit = false;
            }
            else
            {
                *num = result;
            }
        }
        else
        {
            is_digit = false;
        }

        if (!is_digit)
        {
            *num =0;
        }

        once_through = 1;
    }   
}

/******************************************************************/
//  Function name: getaddress
//
//  DESCRIPTION:   This function gets the address from user input
//                 while accounting for the fact that there may be
//                 multiple lines.
//
//  Parameters:    input (string&) : A string being passed by 
//                                   reference that will basically 
//                                   return the address entered by 
//                                   the user.
//
//  Return values:  N/A
//  
/****************************************************************/
void getaddress(string& input)
{
    string line;
    bool stop = false;
    int empty_lines = 0;

    cout << "\nFinally I will need you to enter the address of the account holder.";
    cout << "\nIn order to finish entering the address hit ENTER TWICE.";
    cout << "\nType the address: " << endl;

    while(!stop)
    {
        getline(cin, line);
        
        // if an new line is entered
        if (line.empty())
        {
            empty_lines++;

            // if there are two new lines entered
            if (empty_lines == 1)
            {
                stop = true;
            }
        }

        // if there are no new lines (there was something typed)
        else
        {
            empty_lines = 0;
            input += line;
            input += ' ';
        }
    }
}

/******************************************************************/
//  Function name: main
//
//  DESCRIPTION:   This function creates a user_interface in order
//                 for a user to manage records that contain name,
//                 address, and account number.
//
//  Parameters:    N/A
//
//  Return values:  0 : The function ended
//  
/****************************************************************/
int main()
{
    char input[100];
    char address[500];
    char name[100];
    char file_name[] = "testfile.txt";
    llist my_list(file_name);
    int run = 0;
    int num_input = 0;
    string address_input;

    #ifdef DEBUG
    char d_file1[] = "testfile1.txt";
    char d_file2[] = "testfile2.txt";
    strcpy(name, "John Doe");
    strcpy(address, "123 Main St"); 
    llist original(d_file1);
    original.addRecord(100, name, address);

    // testing copy constructor
    llist copy = original;
    cout << "\n--Testing Copy Constrcutor--";
    cout << "\n****Below is the original llist of records which should \ncontian 1 record: " << endl;
    original.printAllRecords();
    cout << "\n****Below is the copy llist of the original: " << endl;
    copy.printAllRecords();
    
    // testing overload assignment operator
    cout << "\n--Testing Overloaded Assignment Operator--" << endl;
    llist op(d_file2);
    cout << "\n****Below is an empty llist: " << endl;
    op.printAllRecords();
    op = original;
    cout << "\n****Below is the same llist as above but after the = operator: " << endl;
    op.printAllRecords();

    // testing overload << operator
    cout << "\n--Testing Overload << Operator--" << endl;
    cout << original;

    // resets everything
    op.deleteRecord(100);
    name[0] = '\0';
    address[0] = '\0';
    #endif
    
    while(run == 0)
    {
        cout << "\nThe left are the commands that you can type.";
        cout << "\nThe right describes what each command does.";
        cout << "\nLike so -> command:  description\n";
        cout << "\nadd:      Add a new record in the database.";
        cout << "\nprintall: Print all records in the database.";
        cout << "\nfind:     Find record(s) given a specified";
        cout << "\n          account number.";
        cout << "\ndelete:   Delete existing record(s) from the";
        cout << "\n          database given the account number."; 
        cout << "\nquit:     Quit the program.\n";
        cout << "\n\nType what you like to do: " << endl;
        cin >> input;

        // quit
        if (strncmp(input, "quit", strlen(input)) == 0)
        {
            run = 1;
            cout << "\n~You've quit the program~\n" << endl;
        }

        // add
        else if (strncmp(input, "add", strlen(input)) == 0)
        {
            cout << "\nI will need an account number in order to add it to the records.";
            enter_acc_num(&num_input);
            cout << "\nNext I will need you to enter the name of the new account.";
            cout << "\nType the account holder name: " << endl;
            cin.getline(name, 100);
            getaddress(address_input);
            strcpy(address, address_input.c_str()); 
            my_list.addRecord(num_input, name, address);
        }

        // delete
        else if (strncmp(input, "delete", strlen(input)) == 0)
        {
            enter_acc_num(&num_input);
            while (my_list.deleteRecord(num_input) == -1)
            {
                cout << "\n*****\nEither account number was typed incorrectly or doesn't exist, please try again\n*****\n\n";
                enter_acc_num(&num_input);
            } 
            
            cout << "\n***Success Account " << num_input << " was found and deleted***\n" << endl;
        }

        // find
        else if (strncmp(input, "find", strlen(input)) == 0)
        {
            enter_acc_num(&num_input);
            while (my_list.findRecord(num_input) == -1)
            {
                cout << "\n*****\nEither account number was typed incorrectly or doesn't exist, please try again\n*****\n\n" << endl;
                enter_acc_num(&num_input);
            }
        }
        
        // printAll
        else if (strncmp(input, "printall", strlen(input)) == 0)
        {
            my_list.printAllRecords();
        }
        else
        {
            cout << "\n\n******\nYou've typed an invalid option try again\n******\n" << endl;
        }       
    }
}
