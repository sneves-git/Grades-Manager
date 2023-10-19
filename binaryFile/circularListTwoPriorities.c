#include "main.h"

static struct studentNameNumber* nameNumberHead = NULL;
static struct studentNameNumber* nameNumberNode;
static struct elemInQueue* head = NULL;
static struct elemInQueue* node;



//-----------------------------NAMES NUMBERS FILE-------------------------------

//Opens .txt file of the NAMES::NUMBERS, stores it in a simple list with dynamic
//memory and checks for possible mistakes in lines
void readTxtNameNumber(char* txtFileName) {
    int errors = 0;
    int lineNumber = 0;
    char *token = NULL;
    char error[MAXLINESIZE] = "";
    const char separator[2] = "::";
    char fileLine[MAXLINESIZE] = "";

    FILE *txtFile = fopen(txtFileName, "r");

    if (txtFile == NULL) {
        printf("Error. There is no text file with that name.");
    }else {
        //Goes through each file line
        while (get_one_line(txtFile, fileLine, MAXLINESIZE)) {
            //If EOF is reached then the function ends
            if (feof(txtFile) == 1) {
                break;
            }

            error[0] = '\0';
            lineNumber++;


            struct studentNameNumber* currentElem, *nextElem;
            nameNumberNode = (struct studentNameNumber*) calloc(1, sizeof(struct studentNameNumber));

            //Students' name
            token = strtok(fileLine, separator);
            if(token == NULL){
                printError("Line is incorrectly written it is missing information.", lineNumber, &errors, txtFileName);
                continue;
            }
            checkName(token, error);
            if(printError(error, lineNumber, &errors, txtFileName) == 1){ //1 indicates there is an error
                free(nameNumberNode);
                continue;
            }
            strcpy(nameNumberNode -> studentName, token);


            //Students' number
            token = strtok(NULL, separator);
            if(token == NULL){
                printError("Line is incorrectly written it is missing information.", lineNumber, &errors, txtFileName);
                continue;
            }
            checkStudentNumber(token, error);
            if(printError(error, lineNumber, &errors, txtFileName) == 1){
                free(nameNumberNode);
                continue;
            }
            nameNumberNode -> studentNumber = strtoul(token, NULL, 10);



            //circularListOnePriority(nameNumberNode);
            //printNamesList();

            //Simple list
            if(nameNumberHead == NULL){
                nameNumberHead = nameNumberNode;
                nameNumberHead -> next = NULL;
            }else{
                currentElem = nameNumberHead;
                nextElem = nameNumberHead -> next;
                while(nextElem != NULL){
                    currentElem = nextElem;
                    nextElem = nextElem -> next;
                }
                currentElem -> next = nameNumberNode;
                nameNumberNode -> next = NULL;
            }


        }
    }
    fclose(txtFile);
}


//prints the content of the list Names and Numbers
void printNamesList(void){
    struct studentNameNumber* nextElem;
    char name[5] = "NAME", number[7] = "NUMBER";

    if(nameNumberHead == NULL){
        printf("Empty list.\n");
        return;
    }
    printf("\n%*s\t%*s\n\n", MAXWORDSIZE, name, MAXWORDSIZE, number);
    printf("%*s\t%*lu\n",MAXWORDSIZE, nameNumberHead -> studentName, MAXWORDSIZE, nameNumberHead -> studentNumber);

    nextElem = nameNumberHead -> next;
    while(nextElem != NULL){
        printf("%*s\t%*lu\n", MAXWORDSIZE, nextElem -> studentName, MAXWORDSIZE, nextElem -> studentNumber);
        nextElem = nextElem -> next;
    }
    printf("\n\n");
}



//------------------------------CLASSIFICATIONS FILE------------------------------

//Used to search the list of the names and students' number accordingly to the student's
//number presented in the classifications file
char* searchName(unsigned long int classificationsNumber){
    unsigned long int number;
    struct studentNameNumber* currentElem, *nextElem;

    //Checks the first name
    currentElem = nameNumberHead;
    nextElem = nameNumberHead -> next;
    number = nameNumberHead -> studentNumber;  //Student Number from Name&Number file
    if(number == classificationsNumber){
        return (currentElem -> studentName);
    }

    //Checks the rest of the names
    while(nextElem != NULL){
        //If the student number from the Name&Number file is equal to the classifications file
        //number then we insert it in the node
        number = nextElem -> studentNumber;
        currentElem = nextElem;
        nextElem = nextElem -> next;
        if(number == classificationsNumber){
            return (currentElem -> studentName);
        }
    }
    return "";
}


