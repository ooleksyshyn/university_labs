from inventory.distribution_network import DistributionNetwork
from inventory.entry import is_distributive


class Simulator:
    distribution_network: DistributionNetwork

    _forecast_horizon: int
    _order_cycle: int
    _current_point: int
    _sales_generator = None

    def __init__(self, network: DistributionNetwork, model, sales_generator, current_point: int):
        self.distribution_network = network
        self._model = model
        self._sales_generator = sales_generator
        self._current_point = current_point

        self._order_cycle = 30
        self._forecast_horizon = self._order_cycle * 3

        self.distribution_network.do_forecast_demand(self._model, self._forecast_horizon)

    def do_simulation_step(self):
        self._current_point += 1
        self.distribution_network.close_finished_orders(self._current_point)

        if self._current_point % self._order_cycle == 0:
            self.distribution_network.do_forecast_demand(self._model, self._forecast_horizon)
            self.distribution_network.do_ordering(self._current_point, self._order_cycle)

        for locations_map in self.distribution_network.entries.values():
            for entry in locations_map.values():
                if not is_distributive(entry):
                    for channel in entry.channels:
                        channel.sales_history.append(self._sales_generator.generate(channel, self._current_point))
