package Server;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Common.RegionalRailway;

public class RegionalRailwayDAO {
    public static RegionalRailway findById(long id) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM railway_region "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, id);
            ResultSet rs = st.executeQuery();
            RegionalRailway regionalRailway = null;
            if(rs.next()) {
                regionalRailway = new RegionalRailway();
                regionalRailway.setId(rs.getLong(1));
                regionalRailway.setName(rs.getString(2));
            }
            st.close();
            return regionalRailway;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static RegionalRailway findByName(String name) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM railway_region "
                            + "WHERE name = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, name);
            ResultSet rs = st.executeQuery();
            RegionalRailway regionalRailway = null;
            if(rs.next()) {
                regionalRailway = new RegionalRailway();
                regionalRailway.setId(rs.getLong(1));
                regionalRailway.setName(rs.getString(2));
            }
            st.close();
            return regionalRailway;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static boolean update(RegionalRailway regionalRailway) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "UPDATE railway_region "
                            + "SET name = ? "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, regionalRailway.getName());
            st.setLong(2, regionalRailway.getId());
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

    public static boolean insert(RegionalRailway regionalRailway) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "INSERT INTO railway_region (name) "
                            + "VALUES (?) ";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, regionalRailway.getName());
//            ResultSet rs =
                    st.executeUpdate();

            String sqlReturn =
                    "SELECT LAST_INSERT_ID();";
            PreparedStatement stReturn = connection.prepareStatement(sqlReturn);
            ResultSet rs = stReturn.executeQuery();

            if(rs.next()) {
                regionalRailway.setId(rs.getLong(1));
            } else
                return false;
            st.close();
            return true;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static boolean delete(RegionalRailway regionalRailway) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "DELETE FROM railway_region "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, regionalRailway.getId());
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

    public static List<RegionalRailway> findAll(){
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM railway_region";
            PreparedStatement st = connection.prepareStatement(sql);
            ResultSet rs = st.executeQuery();
            List<RegionalRailway> list = new ArrayList<>();
            while(rs.next()) {
                var regionalRailway = new RegionalRailway();
                regionalRailway.setId(rs.getLong(1));
                regionalRailway.setName(rs.getString(2));
                list.add(regionalRailway);
            }
            st.close();
            return list;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }
}