//Opens .txt file of the STUDENTNUMBER::DISCIPLINE::TEST::CLASSIFICATION, stores it with dynamic
//memory allocation in a circular list with two priorities and checks for possible mistakes in lines
int readTxtClassifications(char *txtFileName) {
    int errors = 0;
    int lineNumber = 0;
    char error[MAXLINESIZE] = "";
    const char separator[2] = "::";
    char fileLine[MAXLINESIZE] = "";
    FILE *txtFile = fopen(txtFileName, "r");

    if (txtFile == NULL) {
        printf("Error. There is no text file with that name.");
    } else {
        //Reads the file, line by line, which contains the classifications of the students
        while (get_one_line(txtFile, fileLine, MAXLINESIZE)) {
            //Checks if it has reached the EOF, if so then it stops
            if (feof(txtFile) == 1) {
                break;
            }

            char *token = NULL;
            char name[MAXWORDSIZE] = "";
            int tokenCounter = 0, flag = 0;
            unsigned long int studentNumber = 0;
            float test1 = 0, test2 = 0, summation = 0;

            error[0] = '\0';
            lineNumber++;

            //Student's number
            token = strtok(fileLine, separator);
            if(token == NULL){
                printError("Line is incorrectly written it is missing information.", lineNumber, &errors, txtFileName);
                continue;
            }
            checkStudentNumber(token, error);
            if (printError(error, lineNumber, &errors, txtFileName) == 1) {
                continue;
            }
            studentNumber = strtoul(token, NULL, 10);
            tokenCounter++;


            //Discipline
            token = strtok(NULL, separator);
            if(token == NULL){
                printError("Line is incorrectly written it is missing information.", lineNumber, &errors, txtFileName);
                continue;
            }
            checkName(token, error);
            if (printError(error, lineNumber, &errors, txtFileName) == 1) {
                continue;
            }
            tokenCounter++;


            struct elemInQueue *nextElem;
            if (head != NULL) {
                //Runs through the list to see if that student's number has already been written
                //therefore meaning that the first test has been written and we need to write the 2nd
                unsigned long int number = head -> studentNumber;
                char *subject = head -> schoolSubject;
                nextElem = head;


                //Checks the first node
                if (number == studentNumber && strcasecmp(subject, token) == 0) {
                    //flag - Signals that we found a node that has the same number and discipline
                    //as the one in the classifications line
                    flag = 1;
                }

                //Checks the other nodes
                nextElem = nextElem -> next;
                number = nextElem -> studentNumber;
                subject = nextElem -> schoolSubject;
                while (nextElem != head) {
                    if (number == studentNumber && strcasecmp(subject, token) == 0) {
                        //flag - Signals that we found a node that has the same number and discipline
                        //as the one in the classifications line
                        flag = 1;
                        break;
                    } else {
                        nextElem = nextElem -> next;
                        number = nextElem -> studentNumber;
                        subject = nextElem -> schoolSubject;
                    }
                }
            }


            //We found no number and subject equal to any other in the list so it is created
            //a new node in which we fill in the parameters name, number, discipline, test1
            //and then order the name and discipline by alphabetical priority
            if (flag == 0 || head == NULL) {
                node = (struct elemInQueue *) calloc(1, sizeof(struct elemInQueue));
                if (node == NULL) {
                    return 1;
                }

                //Student's number
                node -> studentNumber = studentNumber;
                //School Subject
                strcpy(node -> schoolSubject, token);

                //Test1
                while ((token = strtok(NULL, separator)) != NULL) {
                    tokenCounter++;

                    if (tokenCounter == 4) {
                        node -> test1 = strtof(token, NULL);
                        break;
                    }
                }
                if(token == NULL || tokenCounter < 4){
                    printError("Line is incorrectly written it is missing information.", lineNumber, &errors, txtFileName);
                    continue;
                }
                checkTests(token, error);
                if (printError(error, lineNumber, &errors, txtFileName) == 1) {
                    free(node);
                    continue;
                }


                //Mean - We assume beforehand that the student had a 0.0 in the second test
                //and calculate its mean (in case the user doesn't introduce it)
                test1 = node -> test1;
                test2 = node -> test2;
                summation = test1 + test2;
                node -> mean = round(summation / 2);

                //Name
                strcpy(name, searchName(node->studentNumber));
                //If a name was found, we can insert the node in the circular list and sort its
                //name and discipline by alphabetical priority
                if (strcmp(name, "") != 0) {
                    strcpy(node -> name, name);
                    circularListTwoPriorities(node);
                }
                    //If there is no name associated to the student number it frees the memory of the
                    //node because it serves no purpose for the program
                else {
                    free(node);
                }
            }


            //There is a number and subject equal to another one in the list so we use the same node
            //to fill in the parameters test2 and mean to be filled
            else if (flag == 1) {
                //If the second test is already written then we discard the extra information
                if(nextElem -> test2 != 0.0){
                    continue;
                }

                //Test2
                while ((token = strtok(NULL, separator)) != NULL) {
                    tokenCounter++;
                    if (tokenCounter == 4) {
                        nextElem -> test2 = strtof(token, NULL);
                        break;
                    }
                }
                if(token == NULL || tokenCounter < 4){
                    printError("Line is incorrectly written it is missing information.", lineNumber, &errors, txtFileName);
                    continue;
                }
                checkTests(token, error);
                if (printError(error, lineNumber, &errors, txtFileName) == 1) {
                    removeNode(nextElem);
                    continue;
                }

                //Mean
                test1 = nextElem -> test1;
                test2 = nextElem -> test2;
                summation = test1 + test2;
                nextElem -> mean = round(summation / 2);
            }
        }
    }

    //Close file
    fclose(txtFile);
}


