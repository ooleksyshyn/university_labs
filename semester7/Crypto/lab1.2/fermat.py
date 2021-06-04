import numpy as np

import binary_exponent


def check_prime_fermat(prime, n_checks):
    if prime == 2:
        return True

    a = [i for i in range(1, prime)]
    np.random.shuffle(a)
    for i in range(min(n_checks, len(a))):
        if binary_exponent.exponent_modulo(a[i], prime - 1, prime) != 1:
            return False

    return True


def main(number):
    print(f"Number {number} is prime: {check_prime_fermat(number, 5000)}")


if __name__ == '__main__':
    main(31)
