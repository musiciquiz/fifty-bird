from cs50 import get_int

def main():
    n = get_height()
    
    for i in range(n):
        # leading spaces
        for j in range((n-i)-1):
            print(" ", end="")
        # LHS hash
        for k in range(n-(n-i)+1):
            print("#", end="")
        # spaces
        print("  ", end="")
        # RHS hasg
        for l in range(n-(n-i)+1):
            print ("#", end="")
        print()    
    
def get_height():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n
    
main()    
    