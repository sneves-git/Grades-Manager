//
// Created by sofia on 20/06/2020.
//

#ifndef BINARYFILE_MAIN_H
#define BINARYFILE_MAIN_H


//-------------LIBRARIES------------
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <math.h>


//-------------CONSTANTS------------
#define MAXWORDSIZE 40
#define MAXLINESIZE 80



//-------------STRUCTURES------------
struct studentNameNumber {
    char studentName[MAXWORDSIZE];
    unsigned long int studentNumber;
    struct studentNameNumber* next;
};

struct elemInQueue {
    char name[MAXWORDSIZE];
    unsigned long int studentNumber;
    char schoolSubject[MAXWORDSIZE];
    float test1;
    float test2;
    float mean;
    struct elemInQueue* next;
};



//-------------FUNCTIONS------------
//main.c
int get_one_line(FILE *, char *, int);
int printError(char*, int, int*, char*);
FILE * saveTxtFileName(FILE*, char *);

//circularListTwoPriorities.c
void readTxtNameNumber(char*);
void printNamesList(void);
char* searchName(unsigned long int);
int readTxtClassifications(char*);
void printList(void);
void createBinary(char*, FILE*);
int removeNode(struct elemInQueue*);
int circularListTwoPriorities(struct elemInQueue*);


//verificationFunctions.c
void trimSpaces(char*);
void checkName(char*, char*);
void checkStudentNumber(char*, char*);
void checkTests(char*, char*);




#endif //BINARYFILE_MAIN_H
