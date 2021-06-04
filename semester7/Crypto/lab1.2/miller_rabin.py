import numpy as np

import binary_exponent


def check_prime_miller_rabin(prime, n_checks):
    if prime == 2:
        return True
    else:
        if prime % 2 == 0:
            return False

    t = prime - 1
    s = 0

    while t % 2 == 0:
        t //= 2
        s += 1

    pretenders = [i for i in range(2, prime - 1)]
    np.random.shuffle(pretenders)
    for i in range(min(n_checks, len(pretenders))):
        a = pretenders[i]
        x = binary_exponent.exponent_modulo(a, t, prime)
        if x == 1 or x == prime - 1:
            continue

        need_continue = False

        for j in range(s):
            x = (x * x) % prime
            if x == 1:
                return False
            if x == prime - 1:
                need_continue = True
                break
        if need_continue:
            continue
        return False

    return True


if __name__ == "__main__":
    print(f"{33} is prime: {check_prime_miller_rabin(33, 10)}")
