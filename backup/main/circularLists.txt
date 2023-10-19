//
// Created by sofia on 17/05/2020.
//

#include "main.h"


static struct studentsMean* meanHead = NULL;
static struct studentsMean* meanNode;
static struct finalists* finalistsHead = NULL;
static struct finalists* finalistsNode;


//------------------OPEN BINARY AND CREATE FINAL CLASSIFICATIONS FILE---------------
//Connects the structures in the binary file in a circular list (the structures
//are already in order)
void readBinary(char* binaryName){
    FILE *binFile = NULL;

    binFile = fopen(binaryName, "rb");

    if(binFile == NULL){
        printf("Error. There is no binary file with that name.");
    }else{
        struct studentsMean* previousElem;


        //First element of the list
        meanHead = (struct studentsMean*) calloc(1, sizeof(struct studentsMean));
        fread(meanHead, sizeof(struct studentsMean), 1, binFile);
        previousElem = meanHead;
        meanHead -> next = NULL;

        //Rest of the elements
        meanNode = (struct studentsMean*) calloc(1, sizeof(struct studentsMean));
        while(fread(meanNode, sizeof(struct studentsMean), 1, binFile)){

            //If the end of the file is reached then we stop
            if(feof(binFile) == 1) {
                free(meanNode); //Frees the last space that won't be used
                break;
            }
            meanNode -> next = meanHead; //New element connects to the head
            previousElem -> next = meanNode; //Previous element connects to new element

            previousElem = meanNode;
            meanNode = (struct studentsMean*) calloc(1, sizeof(struct studentsMean));
        }
    }
}

//Creates the final classifications file in which we have the discipline, name and
//mean in each line, each line is
//separated by \n
void createFinalClassificationsFile(char* fileName){
    struct studentsMean* nextElem;
    FILE* finalClassificationsFile = NULL;

    finalClassificationsFile = fopen(fileName, "w");

    if(meanHead != NULL){
        fprintf(finalClassificationsFile, "%*s\t%*s\t%3.0f\n", MAXWORDSIZE, meanHead -> schoolSubject,MAXWORDSIZE, meanHead -> name, meanHead -> mean);
    }

    nextElem = meanHead -> next;
    while(nextElem != meanHead){
        fprintf(finalClassificationsFile, "%*s\t%*s\t%3.0f\n", MAXWORDSIZE, nextElem -> schoolSubject, MAXWORDSIZE, nextElem -> name, nextElem -> mean);
        nextElem = nextElem -> next;
    }

    fclose(finalClassificationsFile);
}


//Prints elements of the final classifications list (✓)
void printfFinalClassList(void){
    struct studentsMean * nextElem;
    char discipline[11] = "DISCIPLINE", name[5] = "NAME",  mean[5] = "MEAN";

    if(meanHead == NULL){
        printf("Empty list.\n");
        return;
    }
    printf("%*s\t%*s\t%5s\n\n", MAXWORDSIZE, discipline, MAXWORDSIZE, name, mean);
    printf("%*s\t%*s\t%5.0f\n",MAXWORDSIZE, meanHead -> schoolSubject, MAXWORDSIZE, meanHead -> name,  meanHead->mean);

    nextElem = meanHead -> next;
    while(nextElem != meanHead){
        printf("%*s\t%*s\t%5.0f\n",MAXWORDSIZE, nextElem -> schoolSubject, MAXWORDSIZE, nextElem -> name,  nextElem->mean);
        nextElem = nextElem -> next;
    }
    printf("\n");
}



//-------------------------CREATE FINALISTS STRUCTURE AND FILE------------------------

//Creates the finalists structure in a circular list and checks if the student passed
//accordingly to the method chosen by the user (1 - Percentage; 2 - From 0 to 20)
void createFinalistsStruct(void) {
    struct studentsMean *meanNextElem;
    struct finalists *finalistsNextElem;


    if(finalistsHead == NULL) {
        finalistsNode = (struct finalists *) calloc(1, sizeof(struct finalists));

        strcpy(finalistsNode->name, meanHead->name);
        if ((meanHead -> mean) > 9) {
            finalistsNode -> subjectsPassed = 1;
        } else {
            finalistsNode -> subjectsPassed = 0;
        }

        circularListOnePriority(finalistsNode);
    }


    //Goes through all the student's names in the mean List
    meanNextElem = meanHead -> next;
    while (meanNextElem != meanHead) {

        //Checks if the name is already on the list or not
        finalistsNextElem = finalistsHead->next;
        while ((finalistsNextElem != finalistsHead)
               && (strcasecmp(finalistsNextElem->name, meanNextElem->name) != 0)) {

            finalistsNextElem = finalistsNextElem->next;
        }



        //If the name is already in the finalists list then we just check if the student
        //passed the subject or not
        if(strcasecmp(finalistsNextElem->name, meanNextElem->name) == 0) {
            if ((meanNextElem -> mean) > 9) {
                finalistsNextElem->subjectsPassed += 1;
            }
        }

        //If it is the first element or if the name is not on the finalists list then
        //we create space for it and insert it in the list
        else if (finalistsNextElem == finalistsHead) {
            finalistsNode = (struct finalists *) calloc(1, sizeof(struct finalists));

            strcpy(finalistsNode->name, meanNextElem->name);
            if((meanNextElem->mean) > 9) {
                finalistsNode -> subjectsPassed = 1;
            } else {
                finalistsNode -> subjectsPassed = 0;
            }

            circularListOnePriority(finalistsNode);
        }
        meanNextElem = meanNextElem->next;
    }
}



