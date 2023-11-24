#ifndef TRANSITPILOT_CONSOLE_H
#define TRANSITPILOT_CONSOLE_H

#include <stdio.h>
#include <string.h>
#include "econio.h"
#include "debugmalloc.h"

#define CONSOLE_WIDTH 30

#define PrintString_Full(text, left, right, newline) PrintString(text, left, right, -1, TextAlignLeft, newline)
#define PrintLine_Single(character) PrintLine(character, character)
#define PrintBlock_Default(text) PrintBlock(text, TextAlignMiddle)

typedef enum {
    TextAlignLeft,
    TextAlignMiddle,
    TextAlignRight
} TextAlign;

/// Returns the value that is smaller than the other
/// \param a Value A
/// \param b Value B
/// \return The smaller value
int min(int a, int b);

/// Calculates the coordinates of the console cursor from a string
/// \param string The string that has been printed out to the console
void CalculateCoordinates(const char *string);

/// Clear the console and reset the console cursor coordinates
void ClearConsole();

/// Got to a specified coordinate in the console
/// \param x Value on the X axis
/// \param y Value on the Y axis
void GoToXY(int x, int y);

/// Wait for the key ENTER to be pressed ont eh keyboard
void WaitForEnter();

/// Truncate a string that is longer than the maximum length
/// \param text The string that should be truncated
/// \param maxLength The specified maximum length for the text
/// \return The original or the truncated string
char *TruncateString(char *text, int maxLength);

/// Print out a single string to the console
/// \param text The text that should be printed out
/// \param prefix A short string before the text
/// \param suffix A short string after the text
/// \param maxLength The text's maximum length
/// \param textAlign Where to align the text
/// \param placeNewLine Should be a new line started at the end of the text?
void
PrintString(char *text, char *prefix, char *suffix, int maxLength, TextAlign textAlign, bool placeNewLine);

/// Print out to the console a single line of characters
/// \param corner The first and last character
/// \param middle All the characters between the first and last character
void PrintLine(char corner, char middle);

/// Print out a block with text
/// \param text The text in the block
/// \param textAlign The text's align inside the block
void PrintBlock(char *text, TextAlign textAlign);

/// An interactive dropdown menu
/// \param title The title of the dropdown menu
/// \param items The items of the dropdown menu
/// \param itemsCount The number of items in the dropdown menu
/// \param showItems Number of item that should be shown
/// \param titleAlign The align of the title
/// \return -1 if there is no selection, otherwise the selected item's id from the given items array
int ItemSelector(char *title, char **items, int itemsCount, int showItems, TextAlign titleAlign);

#endif //TRANSITPILOT_CONSOLE_H
