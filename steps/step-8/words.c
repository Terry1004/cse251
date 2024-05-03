#include <stdio.h>

/*
 * Name : Terry
 * Program to experiment with character arrays
 */

#define MAX_WORD 20

void copy(char src[], char dst[])
{
    int idx = 0;
    while (src[idx] != 0)
    {
        dst[idx] = src[idx];
        idx++;
    }
    dst[idx] = 0;
}

int main()
{
    char c;
    char str[MAX_WORD + 1];

    puts("Enter text. Include a dot ('.') to end a sentence to exit:");

    int len = 0;

    int sum_len = 0;
    int num_words = 0;

    char longest_word[MAX_WORD + 1] = {0};
    int longest_word_len = 0;
    do
    {
        c = getchar();
        if (c != ' ' && c != '.' && len < MAX_WORD)
        {
            /* This is a character of a word */
            str[len] = c;
            len++;
        }
        else if (len > 0)
        {
            /* The word is done */
            str[len] = 0;

            printf("%s\n", str);
            sum_len += len;
            num_words++;

            if (len > longest_word_len)
            {
                longest_word_len = len;
                copy(str, longest_word);
            }
            len = 0;
        }
    } while (c != '.');

    double avg_len = 0;
    if (num_words > 0)
    {
        avg_len = (double)sum_len / num_words;
    }
    printf("The total number of words is: %d\n", num_words);
    printf("The longest word is: %s\n", longest_word);
}