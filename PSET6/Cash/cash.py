from cs50 import get_float


def coinChange(totalNumber, coins):
    out = 0
    N = totalNumber
    coins.sort()
    index = len(coins)-1
    while True:
        coinValue = coins[index]
        if N >= coinValue:
            out += 1
            N = N - coinValue
        if N < coinValue:
            index -= 1
        if N == 0:
            return out


coins = [1, 5, 10, 25]
inp = get_float("Change owed: ")
while 0 > inp:
    inp = get_float("Change owed: ")

print(coinChange(int(100*inp), coins))