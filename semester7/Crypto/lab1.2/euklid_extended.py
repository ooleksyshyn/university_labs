def euklid_extended(a, b):
    if b == 0:
        return a, 1, 0

    d, x, y = euklid_extended(b, a % b)
    return d, y, x - (a // b) * y


if __name__ == "__main__":
    print(euklid_extended(120, 23))
