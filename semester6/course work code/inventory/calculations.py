from typing import List

from inventory.common import PlanningPeriod
from inventory.transfering import SupplyOrder, arrival_quantity_at, departure_quantity_at
from inventory.transfering import LeadTimeMap, planning_period
from inventory.entry import Entry, DistributionEchelonEntry, SupplierInfo, is_distributive


def calculate_order_quantity(entry: Entry, period: PlanningPeriod, active_orders: List[SupplyOrder]):
    potential_on_hand = entry.info.on_hand

    for i in range(period.current_point, period.arrival_point):
        demand = entry.demand_forecast_at(i)
        potential_on_hand = max(0, potential_on_hand - demand)
        potential_on_hand += arrival_quantity_at(active_orders, entry.planning_thing, i)

    to_order = 0

    for i in range(period.arrival_point, period.arrival_point + period.order_cycle):
        demand = entry.demand_forecast_at(i)
        potential_on_hand = potential_on_hand - demand
        if potential_on_hand < 0:
            to_order += -potential_on_hand
            potential_on_hand = 0

        potential_on_hand += arrival_quantity_at(active_orders, entry.planning_thing, i)

    return to_order + entry.info.safety_stock


def create_distribution_orders(entry: DistributionEchelonEntry, period: PlanningPeriod,
                               lead_times: LeadTimeMap, active_orders: List[SupplyOrder]):

    orders_to_send: List[SupplyOrder] = []

    for child_entry in entry.lower_echelon_entries:
        lead_time = lead_times.get_distance(entry.planning_thing.location_id, child_entry.planning_thing.location_id)
        arrival_point = period.arrival_point + lead_time

        source = entry.planning_thing.location_id
        destination = child_entry.planning_thing.location_id
        planned_period = planning_period(lead_times, source, destination, period)

        if is_distributive(child_entry):
            quantity, orders = create_distribution_orders(child_entry, planned_period, lead_times, active_orders)
            orders_to_send += orders
        else:
            quantity = calculate_order_quantity(child_entry, planned_period, active_orders)

        orders_to_send.append(SupplyOrder(
            item_id=entry.planning_thing.item_id,
            source_id=source,
            target_id=destination,
            quantity=quantity,
            arrival_point=arrival_point
        ))

    potential_on_hand = entry.info.on_hand

    for i in range(period.current_point, period.arrival_point):
        potential_on_hand += arrival_quantity_at(active_orders, entry.planning_thing, i)

        to_send = departure_quantity_at(orders_to_send, entry.planning_thing, i)
        potential_on_hand = max(0, potential_on_hand - to_send)

    to_order = 0

    for i in range(period.arrival_point, period.arrival_point + period.order_cycle):
        potential_on_hand += arrival_quantity_at(active_orders, entry.planning_thing, i)

        to_send = departure_quantity_at(orders_to_send, entry.planning_thing, i)
        potential_on_hand = potential_on_hand - to_send
        if potential_on_hand < 0:
            to_order += -potential_on_hand
            potential_on_hand = 0

    return to_order + entry.info.safety_stock, orders_to_send


def create_orders(entry, supplier: SupplierInfo, period: PlanningPeriod,
                  lead_times: LeadTimeMap, active_orders: List[SupplyOrder]):

    orders_to_send: List[SupplyOrder] = []
    lead_time = lead_times.get_distance(entry.planning_thing.location_id, supplier.location_id)
    arrival_point = period.arrival_point + lead_time
    source = entry.planning_thing.location_id
    destination = supplier.location_id
    planned_period = planning_period(lead_times, source, destination, period)

    if is_distributive(entry):
        to_order, orders = create_distribution_orders(entry, planned_period, lead_times, active_orders)
        orders_to_send += orders
    else:
        to_order = calculate_order_quantity(entry, planned_period, active_orders)

    orders_to_send.append(SupplyOrder(
        item_id=entry.planning_thing.item_id,
        source_id=source,
        target_id=destination,
        quantity=to_order,
        arrival_point=arrival_point
    ))

    return orders_to_send
