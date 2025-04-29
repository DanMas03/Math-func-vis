#ifndef __PSCREATOR__
#define __PSCREATOR__

#include <stdio.h>
#include "parser.h"
/**
 * @brief Creates a PostScript file with the graph of the given function.
 *
 * @param filename The name of the PostScript file to create.
 * @param postfix_expression The postfix expression of the function to graph.
 * @param expression_length The length of the postfix expression.
 * @param limits The limits of the graph.
 * @param function The function to graph as a string.
 */
int create_postscript_file(const char *filename, const token *postfix_expression, int expression_length, graph_limits limits, const char *function, int tok_cnt);

/**
 * @brief Draws the axes and grid lines on the PostScript file.
 *
 * @param file The file pointer to the PostScript file.
 * @param limits The limits of the graph.
 * @param graph_width The width of the graph in points.
 * @param graph_height The height of the graph in points.
 * @param margin The margin around the graph.
 * @param x_interval The interval between vertical grid lines.
 * @param y_interval The interval between horizontal grid lines.
 */
void draw_axes(FILE *file, graph_limits limits, double a4_width, double a4_height, double margin, double x_interval, double y_interval);

/**
 * @brief Draws a border around the graph on the PostScript file.
 *
 * @param file The file pointer to the PostScript file.
 * @param graph_width The width of the graph in points.
 * @param graph_height The height of the graph in points.
 * @param margin The margin around the graph.
 */
void draw_border(FILE *file, double a4_width, double a4_height, double margin);

/**
 * @brief Adds text above the graph on the PostScript file.
 *
 * @param file The file pointer to the PostScript file.
 * @param graph_width The width of the graph in points.
 * @param graph_height The height of the graph in points.
 * @param margin The margin around the graph.
 * @param text The text to add above the graph.
 */
void add_text_above_graph(FILE *file, double a4_width, double a4_height, double margin, const char *text);
#endif