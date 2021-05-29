class PlanningThing:
    def __init__(self, item: int, location: int):
        self._item_id = item
        self._location_id = location

    @property
    def item_id(self):
        return self._item_id

    @property
    def location_id(self):
        return self._location_id


class EntryInfo:
    _order_cycle: int
    _safety_stock: int
    on_hand = 0

    def __init__(self, safety_stock: int, order_cycle: int, on_hand):
        self._safety_stock = safety_stock
        self._order_cycle = order_cycle
        self.on_hand = on_hand

    @property
    def safety_stock(self):
        return self._safety_stock

    @property
    def order_cycle(self):
        return self._order_cycle


class BaseEntry:
    planning_thing: PlanningThing
    info: EntryInfo

    def __init__(self, planning_thing: PlanningThing, info: EntryInfo):
        self.planning_thing = planning_thing
        self.info = info


class PlanningPeriod:
    _current_point: int
    _arrival_point: int
    _order_cycle: int

    def __init__(self, current_point: int, arrival_point: int, order_cycle: int):
        self._current_point = current_point
        self._arrival_point = arrival_point
        self._order_cycle = order_cycle

    @property
    def current_point(self):
        return self._current_point

    @property
    def arrival_point(self):
        return self._arrival_point

    @property
    def order_cycle(self):
        return self._order_cycle
