/*Don't use this code as reference for anything, it's very spaghetti*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

char *read_file(char *filename);
static int	nbrwords(const char *s, char c);
char	**split(char const *s, char c);
char	*substr(char const *str, unsigned int start, size_t len);
int	extract_numbers(char	**array_str);
int	word_to_number(const char *str);
int	find_substr(const char* str);

int main ()
{
	char	*file_content;
	char	**array_str;
	int		total;
	int		i;

	i = 0;
	file_content = read_file("input.txt");
	array_str = split(file_content, '\n');
	total = extract_numbers(array_str);
	printf("Total: %d\n", total);
	free(file_content);
	return (0);
}

int extract_numbers(char **array_str) 
{
    int total = 0;
    int temp_nbr;
    int i = 0;
    int j = 0;

    while (array_str[i]) 
	{
        j = 0;
        while (array_str[i][j])
		{
            if (isdigit(array_str[i][j]))
			{
                temp_nbr = (array_str[i][j] - '0') * 10;
				break;
            }
			else if (isalpha(array_str[i][j]))
			{
				if (find_substr(&array_str[i][j]) != -1)
				{
					temp_nbr = find_substr(&array_str[i][j]) * 10;
					break;
				}
			}
			j++;
		}
		j = strlen(array_str[i]) - 1;
		while (j >= 0)
		{
            if (isdigit(array_str[i][j])) 
			{
            	total += (array_str[i][j] - '0') + temp_nbr;
				break;
            }
			else if (isalpha(array_str[i][j]))
			{
				if (word_to_number(&array_str[i][j]) != -1)
				{
					total += word_to_number(&array_str[i][j]) + temp_nbr;
					j = 0;
					break;
				}
			}
			j--;
        }
        i++;
    }
    return (total);
}

int	find_substr(const char* str)
{
	char	*number[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	char	*needle;
	int		needle_len;
	int		i;
	int		j;
	int		k;

	i = 0;
    while (i < 9)
	{
        needle = number[i];
        needle_len = strlen(needle);

        j = 1;
        while (j <= needle_len) 
		{
            if (j > strlen(str))
                break;
            k = 0;
            char substring[j + 1];
            while (k < j) 
			{
                substring[k] = str[k];
                ++k;
            }
            substring[k] = '\0';
            if (strstr(substring, needle) != 0)
                return (word_to_number(substring));
            ++j;
        }
		++i;
    }
    return (-1);
}

int	word_to_number(const char *str) 
{
    if (strstr(str, "one") != 0)
		return (1);
    if (strstr(str, "two") != 0)
		return (2);
    if (strstr(str, "three") != 0)
		return (3);
    if (strstr(str, "four") != 0)
		return (4);
    if (strstr(str, "five") != 0)
		return (5);
    if (strstr(str, "six") != 0)
		return (6);
    if (strstr(str, "seven") != 0)
		return (7);
    if (strstr(str, "eight") != 0)
		return (8);
    if (strstr(str, "nine") != 0)
		return (9);
    return (-1);
}

char	**split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	nbr_words;

	if (!s)
		return (NULL);

	nbr_words = 0;
	i = 0;
	j = 0;
	array = (char **)calloc((nbrwords(s, c) + 1), sizeof(char *));
	if (!array)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			array[nbr_words] = substr(s, i, j);
			if (!array[nbr_words])
			{
				while (nbr_words > 0)
					free(array[--nbr_words]);
				free(array);
				return (NULL);
			}
			i += j;
			nbr_words++;
		}
		else
			i++;
	}
	array[nbr_words] = NULL;
	return (array);
}
static int	nbrwords(const char *s, char c)
{
	size_t	i;
	size_t	nbr_words;

	nbr_words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			nbr_words++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (nbr_words);
}

char	*substr(char const *str, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	while (str[start] && i < len)
	{
		i++;
		start++;
	}
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = '\0';
	while (i > 0)
	{
		i--;
		start--;
		new[i] = str[start];
	}
	return (new);
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
