#include "console.h"

int COORD_X = 0, COORD_Y = 0;

int min(int a, int b) { return a < b ? a : b; }

void CalculateCoordinates(const char *string) {
    for (int i = 0; string[i] != '\0'; ++i)
        if (string[i] == '\n') {
            COORD_X = 0;
            ++COORD_Y;
        } else ++COORD_X;
}

void ClearConsole() {
    econio_clrscr();
    COORD_X = COORD_Y = 0;
}

void GoToXY(int x, int y) {
    COORD_X = x;
    COORD_Y = y;
    econio_gotoxy(x, y);
}

void WaitForEnter() {
    econio_textcolor(COL_DARKGRAY);
    PrintString("Press [ENTER] to continue", "\n", "", CONSOLE_WIDTH, TextAlignMiddle, false);
    econio_textcolor(COL_RESET);
    econio_rawmode();
    int pressedKey;
    do pressedKey = econio_getch();
    while (pressedKey != KEY_ENTER);
    econio_normalmode();
    GoToXY(0, COORD_Y);
    PrintLine_Single(' ');
    GoToXY(0, COORD_Y);
}

char *TruncateString(char *text, int maxLength) {
    if (strlen(text) <= maxLength)
        return text;

    char shortText[maxLength + 1];
    strcpy(shortText, text);
    shortText[maxLength] = '\0';

    char *truncated = (char *) malloc(sizeof(char) * (maxLength + 1));
    strcpy(truncated, shortText);

    for (int i = maxLength - 3; i <= maxLength; ++i)
        if (i != maxLength)
            truncated[maxLength] = '.';
        else
            truncated[maxLength] = '\0';

    return truncated;
}

void
PrintString(char *text, char *prefix, char *suffix, int maxLength, TextAlign textAlign, bool placeNewLine) {
    int textLength = (int) strlen(text);
    if (maxLength > 4 && textLength > maxLength) {
        char *shortText = TruncateString(text, maxLength);
        printf("%s%s%s", prefix, shortText, suffix);

        CalculateCoordinates(prefix);
        CalculateCoordinates(shortText);
        CalculateCoordinates(suffix);
        free(shortText);

    } else {
        int leftSpace = 0, rightSpace = 0;
        if (maxLength > 0)
            switch (textAlign) {
                case TextAlignLeft:
                    rightSpace = maxLength - textLength;
                    break;
                case TextAlignMiddle:
                    leftSpace = (maxLength - textLength) / 2;
                    rightSpace = maxLength - (leftSpace + textLength);
                    break;
                case TextAlignRight:
                    leftSpace = maxLength - textLength;
                    break;
            }

        printf("%s", prefix);
        for (int i = 0; i < leftSpace; ++i) printf(" ");
        printf("%s", text);
        for (int i = 0; i < rightSpace; ++i) printf(" ");
        printf("%s", suffix);

        CalculateCoordinates(prefix);
        CalculateCoordinates(text);
        CalculateCoordinates(suffix);
    }
    if (placeNewLine) {
        printf("\n");
        CalculateCoordinates("\n");
    }
}

void PrintLine(char corner, char middle) {
    for (int i = 0; i < CONSOLE_WIDTH; ++i, ++COORD_X)
        printf("%c", (i == 0 || i == CONSOLE_WIDTH - 1) ? corner : middle);
    printf("\n");
    COORD_X = 0;
    ++COORD_Y;
}

void PrintBlock(char *text, TextAlign textAlign) {
    PrintLine('O', '=');
    PrintString(text, "| ", " |", CONSOLE_WIDTH - 4, textAlign, true);
    PrintLine('O', '=');
}

int ItemSelector(char *title, char **items, int itemsCount, int showItems, TextAlign titleAlign) {
    PrintLine_Single(' ');
    PrintString(title, " ", " ", CONSOLE_WIDTH - 2, titleAlign, true);

    int key, selectedItem = 0, startListingFrom = 0;
    int maxListingFrom = itemsCount <= showItems ? 0 : itemsCount - showItems;
    int listingCursor = showItems % 2 == 0 ? showItems / 2 : (showItems / 2) + 1;

    econio_rawmode();
    do {
        char counterText[CONSOLE_WIDTH];
        sprintf(counterText, "%d/%d", startListingFrom + selectedItem + 1, itemsCount);
        econio_textcolor(COL_DARKGRAY);
        PrintString(counterText, " ", " ", CONSOLE_WIDTH - 2, TextAlignRight, true);
        econio_textcolor(COL_RESET);
        PrintLine_Single(' ');

        for (int count = 0, index = 0; count < min(showItems, itemsCount); ++count, ++index) {
            econio_textcolor(COL_BLUE);
            PrintString_Full(count == selectedItem ? ">" : " ", " ", "", false);
            econio_textcolor(COL_RESET);
            PrintString(items[startListingFrom + index], " ", " ", CONSOLE_WIDTH - 5, TextAlignLeft, true);
        }
        PrintLine_Single(' ');

        do {
            key = econio_getch();
            switch (key) {
                case KEY_UP:
                    if ((selectedItem <= listingCursor && selectedItem != 0 && startListingFrom == 0) ||
                        selectedItem > listingCursor)
                        --selectedItem;
                    else if (selectedItem == listingCursor)
                        --startListingFrom;
                    GoToXY(COORD_X, COORD_Y - min(showItems, itemsCount) - 3);
                    break;
                case KEY_DOWN:
                    if ((selectedItem >= listingCursor && selectedItem != min(showItems - 1, itemsCount - 1) &&
                         startListingFrom == maxListingFrom) ||
                        selectedItem < listingCursor)
                        ++selectedItem;
                    else if (selectedItem == listingCursor && startListingFrom != maxListingFrom)
                        ++startListingFrom;
                    GoToXY(COORD_X, COORD_Y - min(showItems, itemsCount) - 3);
                    break;
                default:
                    break;
            }
        } while (key != KEY_UP && key != KEY_DOWN && key != KEY_ENTER && key != KEY_BACKSPACE);
    } while (key != KEY_ENTER && key != KEY_BACKSPACE);
    econio_normalmode();

    return key != KEY_BACKSPACE ? startListingFrom + selectedItem : -1;
}