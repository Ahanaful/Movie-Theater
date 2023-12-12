/*Md. Ahanaful Alam 1002143421*/
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ROWS 9
#define MAX_COLS 9
#define TICKET_LIMIT 4

void FillMovieTheater(char seat_map[MAX_ROWS][MAX_COLS], int rows, int cols, char file[])
{
    int k = 0;
    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j<cols; j++)
        {
            seat_map[i][j] = file[k++];  //writing 1D array into a 2D array
        }
    }
}

void PrintSeatMap(char seat_map[MAX_ROWS][MAX_COLS], int rows, int cols)
{
    printf("%11s", "");
    for(int i = 0; i < cols; i++)
    {
        printf("Seat %d ", i+1);
    }
    printf("\n");

    for (int i = 0; i<rows; i++)
    {
        printf("Row %c", 'A'+i);
        for(int j=0; j<cols; j++)
        {
            printf("%7c", seat_map[i][j]);
        }
        printf("\n");
    }
}

int IsSeatSold(char seat_map[MAX_ROWS][MAX_COLS], int row, int col)
{
    int value;
    if (seat_map[row][col] == 'X')
    {
        value = 1;
    }
    else
    {
        seat_map[row][col] = 'X';
        value =0;
    }
    return value;
}

void WriteMovieTheater(char seat_map[MAX_ROWS][MAX_COLS], int row, int col)  //writing 2D array into a file
{
    char hold[100] = {};
    FILE *Output = NULL;
    printf("Enter output filename ");
    scanf("%s", hold);
    Output = fopen(hold, "w+");
    if (Output == NULL)
    {
        printf("File did not open...exiting");
        exit(0);
    }
    fprintf(Output, "%d %d\n", row, col);
    for(int i =0; i<row; i++)
    {
        for(int j = 0; j<col; j++)
        {
            fprintf(Output, "%c", seat_map[i][j]);
        }
    }
    fclose(Output);    
}

int main()
{
    char MovieTheater[MAX_ROWS][MAX_COLS]={};
    int rows = 0, cols = 0, tickets = 0, tickets_sold = 0;
    int ArrayRow, ArrayCol;
    char Row;
    int Seat;
    FILE *FH = NULL;
    char file[100] = {};
    char array[MAX_ROWS*MAX_COLS] = {};

    printf("Enter the name of your Movie Theater file ");
    scanf("%s", file);
    FH = fopen(file, "r+");
    if (FH == NULL)
    {
        printf("File did not open...exiting");
        exit(0);
    }
    fscanf(FH, "%s", array);
    rows = atoi(array);
    fscanf(FH, "%s", array);
    cols = atoi(array);
    fgets(array, sizeof(array)-1, FH);
    fgets(array, sizeof(array)-1, FH);
    fclose(FH);

    FillMovieTheater(MovieTheater, rows, cols, array);

    printf("How many tickets would you like to purchase? (limit %d) ", TICKET_LIMIT);
    scanf("%d", &tickets);

        
    while (tickets < 0 || tickets > TICKET_LIMIT)
    {
        printf("This is a special showing - limit of %d tickets per purchase\n", TICKET_LIMIT);
        printf("How many tickets would you like to purchase? (limit %d) ", TICKET_LIMIT);
        scanf("%d", &tickets);
    }
    if (tickets == 0)
    {
        printf("No movie for you!\n");  
    }
    else
    {
        while (tickets_sold < tickets && tickets != 0)
        {
            PrintSeatMap(MovieTheater, rows, cols);
            printf("\n\nEnter seat choice by entering the row and seat.\nPlease pick a seat ");
            scanf(" %c%d", &Row, &Seat);
            printf("\n");
            Row = toupper(Row);
            ArrayRow = Row - 'A';
            ArrayCol = Seat - 1;
            if (ArrayRow >= 0 && ArrayRow < rows && ArrayCol >= 0 && ArrayCol < cols)
            {
                if (!IsSeatSold(MovieTheater, ArrayRow, ArrayCol))
                {
                    MovieTheater[ArrayRow][ArrayCol] = 'X';
                    tickets_sold++;
                }
                else
                {
                    printf("Seat %c%d is already sold. Pick a different seat.\n", Row, Seat);
                }
            }
            else
            {
                printf("That seat is not in this theater!!\n");
            }
        }
        printf("\nPlease find your way to your seats using this map...\n\n");
        PrintSeatMap(MovieTheater, rows, cols);
        printf("\nEnjoy your movie!\n");
    }
    WriteMovieTheater(MovieTheater, rows, cols);

    return 0;
}