//Creates the finalists file in which we have the name and number of subjects passed
//of each student who passed more than 7 disciplines
void createFinalistsFile(char* fileName){
    struct finalists* nextElem;
    FILE* finalistsFile = NULL;

    finalistsFile = fopen(fileName, "w");
    if(finalistsHead != NULL){
        if(finalistsHead -> subjectsPassed > 7){
            fprintf(finalistsFile, "%*s\t%2d\n", MAXWORDSIZE, finalistsHead -> name, finalistsHead -> subjectsPassed);
        }
    }

    nextElem = finalistsHead -> next;
    while(nextElem != finalistsHead){
        if(nextElem -> subjectsPassed > 7){
            fprintf(finalistsFile, "%*s\t%2d\n", MAXWORDSIZE, nextElem -> name, nextElem -> subjectsPassed);
        }
        nextElem = nextElem -> next;
    }

    fclose(finalistsFile);
}


//Prints finalists (students who passed more than 7 school subjects) List
void printFinalistsList(void){
    int count = 0;
    struct finalists * nextElem;
    char name[5] = "NAME", subjectsPassed[16] = "SUBJECTS PASSED";

    if(finalistsHead != NULL){
        if(finalistsHead -> subjectsPassed > 7){
            count ++;
            printf("%*s\t%15s\n\n", MAXWORDSIZE, name, subjectsPassed);
            printf("%*s\t%15d\n", MAXWORDSIZE, finalistsHead -> name, finalistsHead -> subjectsPassed);
        }
    }



    nextElem = finalistsHead -> next;
    while(nextElem != finalistsHead){
        if(nextElem -> subjectsPassed > 7){
            if(count == 0){
                count++;
                printf("%*s\t%15s\n\n", MAXWORDSIZE, name, subjectsPassed);
            }
            printf("%*s\t%15d\n", MAXWORDSIZE, nextElem -> name, nextElem -> subjectsPassed);
        }
        nextElem = nextElem -> next;
    }
    printf("\n");


    /*
    //Print finalists list (all elements)
    if(finalistsHead == NULL){
        printf("Empty list.\n");
        return;
    }
    printf("%*s\t%15s\n\n", MAXWORDSIZE, name, subjectsPassed);
    printf("%*s\t%15d\n", MAXWORDSIZE, finalistsHead -> name, finalistsHead -> subjectsPassed);

    nextElem = finalistsHead -> next;
    while(nextElem != finalistsHead){
        printf("%*s\t%15d\n", MAXWORDSIZE, nextElem -> name, nextElem -> subjectsPassed);
        nextElem = nextElem -> next;
    }
    printf("\n");
     */
}



//---------------------------CIRCULAR LIST WITH ONE PRIORITY------------------

//Circular list with one priority (name)
void circularListOnePriority(struct finalists * newNode){
    int result = 0;
    struct finalists* nextElem, *currentElem;

    //If it is the first element of the list it starts off as the head
    if(finalistsHead == NULL){
        finalistsHead = newNode;
        newNode -> next = finalistsHead;
    }else{
        //Inserts node at the beginning of the list
        if(strcasecmp(finalistsHead -> name, newNode -> name) > 0){
            newNode -> next = finalistsHead;

            //If there is only one element on the list we connect the previous head to the new head
            //directly
            if(finalistsHead -> next == finalistsHead){
                finalistsHead -> next = newNode;
            }

                //If there is more than one element on the list we need to connect the last element to
                //the new head, therefore, we search for it
            else{
                currentElem = finalistsHead;
                nextElem = finalistsHead -> next;
                while(nextElem != finalistsHead){
                    currentElem = nextElem;
                    nextElem = nextElem -> next;
                }
                currentElem -> next = newNode;
            }

            finalistsHead = newNode;

        }else{
            currentElem = finalistsHead;
            nextElem = finalistsHead -> next;
            while((result = strcasecmp(nextElem -> name, newNode -> name)) < 0
                  && nextElem != finalistsHead) {
                currentElem = nextElem;
                nextElem = nextElem->next;
            }

            if(nextElem->next == finalistsHead && result < 0){
                //Insert at end of list
                currentElem -> next = newNode;
                newNode -> next = finalistsHead;
            }else{
                //Insert in the middle of the list
                newNode -> next = currentElem -> next ;
                currentElem -> next = newNode;
            }
        }
    }
}

