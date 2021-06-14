import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class RailwayRegionDAO {
    public static RailwayRegion findById(long id) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM railway_region "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, id);
            ResultSet rs = st.executeQuery();
            RailwayRegion railwayRegion = null;
            if(rs.next()) {
                railwayRegion = new RailwayRegion();
                railwayRegion.setId(rs.getLong(1));
                railwayRegion.setName(rs.getString(2));
            }
            st.close();
            return railwayRegion;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static RailwayRegion findByName(String name) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM railway_region "
                            + "WHERE name = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, name);
            ResultSet rs = st.executeQuery();
            RailwayRegion railwayRegion = null;
            if(rs.next()) {
                railwayRegion = new RailwayRegion();
                railwayRegion.setId(rs.getLong(1));
                railwayRegion.setName(rs.getString(2));
            }
            st.close();
            return railwayRegion;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static boolean update(RailwayRegion railwayRegion) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "UPDATE railway_region "
                            + "SET name = ? "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, railwayRegion.getName());
            st.setLong(2, railwayRegion.getId());
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

    public static boolean insert(RailwayRegion railwayRegion) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "INSERT INTO railway_region (name) "
                            + "VALUES (?) ";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, railwayRegion.getName());
//            ResultSet rs =
                    st.executeUpdate();

            String sqlReturn =
                    "SELECT LAST_INSERT_ID();";
            PreparedStatement stReturn = connection.prepareStatement(sqlReturn);
            ResultSet rs = stReturn.executeQuery();

            if(rs.next()) {
                railwayRegion.setId(rs.getLong(1));
            } else
                return false;
            st.close();
            return true;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static boolean delete(RailwayRegion railwayRegion) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "DELETE FROM railway_region "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, railwayRegion.getId());
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

    public static List<RailwayRegion> findAll(){
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM railway_region";
            PreparedStatement st = connection.prepareStatement(sql);
            ResultSet rs = st.executeQuery();
            List<RailwayRegion> list = new ArrayList<>();
            while(rs.next()) {
                var railway_region = new RailwayRegion();
                railway_region.setId(rs.getLong(1));
                railway_region.setName(rs.getString(2));
                list.add(railway_region);
            }
            st.close();
            return list;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }
}