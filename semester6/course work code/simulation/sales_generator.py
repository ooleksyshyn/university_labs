import random
import math

import numpy as np

from inventory.entry import SellingChannel


# MAPE - Middle Average Percentage Error
def calculate_MAPE(channel: SellingChannel):
    predicted_values = []
    real_values = []
    for i in range(len(channel.sales_history)):
        if math.isfinite(channel.demand_forecast[i]):
            real_values.append(channel.sales_history[i])
            predicted_values.append(channel.demand_forecast[i])

    actual, pred = np.array(real_values), np.array(predicted_values)
    return np.mean(np.abs((actual - pred) / actual))


class SalesGeneratorWithNoise:
    def __init__(self, noise_generator):
        self._noise_generator = noise_generator

    def generate(self, channel: SellingChannel, time_point: int):
        prediction = channel.demand_forecast[time_point]

        if math.isinf(prediction):
            return 0

        noise = self._noise_generator.generate(channel)

        return max(prediction + noise, 0)


class SimpleSalesGenerator:
    def generate(self, channel: SellingChannel, time_point: int):
        prediction = channel.demand_forecast[time_point]

        if math.isinf(prediction):
            return 0
        else:
            return prediction


class NormalNoiseGeneratorWithStaleMAPE:
    def generate(self, channel: SellingChannel):
        mape = calculate_MAPE(channel)

        if mape >= 1:
            return 0

        # with such sigma, MAPE will be an invariant after generating new sales
        sigma = math.sqrt(math.pi / 2) * mape
        if sigma == 0:
            return 0
        return random.normalvariate(0, sigma)


class UniformNoiseGeneratorWithStaleMAPE:
    def generate(self, channel: SellingChannel):
        mape = calculate_MAPE(channel)
        # with such distribution, MAPE will be an invariant after generating new sales
        return random.uniform(-2 * mape, 2 * mape)
