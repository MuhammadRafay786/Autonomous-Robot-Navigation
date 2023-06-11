#include<stdio.h>
#include"RobotNavigation_Using_GA.h"

// Main Function.
int main()
{
    fp = fopen("rafay.csv", "a+");      // FOr reading and writing mode
    int flag = 0;
    RandomPopulation();
    while (iter < Maximum_iterations && flag == 0) //
    {
        ChangedPopulation(random_population, changed_population);
        turns_storing(changed_population);
        path_inf_storing(changed_population);
        MinimumMaximum();
        Fitness();
        flag = Solution(fit_val);
        if (flag == 1)
        {
            break;
        }
        Parents(random_population, fit_val);
        fprintf(fp, "Number of generation,%d\t, Turns,%d\t, Path length,%d\t, Inf Steps,%d\t, Fitness,%.2f\t\n", iter, turns_population[0], length_population[0], infeasible_population[0], fit_val[0]);
        // printing the fittest values of all parametre for graph
        CrossOver(random_population);
        Mutation(random_population);
        printf("Generation = %d.\n", iter);
        iter++;
    }
    if (flag == 1)
    {
        fprintf(fp, "\nSolution found in %d generations.\n", iter);
        printf("\nSolution found in %d generations.\n", iter);
        Display_function(Grid_Define, dir_bit, or_bit);
    }
    else
    {
        printf("No solution found.");
    }

    return 0;
}

// End of a program.