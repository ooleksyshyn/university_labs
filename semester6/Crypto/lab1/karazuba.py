import math


def karazuba_multiplication(a, b):
    if a < 1_000_000 and b < 1_000_000:
        return a * b

    if a == 0 or b == 0:
        return 0

    k = int(max(math.log(a, 10), math.log(b, 10))) // 2

    pow_10_k = 10 ** k

    a1, a2 = a % pow_10_k, a // pow_10_k
    b1, b2 = b % pow_10_k, b // pow_10_k

    return karazuba_multiplication(a1, b1) + pow_10_k * (karazuba_multiplication(a1 + a2, b1 + b2) -
                                                         karazuba_multiplication(a1, b1) -
                                                         karazuba_multiplication(a2, b2)) + \
           karazuba_multiplication(a2, b2) * pow_10_k * pow_10_k


if __name__ == "__main__":
    print(71438967083174560 * 276543056439028760934956890248)
    print(karazuba_multiplication(71438967083174560, 276543056439028760934956890248))
