//
// Created by sofia on 17/05/2020.
//

#ifndef PROJETO_FUNCTIONS_H
#define PROJETO_FUNCTIONS_H

//-------------LIBRARIES------------
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <locale.h>
#include <math.h>



//-------------CONSTANTS------------
#define MAXWORDSIZE 40
#define MAXLINESIZE 80


//-------------STRUCTURES------------
struct studentsMean{
    char name[MAXWORDSIZE];
    unsigned long int studentNumber;
    char schoolSubject[MAXWORDSIZE];
    float test1;
    float test2;
    float mean;
    struct studentsMean* next;
};

struct finalists{
    char name[MAXWORDSIZE];
    int subjectsPassed;
    struct finalists* next;
};


//-------------FUNCTIONS------------
//main.c
int get_one_line(FILE*, char *, int);
void saveTxtFileName(char *);

//circularLists.c
void readBinary(char*);
void createFinalClassificationsFile(char*);
void printfFinalClassList(void);
void createFinalistsStruct(void);
void createFinalistsFile(char*);
void printFinalistsList(void);
void circularListOnePriority(struct finalists*);


#endif //PROJETO_FUNCTIONS_H
