// Haoyang (Hendrick) Chen 
// chen.haoyang4@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
 
int getrepeat(char *str,char ch)
{
    char *ptr=str;
    int repeat=0;
    while(*ptr==ch)
    {
        ptr+=1;
        repeat++;    
    }
    return repeat;        
}

char *runlengthencoding(char *str,char *rle )
{
    char *ptr=str;
    char *ptrend=&str[strlen(str)];
    char encoding[100];
    int repeat;
    strcpy(rle,"");

    while(ptr<ptrend)
    {
        repeat=getrepeat(ptr,*ptr);
        if(repeat>1)
        {
            sprintf(encoding,"%c%d",*ptr,repeat);
            strcat(rle,encoding);
            ptr=ptr+repeat;
        }else
        {
            sprintf(encoding,"%c",*ptr);
            strcat(rle,encoding);
            ptr++;
        }
    }
    
    return rle;    
}

int getcount(char *rle)
{   
    int count=0;
    while (isdigit(*rle))
    {
        count = count * 10 + (*rle - '0');
        rle++;
    }
    return count;
}

char *decode_rle(char *rle, char *str)
{
    char *ptr = rle;
    char *ptrend = &rle[strlen(rle)];
    char decoding[100];
    int i = 0, j = 0, count = 0, digit = 0;
    strcpy(str, "");

    while (ptr < ptrend)
    {
        char currentChar = *ptr++;
        count = 0;

        // Read digits following the character
        while (ptr < ptrend && isdigit(*ptr))
        {
            count = count * 10 + (*ptr - '0');
            ptr++;
        }

        // If no digits follow, it means the count is 1
        if (count == 0)
        {
            count = 1;
        }

        // Append the character 'count' times to the decoded string
        for (j = 0; j < count; j++)
        {
            str[i++] = currentChar;
        }
    }

    str[i] = '\0'; // Null-terminate the decoded string

    return str;
}


int main()
{
    char str_org[]="WWWWWWWWWWWWWWWWWWWWWWWWWWWWbAAAABBCBBCBBCaaa";
    char rle[100];
    runlengthencoding(str_org,rle);
    printf("str_org:[%s] => rle:[%s]\n",str_org,rle);

    char str_dec[100];
    decode_rle(rle,str_dec);
    printf("rle:[%s] => str_dec:[%s]\n",rle, str_dec);
    return 0;
}
