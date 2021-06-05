def exponent_modulo(number, power, modulo):
    result = 1

    while power > 0:
        if power % 2 != 0:
            result = (result * number) % modulo
        number = (number * number) % modulo
        power //= 2

    return result
