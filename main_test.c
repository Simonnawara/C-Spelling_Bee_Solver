#include <iostream.h>

#define PRINTLN(STR) std::cout << STR << std::endl
#define SWAP(ARRAY, I, J) if(I != J) { ARRAY[I] ^= ARRAY[J]; ARRAY[J] ^= ARRAY[I]; ARRAY[I] ^= ARRAY[J]; }

void PrintCombinations_Rec(char* str, size_t idx)
{
    const size_t len = strlen(str);
    if( len == idx)
        PRINTLN(str);
    else
    {
        for (size_t i = idx; i < len; ++i)
        {
            SWAP(str, idx, i);
            PrintCombinations_Rec(str, idx + 1);
            SWAP(str, i, idx);
        }
    }
}

void PrintCombinations(const char* input)
{
    const size_t len = strlen(input);
    char* str = new char[len + 1];
    strncpy_s(str, len + 1, input, len);

    // Recursive call
    PrintCombinations_Rec(str, 0);

    delete[] str;
}

int main(int argc, char** argv)
{
    PrintCombinations("ABCD");
    return EXIT_SUCCESS;
}