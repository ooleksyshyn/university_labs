from euklid_extended import euklid_extended


class MontgomeryMultiplier:
    def __init__(self, a, e, n):
        self._a = a
        self._e = e
        self._n = n

        # calculate r
        self._r = 1
        while self._r < n:
            self._r *= 2

    # calculates (a * b * r^(-1)) % n
    def _mon_pro(self, a, b):
        _, _, n_1 = euklid_extended(self._r, self._n)
        n_1 = -n_1

        t = a * b
        u = (t + ((t * n_1) % self._r) * self._n) // self._r

        while u >= self._n:
            u -= self._n
        return u

    def multiply(self):
        a_1 = (self._a * self._r) % self._n
        x_1 = 1

        power = self._e

        while power > 0:
            x_1 = self._mon_pro(x_1, a_1)
            power -= 1

        return x_1
