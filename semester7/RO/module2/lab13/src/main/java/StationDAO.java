import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class StationDAO {
    public static Station findById(long id) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM station "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, id);
            ResultSet rs = st.executeQuery();
            Station station = null;
            if(rs.next()) {
                station = new Station();
                station.setId(rs.getLong(1));
                station.setName(rs.getString(2));
                station.setRegionalRailwayId(rs.getLong(3));
                station.setRailwayConnections(rs.getLong(4));
            }
            st.close();
            return station;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static Station findByName(String name) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM station "
                            + "WHERE name = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, name);
            ResultSet rs = st.executeQuery();
            Station station = null;
            if(rs.next()) {
                station = new Station();
                station.setId(rs.getLong(1));
                station.setName(rs.getString(2));
                station.setRegionalRailwayId(rs.getLong(3));
                station.setRailwayConnections(rs.getLong(4));
            }
            st.close();
            return station;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static boolean update(Station station) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "UPDATE station "
                            + "SET name = ?, railway_region_id = ?, railway_connections = ? "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, station.getName());
            st.setLong(2, station.getRegionalRailwayId());
            st.setLong(3, station.getRailwayConnections());
            st.setLong(4, station.getId());
            var result = st.executeUpdate();
            st.close();
            if(result>0)
                return true;
            else
                return false;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static boolean insert(Station station) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "INSERT INTO station (name,railway_region_id,railway_connections) "
                            + "VALUES (?,?,?) ";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, station.getName());
            st.setLong(2, station.getRegionalRailwayId());
            st.setLong(3, station.getRailwayConnections());
//            ResultSet rs =
                    st.executeUpdate();

            String sqlReturn =
                    "SELECT LAST_INSERT_ID();";
            PreparedStatement stReturn = connection.prepareStatement(sqlReturn);
            ResultSet rs = stReturn.executeQuery();


            if(rs.next()) {
                station.setId(rs.getLong(1));
            } else
                return false;
            st.close();
            return true;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static boolean delete(Station station) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "DELETE FROM station "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, station.getId());
            var result = st.executeUpdate();
            st.close();
            if(result>0)
                return true;
            else
                return false;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static List<Station> findAll(){
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM station";
            PreparedStatement st = connection.prepareStatement(sql);
            ResultSet rs = st.executeQuery();
            List<Station> list = new ArrayList<>();
            while(rs.next()) {
                var station = new Station();
                station.setId(rs.getLong(1));
                station.setName(rs.getString(2));
                station.setRegionalRailwayId(rs.getLong(3));
                station.setRailwayConnections(rs.getLong(4));
                list.add(station);
            }
            st.close();
            return list;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static List<Station> findByRailwayRegionId(Long id){
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM station "
                            + "WHERE railway_region_id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, id);
            ResultSet rs = st.executeQuery();
            List<Station> list = new ArrayList<>();
            while(rs.next()) {
                var station = new Station();
                station.setId(rs.getLong(1));
                station.setName(rs.getString(2));
                station.setRegionalRailwayId(rs.getLong(3));
                station.setRailwayConnections(rs.getLong(4));
                list.add(station);
            }
            st.close();
            return list;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }
}