// Standard Libraries included
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Macros Defining.
#define Grid 20
#define n_Population 800
#define Maximum_iterations 3000
#define inner_size (Grid - 2)
#define W_l 2
#define W_t 2
#define W_f 3
const char emptySpace = ' ';
const char obstacle = 178;
const char start = 219;
const char goal = 219;
const char rStep = 46; // 46


// Functions Declarations.
void RandomPopulation();
void ChangedPopulation(int random_population[n_Population][inner_size], int changed_population[n_Population][Grid]);
void turns_storing(int changed_population[n_Population][Grid]);
void path_inf_storing(int changed_population[n_Population][Grid]);
void MinimumMaximum();
void Fitness();
void Parents(int random_population[n_Population][inner_size], float fit_val[n_Population]);
void CrossOver(int random_population[n_Population][inner_size]);
void Mutation(int random_population[n_Population][inner_size]);
void Display_function(int Grid_Define[Grid][Grid], int dir_bit[n_Population], int or_bit[n_Population]);
int Solution(float fit_val[n_Population]);


// Global variables and arrays.
int Grid_Define[Grid][Grid] =
     {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
     {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
     {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
     {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
     {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
     {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
     {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
     {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
     {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
     {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0}};


char sGrid[Grid][Grid];
int dir_bit[n_Population];
int or_bit[n_Population];
int minimum[3], maximum[3];
int random_population[n_Population][inner_size];
int changed_population[n_Population][Grid];
int turns_population[n_Population];
int length_population[n_Population];
int infeasible_population[n_Population];
int Sol = 0;
float fit_val[n_Population];
int iter = 0;
FILE *fp;

// Functions Definitions.
// FOr generating random Populations 
void RandomPopulation()
{
    srand(time(NULL)); 
    for (int i = 0; i < n_Population; i++)
    {
        for (int j = 0; j < inner_size; j++)
            random_population[i][j] = rand() % Grid; //for storing numbers between 0 and grid
        dir_bit[i] = rand() % 2;                     // for getting between 0 and 1
        or_bit[i] = rand() % 2;
    } 
}

// Changed population will assign first column as 0 and last column as grid-1
void ChangedPopulation(int random_population[n_Population][inner_size], int changed_population[n_Population][Grid])
{ 
    for (int i = 0; i < n_Population; i++)
    {
        changed_population[i][0] = 0;      
        for (int j = 0; j < Grid - 1; j++)
        {
            changed_population[i][j + 1] = random_population[i][j]; // Copying the data of changed population to random population
        }
        changed_population[i][Grid - 1] = (Grid - 1);
    }
}

// For turns storing, we will check whether 1st and 2nd index are equal or not and then increment.
void turns_storing(int changed_population[n_Population][Grid])
{
    int turn = 0;
    for (int i = 0; i < n_Population; i++)
    {
        for (int j = 0; j < Grid - 1; j++) // Grid-1 = representing the comparison of one value with other only.
        {
            if (changed_population[i][j] != changed_population[i][j + 1])
            {
                turn++;
            }
        }
        turns_population[i] = turn; // Storing the turns in an array of turns
        turn = 0;                   
    }
}

// For Path length and infeasible steps.
void path_inf_storing(int changed_population[n_Population][Grid])
{                                     
    int length = 0, decision_bit = 0; 
    // In decision_bit = 0, it is for column fiirst and for 1 , it is for row first
    int k = 0, infeasible_population_step = 0;

    for (int i = 0; i < n_Population; i++)
    { // Only if "XOR" is '0' then decision_bit is '0'.
        if ((dir_bit[i] ^ or_bit[i]) == 0)
        {
            decision_bit = 0;
        }
        else
        {
            decision_bit = 1;
        }
        if ((Solution(fit_val) == 1) && (i == Sol))
        {                          // If solution is found then printing coordinates will be as.
            if (decision_bit != 0) // 
            {
                printf("(0 , 0), "); // For desicion_bit != 0.
            }
        }
        for (int j = 0; j < (Grid - 1); j++) 
        // Grid - 1 is used because we are comparing with next element.
        {                                    
            if (changed_population[i][j + 1] > changed_population[i][j])  // if next value is greater than previous one.
            {                                                   
                while (k != ((changed_population[i][j + 1]) + 1)) //+ 1 because to iterate one more time to get the correct result.
                {
                    if (or_bit[i] == 0) // Column-Wise Approach
                    {
                        if ((Solution(fit_val) == 1) && (i == Sol))
                        {
                            printf("(%d , %d), ", k, j + decision_bit);
                            sGrid[k][j + decision_bit] = rStep; 
                            // The place of grid is assigned
                        }
                        if (Grid_Define[k][j + decision_bit] == 1)
                        {
                            infeasible_population_step++; //verifying infeasible step by comparing it with the obstacles given above
                        }
                    }
                    else // Row-Wise Approach
                    {
                        if ((Solution(fit_val) == 1) && (i == Sol))
                        {
                            printf("(%d , %d), ", j + decision_bit, k); // the column are inverted into rows for row-wise approach.
                            sGrid[j + decision_bit][k] = rStep;
                        }

                        if (Grid_Define[j + decision_bit][k] == 1)
                        {
                            infeasible_population_step++;
                        }
                    }
                    k++;      // Loop control variable.
                    length++; // Path length increment.
                }
                k--; // to assign the previous value.
            }
            else                                                 
            {                                                    
                while (k != ((changed_population[i][j + 1]) - 1)) // to get the previous value and compared
                {
                    if (or_bit[i] == 0) // Column-Wise Approach.
                    {
                        if ((Solution(fit_val) == 1) && (i == Sol)) 
                        {
                            printf("(%d , %d), ", k, j + decision_bit); 
                            sGrid[k][j + decision_bit] = rStep;         // Same direction in every column wise and coordinates change will be in 2nd coordinate.
                        }

                        if (Grid_Define[k][j + decision_bit] == 1)
                        {
                            infeasible_population_step++; // Infeasible steps detection
                        }
                    }
                    else // Row-Wise Approach.
                    {
                        if ((Solution(fit_val) == 1) && (i == Sol))
                        {
                            printf("(%d , %d), ", j + decision_bit, k);
                            sGrid[j + decision_bit][k] = rStep; // The direction of coordinates are reversed in row-wise approach
                        }
                        if (Grid_Define[j + decision_bit][k] == 1)
                        {
                            infeasible_population_step++;
                        }
                    }
                    k--;      // Loop control decreament.
                    length++; 
                }
                k++; //to assigning next value
            }
        }
        if ((Solution(fit_val) == 1) && (i == Sol))
        {
            if (decision_bit == 0)
            {
                printf("(%d , %d)", Grid - 1, Grid - 1); // Printing purpose.
            }
        }
        length_population[i] = length;                         // Storing actual path length in array
        length = 0;                                            // Stating to 0 for next increment
        infeasible_population[i] = infeasible_population_step; // Storing value of infeasibl steps in an array
        infeasible_population_step = 0;                        // Stating to 0 for next increment
        k = 0;                                                 // Stating to 0 for next increment
    }
}

// MinimumMaximum Function to normalize the values. 
void MinimumMaximum()
{
    // We used maximum and minimum function to normalize our turns, paths, infeasible between 0 and 1 by comparing their minimum and maximum values
    // For Turns:
    minimum[0] = turns_population[0]; 
    maximum[0] = turns_population[0];
    // For Path Length:
    minimum[1] = length_population[0]; 
    maximum[1] = length_population[0];
    // For steps_inf:
    minimum[2] = infeasible_population[0]; 
    maximum[2] = infeasible_population[0];
    for (int i = 0; i < n_Population; i++)
    {
        if (turns_population[i] < minimum[0]) // Comparison between array of turns and minimum turns and store that in array
        {
            minimum[0] = turns_population[i];
        }
        if (turns_population[i] > maximum[0]) // Comparison between array of turns and maximum turns and store that in array
        {
            maximum[0] = turns_population[i];
        }
        // For PATH-LENGTH:
        if (length_population[i] < minimum[1]) // Comparison between array of turns and minimum path length and store that in array
        {
            minimum[1] = length_population[i];
        }
        if (length_population[i] > maximum[1]) // Comparison between array of turns and maximum path length and store that in array
        {
            maximum[1] = length_population[i];
        }
        if (infeasible_population[i] < minimum[2]) // Comparison between array of turns and maximum infeasible steps and store that in array
        {
            minimum[2] = infeasible_population[i];
        }
        if (infeasible_population[i] > maximum[2]) // Comparison between array of turns and maximum infeasible steps and store that in array
        {
            maximum[2] = infeasible_population[i];
        }
    }
}

// Fitness is calculated for final turns, length and infeasible steps by putting their values in their formula
void Fitness()
{
    float Final_turns, Final_length, Final_inf;
    int S_minimum = 0; //Minimum obstacle must be zero for a optimum path
    for (int i = 0; i < n_Population; i++)
    {
        Final_turns = 1 - (float)(turns_population[i] - minimum[0]) / (maximum[0] - minimum[0]);
        Final_length = 1 - (float)(length_population[i] - minimum[1]) / (maximum[1] - minimum[1]);
        Final_inf = 1 - (float)(infeasible_population[i] - S_minimum) / (maximum[2] - S_minimum);
        fit_val[i] = (100 * W_f * Final_inf) * (float)((W_l * Final_length) + (W_t * Final_turns)) / (W_l + W_t); // FInal Fitness of each population.
    }
}

// Parent Selection is done of fitness value and their population value by bubble sorting their values in assending order
void Parents(int random_population[n_Population][inner_size], float fit_val[n_Population])
{
    // Selection according to the fitness value.
    int temp = 0;
    int Temp_arr[inner_size];

    for (int i = 0; i < n_Population; i++)         
    {                                              
        for (int j = i + 1; j < n_Population; j++) 
        {                                          
            if (fit_val[j] > fit_val[i])
            {
                // Fit_val[j] is higher than fit_val[i], This condition is used because we have to sort
                // the population in such a way that their highest fitness would be at higher order
                for (int k = 0; k < inner_size; k++)
                {
                    Temp_arr[k] = random_population[i][k];
                }
                for (int k = 0; k < inner_size; k++)
                {
                    random_population[i][k] = random_population[j][k];
                }
                for (int k = 0; k < inner_size; k++)
                {
                    random_population[j][k] = Temp_arr[k]; 
                }
                // Bubble sorting

                // bubble sorting of the fitness
                temp = fit_val[i]; 
                fit_val[i] = fit_val[j];
                fit_val[j] = temp;
                temp = 0;
                // Bubble sorting of the orientation bit
                temp = or_bit[i]; 
                or_bit[i] = or_bit[j];
                or_bit[j] = temp;
                temp = 0;
                // Bubble sorting of the direction bit
                temp = dir_bit[i]; 
                dir_bit[i] = dir_bit[j];
                dir_bit[j] = temp;
            }
        }
    }
}

// Crossover is done after parent selection so that if we have the population with less fitness, they will cross over 
// to increase their fitness value and crossover is done at random point.
void CrossOver(int random_population[n_Population][inner_size])
{ 
    srand(time(NULL));
    int cross_point = (rand() % (inner_size - 1)) + 1; 
    int temp_arr[inner_size - cross_point]; // For storing half values in array.

    int k = 0;
    for (int i = 0; i < n_Population; i++)   
    {                                       
        for (int j = 0; j < inner_size; j++) 
        {
            random_population[k + (n_Population / 2)][j] = random_population[i][j];
          // Next half of the population is bubble-sorted.
        }
        k++;
    }
    for (int i = (n_Population / 2); i < n_Population; i = i + 2) // For interchanging the values of two population with other two populations.
    {
        for (int j = 0; j < (inner_size - cross_point); j++)
        {                                                    
            temp_arr[j] = random_population[i + 1][j + cross_point];
        }
        for (int j = 0; j < (inner_size - cross_point); j++)
        {

            random_population[i + 1][j + cross_point] = random_population[i][j + cross_point];
        }
        for (int j = 0; j < (inner_size - cross_point); j++)
        {

            random_population[i][j + cross_point] = temp_arr[j];
        }
    }
}

// Fittest population's direction and orientation is mutated at random point after skipping 3 populations
void Mutation(int random_population[n_Population][inner_size])
{
    srand(time(NULL));
    for (int i = 0; i < n_Population; i = i + 1)
    {
        
        int index = rand() % inner_size;
        int val = rand() % Grid;      
        random_population[i][index] = val;
    }
    for (int i = (n_Population / 2); i < n_Population; i = i + 3) 
    {
        or_bit[i] = rand() % 2;
        dir_bit[i] = rand() % 2;
    }
}

// Solution is calculated from the fitness and infeasible step.
int Solution(float fit_val[n_Population])
{
    for (int i = 0; i < n_Population; i++)
    {
        if (fit_val[i] == 300.00 && infeasible_population[i] == 0) 
        {
            Sol = i;
            // Storing the Solution at the index so it will print on board.
            return 1;
        }
    }
    return 0;
}

// This final display function will display the direction bit, orientation bit, turns, path length, infeasible steps and board grid on 
// the terminal and in the file.
void Display_function(int Grid_Define[Grid][Grid], int dir_bit[n_Population], int or_bit[n_Population])
{
    fprintf(fp, "[ 0 ");
    printf("\n[ 0 ");
    for (int i = 0; i < inner_size; i++)
    {
        fprintf(fp, "%d ", random_population[Sol][i]);
        printf("%d ", random_population[Sol][i]);
    }
    fprintf(fp, "%d ]\n", Grid - 1);
    printf("%d ]\n", Grid - 1);
    fprintf(fp, "\nor_bit  = %d\n", or_bit[Sol]);   // Displaying orientation
    fprintf(fp, "dir_bit    = %d\n", dir_bit[Sol]); // Displaying Direction
    fprintf(fp, "No. of turns = %d\n", turns_population[Sol]);  //Dislaying turns
    fprintf(fp, "length_population  = %d\n", length_population[Sol]);   // Displaying path length
    fprintf(fp, "Infesible _Steps = %d\n", infeasible_population[Sol]); // Displaying Infeasible steps.
    fprintf(fp, "Fitness = %0.2f\n", fit_val[Sol]); // Displaying Fitness
    printf("\n---------------------------------------\n");
    printf("\nOrientation  = %d\t", or_bit[Sol]);
    printf("Direction = %d\t\n", dir_bit[Sol]);
    printf("Turns = %d\t\t", turns_population[Sol]);
    printf("Path Length = %d\t\t", length_population[Sol]);
    printf("Infeasible Steps = %d\t\n", infeasible_population[Sol]);
    printf("Fitness = %0.2f\n", fit_val[Sol]);
    printf("\n---------------------------------------\n  ");
    for (int i = 0; i < Grid; i++)
    {
        for (int j = 0; j < Grid; j++)
        {
            if (Grid_Define[i][j] == 0)
            {
                sGrid[i][j] = ' ';
            }
            else if (Grid_Define[i][j] == 1)
            {
                sGrid[i][j] = obstacle;
            }
        }
    }
    printf("\n");
    path_inf_storing(changed_population); // For printing the steps of solved population.
    printf("\b\n");
    sGrid[0][0] = start;
    sGrid[Grid - 1][Grid - 1] = goal;
    printf("\n---------------------------------------");
    // Displaying Grid
    for (int i = 0; i < Grid; i++)
    {
        fprintf(fp, "\n%2d|", i);
        for (int j = 0; j < Grid; j++)
        {
            fprintf(fp, "%c", sGrid[i][j]);
            fprintf(fp, "|");
        }

        printf("\n%2d|", i);
        for (int j = 0; j < Grid; j++)
        {
            printf("%c", sGrid[i][j]);
            printf("|");
        }
    }

    fprintf(fp, "\n---------------------------------------\n");
    printf("\n---------------------------------------\n  ");
    for (int i = 0; i < Grid; i++)
    {
        fprintf(fp, " %2d", i);
        printf(" %2d", i);
    }
    printf("\n");
    fclose(fp);
}
// End of a program.