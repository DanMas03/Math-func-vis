#ifndef __CONVERTOR__
#define __CONVERTOR__
#include "consts.h"
#include "parser.h"
#include <string.h>

/**
 * @brief Determines the precedence of an operator.
 *
 * @param op The operator whose precedence is to be determined.
 * @return The precedence level of the operator.
 */
int precedence(const char *op);

/**
 * @brief Checks if an operator is right associative.
 *
 * @param op The operator to check.
 * @return 1 if the operator is right associative, 0 otherwise.
 */
int is_right_associative(const char *op);

/**
 * @brief Converts an infix expression to Reverse Polish Notation (RPN).
 *
 * @param infix The input infix expression as an array of tokens.
 * @param n The length of the infix expression.
 * @param postfix The output array where the postfix expression will be stored.
 * @param m Pointer to an integer where the length of the postfix expression will be stored.
 */
void convert_to_rpn(const token *infix, int n, token *postfix, int *m,int tok_cnt);
#endif