#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "parser.h"

/**
 * @brief Determines the precedence of an operator.
 *
 * @param op The operator whose precedence is to be determined.
 * @return The precedence level of the operator.
 */
int precedence(const char *op)
{
    if (op == NULL)
    {
        exit(5);
    }
    if (strcmp(op, "^") == 0)
        return 3;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        return 2;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 1;
    return 0;
}

/**
 * @brief Checks if an operator is right associative.
 *
 * @param op The operator to check.
 * @return 1 if the operator is right associative, 0 otherwise.
 */
int is_right_associative(const char *op)
{
    if (op == NULL)
    {
        exit(5);
    }
    return strcmp(op, "^") == 0;
}

/**
 * @brief Converts an infix expression to Reverse Polish Notation (RPN).
 *
 * @param infix The input infix expression as an array of tokens.
 * @param n The length of the infix expression.
 * @param postfix The output array where the postfix expression will be stored.
 * @param m Pointer to an integer where the length of the postfix expression will be stored.
 */
void convert_to_rpn(const token *infix, int n, token *postfix, int *m,int tok_cnt)
{
    if (infix == NULL || postfix == NULL || m == NULL)
    {
        exit(5);
    }
    if (n <= 0)
    {
        exit(5);
    }
    stack s;
    init_stack(&s,tok_cnt); // Initialize the stack

    *m = 0; // Initialize the length of the postfix expression

    for (int i = 0; i < n; i++)
    {
        token t = infix[i];

        if (t.type == NUM || t.type == VAR)
        {
            postfix[(*m)++] = t; // Add numbers and variables directly to the postfix expression
        }
        else if (t.type == FUNC)
        {
            push(&s, t,tok_cnt); // Push functions onto the stack
        }
        else if (t.type == OP)
        {
            // Pop operators from the stack to the postfix expression based on precedence and associativity
            while (!is_empty(&s) && (peek(&s).type == OP || peek(&s).type == FUNC))
            {
                token top = peek(&s);
                if ((top.type == FUNC) ||
                    (precedence(top.value) > precedence(t.value)) ||
                    (precedence(top.value) == precedence(t.value) && !is_right_associative(t.value)))
                {
                    postfix[(*m)++] = pop(&s);
                }
                else
                {
                    break;
                }
            }
            push(&s, t,tok_cnt); // Push the current operator onto the stack
        }
        else if (t.type == LBR)
        {
            push(&s, t,tok_cnt); // Push left parentheses onto the stack
        }
        else if (t.type == RBR)
        {
            // Pop from the stack to the postfix expression until a left parenthesis is encountered
            while (!is_empty(&s) && peek(&s).type != LBR)
            {
                postfix[(*m)++] = pop(&s);
            }
            if (is_empty(&s) || peek(&s).type != LBR)
            {
                exit(5);
            }
            pop(&s); // Remove the left parenthesis
            // If there is a function on top of the stack, pop it as well
            if (!is_empty(&s) && peek(&s).type == FUNC)
            {
                postfix[(*m)++] = pop(&s);
            }
        }
    }

    // Pop all remaining operators from the stack to the postfix expression
    while (!is_empty(&s))
    {
        token top = pop(&s);
        if (top.type == LBR)
        {
            exit(EXIT_FAILURE);
        }
        postfix[(*m)++] = top;
    }
    postfix[(*m)++] = (token){END, "\0"}; // Add end token to the postfix expression
    free_stack(&s); // Free the stack
}
