# Librarys
from cs50 import get_int
import sys


def main():
    # Get credit card number
    number = get_int("Credit card number: ")
    
    # checking number long enough
    if number < 100000000000:
        print("INVALID")
        sys.exit(1)
    
    # If number long enough
    else:
        # Usefull variables
        n = number % 10
        Nn = number - n
        N = Nn / 10
        Nu = number
        num = number
        y = 0
        x = 0
    
    # Double and add the digits of every second digit starting from the second last
    while N > 0:
        a = (N % 10) * 2
        if a > 9:
            b = a % 10
            c = (a - b) / 10
            y = y + b + c
        else:
            y = a + y
        N = ((N - (N % 100)) / 100)
    
    # Add every digit from the last    
    while Nu > 0:
        d = Nu % 10
        x = d + x
        Nu = ((Nu - (Nu % 100)) / 100)
        
    # Checking sum
    s = x + y
    Csum = s % 10
    
    if Csum != 0:
        print(INVALID)
        sys.exit(1)
    else:
        # Determining which card type
        while num > 9:
            num = ((num - (num % 10)) / 10)
            if 39 < num and num < 50:
                print("VISA")
                sys.exit(0)
            elif 50 < num and num < 56:
                print("MASTERCARD")
                sys.exit(0)
            elif num == 34 or num == 37:
                print("AMEX")
                sys.exit(0)
            elif num < 10:
                print("INVALID")
                sys.exit(0)
            

main()
