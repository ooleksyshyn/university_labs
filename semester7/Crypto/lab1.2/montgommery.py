from euklid_extended import euklid_extended


def mon_mult(a, b, n):
    r = 1

    while r < n:
        r *= 2

    _, _, n_1 = euklid_extended(r, n)
    n_1 = -n_1

    t = a * b
    u = (t + ((t * n_1) % r) * n) // r

    while u >= n:
        u -= n
    return u


def mon_exp(a, e, n):
    r = 1
    while r < n:
        r *= 2

    a_1 = (a * r) % n
    x_1 = r % n

    for i in range(j - 1, -1, -1):
        x_1 = mon_mult(x_1, x_1, n)
        if i == 0:
            x_1 = mon_mult(x_1, a_1, n)

    return mon_mult(x_1, 1, n)
