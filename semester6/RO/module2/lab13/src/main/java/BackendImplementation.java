import java.rmi.server.UnicastRemoteObject;
import java.util.List;
import java.net.MalformedURLException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class BackendImplementation extends UnicastRemoteObject implements Backend {

    protected BackendImplementation() throws RemoteException {
        super();
        // TODO Auto-generated constructor stub
    }

    @Override
    public RegionalRailway regionalRailwayFindById(Long id) throws RemoteException {
        return RegionalRailwayDAO.findById(id);
    }

    @Override
    public Station stationFindByName(String name) throws RemoteException {
        return StationDAO.findByName(name);
    }

    @Override
    public RegionalRailway regionalRailwayFindByName(String name) throws RemoteException {
        return RegionalRailwayDAO.findByName(name);
    }

    @Override
    public boolean stationUpdate(Station station) throws RemoteException {
        return StationDAO.update(station);
    }

    @Override
    public boolean regionalRailwayUpdate(RegionalRailway regionalRailway) throws RemoteException {
        return RegionalRailwayDAO.update(regionalRailway);
    }

    @Override
    public boolean stationInsert(Station station) throws RemoteException {
        return StationDAO.insert(station);
    }

    @Override
    public boolean regionalRailwayInsert(RegionalRailway regionalRailway) throws RemoteException {
        return RegionalRailwayDAO.insert(regionalRailway);
    }

    @Override
    public boolean regionalRailwayDelete(RegionalRailway regionalRailway) throws RemoteException {
        return RegionalRailwayDAO.delete(regionalRailway);
    }

    @Override
    public boolean stationDelete(Station station) throws RemoteException {
        return StationDAO.delete(station);
    }

    @Override
    public List<RegionalRailway> regionalRailwayAll() throws RemoteException {
        return RegionalRailwayDAO.findAll();
    }

    @Override
    public List<Station> stationAll() throws RemoteException {
        return StationDAO.findAll();
    }

    @Override
    public List<Station> stationFindByRegionalRailwayId(Long idc) throws RemoteException {
        return StationDAO.findByRailwayRegionId(idc);
    }


    public static void main(String[] args) throws RemoteException, MalformedURLException {
        var bck = new BackendImplementation();
        Registry registry = LocateRegistry.createRegistry(12345);
        registry.rebind("Lab13", bck);
        System.out.println("Server started!");
    }
}