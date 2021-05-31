import java.rmi.*;
import java.util.List;

public interface Backend extends Remote{
    public RegionalRailway regionalRailwayFindById(Long id) throws RemoteException;
    public Station stationFindByName(String name) throws RemoteException;
    public RegionalRailway regionalRailwayFindByName(String name) throws RemoteException;
    public boolean stationUpdate(Station station) throws RemoteException;
    public boolean regionalRailwayUpdate(RegionalRailway regionalRailway) throws RemoteException;
    public boolean stationInsert(Station station) throws RemoteException;
    public boolean regionalRailwayInsert(RegionalRailway regionalRailway) throws RemoteException;
    public boolean regionalRailwayDelete(RegionalRailway regionalRailway) throws RemoteException;
    public boolean stationDelete(Station station) throws RemoteException;
    public List<RegionalRailway> regionalRailwayAll() throws RemoteException;
    public List<Station> stationAll() throws RemoteException;
    public List<Station> stationFindByRegionalRailwayId(Long idc) throws RemoteException;
}