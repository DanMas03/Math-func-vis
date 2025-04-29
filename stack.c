#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "parser.h"

void init_stack(stack *s, int max_tok_cnt)
{
    s->data = (token *)malloc(max_tok_cnt * sizeof(token));
    s->top = -1;
}

int is_empty(const stack *s)
{
    return s->top == -1;
}

/**
 * @brief Checks if the stack is full.
 *
 * This function checks if the stack is full by comparing the top index to
 * MAX_TOKENS - 1.
 *
 * @param s Pointer to the stack to check.
 * @return 1 if the stack is full, 0 otherwise.
 */
int is_full(const stack *s, int max_tok_cnt)
{
    return s->top == max_tok_cnt - 1;
}

/**
 * @brief Pushes a token onto the stack.
 *
 * This function pushes a token onto the stack. If the stack is full, it prints
 * an error message and exits the program.
 *
 * @param s Pointer to the stack to push the token onto.
 * @param t The token to push onto the stack.
 */
void push(stack *s, token t, int max_tok_cnt)
{
    if (is_full(s, max_tok_cnt))
    {
    
        exit(6);
    }
    s->data[++s->top] = t;
}

/**
 * @brief Pops a token from the stack.
 *
 * This function pops a token from the stack. If the stack is empty, it prints
 * an error message and exits the program.
 *
 * @param s Pointer to the stack to pop the token from.
 * @return The token popped from the stack.
 */
token pop(stack *s)
{
    if (is_empty(s))
    {
        
        exit(6);
    }
    return s->data[s->top--];
}

/**
 * @brief Peeks at the top token of the stack.
 *
 * This function peeks at the top token of the stack without removing it. If
 * the stack is empty, it prints an error message and exits the program.
 *
 * @param s Pointer to the stack to peek at.
 * @return The token at the top of the stack.
 */
token peek(const stack *s)
{
    if (is_empty(s))
    {
        
        exit(6);
    }
    return s->data[s->top];
}

/**
 * @brief Frees the stack.
 *
 * This function frees the memory allocated for the stack.
 *
 * @param s Pointer to the stack to free.
 * @return 0 on success.
 */
int free_stack(stack *s)
{
    free(s->data);
    return 0;
}
