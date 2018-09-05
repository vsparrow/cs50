#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    // ***************************************************************
    // prompts the user for a credit card number
    long long n;
    do
    {
        n = get_long_long("Please enter credit card number: ");
    }
    while (n < 1000);
    long long num2 = n;
    // ***************************************************************
    // see if valid checksum

    bool odd = true;
    int oddsum = 0;
    int evensum = 0;
    int size_of_n = 0;
    while (n > 0)
    {
        size_of_n++;
        int current = n % 10;
        if (odd == true)
        {
            oddsum = oddsum + current;
        }
        else
        {
            current = current * 2;
            while (current > 0)
            {
                evensum = evensum + (current % 10);
                current = current / 10;
            }
        }
        odd = !odd;
        n = n / 10;

    }

    //CHECK if last digit in totalsum (excample 60) is a 0
    // *******************************
    int totalsum = oddsum + evensum;
    if (totalsum % 10 > 0)
    {
        printf("INVALID\n");
        return 0;
    }


    // ***************************************************
    // see if amex, visa, mastercard
    char *string[10];
    int which = -1;
    switch (size_of_n)
    {
        case 15:
            string[0] = "amex";
            which = 1;
            break;
        case 13:
            string[0] = "visa";
            which = 2;
            break;
        case 16:
            string[0] = "vorm";
            which = 3;
            break;
        default:
            printf("INVALID\n");
            return 0;
    }

    // ***************************************************
    // check first digit based on string
    //  American Express numbers all start with 34 or 37;
    //  MasterCard numbers start with 51, 52, 53, 54, or 55
    //  Visa numbers all start with 4.
    if (which == 1)
    {
        if (num2 / 10000000000000 == 34 || num2 / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (which == 2)
    {
        if (num2 / 1000000000000 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (which == 3)
    {
        // 1000000000000000  15 for visa
        // 100000000000000   15 for mastercard
        if (num2 / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if (num2 / 100000000000000 > 50 && num2 / 100000000000000 < 56)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    // always return 0.
    return 0;
}