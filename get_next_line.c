#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    if(str == NULL)
        return(0);
    while(str[i])
        i++;
    return(i);
}
int ft_newline(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '\n')
            return(1);
        i++;
    }
    return(0);
}
char *ft_strdup(char *str)
{
    int i = 0;
    int len = ft_strlen(str);
    char *dup;
    dup = malloc(len + 1);
    while(str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return(dup);
}
char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    char *dup;
    char *all;
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);
    if(s1 == NULL)
        return(ft_strdup(s2));
    if(s2 == NULL)
    {
        dup = ft_strdup(s1);
        free(s1);
        return(dup);
    }
    all = malloc(len1 + len2 + 1);
    while(s1[i])
    {
        all[i] = s1[i];
        i++;
    }
    while(s2[j])
    {
        all[i] = s2[j];
        i++;
        j++;
    }
    all[i] = '\0';
    free(s1);
    return(all);
}
char *ft_read(int fd,char **rest)
{
    char *buffer;
    char *redable;
    int rd = 1;
    redable = NULL;
    buffer = malloc(BUFFER_SIZE + 1);
    while(rd >= 1)
    {
        rd = read(fd, buffer,BUFFER_SIZE);
        if(rd == 0)
            break;
        else if(rd <= 0)
        {
            free(redable);
            redable = NULL;
            free((*rest));
            (*rest) = NULL;
            break;
        }
        buffer[rd] = '\0';
        redable = ft_strjoin(redable, buffer);
        if(ft_newline(redable) == 1)
            break;
    }
    free(buffer);
    return(redable);
}
char *get_line(char *all)
{
    int i = 0;
    int k = 0;
    char *line;
    while(all[i])
    {
        if(all[i] == '\n')
        {
            break;
        }
        i++;
    }
    k = i;
    line = malloc(k + 2);
    i = 0;
    while(i <= k)
    {
        line[i] = all[i];
        i++;
    }
    line[i] = '\0';
    return(line);
}
char *get_rest(char *all)
{
    int i = 0;
    int j = 0;
    char *rest;
    while(all[i] != '\n' && all[i])
        i++;
    if(all[i] == '\n')
        i++;
    if(all[i] == '\0')
        return(NULL);
    
    rest = malloc(ft_strlen(all) - i + 1);
    while(all[i])
    {
        rest[j] = all[i];
        j++;
        i++;
    }
    rest[j] = '\0';
    return(rest);
}
char *get_next_line(int fd)
{
    char *redable;
    char *all;
    char *line;
    static char *rest;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    redable = ft_read(fd,&rest);
    if(redable == NULL && rest == NULL)
        return(NULL);
    all = ft_strjoin(rest,redable);
    free(redable);
    line = get_line(all);
    rest = get_rest(all);
    free(all);
    return(line);
}