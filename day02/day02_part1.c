#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

char *read_file(char *filename);
int process_content(char *content);
int check_color_not_valid(int nbr, char c);
int count_digits(int nbr);

int main ()
{
    char	*content;
    int    total;
	
	content = read_file("input.txt");
    total = process_content(content);
    free (content);
    printf("Total game IDs: %i\n", total);
}

int process_content(char *content)
{
    int game_id = 0;
    int total_game_ids = 0;
    int i = 0;
    int temp_nbr = 0;

    while (content[i])
    {
        while (content[i] != ':' && content[i])
        {
            if (isdigit(content[i])) //extract game ID
            {
                game_id = atoi(&(content[i]));
                i += count_digits(game_id);
            }
            else
                i++;
        }
        while (content[i] != '\n' && content[i]) //iterate through numbers of current game
        {
            if (isdigit(content[i]))
            {
                temp_nbr = atoi(&content[i]);
                i += count_digits(temp_nbr);
            }
            if (check_color_not_valid(temp_nbr, content[i]) == 1)
            {
                while (content[i] != '\n' && content[i]) // skip to next string aka next game;
                     i++;
                game_id = 0;
            }
            else if (content[i] == 'g') //skip two chars to jump over the "r" in "green"
                i += 2;
            else
                i++; //regular skip
        }
        if (game_id != 0)
        total_game_ids += game_id;
        i++; //move to next string;
    }
    return (total_game_ids);
}
int check_color_not_valid(int nbr, char c)
{
    int red = 12;
    int green = 13;
    int blue = 14;

    if (c == 'r')
    {
        if (nbr > red)
            return (1); //invalid: too many red cubes
    }
    if (c == 'g')
    {
        if (nbr > green)
            return (1); //invalid: too many green cubes     
    }
    if (c == 'b')
    {
        if (nbr > blue)
            return (1); //invalid: too many blue cubes
    }
    return (0); //game may be valid
}

int count_digits(int nbr)
{
    int digits = 0;

    while (nbr != 0)
    {
        nbr = nbr / 10;
        digits++;
    }
    return (digits);
}
char *read_file(char *filename)
{
	char *contents;
	long length;
	FILE *file;
    
	file = fopen(filename, "r");
    if (file == NULL)
        return (printf("Error opening input.txt\n"), NULL);
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (length < 0) 
	{
        fclose(file);
        return (printf("Error determining file size\n"), NULL);
    }
    contents = (char *)malloc(sizeof(char) * (length + 1));
    if (contents == NULL)
	{
        fclose(file);
        return (printf("Error allocating memory\n"), NULL);
    }
    fread(contents, 1, length, file);
    contents[length] = '\0';
    fclose(file);
    return (contents);
}