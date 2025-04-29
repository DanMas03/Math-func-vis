#ifndef __VALIDATOR__
#define __VALIDATOR__

/**
 * @brief Checks if the given filename has a .ps extension.
 *
 * This function checks if the input filename ends with the .ps extension
 * and returns 1 if it does, otherwise returns 0.
 *
 * @param filename The input filename to check.
 * @return 1 if the filename ends with .ps, 0 otherwise.
 */
int is_ps_file(const char *filename);

/**
 * @brief checks if file can be created
 * 
 * @param filename The input filename to check.
 * @return int 1 if file can be created
 */
int can_create_file(const char *filename);

/**
 * @brief Checks if the given string is a recognized function.
 *
 * This function compares the input string with a predefined list of function names
 * and returns 1 if it matches any of them, otherwise returns 0.
 *
 * @param func The input string to check.
 * @return 1 if the input string is a recognized function, 0 otherwise.
 */
int is_function(const char *func);

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
int process_alpha(const char **cursor, int *last_c_func, int *last_c_operand, int *last_c_operator, int *last_c_lbr, int *last_c_rbr);

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
int process_number(const char **cursor, int *last_c_operand, int *last_c_operator, int *last_c_func, int *last_c_lbr, int *last_c_rbr);

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
int process_bracket_open(int *br_balance, int *last_c_func, int *last_c_operator, int *last_c_operand, int *last_c_lbr, int *last_c_rbr);

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
int process_bracket_close(int *br_balance, int *last_c_operator, int *last_c_operand, int *last_c_lbr, int *last_c_rbr);

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
int process_operator(const char **cursor, int *last_c_operator, int *last_c_operand, int *last_c_rbr);

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
int validate_function(const char *function);

/**
 * @brief 
 *
 * This function checks if the input limits string is in the correct format "minX:maxX:minY:maxY"
 * where each value can be converted to a number. It returns 1 if the format is valid, otherwise returns 0.
 *
 * @param limits The input limits string to check.
 * @return 1 if the limits string is valid, 0 otherwise.
 */
int validate_limit(const char *limit);

#endif