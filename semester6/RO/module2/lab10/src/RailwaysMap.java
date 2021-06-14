import java.util.HashMap;
import java.util.Map;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class RailwaysMap {
    private Map<String, RegionalRailway> regions = new HashMap<>();
    private Map<String,String> regionNames = new HashMap<>();
    private Map<String, Station> stations = new HashMap<>();
    private Map<String,String> stationNames = new HashMap<>();

    public void generateId(RegionalRailway c) {
        var id = regions.size();
        String idStr = "reg"+id;
        while(regions.get(idStr) != null) {
            id++;
            idStr = "reg"+id;
        }
        c.setId(idStr);
    }
    public void generateId(Station c) {
        var id = stations.size();
        String idStr = "st"+id;
        while(stations.get(idStr) != null) {
            id++;
            idStr = "st"+id;
        }
        c.setId(idStr);
    }

    public void addRegion(RegionalRailway c) {
        var changed = false;
        if(regions.get(c.getId())!=null) {
            changed = true;
            generateId(c);
        }
        if (changed) {
            for(Station ct: c.getStations())
                ct.setRegionId(c.getId());
        }
        regions.put(c.getId(), c);
        regionNames.put(c.getName(), c.getId());
    }

    public void removeRegion(RegionalRailway c) {
        regions.remove(c.getId());
        regionNames.remove(c.getName());
        for(Station ct: c.getStations())
            stations.remove(ct.getId());
    }

    public void addStation(Station s) {
        if(stations.get(s.getId())!=null) {
            generateId(s);
        }
        stations.put(s.getId(),s);

        if (regions.get(s.getRegionId()).getStations().stream().noneMatch(station -> s.getId().equals(station.getId()))) {
            regions.get(s.getRegionId()).getStations().add(s);
        }

        stationNames.put(s.getName(), s.getId());
    }

    public void removeStation(Station c) {
        stations.remove(c.getId());
        stationNames.remove(c.getName());
        regions.get(c.getRegionId()).getStations().remove(c);
    }

    public void transferStation(Station station, RegionalRailway regionalRailway) {
        var old = regions.get(station.getRegionId());
        if (old != null)
            old.getStations().remove(station);
        station.setRegionId(regionalRailway.getId());
        regionalRailway.getStations().add(station);
    }

    public void rename(RegionalRailway c, String name) {
        regionNames.remove(c.getName());
        c.setName(name);
        regionNames.put(c.getName(),c.getId());
    }
    public void rename(Station c, String name) {
        stationNames.remove(c.getName());
        c.setName(name);
        stationNames.put(c.getName(),c.getId());
    }


    public RegionalRailway getRegion(String name) {
        var id = regionNames.get(name);
        if(id != null)
            return regions.get(id);
        return null;
    }
    public Station getStation(String name) {
        var id = stationNames.get(name);
        if(id != null)
            return stations.get(id);
        return null;
    }
}