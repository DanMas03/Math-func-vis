#ifndef __STACK__
#define __STACK__
#include "parser.h"
#include "consts.h"

typedef struct
{
    token *data;
    int top;
} stack;

/**
 * @brief Initializes the stack.
 *
 * This function initializes the stack by setting the top index to -1.
 *
 * @param s Pointer to the stack to initialize.
 * @param max_tok_cnt The maximum number of tokens allowed in the stack.
 */
void init_stack(stack *s, int max_tok_cnt);

/**
 * @brief Checks if the stack is empty.
 *
 * This function checks if the stack is empty by comparing the top index to -1.
 *
 * @param s Pointer to the stack to check.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int is_empty(const stack *s);

/**
 * @brief Checks if the stack is full.
 *
 * This function checks if the stack is full by comparing the top index to
 * MAX_TOKENS - 1.
 *
 * @param s Pointer to the stack to check.
 * @param max_tok_cnt The maximum number of tokens allowed in the stack.
 * @return 1 if the stack is full, 0 otherwise.
 */
int is_full(const stack *s, int max_tok_cnt);

/**
 * @brief Pushes a token onto the stack.
 *
 * This function pushes a token onto the stack. If the stack is full, it prints
 * an error message and exits the program.
 *
 * @param s Pointer to the stack to push the token onto.
 * @param t The token to push onto the stack.
 * @param max_tok_cnt The maximum number of tokens allowed in the stack.
 */
void push(stack *s, token t, int max_tok_cnt);

/**
 * @brief Pops a token from the stack.
 *
 * This function pops a token from the stack. If the stack is empty, it prints
 * an error message and exits the program.
 *
 * @param s Pointer to the stack to pop the token from.
 * @return The token popped from the stack.
 */
token pop(stack *s);

/**
 * @brief Peeks at the top token of the stack.
 *
 * This function peeks at the top token of the stack without removing it. If
 * the stack is empty, it prints an error message and exits the program.
 *
 * @param s Pointer to the stack to peek at.
 * @return The token at the top of the stack.
 */
token peek(const stack *s);

/**
 * @brief Frees the stack.
 *
 * This function frees the memory allocated for the stack.
 *
 * @param s Pointer to the stack to free.
 * @return 0 on success.
 */
int free_stack(stack *s);
#endif