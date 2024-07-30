#include <stdarg.h>
#include <unistd.h>
void ft_putstr(char *str,int *len)
{
    int i = 0;
    if(str == NULL)
        ft_putstr("(null)",len);
    else{
    while(str[i])
    {
        write(1,&str[i],1);
        i++;
        (*len)++;
    }
    }
}
void ft_putnumber(int num,int *len)
{
    int n = 0;
    if(num == -2147483648)
    {
        write(1,"-2147483648",11);
        (*len) += 11; 
    }
    else if(num < 0)
    {
        write(1,"-", 1);
        (*len) += 1;
        num = -num;
        ft_putnumber(num,len);
    }
    else
    {
        if(num > 9)
            ft_putnumber(num / 10, len);
        n = (num % 10) + 48;
        write(1, &n, 1);
        (*len) += 1;
    }
}
void ft_puthexa(unsigned int n,int *len)
{
    char *tmp = "0123456789abcdef";

    if(n <= 16)
    {
        write(1, &tmp[n], 1);
        (*len) += 1;
    }
    else
    {
        ft_puthexa(n /16,len);
        ft_puthexa(n % 16,len);
    }
}
void ft_write(char c,va_list ptr,int *len)
{
    if(c == 's')
        ft_putstr(va_arg(ptr,char *),len);
    else if(c == 'd')
        ft_putnumber(va_arg(ptr,int),len);
    else if(c == 'x')
        ft_puthexa(va_arg(ptr,unsigned int),len);
    else if(c == '%')
    {
        write(1,&c,1);
        (*len)++;
    }
}
int ft_printf(const char *str, ... )
{
    int i = 0;
    int len = 0;
    va_list ptr;

    va_start(ptr,str);
    while(str[i])
    {
        if(str[i] == '%')
        {
            i++;
            ft_write(str[i],ptr, &len);
            i++;
        }
        else
        {
            write(1,&str[i],1);
            i++;
            len++;
        }
    }
    return(len);
}
#include <stdio.h>
int main()
{
    int d = 123;
    //char *str = "jamila";
    unsigned int x = 42;
    printf("----------------%d",ft_printf("\n%d\n%x\n",d,x));
}







#include <unistd.h>
#include <stdarg.h>
void ft_putstr(char *str,int *len)
{
    int i = 0;
    if(str == NULL)
        ft_putstr("(null)",len);
    else
    {
        while(str[i])
        {
            write(1, &str[i], 1);
            (*len)++;
            i++;
        }
    }
}
void ft_putnumbr(long int n,int *len)
{
    int num = 0;
    if(n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    else {
    if(n > 9)
        ft_putnumbr(n / 10,len);
    num = (n % 10) + 48;
    write(1,&num, 1);
    (*len)++;
    }
}
void ft_puthexa(unsigned int n, int *len)
{
    char *tmp = "0123456789abcdef";
    if(n < 16)
    {
        write(1, &tmp[n], 1);
        (*len)++;
    }
    else{
        ft_puthexa(n / 16, len);
        ft_puthexa(n % 16,len);
    }
}
int ft_printf(const char *str, ... )
{
    va_list ptr;
    int i = 0;
    int len = 0;

    va_start(ptr,str);
    while(str[i])
    {
        if(str[i] == '%')
        {
            i++;
            if(str[i] == 's')
                ft_putstr(va_arg(ptr,char *), &len);
            else if(str[i] == 'd')
                ft_putnumbr(va_arg(ptr, int), &len);
            else if(str[i] == 'x')
                ft_puthexa(va_arg(ptr,unsigned int), &len);
            i++;
        }
        else
        {
            write(1,&str[i],1);
            len++;
            i++;
        }
    }
    return(len);
}