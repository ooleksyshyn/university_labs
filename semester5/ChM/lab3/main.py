import math
import random
import matplotlib.pyplot as plt


def f(x):
    return math.sinh(x) - 12 * math.tanh(x) - 0.311


def inverse_interpolate(x, y, y0):
    summ = 0

    for i in range(n_points):
        product = x[i]
        for j in range(n_points):
            if i != j:
                product *= (y0 - y[j])/(y[i] - y[j])
        summ += product

    return summ


n_points = 7

x = sorted([random.uniform(2, 4) for _ in range(n_points)])
y = [f(i) for i in x]


values_to_interpolate = sorted([random.uniform(2, 4) for _ in range(10)])

plt.plot(x, y, "r", [inverse_interpolate(x, y, yi) for yi in values_to_interpolate], values_to_interpolate, "b--")
plt.show()

for i in values_to_interpolate:
    print(f(inverse_interpolate(x, y, i)), i)
