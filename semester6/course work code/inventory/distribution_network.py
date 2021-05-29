from typing import Dict, List

from inventory.entry import SupplierInfo
from inventory.transfering import LeadTimeMap, InvalidOrderException, SupplyOrder, PlanningPeriod
from inventory.calculations import create_orders


class DistributionNetwork:
    lead_times: LeadTimeMap = LeadTimeMap(0)
    entries = dict()  # dictionary item => location => entry
    suppliers: Dict[int, SupplierInfo] = {}  # item => supplier
    active_orders: List[SupplyOrder] = []

    top_level_entries: List = []

    def __init__(self, n_locations):
        self.lead_times.__init__(n_locations)

    def create_order(self, item: int, source_location: int, destination: int, quantity: int, time_point: int):

        is_not_supplier = source_location in self.entries[item]

        if is_not_supplier and self.entries[item][source_location].on_hand < quantity:
            raise InvalidOrderException("Cannot create transfer orders: not enough on hand in source location")

        order = SupplyOrder(
            item,
            source_location,
            destination,
            quantity,
            time_point + self.lead_times.get_distance(source_location, destination)
        )

        if is_not_supplier:
            self.entries[item][source_location].on_hand -= quantity
        self.active_orders.append(order)

    def close_order(self, order: SupplyOrder):
        item = order.source_thing.item_id
        location = order.source_thing.location_id

        self.entries[item][location].info.on_hand += order.quantity
        self.active_orders.remove(order)

    def do_forecast_demand(self, model, horizon):
        for locations in self.entries.values():
            for entry in locations.values():
                entry.do_forecast_demand(model, horizon)

    def close_finished_orders(self, time_point: int):
        for order in self.active_orders:
            if order.is_ready(time_point):
                self.close_order(order)

    def do_ordering(self, current_point: int, order_cycle: int):
        for entry in self.top_level_entries:
            supplier = self.suppliers[entry.planning_thing.item_id]
            lead_time = self.lead_times.get_distance(entry.planning_thing.location_id, supplier.location_id)
            period = PlanningPeriod(current_point, current_point + lead_time, order_cycle)
            self.active_orders += create_orders(entry, supplier, period, self.lead_times, self.active_orders)
