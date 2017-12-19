/*
 *Written By: Ari Perez
 *Novemeber 2017
 */


#include "BinarySearchTreeAPI.h"
#include "ai.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char**argv)
{
    int quit = 0;
    int option = 0;
    char temp[100];
    char input[2][100];
    FILE *userFile = fopen(argv[1], "r");
    if (argv[1] == NULL || userFile == NULL)
    {
        printf("ERROR! No file given!\n");
        return 0;
    }

    Tree * bTree = createBinTree(&compareKnowledge, &deleteKnowledge);

    //Read in keywords
    int num = 0;
    while (fgets(temp,99, userFile))
    {
        num++;
        if (temp[strlen(temp) - 1] == '\n')
        {
            temp[strlen(temp) - 1] = '\0';
        }
        strcpy(input[num-1], temp);
        //printf("--%s\n", input[num-1]);
        if (num == 2)
        {
            Knowledge *newK  = createKnowledge(input[0], input[1]);
            addToTree(bTree, (TreeDataPtr)newK);
            memset(input[0],0, 100);
            memset(input[1], 0, 100);
            num = 0;

        }

        memset(temp, 0, 100);


    }

    while(!quit)
    {
        printf("####MENU#######\n");
        printf("1) Add a new rule\n");
        printf("2) Remove a rule\n");
        printf("3) Display Rules\n");
        printf("4) Modify rule rating\n");
        printf("5) Discuss\n");
        printf("6) Quit\n");
        printf("Please enter a number: ");
        fscanf(stdin,"%d",&option);
        getchar();

        if (option == 1)
        {
            char keyword[100];
            char sentence[100];
            double importance = 0;
            int valid = 0;
            while (!valid)
            {
                printf("Please enter the information for your new rule: \n");
                fgets(keyword, 99, stdin);
                if (keyword[strlen(keyword) - 1] == '\n')
                {
                    keyword[strlen(keyword) - 1] = '\0';
                }
                fgets(sentence,99,stdin);
                if (sentence[strlen(sentence) - 1] == '\n')
                {
                    sentence[strlen(sentence) - 1] = '\0';
                }
                fscanf(stdin, "%lf", &importance);
                getchar();
                if (importance < 1 && importance > 0)
                {
                    valid = 1;
                    Knowledge *newK  = createKnowledge(keyword, sentence);
                    setRate(newK, importance);
                    //printKnowledge(newK);

                    addToTree(bTree, (TreeDataPtr)newK);


                }

                else {
                    printf("Invalid input! Please try again!");
                }
            }


        }

        else if (option == 2)
        {
            char keyword[100];
            printf("Enter the keyword for the rule you wish to delete: \n");
            fgets(keyword, 99, stdin);
            if (keyword[strlen(keyword) - 1] == '\n')
            {
                keyword[strlen(keyword) - 1] = '\0';
            }
            Knowledge *newK  = createKnowledge(keyword, "");
            removeFromTree(bTree, (TreeDataPtr)newK);
            free(newK);


        }

        else if (option == 3)
        {
            printInOrder(bTree, printKnowledge);
            printf("\n");
        }

        else if (option == 4)
        {
            char keyword[100];
            printf("Enter the keyword for the rule you wish to modify: \n");
            fgets(keyword, 99, stdin);
            if (keyword[strlen(keyword) - 1] == '\n')
            {
                keyword[strlen(keyword) - 1] = '\0';
            }
            Knowledge *newK  = createKnowledge(keyword, "");

            TreeDataPtr find = findInTree(bTree, (TreeDataPtr)newK);
            if (find != NULL)
            {
                double newRating = 0.0;
                printKnowledge(find);
                printf("Personalized Rating: %lf\n", getRating(find));
                printf("Please enter the new rating: ");
                fscanf(stdin, "%lf", &newRating);
                getchar();
                setRate(find, newRating);
            }

            else {
                printf("That rule does not exist!\n");
            }

        }

        else if (option == 5)
        {
            //char keyword[100];
            char input[100];
            double highest = -1.0;
            char *token;
            const char sym[2] = " ";
            TreeDataPtr find = NULL;
            printf("Say something: \n");
            fgets(input, 99, stdin);
            if (input[strlen(input) - 1] == '\n')
            {
                input[strlen(input) - 1] = '\0';
            }

            token = strtok(input, sym);

            while (token != NULL)
            {
                Knowledge *newK  = createKnowledge(token, "");
                TreeDataPtr temp = findInTree(bTree, (TreeDataPtr)newK);
                if (temp != NULL)
                {
                    double currRate = getRating(temp) + getSystem(temp);
                    if (currRate > highest)
                    {
                        find = temp;
                        highest = currRate;
                    }
                }
                token = strtok(NULL, sym);

            }

            if (find == NULL)
            {
                printf("I don't know what to say!\n");
            }

            else
            {
                char feedback[10];
                printOutput(find);
                printf("Was this helpful y/n?");
                fgets(feedback, 9, stdin);
                if(strcmp(feedback, "n\n") == 0)
                {
                    printf("Thanks for your feedback!\n");
                    setCount(find, 1);
                    double newSys = getSystem(find) - (getSystem(find)*getLearningRate(find)/getCount(find));
                    setSystem(find, newSys);
                }
                else {
                    setCount(find, 1);
                    double newSys = getSystem(find) + (getSystem(find)*getLearningRate(find)/getCount(find));
                    setSystem(find, newSys);

                }

            }

        }

        else if (option == 6)
        {
            quit = 1;
        }
    }

    return 0;
}
