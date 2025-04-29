#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "evaluator.h"
#include "parser.h"
#include <stdio.h>

/**
 * @brief Evaluates a binary operation between two operands.
 *
 * @param a The first operand.
 * @param b The second operand.
 * @param op The operator as a string.
 * @return The result of the operation.
 */
double evaluate_ops(double a, double b, const char *op)
{
    // Check if the operator is valid
    if (op == NULL || strchr("+-*/^", *op) == NULL)
    {
        exit(2);
    }
    // Check if the operands are valid numbers
    if (isnan(a) || isnan(b))
    {
        return NAN;
    }

    // Perform the operation based on the operator
    if (strcmp(op, "^") == 0)
    {
        return pow(a, b);
    }
    else if (strcmp(op, "*") == 0)
    {
        return a * b;
    }
    else if (strcmp(op, "/") == 0)
    {
        return a / b;
    }
    else if (strcmp(op, "+") == 0)
    {
        return a + b;
    }
    else if (strcmp(op, "-") == 0)
    {
        return a - b;
    }    
    exit(2);
}

/**
 * @brief Evaluates a mathematical function with a single argument.
 *
 * @param func The function name as a string.
 * @param value The argument to the function.
 * @return The result of the function.
 */
double evaluate_func(const char *func, double value)
{
    // Check if the function is valid
    if (func == NULL)
    {
        return 0;
    }
    // Check if the value is a valid number
    if (isnan(value))
    {
        return 0;
    }

    // Perform the function based on the function name
    if (strcmp(func, "sin") == 0)
    {
        return sin(value);
    }
    else if (strcmp(func, "cos") == 0)
    {
        return cos(value);
    }
    else if (strcmp(func, "tan") == 0)
    {
        return tan(value);
    }
    else if (strcmp(func, "asin") == 0)
    {
        return asin(value);
    }
    else if (strcmp(func, "acos") == 0)
    {
        return acos(value);
    }
    else if (strcmp(func, "atan") == 0)
    {
        return atan(value);
    }
    else if (strcmp(func, "sinh") == 0)
    {
        return sinh(value);
    }
    else if (strcmp(func, "cosh") == 0)
    {
        return cosh(value);
    }
    else if (strcmp(func, "tanh") == 0)
    {
        return tanh(value);
    }
    else if (strcmp(func, "log") == 0)
    {
        return log(value);
    }
    else if (strcmp(func, "ln") == 0)
    {
        return log(value);
    }
    else if (strcmp(func, "exp") == 0)
    {
        return exp(value);
    }
    else if (strcmp(func, "sqrt") == 0)
    {
        return sqrt(value);
    }
    else if (strcmp(func, "abs") == 0)
    {
        return fabs(value);
    }
}

/**
 * @brief Evaluates a Reverse Polish Notation (RPN) expression.
 *
 * @param rpn The RPN expression as an array of tokens.
 * @param x The value to substitute for the variable in the expression.
 * @return The result of the evaluation.
 */
double evaluate_rpn(const token *rpn, double x, int tok_cnt)
{
    // Check if the RPN expression is valid
    if (rpn == NULL)
    {
        return;
    }

    double stack[tok_cnt];
    int stack_index = 0;
    int i;
    // Iterate through the tokens in the RPN expression
    for (i = 0; rpn[i].type != END; i++)
    {
        // If the token is a number, push it onto the stack
        if (rpn[i].type == NUM)
        {
            stack[stack_index++] = strtod(rpn[i].value, NULL);
        }
        // If the token is a variable, push the value of x onto the stack
        else if (rpn[i].type == VAR)
        {
            stack[stack_index++] = x;
        }
        // If the token is a function, evaluate the function with the top value on the stack
        else if (rpn[i].type == FUNC)
        {
            double value = stack[--stack_index];
            stack[stack_index++] = evaluate_func(rpn[i].value, value);
        }
        // If the token is an operator, evaluate the operation with the top two values on the stack
        else if (rpn[i].type == OP)
        {
            double b = stack[--stack_index];
            double a = stack[--stack_index];
            stack[stack_index++] = evaluate_ops(a, b, rpn[i].value);
        }
    }

    // Return the result of the evaluation
    return stack[0];
}
