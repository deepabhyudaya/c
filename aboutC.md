Key Difference

Struct:
Stores all its members at the same time.
Each member gets its own memory space.
Use a struct when you need all the data fields simultaneously.

Union:
Stores only one member at a time.
All members share the same memory space.
Use a union when only one value is needed at any given time, and you want to save memory.

Function Purpose
strlen() Gets the length of a string.
strcpy() Copies one string to another.
strncpy() Copies a specified number of characters.
strcat() Concatenates two strings.
strncat() Concatenates a specified number of characters.
strcmp() Compares two strings lexicographically.
strncmp() Compares first n characters of strings.
strchr() Finds the first occurrence of a character.
strrchr() Finds the last occurrence of a character.
strstr() Finds the first occurrence of a substring.
strtok() Splits a string into tokens.
memset() Fills memory with a constant byte.
memcpy() Copies memory.
memcmp() Compares two memory blocks.

+-----------------------+ <- High memory
| Stack | (Local variables, function calls)
+-----------------------+
| Heap | (Dynamic allocations via malloc/calloc)
+-----------------------+
| Uninitialized Data | (BSS: global/static uninitialized vars)
+-----------------------+
| Initialized Data | (Global/static initialized vars)
+-----------------------+
| Text | (Code segment: program instructions)
+-----------------------+ <- Low memory
