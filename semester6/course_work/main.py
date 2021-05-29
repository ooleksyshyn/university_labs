import random

from simulation.simulation import Simulator
from inventory.distribution_network import DistributionNetwork
from inventory.entry import *
from simulation.sales_generator import NormalNoiseGeneratorWithStaleMAPE, SalesGeneratorWithNoise


class ConstandModel:
    def forecast(self, channel: SellingChannel, horizon):
        if len(channel.demand_forecast) == 0:
            result = [
                channel.sales_history[-1]
                for _ in range(len(channel.sales_history) + horizon)
            ]
        else:
            result = channel._demand_forecast + [
                channel.sales_history[-1]
                for _ in range(horizon)
            ]
        return result


def create_distribution_network() -> DistributionNetwork:
    network = DistributionNetwork(4)

    locations = [0, 1]
    other_locations = [2, 3]
    items = [1, 2, 3]

    for item in items:
        network.entries[item] = dict()

    for location in locations + other_locations:
        for location_2 in locations + other_locations:
            network.lead_times._map[location][location_2] = int(location != location_2)

    info = SupplierInfo(other_locations[1])
    for item in items:
        network.suppliers[item] = info

    for item in items:
        entry = DistributionEchelonEntry(PlanningThing(item, other_locations[0]), EntryInfo(1000, 10, 1000))

        for location in locations:
            child_entry = Entry(PlanningThing(item, location), EntryInfo(1000, 10, 1000))

            channel = SellingChannel(1)
            channel.sales_history = [random.randrange(0, 2000) for i in range(15)]

            child_entry.channels = [channel]

            entry.lower_echelon_entries.append(child_entry)
            network.entries[item][location] = child_entry

        network.entries[item][entry.planning_thing.location_id] = entry
        network.top_level_entries.append(entry)

    return network


# example of usage
def main():
    model = ConstandModel()
    generator = SalesGeneratorWithNoise(NormalNoiseGeneratorWithStaleMAPE())
    network = create_distribution_network()
    sim = Simulator(network, model, generator, 12)

    for _ in range(50):
        sim.do_simulation_step()


if __name__ == "__main__":
    main()
