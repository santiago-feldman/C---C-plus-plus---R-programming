/***************************************************************************//**
  @file     +gameoflifev1.c+
  @brief    +Finite & preset world implementation of Conway´s Game of Life+
  @author   +Santiago Feldman+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define WIDTH   25
#define HEIGHT  20
#define DEAD    ' '
#define ALIVE   '*'
#define QUIT    'q'	 

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
char world[HEIGHT][WIDTH];

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/* initialize_world -- set up world, all cells initialized 
* to DEAD or ALIVE  
*/ 
void initialize_world(void); 

/* output_world - outputs the current world state to the console  
*/ 
void output_world(void); 

/* update_world - updates the current world to the next generation
*/
void update_world(void);


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int main(void)
{

    printf("Welcome to Conway's Game of Life!\n"
            "Rules:\n"
            "\t* Enter the number of generations you would like to advance\n"
            "\t* Press enter to advance only one generation\n"
            "\t* Press q to quit\n"
            "Current state of the world:\n");
        
    initialize_world();
    output_world();

    int num_gen = 0;
    char invalid_flag = 0;
    char c = 0;

    while(c != QUIT)
    {
        c = getchar();

        if(c == QUIT)
        {
            num_gen = 0;
            printf("Thank you for playing!\n");
        }
        else if (c == '\n')
        {
            num_gen = 1;
        }
        else if(c >= '0' && c <= '9')
        {
            do
            {
                num_gen = num_gen * 10 + (c - '0');
                c = getchar();
            }
            while (c >= '0' && c <= '9');

            if(c != '\n')
            {
                printf("Invalid expression. Please try again:\n");
                num_gen = 0;
                invalid_flag = 1;
            }
        }
        else
        {
            printf("Invalid character. Please try again:\n");
            invalid_flag = 1;
        }

        while (num_gen != 0)
        {
            update_world();
            --num_gen;
        }

        if(invalid_flag == 0)
            output_world();
        else
        {
            while ((c = getchar()) != '\n' && c != EOF);    // Empty the getchar() buffer
            invalid_flag = 0;
        }
    }

    return 0;
}

void initialize_world(void)
{
    //Alive and dead cells pattern for initialization
    char pat[]={ALIVE,DEAD,ALIVE,DEAD,DEAD,ALIVE,ALIVE};   
    int size_pat = sizeof(pat)/sizeof(pat[0]);

    int i, j, k = 0;
    for (i = 0; i < HEIGHT; ++i)
    {
        for (j = 0; j < WIDTH; ++j)
        {
            world[i][j] = pat[k];
            k = (k == size_pat-1) ? 0 : k+1;
        }
    }
}

void output_world(void)
{
    int i, j;
    for ( i = 0; i < HEIGHT; ++i)
    {
        for ( j = 0; j < WIDTH; ++j)
        {
            printf("|%c", world[i][j]);
        }
        printf("|\n");
    }
}

void update_world(void)
{
    char ln;                        // Living neighbors 
    char temp[HEIGHT][WIDTH];       // Temporary matrix for updating world
    int i, j;

    // Check all surrounding neighbor cells
    for (i = 0; i < HEIGHT; ++i)
    {
        for(j = 0; j < WIDTH; ++j)
        {
            ln = 0;                 // Reset counter

            if (i != 0)
            {
                if(world[i-1][j] == ALIVE) ++ln;           
                if ((j != 0) && (world[i-1][j-1] == ALIVE)) ++ln;
                if ((j != WIDTH-1) && (world[i-1][j+1] == ALIVE)) ++ln; 
            }

            if (i != HEIGHT-1)
            {
                if(world[i+1][j] == ALIVE) ++ln;           
                if ((j != 0) && (world[i+1][j-1] == ALIVE)) ++ln;
                if ((j != WIDTH-1) && (world[i+1][j+1] == ALIVE)) ++ln; 
            }

            if((j != 0) && (world[i][j-1] == ALIVE)) ++ln;
            if((j != WIDTH-1) && (world[i][j+1] == ALIVE)) ++ln;
        
            if(world[i][j] == DEAD)
                temp[i][j] = (ln == 3) ? ALIVE : DEAD;
            else
                temp[i][j] = ((ln == 2) || (ln == 3)) ? ALIVE : DEAD;
        }
    }

    // Update to next generation
    for (i = 0; i < HEIGHT; ++i)
    {
        for (j = 0; j < WIDTH; ++j)
        {
            world[i][j] = temp[i][j];
        }
    }
}