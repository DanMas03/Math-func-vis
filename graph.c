#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "parser.h"
#include "evaluator.h"
#include "validator.h"
#include "ps_creator.h"
#include "convertor.h"
#include "consts.h"
void run_test(const char *func, const char *path, const char *lim);

/**
 * @brief Entry point of the application.
 * 
 * @param argc Number of command line arguments 
 * @param argv Arguments
 * @return int
 */
int main(int argc, char *argv[]){

    if(argc < 3){
        printf("Missing arguments!\n"
        "Program needs 2 arguments for functioning, function (for example sin(x)) and postscript output file(example.ps).\n"
        "Optional argument can also be added to determine how big the graph should be (for example: [10,10])\n.");

        return 1;
    } 
    graph_limits *limits;

    
    char *func = argv[1];
    char *path = argv[2];
    char *lim = 0;
    if(argc>3)
    {
        lim = argv[3];
    }
    
    int tok_cnt = validate_function(func);
    
    if(!tok_cnt)
    {
        printf("Error! Invalid function!\n");
        return 2;
    }
    tok_cnt++;//space for end token
    int is_valid_file = is_ps_file(path);
    if(!is_valid_file)
    {
        printf("Error! Invalid file name!\n");
        return 3;
    }
    
    limits = parse_limits(lim);
    if(!limits->x_start && !limits->x_end && !limits->y_start && !limits->y_end)
    {
        printf("Error! Invalid limits!\n");
        free_limits(&limits);

        return 4;
    }
    token *infix = (token*)malloc(tok_cnt * sizeof(token));
    token *postfix= (token*)malloc(tok_cnt * sizeof(token));
    int count = tokenize(func, infix, tok_cnt);
    int rpn_cnt = 0;
    
    convert_to_rpn(infix, count, postfix, &rpn_cnt,tok_cnt);
    free(infix);
    if(!create_postscript_file(path, postfix, rpn_cnt, *limits, func,tok_cnt))
    {
        printf("Error creating PostScript file!\n");
        free(postfix);
        free_limits(&limits);
        return 3;
    }

    free(postfix);
    free_limits(&limits);
    return 0;
}