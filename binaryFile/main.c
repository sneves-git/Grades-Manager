#include "main.h"
//Function that prints errors found in the .txt files lines
int printError(char* error, int lineNumber, int* errors, char* fileName){
    char lineError[MAXLINESIZE*2] = "";

    //If the string in not empty it is because it has an error written in it
    if( strcmp(error, "") != 0 ){
        if(*errors == 0){
            printf("\n\t\t\tERRORS IN FILE: %s\n", fileName);
        }
        *errors += 1;
        sprintf(lineError, "Error in line %d. ", lineNumber);
        strcat(lineError, error);
        printf("%s\n", lineError);
        return 1;
    }
    return 0;
}


//Asks the user for the .txt file name until he gives him a valid answer
FILE * saveTxtFileName(FILE *txtFile, char *fileName){
    while (txtFile == NULL){
        printf("\nName of data file: ");
        if(get_one_line(stdin, fileName, MAXWORDSIZE) == EOF){
            printf("Ending program... You pressed EOF.");
            exit(0);
        }

        txtFile = fopen(fileName, "r");
        if(txtFile == NULL){
            printf("File does not exist. Try again.\n");
        }
    }

    return txtFile;
}


// Árvore binária genérica com acesso a ficheiros - João Gabriel Silva 2020-04-26
/* get next line from input - "lim" includes the terminating zero */
int get_one_line(FILE * fich, char *linha, int lim) {
    int c, i;
    i = 0;
    while (isspace(c = fgetc(fich)));
    if (c != EOF) {
        if (!iscntrl(c)) linha[i++] = c;
    } else
        return c;

    for (; i < lim - 1;) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}


int main() {
    int choice = 0, previousChoice = 0;
    char nameNumberName[MAXWORDSIZE] = "";
    char classificationsName[MAXWORDSIZE] = "";
    static char binaryName[MAXWORDSIZE] = "binary.bin";
    FILE* fileTxtNameNumber = NULL;
    FILE* fileTxtClassifications = NULL;
    FILE* fileBinaryStruct = NULL;


    printf("Please choose the name of the data file that you want to introduce first: \n\t"
           "1 - Student's names and numbers\n\t"
           "2 - Student's classifications\n\t"
           "Choice: ");
    while(1){
        choice = 0;
        scanf("%d", &choice);
        while (getchar() != '\n');  //clean rest of the line

        //Checks whether or not user chose to insert the name of the student's names and number file, if the classifications
        //binary file hasn't been written yet and if this option has not been completed before
        if(choice == 1 && fileTxtClassifications == NULL && previousChoice != 1){
            previousChoice = choice;
            fileTxtNameNumber = saveTxtFileName(fileTxtNameNumber, nameNumberName);
        }
            //Checks if option 1 was selected and if the previous choice wasn't the same
        else if(choice == 1 && previousChoice != 1){
            saveTxtFileName(fileTxtNameNumber, nameNumberName);
            break;
        }

        //Checks whether or not user chose to insert the name of the classifications file, if the names
        //and numbers binary file hasn't been written yet and if this option has not been completed before
        if(choice == 2 && fileTxtNameNumber == NULL && previousChoice != 2){
            previousChoice = choice;
            fileTxtClassifications = saveTxtFileName(fileTxtClassifications, classificationsName);

        }else if(choice == 2 && previousChoice != 2){
            saveTxtFileName(fileTxtClassifications, classificationsName);
            break;
        }

        //Advises the user as to what files have already been written and what not so he knows what
        //to choose
        if(previousChoice == 1){
            printf("\n1 - Student's names and numbers (✓)\n"
                     "2 - Student's classifications\n"
                     "Choice: ");
        }else if(previousChoice == 2){
            printf("\n1 - Student's names and numbers\n"
                     "2 - Student's classifications (✓)\n"
                     "Choice: ");
        }else{
            printf("\nInvalid Choice. Choose the number 1 or 2.\n"
                     "1 - Student's names and numbers\n"
                     "2 - Student's classifications\n"
                     "Choice: ");

        }
    }

    printf("\n--------------------------------------");
    //Reads and creates a simple list for names and numbers
    readTxtNameNumber(nameNumberName);

    //Creates classifications structure
    readTxtClassifications(classificationsName);
    createBinary(binaryName, fileBinaryStruct);
    printf("--------------------------------------\n\n");


    while(1){
        choice = -1;

        printf("Choose one of the following options:\n\t"
               "0 - Leave\n\t"
               "1 - See names and numbers list\n\t"
               "2 - See classifications list\n\t"
               "Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  //clean rest of the line
        printf("\n");

        if(choice == 0){
            return 0;
        }else if(choice == 1){
            printNamesList();
        }else if(choice == 2){
            printList();
        }
    }


    return 0;
}
