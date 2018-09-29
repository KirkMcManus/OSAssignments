/*
Kirk lee McManus Jr.
9/19/2018
Project 1: Amortization Schedule
 */


#include <stdio.h>   // FILE*, fopen(), fclose(), getline(), fputc(), fprintf(), size_t
#include <stdlib.h>  // exit()
#include <math.h>   //pow()

const int LINE_SIZE = 256;//sets the Line size

int main( int argc, char* argv[]){

    FILE* stockFS = NULL; // file stream for input file

    printf("Please enter the loan terms filename: Processing terms from ");
    char inputFilename[100]; //this ensures that the input can fit with input size
    scanf("%s",inputFilename); // user will be prompted to enter name of file
    char* line; // stores a line read in from the file
    size_t bufferSize = LINE_SIZE;

    // data temp variables
    float P; //initial loan amount
    float R; //annual interest rate
    int T; //number of years
    float J; //monthly interest rate
    int N = 12;
    float M; //number of cpmpounding periods in a year

    // open the file for reading
    stockFS = fopen( inputFilename, "r");
    if( stockFS == NULL){
        fprintf( stderr, "ERROR: Unable to open stock data file %s!\n", inputFilename);
        exit(1);
    }

    // Allocate memory (and verify that it worked) for reading in a line from the file
    line = (char*)malloc( bufferSize * sizeof(char) );
    if( line == NULL){
        fprintf( stderr, "ERROR: Unable to allocate memory for the line buffer!\n");
        exit(1);
    }

    // read in a line at a time, parse it and then send it to STDOUT
    while( getline( &line, &bufferSize, stockFS) != -1 &&
           sscanf( line, "%f\t%f\t%d", &P, &R, &T) == 3){
    }

    R = R/100; //will lower the rate from a % to a decimal
    printf("\nProcessing %d-year loan for %.0f cents at an annual interest rate of %.3f",T,P,R);
    J = R/N; //Monthly Interest Rate
    M = P * (J + (J/((pow(1+J,T*12))-1)));//Monthly Payment

    //lines 50-55 will print out certain texts
    printf("\n\nAmortization Schedule\n\n");
    printf("Intitial Balance (cents): %.0f\n", P);
    printf("APR: %.3f\n", R);
    printf("Years: %d\n\n", T);
    printf("Monthly Payment (cents): %.0f\n\n", M);
    printf("Month\tInt.\tPrinc.\tBalance\n" );

    //variables will be initialized for the for loop
    int Int; //Interest
    int Princ; //Principle
    int Balance = P; //Balance will be P for the sakes of the loop

    for(int i = 0; i < N*T; i++)
    {Int = J * P; //Interest is the multiplication of the interest rate and # of compounding periods
    Princ = ceil(M - Int); //the result will be rounded up
    Balance = Balance - Princ; //in every loop the new Balance will subtract itelf with the principle
    P = Balance; //P will be the new Balance

    //this if statement will add the elipses if i ==6
      if( i == 6){
      printf("...\n");
    }

    //this statement will print out Int,Princ,Balance according to the parameters
      if(i > ((N*T)-7) || i < 6) {
        printf("%d\t%d\t%d\t%d\n", i+1,Int,Princ,Balance);}
      }



    // close the file stream
    fclose( stockFS );

    // de-allocate memory
    free( line );

    return 0;
}
