package Client;


import Common.RegionalRailway;
import Common.Station;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Client {
    private Socket sock = null;
    private PrintWriter out = null;
    private BufferedReader in = null;
    private static final String split = "#";

    Client(String ip, int port) throws IOException{
        // establish connection
        sock = new Socket(ip,port);
        // get input/output streams
        in = new BufferedReader(
                new InputStreamReader(sock.getInputStream( )));
        out = new PrintWriter(sock.getOutputStream(), true);
    }

    public RegionalRailway regionalRailwayFindById(Long id) {
        var query = "RegionalRailwayFindById"+split+id.toString();
        out.println(query);
        String response = "";
        try {
            response = in.readLine();
            return new RegionalRailway(id,response);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    public Station stationFindByName(String name) {
        var query = "StationFindByName"+split+name;
        out.println(query);
        String response = "";
        try {
            response = in.readLine();
            String[] fields = response.split(split);
            var id = Long.parseLong(fields[0]);
            var regionalRailwayId = Long.parseLong(fields[1]);
            var railwayConnections = Long.parseLong(fields[3]);
            return new Station(id,regionalRailwayId,name,railwayConnections);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    public RegionalRailway regionalRailwayFindByName(String name) {
        var query = "RegionalRailwayFindByName"+split+name;
        out.println(query);
        try {
            var response = Long.parseLong(in.readLine());
            return new RegionalRailway(response,name);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    public boolean stationUpdate(Station station) {
        var query = "StationUpdate"+split+ station.getId().toString()+
                "#"+ station.getRegionalRailwayId().toString()+"#"+ station.getName()
                +"#"+ station.getRailwayConnections().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return false;
    }

    public boolean regionalRailwayUpdate(RegionalRailway regionalRailway) {
        var query = "RegionalRailwayUpdate"+split+ regionalRailway.getId().toString()+
                "#"+ regionalRailway.getName();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return false;
    }

    public boolean stationInsert(Station station) {
        var query = "StationInsert"+
                "#"+ station.getRegionalRailwayId().toString()+"#"+ station.getName()
                +"#"+ station.getRailwayConnections().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return false;
    }

    public boolean regionalRailwayInsert(RegionalRailway regionalRailway) {
        var query = "RegionalRailwayInsert"+
                "#"+ regionalRailway.getName();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return false;
    }

    public boolean regionalRailwayDelete(RegionalRailway regionalRailway) {
        var query = "RegionalRailwayDelete"+split+ regionalRailway.getId().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return false;
    }

    public boolean stationDelete(Station station) {
        var query = "StationDelete"+split+ station.getId().toString();
        out.println(query);
        try {
            var response = in.readLine();
            if ("true".equals(response))
                return true;
            else
                return false;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return false;
    }

    public List<RegionalRailway> regionalRailwayAll(){
        var query = "RegionalRailwayAll";
        out.println(query);
        var list = new ArrayList<RegionalRailway>();
        try {
            var response = in.readLine();
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=2) {
                var id = Long.parseLong(fields[i]);
                var name = fields[i+1];
                list.add(new RegionalRailway(id,name));
            }
            return list;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    public List<Station> stationAll(){
        var query = "StationAll";
        out.println(query);
        var list = new ArrayList<Station>();
        try {
            var response = in.readLine();
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=4) {
                var id = Long.parseLong(fields[i]);
                var regionalRailwayId = Long.parseLong(fields[i+1]);
                var name = fields[i+2];
                var railwayConnections = Long.parseLong(fields[i+3]);
                list.add(new Station(id,regionalRailwayId,name,railwayConnections));
            }
            return list;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    public List<Station> stationFindByRegionalRailwayId(Long idc){
        var query = "StationFindByRegionalRailwayId"+split+idc.toString();
        out.println(query);
        var list = new ArrayList<Station>();
        try {
            var response = in.readLine();
            String[] fields = response.split(split);
            for(int i=0;i<fields.length; i+=4) {
                var id = Long.parseLong(fields[i]);
                var regionalRailwayId = Long.parseLong(fields[i+1]);
                var name = fields[i+2];
                var railwayConnections = Long.parseLong(fields[i+3]);
                list.add(new Station(id,regionalRailwayId,name,railwayConnections));
            }
            return list;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    public void disconnect(){
        try {
            sock.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws IOException {
        //(new Client()).test("localhost",12345);
    }
}