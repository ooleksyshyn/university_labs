from typing import List, Dict
import math

from inventory.common import PlanningThing, BaseEntry, EntryInfo


class SellingChannel:
    _channel_id: int = 0
    sales_history: List[int] = []
    _demand_forecast: List[float] = []

    def __init__(self, channel_id: int):
        self._channel_id = channel_id

    @property
    def channel_id(self):
        return self._channel_id

    @property
    def demand_forecast(self):
        return self._demand_forecast

    def do_forecast_demand(self, model, horizon: int):
        self._demand_forecast = model.forecast(self, horizon)


class Entry(BaseEntry):
    channels: List[SellingChannel] = []

    def __init__(self, planning_thing: PlanningThing, info: EntryInfo):
        super().__init__(planning_thing, info)

    def do_forecast_demand(self, model, horizon: int):
        for channel in self.channels:
            channel.do_forecast_demand(model, horizon)

    def demand_forecast_at(self, time_point: int):
        return sum([channel.demand_forecast[time_point] for channel in self.channels])


class DistributionEchelonEntry(BaseEntry):
    lower_echelon_entries: List = []

    def __init__(self, planning_thing: PlanningThing, info: EntryInfo):
        super().__init__(planning_thing, info)

    def do_forecast_demand(self, model, horizon: int):
        for entry in self.lower_echelon_entries:
            entry.do_forecast_demand(model, horizon)


def is_distributive(entry):
    return entry.__class__ == DistributionEchelonEntry


class SupplierInfo:
    _on_hand = math.inf
    _location_id: int

    def __init__(self, location_id: int):
        self._location_id = location_id

    @property
    def location_id(self):
        return self._location_id

    @property
    def on_hand(self):
        return self._on_hand
