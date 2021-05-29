from typing import List

from inventory.common import PlanningThing, PlanningPeriod


class LeadTimeMap:
    _map: List[List[int]] = []

    def __init__(self, n_locations):
        self._map = [[0 for _ in range(n_locations)] for _ in range(n_locations)]

    def get_distance(self, id1: int, id2: int) -> int:
        return self._map[id1][id2]


class SupplyOrder:
    _quantity: int
    _arrival_point: int

    source_thing: PlanningThing
    target_thing: PlanningThing

    def __init__(self, item_id: int, source_id: int, target_id: int, quantity: int, arrival_point: int):
        self.source_thing = PlanningThing(item_id, source_id)
        self.target_thing = PlanningThing(item_id, target_id)
        self._quantity = quantity
        self._arrival_point = arrival_point

    @property
    def quantity(self) -> int:
        return self._quantity

    def is_ready(self, current_point: int) -> bool:
        return current_point >= self._arrival_point

    def arrival_point(self):
        return self._arrival_point


class InvalidOrderException(Exception):
    pass


class Transaction:
    _entry: PlanningThing
    _channel_id: int
    _quantity_sold: int

    def __init__(self, entry: PlanningThing, channel_id: int, quantity_sold):
        self._entry = entry
        self._channel_id = channel_id
        self._quantity_sold = quantity_sold

    @property
    def entry(self) -> PlanningThing:
        return self._entry

    @property
    def quantity_sold(self) -> int:
        return self._quantity_sold

    @property
    def channel_id(self):
        return self._channel_id


def arrival_quantity_at(active_orders: List[SupplyOrder], thing: PlanningThing, point: int) -> int:
    return sum([
        order.quantity
        for order in active_orders
        if order.target_thing == thing and order.arrival_point() == point
    ])


def departure_quantity_at(active_orders: List[SupplyOrder], thing: PlanningThing, point: int) -> int:
    return sum([
        order.quantity
        for order in active_orders
        if order.source_thing == thing and order.arrival_point() == point
    ])


def planning_period(lead_times: LeadTimeMap, source: int, destination: int, period: PlanningPeriod) -> PlanningPeriod:
    offset = lead_times.get_distance(source, destination)
    return PlanningPeriod(period.current_point, period.arrival_point + offset, period.order_cycle)
