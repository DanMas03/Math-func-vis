#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "parser.h"
#include "validator.h"

/**
 * @brief Frees the memory allocated for graph_limits structure.
 *
 * @param glims Pointer to the graph_limits structure to free.
 */
void free_limits(graph_limits **glims)
{
    if (!glims || !*glims)
        return;
    free(*glims);
}

/**
 * @brief Adds a token to the tokens array.
 *
 * @param tokens Array to store the tokens.
 * @param count Pointer to the current count of tokens.
 * @param max_tokens Maximum number of tokens allowed.
 * @param type The type of the token.
 * @param value The value of the token.
 */
void add_token(token tokens[], int *count, int max_tokens, token_type type, const char *value)
{
    if (!tokens || !count || !value || *count >= max_tokens)
        return;

    tokens[*count].type = type;
    strncpy(tokens[*count].value, value, sizeof(tokens[*count].value) - 1);
    tokens[*count].value[sizeof(tokens[*count].value) - 1] = '\0';
    (*count)++;
}

/**
 * @brief Tokenizes a mathematical function string into an array of tokens.
 *
 * @param function The mathematical function string to tokenize.
 * @param tokens Array to store the tokens.
 * @return The number of tokens generated.
 */
int tokenize(const char *function, token *tokens,int tok_cnt)
{
    
    if (!function || !tokens)
        return 0;

    int token_count = 0;
    const char *cursor = function;
    char buffer[MAX_TOK_LEN];
    while (*cursor != '\0')
    {
        // Skip whitespace
        if (isspace(*cursor))
        {
            cursor++;
            continue;
        }
        // skip
        if (*cursor == '"')
        {
            cursor++;
            continue;
        }
        memset(buffer, 0, sizeof(buffer));
        // Handle numbers
        if (isdigit(*cursor) || (*cursor == '.' && isdigit(*(cursor + 1))) ||
            (*cursor == '-' && isdigit(*(cursor + 1))) || (*cursor == '-' && *(cursor + 1) == '.' && isdigit(*(cursor + 2))))
        {
            int length = 0;
            int has_exponent = 0;
            while ((isdigit(*cursor) || *cursor == '.' || *cursor == 'e' || *cursor == 'E' || *cursor == '-' || *cursor == '+') && length < sizeof(buffer) - 1)
            {
                if ((*cursor == 'e' || *cursor == 'E') && !has_exponent)
                {
                    has_exponent = 1;
                }
                else if ((*cursor == 'e' || *cursor == 'E') && has_exponent)
                {
                    break;
                }
                if (length < 19)
                {
                    buffer[length++] = *cursor;
                }
                cursor++;
            }
            buffer[length] = '\0';
            add_token(tokens, &token_count, tok_cnt, NUM, buffer);
        }
        // Handle variables and functions
        else if (isalpha(*cursor))
        {
            int length = 0;
            while (isalpha(*cursor) && length < sizeof(buffer) - 1)
            {
                if (length < 19)
                {
                    buffer[length++] = *cursor;
                }
                cursor++;
            }
            buffer[length] = '\0';

            if (strcmp(buffer, "x") == 0)
            {
                add_token(tokens, &token_count, tok_cnt, VAR, buffer); // Variable
            }
            else
            {
                add_token(tokens, &token_count, tok_cnt, FUNC, buffer); // Function
            }
        }
        // Handle left bracket
        else if (*cursor == '(')
        {
            add_token(tokens, &token_count, tok_cnt, LBR, "(");
            cursor++;
        }
        // Handle right bracket
        else if (*cursor == ')')
        {
            add_token(tokens, &token_count, tok_cnt, RBR, ")");
            cursor++;
        }
        // Handle operators
        else if (strchr("+-*/^", *cursor))
        {
            snprintf(buffer, sizeof(buffer), "%c", *cursor);
            add_token(tokens, &token_count, tok_cnt, OP, buffer);
            cursor++;
        }
    }
    // Add end token
    add_token(tokens, &token_count, tok_cnt, END, "\0");

    return token_count;
}

/**
 * @brief Parses a string representing graph limits and returns a graph_limits structure.
 *
 * @param limits_str The string representing the graph limits.
 * @return A graph_limits structure with the parsed limits.
 */
graph_limits *parse_limits(const char *limits_str)
{
    graph_limits *temp;
    char copy[50];
    // If parameter is empty, create default limits
    if (!limits_str)
    {
        temp = (graph_limits *)malloc(sizeof(graph_limits));
        if (!temp)
        {
            return;
        }
        temp->x_start = -10;
        temp->x_end = 10;
        temp->y_start = -10;
        temp->y_end = 10;
        return temp;
    }
    strcpy(copy, limits_str);
    char *token;
    char *en_ptr;
    double result;
    char del = ':';
    int i = 0;
    temp = (graph_limits *)malloc(sizeof(graph_limits));
    if (!temp)
    {
        return;
    }
    // Tokenize the limits string
    token = strtok(copy, &del);
    while (token)
    {
        switch (i)
        {
        case 0:
            if (!validate_limit(token))
            {
                temp->x_start = 0;
                temp->x_end = 0;
                temp->y_start = 0;
                temp->y_end = 0;
                return temp;
            }
            result = strtod(token, &en_ptr);
            temp->x_start = result;
            break;
        case 1:
            if (!validate_limit(token))
            {
                temp->x_start = 0;
                temp->x_end = 0;
                temp->y_start = 0;
                temp->y_end = 0;
                return temp;
            }
            validate_limit(token);
            result = strtod(token, &en_ptr);
            temp->x_end = result;
            break;
        case 2:
            if (!validate_limit(token))
            {
                temp->x_start = 0;
                temp->x_end = 0;
                temp->y_start = 0;
                temp->y_end = 0;
                return temp;
            }
            result = strtod(token, &en_ptr);
            temp->y_start = result;
            break;
        case 3:
            if (!validate_limit(token))
            {
                temp->x_start = 0;
                temp->x_end = 0;
                temp->y_start = 0;
                temp->y_end = 0;
                return temp;
            }
            result = strtod(token, &en_ptr);
            temp->y_end = result;
            break;
        }
        // Check for out of range error
        if (result == 0)
        {
            if (errno == ERANGE)
            {
                
                temp->x_start = 0;
                temp->x_end = 0;
                temp->y_start = 0;
                temp->y_end = 0;
                return temp;
            }
        }
        token = strtok(NULL, &del);
        i++;
    }
    if (temp->x_start >= temp->x_end || temp->y_start >= temp->x_end)
    {
        
        temp->x_start = 0;
        temp->x_end = 0;
        temp->y_start = 0;
        temp->y_end = 0;
        return temp;
    }
    return temp;
}