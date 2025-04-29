#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "evaluator.h"
#include "ps_creator.h"

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
void draw_axes(FILE *file, graph_limits limits, double a4_width, double a4_height, double margin, double x_interval, double y_interval)
{
    // Calculate the positions of the axes based on the limits
    double x_axis_y = margin + ((0 - limits.y_start) / (limits.y_end - limits.y_start)) * (a4_height - 2 * margin);
    double y_axis_x = margin + ((0 - limits.x_start) / (limits.x_end - limits.x_start)) * (a4_width - 2 * margin);

    // Draw light gray grid
    fprintf(file, "0.8 setgray\n");
    for (double x = limits.x_start; x <= limits.x_end; x += x_interval)
    {
        double scaled_x = margin + ((x - limits.x_start) / (limits.x_end - limits.x_start)) * (a4_width - 2 * margin);
        fprintf(file, "newpath\n");
        fprintf(file, "%lf %lf moveto\n", scaled_x, margin);
        fprintf(file, "%lf %lf lineto\n", scaled_x, a4_height - margin);
        fprintf(file, "closepath\n");
        fprintf(file, "stroke\n");
        
    }

    for (double y = limits.y_start; y <= limits.y_end; y += y_interval)
    {
        double scaled_y = margin + ((y - limits.y_start) / (limits.y_end - limits.y_start)) * (a4_height - 2 * margin);
        fprintf(file, "newpath\n");
        fprintf(file, "%lf %lf moveto\n", margin, scaled_y);
        fprintf(file, "%lf %lf lineto\n", a4_width - margin, scaled_y);
        fprintf(file, "closepath\n");
        fprintf(file, "stroke\n");
    }

    // Reset to black color
    fprintf(file, "0 setgray\n");

    // Draw X axis
    fprintf(file, "newpath\n");
    fprintf(file, "%lf %lf moveto\n", margin, x_axis_y);
    fprintf(file, "%lf %lf lineto\n", a4_width - margin, x_axis_y);
    fprintf(file, "closepath\n");
    fprintf(file, "stroke\n");

    // Draw Y axis
    fprintf(file, "newpath\n");
    fprintf(file, "%lf %lf moveto\n", y_axis_x, margin);
    fprintf(file, "%lf %lf lineto\n", y_axis_x, a4_height - margin);
    fprintf(file, "closepath\n");
    fprintf(file, "stroke\n");

    // Label X axis
    fprintf(file, "/Times-Roman findfont 12 scalefont setfont\n");
    fprintf(file, "%lf %lf moveto\n", a4_width - margin + 5, x_axis_y - 10);
    fprintf(file, "(X) show\n");

    // Label Y axis
    fprintf(file, "%lf %lf moveto\n", y_axis_x + 10, a4_height - margin + 5);
    fprintf(file, "(Y) show\n");

    // Draw numbers on X axis
    for (double x = limits.x_start; x <= limits.x_end; x += x_interval)
    {
        if (x == 0)
            continue; // Skip origin
        double scaled_x = margin + ((x - limits.x_start) / (limits.x_end - limits.x_start)) * (a4_width - 2 * margin);
        fprintf(file, "%lf %lf moveto\n", scaled_x, x_axis_y - 15);
        if (floor(x) == x)
        {
            fprintf(file, "(%.0lf) show\n", x);
        }
        else
        {
            fprintf(file, "(%.1lf) show\n", x);
        }
    }

    // Draw numbers on Y axis
    for (double y = limits.y_start; y <= limits.y_end; y += y_interval)
    {
        if (y == 0)
            continue; // Skip origin
        double scaled_y = margin + ((y - limits.y_start) / (limits.y_end - limits.y_start)) * (a4_height - 2 * margin);
        fprintf(file, "%lf %lf moveto\n", y_axis_x + 5, scaled_y - 5);
        if (floor(y) == y)
        {
            fprintf(file, "(%.0lf) show\n", y);
        }
        else
        {
            fprintf(file, "(%.1lf) show\n", y);
        }
    }
}

/**
 * @brief Draws a border around the graph on the PostScript file.
 *
 * @param file The file pointer to the PostScript file.
 * @param graph_width The width of the graph in points.
 * @param graph_height The height of the graph in points.
 * @param margin The margin around the graph.
 */
