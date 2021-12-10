from cs50 import get_int


def main():
    while True:
        # get hight
        h = get_int(" What hight is the pyramid? ")
        if h < 9 and h > 0:
            # call pyramid
            w = h
            pyramid(h, w)
            break


def pyramid(h, w):
    H = h - 1
    # till lat one
    if h > 1:
        pyramid(H, w)
    # print pyramid line
    for i in range(w - h):
        print(" ", end="")
    for i in range(h):
        print("#", end="")
    print("  ", end="")
    for i in range(h):
        print("#", end="")
    # next line
    print()


main()
