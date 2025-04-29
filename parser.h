#ifndef __PARSER__
#define __PARSER__

#include "consts.h"

typedef enum
{
    NUM,  /*number*/
    VAR,  /*variable x*/
    OP,   /*operator (+,-,* etc.)*/
    FUNC, /*fucktion (sin,cos etc.)*/
    LBR,  /*left bracket '(' */
    RBR,  /*right bracket ')'*/
    END   /*end of token*/
} token_type;

typedef struct
{
    token_type type;         /*token type*/
    char value[MAX_TOK_LEN]; /*token*/
} token;

typedef struct
{
    double x_start, x_end, y_start, y_end;
} graph_limits;

/**
 * @brief Frees the memory allocated for graph_limits structure.
 *
 * @param glims Pointer to the graph_limits structure to be freed.
 */
void free_limits(graph_limits **glims);

/**
 * @brief Adds a token to the tokens array.
 *
 * @param tokens Array of tokens.
 * @param count Pointer to the current count of tokens.
 * @param max_tokens Maximum number of tokens allowed.
 * @param type Type of the token.
 * @param value Value of the token.
 */
void add_token(token tokens[], int *count, int max_tokens, token_type type, const char *value);

/**
 * @brief Tokenizes a mathematical function string into an array of tokens.
 *
 * @param function The mathematical function string to tokenize.
 * @param tokens Array to store the tokens.
 * @return The number of tokens generated.
 */
int tokenize(const char *function, token *tokens,int tok_cnt);

/**
 * @brief Parses a string representing graph limits and returns a graph_limits structure.
 *
 * @param limits_str The string representing the graph limits.
 * @return A graph_limits structure with the parsed limits.
 */
graph_limits *parse_limits(const char *limits_str);

#endif
