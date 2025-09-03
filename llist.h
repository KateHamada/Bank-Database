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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This is the header file for the llist class
//
/****************************************************************/

#include <ostream>
#include "record.h"

#ifndef LLIST_H
#define LLIST_H

using namespace std;

class llist
{
    private:
        record *    start;
        char        filename[20];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        llist(const llist& other);
        llist& operator=(const llist&);
        friend ostream& operator<<(ostream&, const llist&);
        int addRecord(int, char [ ],char [ ]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};

#endif
