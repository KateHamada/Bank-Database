/*****************************************************************
//
//  NAME:        Kate Hamada
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        February 6, 2025
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   This is the header file for record variables
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[25];
    char               address[45];
    struct record*     next;
};

#endif
