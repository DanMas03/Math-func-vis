#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

// List of recognized function names
const char *FUNCTIONS[] = {"sin", "cos", "tan",
                           "asin", "acos", "atan",
                           "sinh", "cosh", "tanh",
                           "log", "ln", "exp", "sqrt", "abs"};

/**
 * @brief Checks if the given string is a recognized function.
 *
 * This function compares the input string with a predefined list of function names
 * and returns 1 if it matches any of them, otherwise returns 0.
 *
 * @param func The input string to check.
 * @return 1 if the input string is a recognized function, 0 otherwise.
 */
int is_function(const char *func)
{
    if (func == NULL)
        return 0;

    int count = sizeof(FUNCTIONS) / sizeof(FUNCTIONS[0]);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(func, FUNCTIONS[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Checks if the given filename has a .ps extension.
 *
 * This function checks if the input filename ends with the .ps extension
 * and returns 1 if it does, otherwise returns 0.
 *
 * @param filename The input filename to check.
 * @return 1 if the filename ends with .ps, 0 otherwise.
 */
int is_ps_file(const char *filename)
{
    if (filename == NULL)
        return 0;

    const char *ext = strrchr(filename, '.');
    return (ext && strcmp(ext, ".ps") == 0);
}
/**
 * @brief checks if file can be created
 * 
 * @param filename The input filename to check.
 * @return int 1 if file can be created
 */
int can_create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fclose(file);       
        remove(filename);   
        return 1;           
    }
    return 0;              
}

/**
 * @brief Processes an alphabetic sequence in the input string.
 *
 * This function processes a sequence of alphabetic characters, determines if it is a valid
 * function or variable, and updates the state variables accordingly. It also handles errors
 * related to invalid functions or missing operators.
 *
 * @param cursor Pointer to the current position in the input string.
 * @param last_c_func Pointer to the last function state variable.
 * @param last_c_operand Pointer to the last operand state variable.
 * @param last_c_operator Pointer to the last operator state variable.
 * @param last_c_lbr Pointer to the last left bracket state variable.
 * @param last_c_rbr Pointer to the last right bracket state variable.
 * @return 1 if the sequence is valid, 0 otherwise.
 */
int process_alpha(const char **cursor, int *last_c_func, int *last_c_operand, int *last_c_operator, int *last_c_lbr, int *last_c_rbr)
{
    if (cursor == NULL || *cursor == NULL || last_c_func == NULL || last_c_operand == NULL || last_c_operator == NULL || last_c_lbr == NULL || last_c_rbr == NULL)
    {
        return 0;
    }

    char buffer[32]; // Buffer to store the alphabetic sequence
    int len = 0;     // Length of the sequence

    // Read the alphabetic sequence
    while (isalpha(**cursor))
    {
        if (len < (int)sizeof(buffer) - 1)
        {
            buffer[len] = **cursor;
            len++;
        }
        (*cursor)++;
    }
    buffer[len] = '\0'; // Null-terminate the buffer

    // Check if the sequence is a valid function or variable
    if (*last_c_operator || *last_c_lbr || (!*last_c_func && !*last_c_rbr && !*last_c_operand))
    {
        if (is_function(buffer))
        {
            *last_c_func = 1;
            *last_c_operand = 0;
            *last_c_operator = 0;
            *last_c_lbr = 0;
            *last_c_rbr = 0;
        }
        else if (strcmp(buffer, "x") == 0)
        {
            *last_c_operand = 1;
            *last_c_operator = 0;
            *last_c_func = 0;
            *last_c_lbr = 0;
            *last_c_rbr = 0;
        }
        else
        {
            
            return 0;
        }
    }
    else
    {
        
        return 0;
    }
    return 1;
}

/**
 * @brief Processes a numeric sequence in the input string.
 *
 * This function processes a sequence of numeric characters, including handling decimal points,
 * and updates the state variables accordingly. It also handles errors related to invalid number
 * formats or missing operators.
 *
 * @param cursor Pointer to the current position in the input string.
 * @param last_c_operand Pointer to the last operand state variable.
 * @param last_c_operator Pointer to the last operator state variable.
 * @param last_c_func Pointer to the last function state variable.
 * @param last_c_lbr Pointer to the last left bracket state variable.
 * @param last_c_rbr Pointer to the last right bracket state variable.
 * @return 1 if the sequence is valid, 0 otherwise.
 */
int process_number(const char **cursor, int *last_c_operand, int *last_c_operator, int *last_c_func, int *last_c_lbr, int *last_c_rbr)
{
    if (cursor == NULL || *cursor == NULL || last_c_operand == NULL || last_c_operator == NULL || last_c_func == NULL || last_c_lbr == NULL || last_c_rbr == NULL)
    {
        return 0;
    }

    int dot_cnt = 0;  // Counter for decimal points
    int e_cnt = 0;    // Counter for 'e' or 'E'
    int sign_cnt = 0; // Counter for '+' or '-'

    // Read the numeric sequence
    while (isdigit(**cursor) || **cursor == '.' || **cursor == 'e' || **cursor == 'E' || **cursor == '+' || **cursor == '-')
    {
        if (**cursor == '.')
        {
            dot_cnt++;
            if (dot_cnt > 1 || e_cnt > 0)
            {
                
                return 0;
            }
        }
        else if (**cursor == 'e' || **cursor == 'E')
        {
            e_cnt++;
            if (e_cnt > 1 || !isdigit(*(*cursor - 1)))
            {
                
                return 0;
            }
            sign_cnt = 0; // Reset sign counter after 'e' or 'E'
        }
        else if (**cursor == '+' || **cursor == '-')
        {
            sign_cnt++;
            if (sign_cnt > 1 && !isdigit(*(*cursor + 1)))
            {
                
                return 0;
            }
        }
        (*cursor)++;
    }

    // Check if the sequence is valid
    if (*last_c_operator || *last_c_lbr || (!*last_c_func && !*last_c_rbr && !*last_c_operand))
    {
        *last_c_operand = 1;
        *last_c_operator = 0;
        *last_c_func = 0;
        *last_c_lbr = 0;
        *last_c_rbr = 0;
    }
    else
    {
        
        return 0;
    }
    return 1;
}

/**
 * @brief Processes an opening bracket in the input string.
 *
 * This function processes an opening bracket, updates the bracket balance and state variables
 * accordingly, and handles errors related to missing operators before the bracket.
 *
 * @param br_balance Pointer to the bracket balance variable.
 * @param last_c_func Pointer to the last function state variable.
 * @param last_c_operator Pointer to the last operator state variable.
 * @param last_c_operand Pointer to the last operand state variable.
 * @param last_c_lbr Pointer to the last left bracket state variable.
 * @param last_c_rbr Pointer to the last right bracket state variable.
 * @return 1 if the bracket is valid, 0 otherwise.
 */
int process_bracket_open(int *br_balance, int *last_c_func, int *last_c_operator, int *last_c_operand, int *last_c_lbr, int *last_c_rbr)
{
    if (br_balance == NULL || last_c_func == NULL || last_c_operator == NULL || last_c_operand == NULL || last_c_lbr == NULL || last_c_rbr == NULL)
    {
        return 0;
    }

    // Check if the opening bracket is valid
    if (*last_c_func || *last_c_operator||( !*last_c_operand && !*last_c_rbr))
    {
        *last_c_lbr = 1;
        *last_c_rbr = 0;
        *last_c_func = 0;
        *last_c_operand = 0;
        *last_c_operator = 0;
        (*br_balance)++;
        return 1;
    }
    else
    {
    
        return 0;
    }

}

/**
 * @brief Processes a closing bracket in the input string.
 *
 * This function processes a closing bracket, updates the bracket balance and state variables
 * accordingly, and handles errors related to missing opening brackets or empty brackets.
 *
 * @param br_balance Pointer to the bracket balance variable.
 * @param last_c_operator Pointer to the last operator state variable.
 * @param last_c_operand Pointer to the last operand state variable.
 * @param last_c_lbr Pointer to the last left bracket state variable.
 * @param last_c_rbr Pointer to the last right bracket state variable.
 * @return 1 if the bracket is valid, 0 otherwise.
 */
int process_bracket_close(int *br_balance, int *last_c_operator, int *last_c_operand, int *last_c_lbr, int *last_c_rbr, int *last_c_func)
{
    if (br_balance == NULL || last_c_operator == NULL || last_c_operand == NULL || last_c_lbr == NULL || last_c_rbr == NULL || last_c_func == NULL)
    {
        return 0;
    }

    // Check if the closing bracket is valid
    if (*br_balance == 0)
    {
        
        return 0;
    }
    else if (*last_c_lbr)
    {
        
        return 0;
    }
    else
    {
        *last_c_operator = 0;
        *last_c_operand = 0;
        *last_c_func = 0;
        *last_c_lbr = 0;
        *last_c_rbr = 1;
        (*br_balance)--;
    }
    return 1;
}

/**
 * @brief Processes an operator in the input string.
 *
 * This function processes an operator, updates the state variables accordingly, and handles
 * errors related to missing operands before the operator.
 *
 * @param cursor Pointer to the current position in the input string.
 * @param last_c_operator Pointer to the last operator state variable.
 * @param last_c_operand Pointer to the last operand state variable.
 * @param last_c_rbr Pointer to the last right bracket state variable.
 * @return 1 if the operator is valid, 0 otherwise.
 */
int process_operator(const char **cursor, int *last_c_operator, int *last_c_operand, int *last_c_rbr, int *last_c_func, int *last_c_lbr)
{
    if (cursor == NULL || *cursor == NULL || last_c_operator == NULL || last_c_operand == NULL || last_c_rbr == NULL || last_c_func == NULL || last_c_lbr == NULL)
    {
        return 0;
    }

    // Check if the operator is valid
    if (*last_c_operand || *last_c_rbr)
    {
        *last_c_operator = 1;
        *last_c_operand = 0;
        *last_c_func = 0;
        *last_c_lbr = 0;
        *last_c_rbr = 0;
        (*cursor)++;
    }
    else
    {
        
        return 0;
    }
    return 1;
}

/**
 * @brief Validates the syntax of a mathematical function string.
 *
 * This function validates the syntax of a given mathematical function string by processing
 * each character and ensuring that the sequence of tokens (functions, variables, numbers,
 * operators, and brackets) is correct. It handles various syntax errors and maintains the
 * balance of brackets.
 *
 * @param function The input mathematical function string to validate.
 * @return 1 if the function string is valid, 0 otherwise.
 */
int validate_function(const char *function)
{
    if (function == NULL)
        return 0;
    int quote = 0;                 // Quote state
    int br_balance = 0;            // Bracket balance
    int last_c_operator = 0;       // Last operator state
    int last_c_operand = 0;        // Last operand state
    int last_c_func = 0;           // Last function state
    int last_c_lbr = 0;            // Last left bracket state
    int last_c_rbr = 0;            // Last right bracket state
    int tok_cnt = 0;               // Token count
    const char *cursor = function; // Cursor to traverse the input string

    // Process each character in the input string
    while (*cursor != '\0')
    {
        if (*cursor == '"')
        {
            if (quote && *(cursor + 1) != '\0')
                return 0;
            quote = !quote;
            cursor++;
            continue;
        }
        if (isspace(*cursor))
        {
            cursor++;
            continue;
        }
        else if (isalpha(*cursor))
        {
            if (!process_alpha(&cursor, &last_c_func, &last_c_operand, &last_c_operator, &last_c_lbr, &last_c_rbr))
            {
                return 0;
            }
        }
        else if (isdigit(*cursor) || *cursor == '.')
        {
            // Check if + or - is followed by a digit
            if (isdigit(*(cursor + 1)))
            {
                if (!process_number(&cursor, &last_c_operand, &last_c_operator, &last_c_func, &last_c_lbr, &last_c_rbr))
                {
                    return 0;
                }
            }
            else if (isdigit(*cursor) || *cursor == '.')
            {
                if (!process_number(&cursor, &last_c_operand, &last_c_operator, &last_c_func, &last_c_lbr, &last_c_rbr))
                {
                    return 0;
                }
            }
        }
        else if (*cursor == '(')
        {
            if (!process_bracket_open(&br_balance, &last_c_func, &last_c_operator, &last_c_operand, &last_c_lbr, &last_c_rbr))
            {
                return 0;
            }
            cursor++;
        }
        else if (*cursor == ')')
        {
            if (!process_bracket_close(&br_balance, &last_c_operator, &last_c_operand, &last_c_lbr, &last_c_rbr, &last_c_func))
            {
                return 0;
            }
            cursor++;
        }
        else if (strchr("+-*/^", *cursor))
        {
            if (!process_operator(&cursor, &last_c_operator, &last_c_operand, &last_c_rbr, &last_c_func, &last_c_lbr))
            {
                return 0;
            }
        }
        else
        {
            
            return 0;
        }

        tok_cnt++;
    }

    // Check for unmatched brackets
    if (br_balance > 0)
    {
        
        return 0;
    }
    if (br_balance < 0)
    {
        
        return 0;
    }
    if (last_c_operator)
    {
        
        return 0;
    }

    return tok_cnt;
}
/**
 * @brief 
 *
 * This function checks if the input limits string is in the correct format "minX:maxX:minY:maxY"
 * where each value can be converted to a number. It returns 1 if the format is valid, otherwise returns 0.
 *
 * @param limits The input limits string to check.
 * @return 1 if the limits string is valid, 0 otherwise.
 */
int validate_limit(const char *limit)
{
    if(!limit)
    {
        return 0;
    }
    int dot_cnt = 0;  // Counter for decimal points
    int e_cnt = 0;    // Counter for 'e' or 'E'
    int sign_cnt = 0; // Counter for '+' or '-'

    // Read the numeric sequence
    while (isdigit(*limit) || *limit == '.' || *limit == 'e' || *limit == 'E' || *limit == '+' || *limit == '-')
    {
        if (*limit == '.')
        {
            dot_cnt++;
            if (dot_cnt > 1 || e_cnt > 0)
            {
                
                return 0;
            }
        }
        else if (*limit == 'e' || *limit == 'E')
        {
            e_cnt++;
            if (e_cnt > 1 || !isdigit(*(limit - 1)))
            {
                
                return 0;
            }
            sign_cnt = 0; // Reset sign counter after 'e' or 'E'
        }
        else if (*limit == '+' || *limit == '-')
        {
            sign_cnt++;
            if (sign_cnt > 2 || !isdigit(*(limit + 1)))
            {
                
                return 0;
            }
        }
        limit++;
    }
    return 1;
}