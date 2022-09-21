from cs50 import get_int
h = get_int("Height: ")
while not 0 < h < 9:
    h = get_int("Height: ")

print(*list(map(lambda i: (h-i)*" "+i*"#"+"  "+i*"#", range(1, h+1))), sep="\n")



