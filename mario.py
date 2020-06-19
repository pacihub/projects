from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height <= 8 and height >= 1:
        break


for i in range(1, height + 1):
    for space in range(1, height + 1 - i):
        print(" ", end = "")

    for hash in range(i):
        print("#", end = "")

    print()


#including those +1 in the for loop, because the range function does not include
#1,height+1 means it will start with 1