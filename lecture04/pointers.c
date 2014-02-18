#include <stdio.h>
void fortune_cookie(char msg[])
{
    printf("Message reads: %s\n", msg);
    printf("Message address: %p\n", msg);
}

void fortune_cookie2(char *msg)
{
    printf("Message reads: %s\n", msg);
    printf("Message address: %p\n", msg);
}

void fortune_cookie3(char *msg)
{
    printf("Message reads: %s\n", msg);
    printf("Message address: %p\n", &msg);
}

int main()
{
    char quote[] = "Cookies make you fat";
    fortune_cookie(quote);

    char quote2[] = "Cookies make you skinny";
    fortune_cookie2(quote2);

    char *quote3 = "Cookies make you healthy";
    fortune_cookie3(quote3);

    return 0;

}

