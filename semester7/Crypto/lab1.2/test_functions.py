import pytest
from binary_exponent import exponent_modulo
from euklid_extended import euklid_extended
from fermat import check_prime_fermat
from karazuba import karazuba_multiplication
from miller_rabin import check_prime_miller_rabin


def test_binary_exponent():
    assert (2 ** 30) % 7 == exponent_modulo(1, 30, 7)
    assert (3 ** 25) % 31 == exponent_modulo(3, 25, 31)
    assert (4 ** 20) % 37 == exponent_modulo(4, 20, 37)


def test_fermat():
    assert check_prime_fermat(7, 7)
    assert check_prime_fermat(2, 2)
    assert not check_prime_fermat(4, 4)
    assert check_prime_fermat(31, 31)
    assert check_prime_fermat(101, 101)
    assert not check_prime_fermat(259, 259)
    assert check_prime_fermat(7919, 7919)


def test_miller_rabin():
    assert check_prime_miller_rabin(7, 7)
    assert check_prime_miller_rabin(2, 2)
    assert not check_prime_miller_rabin(4, 4)
    assert check_prime_miller_rabin(31, 31)
    assert check_prime_miller_rabin(101, 101)
    assert not check_prime_miller_rabin(259, 259)
    assert check_prime_miller_rabin(7919, 7919)


def test_karazuba():
    assert 473168967712896347 * 1834768970918324856 == karazuba_multiplication(473168967712896347, 1834768970918324856)
    assert 836789672039876089945 * 4893982 == karazuba_multiplication(836789672039876089945, 4893982)
    assert karazuba_multiplication(0, 134756980237596840) == 0
    assert karazuba_multiplication(2763984789713, 0) == 0
    assert karazuba_multiplication(12903, 2839) == 12903 * 2839


def test_euklid_extended():
    assert euklid_extended(120, 43) == (1, 19, -53)
    assert euklid_extended(120, 23) == (1, -9, 47)
