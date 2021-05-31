package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import Common.RegionalRailway;
import Common.Station;

public class Server {
    private ServerSocket server = null;
    private Socket sock = null;
    private PrintWriter out = null;
    private BufferedReader in = null;

    public void start(int port) throws IOException {
        server = new ServerSocket(port);
        while (true) {
            sock = server.accept();
            in = new BufferedReader(new InputStreamReader(sock.getInputStream( )));
            out = new PrintWriter(sock.getOutputStream(), true);
            while (processQuery());
        }
    }

    private boolean processQuery() {
        int result = 0;
        String response = "";
        try {
            String query = in.readLine();
            if (query==null)
                return false;

            String[] fields = query.split("#");
            if (fields.length == 0){
                return true;
            } else {
                var action = fields[0];
                RegionalRailway regionalRailway;
                Station station;

                System.out.println(action);

                switch(action) {
                    case "RegionalRailwayFindById":
                        var id = Long.parseLong(fields[1]);
                        regionalRailway = RegionalRailwayDAO.findById(id);
                        response = regionalRailway.getName();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "StationFindByRegionalRailwayid":
                        id = Long.parseLong(fields[1]);
                        var list = StationDAO.findByRegionalRailwayId(id);
                        var str = new StringBuilder();
                        for(Station c: list) {
                            str.append(c.getId());
                            str.append("#");
                            str.append(c.getRegionalRailwayId());
                            str.append("#");
                            str.append(c.getName());
                            str.append("#");
                            str.append(c.getRailwayConnections());
                            str.append("#");
                        }
                        response = str.toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "StationFindByName":
                        var name = fields[1];
                        station = StationDAO.findByName(name);
                        response = station.getId().toString()+"#"+ station.getRegionalRailwayId().toString()+"#"+ station.getName()+"#"+ station.getRailwayConnections().toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "RegionalRailwayFindByName":
                        name = fields[1];
                        regionalRailway = RegionalRailwayDAO.findByName(name);
                        response = regionalRailway.getId().toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "StationUpdate":
                        id = Long.parseLong(fields[1]);
                        var regionalRailwayId = Long.parseLong(fields[2]);
                        name = fields[3];
                        var railwayConnections = Long.parseLong(fields[4]);
                        station = new Station(id,regionalRailwayId,name,railwayConnections);
                        if(StationDAO.update(station))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "RegionalRailwayUpdate":
                        id = Long.parseLong(fields[1]);
                        name = fields[2];
                        regionalRailway = new RegionalRailway(id,name);
                        if (RegionalRailwayDAO.update(regionalRailway))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "StationInsert":
                        regionalRailwayId = Long.parseLong(fields[1]);
                        name = fields[2];
                        railwayConnections = Long.parseLong(fields[3]);
                        station = new Station((long) 0,regionalRailwayId,name,railwayConnections);
                        if(StationDAO.insert(station))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "RegionalRailwayInsert":
                        name = fields[1];
                        regionalRailway = new RegionalRailway();
                        regionalRailway.setName(name);

                        System.out.println(name);

                        if(RegionalRailwayDAO.insert(regionalRailway))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "StationDelete":
                        id = Long.parseLong(fields[1]);
                        station = new Station();
                        station.setId(id);
                        if(StationDAO.delete(station))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "RegionalRailwayDelete":
                        id = Long.parseLong(fields[1]);
                        regionalRailway = new RegionalRailway();
                        regionalRailway.setId(id);
                        if(RegionalRailwayDAO.delete(regionalRailway))
                            response = "true";
                        else
                            response = "false";
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "StationAll":
                        var list1 = StationDAO.findAll();
                        str = new StringBuilder();
                        for(Station c: list1) {
                            str.append(c.getId());
                            str.append("#");
                            str.append(c.getRegionalRailwayId());
                            str.append("#");
                            str.append(c.getName());
                            str.append("#");
                            str.append(c.getRailwayConnections());
                            str.append("#");
                        }
                        response = str.toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                    case "RegionalRailwayAll":
                        var list2 = RegionalRailwayDAO.findAll();
                        str = new StringBuilder();
                        for(RegionalRailway c: list2) {
                            str.append(c.getId());
                            str.append("#");
                            str.append(c.getName());
                            str.append("#");
                        }
                        response = str.toString();
                        System.out.println(response);
                        out.println(response);
                        break;
                }
            }

            return true;
        }
        catch(IOException e){
            return false;
        }
    }
    public static void main(String[] args) {
        try {
            Server srv = new Server();
            srv.start(12345);
        } catch(IOException e) {
            System.out.println("Возникла ошибка");
        }
    }
}