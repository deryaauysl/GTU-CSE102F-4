#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining structure for modifying module
typedef struct
{
    int scalar;
    char module_id[30];

    // using for control module include * or not
    int flag;

} module_t;

// function for parse modules
void parse(char *input, module_t module[100], int *number_of_terms)
{
    int scalar;
    char id[30];
    int i = 0;
    int flag = 0;

    // tokenize modules
    char *token = strtok(input, "+");
    while (token != NULL)
    {
        // take scalar and id values of module
        if (sscanf(token, "%d * %s", &scalar, id) == 2)
        {
            // copy id string to real module_id
            strcpy(module[i].module_id, id);
            module[i].scalar = scalar;
            // flag equal to 1 if you use scalar and id together
            module[i].flag = 1;
        }
        else if (sscanf(token, "%d", &module[i].scalar) == 1)
        {
            // flag equal to 0 if you dont use scalar and id together
            module[i].flag = 0;
        }

        i++;
        // skip another token
        token = strtok(NULL, "+");
    }
    // control number of terms
    (*number_of_terms) = i;
}

// function for evaluating modules
int evaluate(char *modul)
{
    // defining structures
    module_t module[100];

    int number_of_terms = 0;
    double sum = 0, result = 0;
    char input[1000];
    int i;

    printf("Define %s:\n", modul);

    // taking the main module
    fgets(input, sizeof(input), stdin);

    // parse this module
    parse(input, module, &number_of_terms);

    for (i = 0; i < number_of_terms; i++)
    {
        // if you find * sign
        if (module[i].flag == 1)
        {
            result = evaluate(module[i].module_id);
            sum += result * module[i].scalar;
        }
        // if you dont find * sign
        else
        {
            sum += module[i].scalar;
        }
    }

    return sum;
}

int main()
{
    int final_result = 0;
    char modul_name[30];

    printf("Module name?:\n");
    scanf("%s", modul_name);

    // getchar for removing \n character that scanf put beginning the stack
    getchar();

    // evalueate and print
    final_result = evaluate(modul_name);
    printf("%d\n", final_result);

    return 0;
}