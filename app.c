#include <omp.h>    //Use OpenMP
#include <stdio.h>  //Provide I/O
#include <stdlib.h> //Use NULL
#include <unistd.h> //Use usleep (sleep for a number of microseconds)
#include <math.h>
#include "numGen.c"
#define NUM_PHIL 5 // The number of philosophers
#define MEALS 100  // The number of meals per philosopher

/*
Group Members: Naveen Kumar Rajesh, Cameron Williams, Connor Reid, Dalton Kolh, Iness Ghourrabou
Description: A simple caesar cipher program that uses a random number generator from the dining philosophers problem.
Last Updated: 05/10/2022
*/

static omp_lock_t chopsticks[NUM_PHIL]; // Locks to represent chopsticks
 
int encrypt(char *eMessage, int key)
{
 
    char ch;
    int i;
 
    //Program will run until for the length of the string in the eMessage array
    for (i = 0; eMessage[i] != '\0'; ++i)
    {
        ch = eMessage[i];
 
        //If the character in the array is between 'a' and 'z' on the ASCII table it will
        //add the value of the randomized key to the character
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
 
            //If by chance the value of the character + key exceeds the boundaries of z
            //it will subtract the ASCII value of 'z' (122), add 'a' (97), and subtract 1.
            if (ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
 
            eMessage[i] = ch; //The newly encrypted character is stored into the eMessage array (replacing the original character)
        }
        //If the character in the array is between 'A' and 'Z' on the ASCII table it will
        //add the value of the randomized key to the character
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
 
            //If by chance the value of the character + key exceeds the boundaries of z
            //it will subtract the ASCII value of 'Z' (90), add 'A' (65), and subtract 1.
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
 
            eMessage[i] = ch; //The newly encrypted character is stored into the eMessage array (replacing the original character)
        }
    }
 
    //The newly replaced array of characters (eMessage) is then provided to the user
    printf("\nEncrypted message: %s", eMessage);
    //The randomly generated key is produced to the user to use for decryption
    printf("\nYour Key: %d", key);
}
 
int decrypt(char *dMessage, int dkey)
{
 
    char ch;
    int i;
    char message[1000];
 
    //Program will run until for the length of the string in the dMessage array
    for (i = 0; dMessage[i] != '\0'; ++i)
    {
        ch = dMessage[i];
 
        //If the character in the array is between 'a' and 'z' on the ASCII table it will
        //subtract the value of the user inputted randomized key to the character
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - dkey;
 
            //If by chance the value of the character - key exceeds the boundaries of a
            //it will add the ASCII value of 'z' (122), subtract 'a' (97), and add 1.
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
 
            dMessage[i] = ch; //The original character is placed back into the array
        }
 
        //If the character in the array is between 'A' and 'Z' on the ASCII table it will
        //subtract the value of the user inputted randomized key to the character
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - dkey;
 
            //If by chance the value of the character - key exceeds the boundaries of a
            //it will add the ASCII value of 'Z' (90), subtract 'A' (65), and add 1.
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
 
            dMessage[i] = ch; //The original character is placed back into the array
        }
    }
 
    //The original message is displayed to the user
    printf("\nDecrypted message: %s\n", dMessage);
}
 

 
// Main function.
int main(int argc, char **argv)
{
    int i;
 
    // Initialize locks
    for (i = 2; i < NUM_PHIL; i++)
        omp_init_lock(&chopsticks[i]);
        // Create and start philosopher threads.
#pragma omp parallel num_threads(NUM_PHIL)
    {
        philosopher();
    }
    // Wait for philosophers to finish then destroy locks.
    for (i = 0; i < NUM_PHIL; i++)
        omp_destroy_lock(&chopsticks[i]);
 
    // End program.
    float numbers[i];
    FILE *fptr;
    float number = 1;
    int num;
    fptr = fopen("numbers.txt", "r");
    for (i = 0; i < 5; i++)
    {
        fscanf(fptr, "%f,", &numbers[i]);
        numbers[i] = numbers[i] * 100000000;
    }
    //  for(i = 0; i < 3; i++)
    //  {
    //        number += numbers[i] / numbers[i + 1];
    //  }
    number = numbers[0] / numbers[1] * numbers[2] / numbers[3] * numbers[4];
    num = (int)number; // random number
    num = num % 10;
    printf("%d \n", num);
    fclose(fptr);
    remove("numbers.txt");
 
    // UI
 
    int userchoice;
    int deckey;
    char userstring[1000];
    char encrmessage[1000];
 
    printf("Do you want to encrypt or decrypt a message (1 or 2)?\n");
    scanf("%d", &userchoice);
 
    if (userchoice == 1)
    {
        printf("\nEnter the message you would like to encrypt: ");
        scanf("%s", userstring);
        encrypt(userstring, num);
    }
    else if (userchoice == 2)
    {
        printf("\nEnter the encrypted message you would like to decrypt: ");
        scanf("%s", encrmessage);
        printf("\nEnter the decryption key: ");
        scanf("%d", &deckey);
        decrypt(encrmessage, deckey);
    }
    else
    {
        printf("Invalid!");
    }
    return 0;
}