void draw_border(FILE *file, double a4_width, double a4_height, double margin)
{
    fprintf(file, "newpath\n");
    fprintf(file, "%lf %lf moveto\n", margin, margin);
    fprintf(file, "%lf %lf lineto\n", a4_width - margin, margin);
    fprintf(file, "%lf %lf lineto\n", a4_width - margin, a4_height - margin);
    fprintf(file, "%lf %lf lineto\n", margin, a4_height - margin);
    fprintf(file, "closepath\n");
    fprintf(file, "stroke\n");
}

/**
 * @brief Creates a PostScript file with the graph of the given function.
 *
 * @param filename The name of the PostScript file to create.
 * @param postfix_expression The postfix expression of the function to graph.
 * @param expression_length The length of the postfix expression.
 * @param limits The limits of the graph.
 * @param function The function to graph as a string.
 */
int create_postscript_file(const char *filename, const token *postfix_expression, int expression_length, graph_limits limits, const char *function,int tok_cnt)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        
        return 0;
    }
    
    // dimensions in points
    double graph_width = 595;
    double graph_height = (graph_width+2*MARGIN)/2;// this is to make the graph 2:1 after subtracting the margins
    double x_interval = (limits.x_end - limits.x_start) / DEFAULT_RANGE_X;
    double y_interval = (limits.y_end - limits.y_start) / DEFAULT_RANGE_Y;

    // Write PostScript header
    fprintf(file, "%%!PS-Adobe-3.0\n");
    fprintf(file, "%%%%BoundingBox: 0 0 %lf %lf\n", graph_width, graph_height);
    fprintf(file, "%%%%Title: \n", function);
    fprintf(file, "%%%%Creator: Daniel Mašek\n");


    // Draw border
    draw_border(file, graph_width, graph_height, MARGIN);
    
    // Draw axes
    draw_axes(file, limits, graph_width, graph_height, MARGIN, x_interval, y_interval);

    // Add title of graph
    add_text_above_graph(file, graph_width, graph_height, MARGIN, function);

    // Set color to dark blue
    fprintf(file, "0 0 0.5 setrgbcolor\n");

    // Calculate the step size for sampling the function
    double step = (limits.x_end - limits.x_start) / NUM_OF_SAMPLES;
    int first_point = 1; // Flag to check if the current point is the first point
    double y_prev = NAN; // Previous y value to check for discontinuities
    fprintf(file, "newpath\n");
    // Loop through the x values from x_start to x_end with the calculated step size
    for (double x = limits.x_start; x <= limits.x_end; x += step)
    {
        // Evaluate the function at the current x value using Reverse Polish Notation (RPN)
        double y = evaluate_rpn(postfix_expression, x,tok_cnt);

        // Skip the current point if the y value is not a number or out of the y limits
        if (isnan(y) || y < limits.y_start || y > limits.y_end || fabs(y - y_prev) > (limits.y_end - limits.y_start)*DISCONTUITY_THRESHOLD_SCALE)
        {
            fprintf(file, "stroke\n");
            fprintf(file, "newpath\n");
            y_prev = y;
            first_point = 1; // Reset the flag
            continue;
        }

        // Scale the x and y values to fit within the graph dimensions and margins
        double scaled_x = MARGIN + ((x - limits.x_start) / (limits.x_end - limits.x_start)) * (graph_width - 2 * MARGIN);
        double scaled_y = MARGIN + ((y - limits.y_start) / (limits.y_end - limits.y_start)) * (graph_height - 2 * MARGIN);

        // If it's the first point, move to the scaled coordinates
        if (first_point)
        {
            fprintf(file, "%lf %lf moveto\n", scaled_x, scaled_y);
            first_point = 0; // Reset the flag after the first point
        }
        else
        {
            // For subsequent points, draw a line to the scaled coordinates
            fprintf(file, "%lf %lf lineto\n", scaled_x, scaled_y);
        }
        y_prev = y; // Update the previous y value
    }
    fprintf(file, "stroke\n");
    fprintf(file, "showpage\n");
    fclose(file);
    return 1;
}

/**
 * @brief Adds text above the graph on the PostScript file.
 *
 * @param file The file pointer to the PostScript file.
 * @param graph_width The width of the graph in points.
 * @param graph_height The height of the graph in points.
 * @param margin The margin around the graph.
 * @param text The text to add above the graph.
 */
void add_text_above_graph(FILE *file, double a4_width, double a4_height, double margin, const char *text)
{
    fprintf(file, "/Times-Roman findfont 16 scalefont setfont\n");
    fprintf(file, "%lf %lf moveto\n", (a4_width / 2) - (strlen(text) * 4), a4_height - margin + 20);
    fprintf(file, "(%s) show\n", text);
}