//Prints final list where all the data from both inputs (.txt) is stored
void printList(void){
    struct elemInQueue * nextElem;
    char name[5] = "NAME", discipline[11] = "DISCIPLINE", number[7] = "NUMBER", test1[7] = "TEST 1", test2[7] = "TEST 2",mean[5] = "MEAN";

    if(head==NULL){
        printf("List is empty.\n");
        return;
    }

    printf("%*s\t%*s\t%*s\t%6s\t%6s\t%6s\n\n", MAXWORDSIZE, name, MAXWORDSIZE, discipline, MAXWORDSIZE, number, test1, test2, mean);
    printf("%*s\t%*s\t%*lu\t%6.2f\t%6.2f\t%6.2f\n",
           MAXWORDSIZE, head -> name, MAXWORDSIZE, head -> schoolSubject, MAXWORDSIZE, head->studentNumber, head->test1, head->test2, head->mean);

    nextElem = head -> next;
    while(nextElem != head){
        printf("%*s\t%*s\t%*lu\t%6.2f\t%6.2f\t%6.2f\n",
                MAXWORDSIZE, nextElem -> name, MAXWORDSIZE, nextElem -> schoolSubject, MAXWORDSIZE, nextElem->studentNumber, nextElem->test1, nextElem-> test2, nextElem->mean);
        nextElem = nextElem -> next;
    }
    printf("\n\n");
}


//---------------------------------BINARY FILE CREATION---------------------------------
//Creates the binary file with the structures in alphabetical order
void createBinary(char* binaryName, FILE* fileBinaryStruct){
    struct elemInQueue* nextElem;

    fileBinaryStruct = fopen(binaryName, "wb");

    fwrite(head, sizeof(struct elemInQueue), 1, fileBinaryStruct);

    nextElem = head -> next;
    while(nextElem != head){
        fwrite(nextElem, sizeof(struct elemInQueue), 1, fileBinaryStruct);
        nextElem = nextElem -> next;
    }

    fclose(fileBinaryStruct);
}



//-----------------------------CIRCULAR LIST WITH TWO PRIORITIES---------------------------


//Removes the node which has an element incorrect
int removeNode(struct elemInQueue* node){
    struct elemInQueue * previousNode;

    //If the head is the only element it removes it
    if(node == head && node -> next == head){
        free(node);
        head = NULL;
    }else{
        //Searches for the previous elem to node and connects it to next elem to node
        previousNode = node;
        while(previousNode->next != node){
            previousNode = previousNode->next;
        }
        previousNode->next = node->next;
        //If the node is the head then new head is next elem to node
        if(node==head){
            head = node->next;
        }
        //Frees the memory
        free(node);
    }
}


//Circular list with two priorities (name and discipline)
int circularListTwoPriorities(struct elemInQueue * newNode){
    int disciplineResult = 0, nameResult = 0;
    struct elemInQueue * nextElem, *currentElem;

    //If it is the first element of the list it starts off as the head
    if(head == NULL){
        head = newNode;
        newNode -> next = head;
    }else{
        //Inserts node at the beginning of the list
        if(strcasecmp(head -> schoolSubject, newNode -> schoolSubject) > 0){
            newNode -> next = head;

            //If there is only one element on the list we connect the previous head to the new head
            //directly
            if(head -> next == head){
                head -> next = newNode;
            }

            //If there is more than one element on the list we need to connect the last element to
            //the new head, therefore, we search for it
            else{
                currentElem = head;
                nextElem = head->next;
                while(nextElem != head){
                    currentElem = nextElem;
                    nextElem = nextElem -> next;
                }
                currentElem -> next = newNode;
            }

            head = newNode;
        }else if(strcasecmp(head -> schoolSubject, newNode -> schoolSubject) == 0
                 && strcasecmp(head -> name, newNode -> name) > 0){

            newNode -> next = head;

            //If there is only one element on the list we connect the previous head to the new head
            //directly
            if(head -> next == head){
                head -> next = newNode;
            }
                //If there is more than one element on the list we need to connect the last element to
                //the new head, therefore, we search for it
            else{
                currentElem = head;
                nextElem = head->next;
                while(nextElem != head){
                    currentElem = nextElem;
                    nextElem = nextElem -> next;
                }
                currentElem -> next = newNode;
            }

            head = newNode;

        }else{
            currentElem = head;
            nextElem = head->next;
            while(strcasecmp(nextElem -> schoolSubject, newNode -> schoolSubject) < 0
                  && nextElem != head) {
                currentElem = nextElem;
                nextElem = nextElem->next;
            }
            while((disciplineResult = strcasecmp(nextElem -> schoolSubject, newNode -> schoolSubject)) == 0
                  && strcasecmp(nextElem -> name, newNode -> name) < 0
                  && nextElem != head){
                currentElem = nextElem;
                nextElem = nextElem->next;
            }

            if(nextElem -> next == head && disciplineResult < 0){
                //Insert at end of list
                currentElem -> next = newNode;
                newNode -> next = head;
            }else{
                //Insert in the middle of the list
                newNode -> next = currentElem -> next ;
                currentElem -> next = newNode;
            }
        }
    }

    return 0;
}

