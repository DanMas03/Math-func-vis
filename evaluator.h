#ifndef __EVALUATOR__
#define __EVALUATOR__
#include "consts.h"
#include "stack.h"
#include <math.h>

/**
 * @brief Evaluates a binary operation between two operands.
 *
 * @param a The first operand.
 * @param b The second operand.
 * @param op The operator as a string.
 * @return The result of the operation.
 */
double evaluate_ops(double a, double b, const char *op);

/**
 * @brief Evaluates a mathematical function with a single argument.
 *
 * @param func The function name as a string.
 * @param value The argument to the function.
 * @return The result of the function.
 */
double evaluate_func(const char *func, double value);

/**
 * @brief Evaluates a Reverse Polish Notation (RPN) expression.
 *
 * @param rpn The RPN expression as an array of tokens.
 * @param x The value to substitute for the variable in the expression.
 * @return The result of the evaluation.
 */
double evaluate_rpn(const token *rpn, double x, int tok_cnt);

#endif