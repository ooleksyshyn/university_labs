import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public class UserInterface extends JFrame{
    private static RailwayRegion oldRailwayRegion = null;
    private static Station oldStation = null;

    private static boolean editMode = false;
    private static boolean railwayRegionMode = true;

    private static JButton btnAddRailwayRegion = new JButton("Add Railway region");
    private static JButton btnAddStation = new JButton("Add Station");
    private static JButton btnEdit= new JButton("Edit Data");
    private static JButton btnCancel= new JButton("Cancel");
    private static JButton btnSave= new JButton("Save");
    private static JButton btnDelete= new JButton("Delete");

    private static Box menuPanel = Box.createVerticalBox();
    private static Box actionPanel = Box.createVerticalBox();
    private static Box comboPanel = Box.createVerticalBox();
    private static Box stationPanel = Box.createVerticalBox();
    private static Box railwayRegionPanel = Box.createVerticalBox();

    private static JComboBox comboRailwayRegion = new JComboBox();
    private static JComboBox comboStation = new JComboBox();

    private static JTextField tfRailwayRegionName = new JTextField(30);
    private static JTextField tfStationName = new JTextField(30);
    private static JTextField tfStationRailwayRegionName = new JTextField(30);
    private static JTextField tfStationRailwayConnections = new JTextField(30);

    private static JFrame frame;

    UserInterface(){
        super("Railway map");
        frame = this;
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                frame.dispose();
                DBConnection.closeConnection();
                System.exit(0);
            }
        });
        Box box = Box.createVerticalBox();

        // Menu
        menuPanel.add(btnAddRailwayRegion);
        btnAddRailwayRegion.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                editMode = false;
                railwayRegionMode = true;
                menuPanel.setVisible(false);
                comboPanel.setVisible(false);
                railwayRegionPanel.setVisible(true);
                stationPanel.setVisible(false);
                actionPanel.setVisible(true);
                //setContentPane(box);
                pack();
            }
        });
        menuPanel.add(btnAddStation);
        btnAddStation.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                editMode = false;
                railwayRegionMode = false;
                menuPanel.setVisible(false);
                comboPanel.setVisible(false);
                railwayRegionPanel.setVisible(false);
                stationPanel.setVisible(true);
                actionPanel.setVisible(true);
                //setContentPane(box);
                pack();
            }
        });
        menuPanel.add(btnEdit);
        btnEdit.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                editMode = true;
                menuPanel.setVisible(false);
                comboPanel.setVisible(true);
                railwayRegionPanel.setVisible(false);
                stationPanel.setVisible(false);
                actionPanel.setVisible(true);
                //setContentPane(box);
                pack();
            }
        });

        // ComboBoxes
        comboPanel.add(new JLabel("RailwayRegion:"));
        comboPanel.add(comboRailwayRegion);
        comboRailwayRegion.addActionListener (new ActionListener () {
            public void actionPerformed(ActionEvent e) {
                String name = (String) comboRailwayRegion.getSelectedItem();
                oldRailwayRegion = RailwayRegionDAO.findByName((String) comboRailwayRegion.getSelectedItem());
                railwayRegionMode = true;
                railwayRegionPanel.setVisible(true);
                stationPanel.setVisible(false);
                fillRailwayRegionFields();
                //setContentPane(box);
                pack();
            }
        });
        comboPanel.add(new JLabel("Station:"));
        comboPanel.add(comboStation);
        comboStation.addActionListener (new ActionListener () {
            public void actionPerformed(ActionEvent e) {
                String name = (String) comboStation.getSelectedItem();
                oldStation = StationDAO.findByName((String) comboStation.getSelectedItem());
                railwayRegionMode = false;
                railwayRegionPanel.setVisible(false);
                stationPanel.setVisible(true);
                fillStationFields();
                //setContentPane(box);
                pack();
            }
        });
        fillComboBoxes();
        comboPanel.setVisible(false);

        // Station Fields
        stationPanel.add(new JLabel("Name:"));
        stationPanel.add(tfStationName);
        stationPanel.add(new JLabel("Railway region Name:"));
        stationPanel.add(tfStationRailwayRegionName);
        stationPanel.add(new JLabel("Railway connections:"));
        stationPanel.add(tfStationRailwayConnections);
        stationPanel.setVisible(false);

        // RailwayRegion Fields
        railwayRegionPanel.add(new JLabel("Name:"));
        railwayRegionPanel.add(tfRailwayRegionName);
        railwayRegionPanel.setVisible(false);

        // Action Bar
        actionPanel.add(btnSave);
        btnSave.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                save();
            }
        });
        actionPanel.add(btnDelete);
        btnDelete.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                delete();
            }
        });
        actionPanel.add(btnCancel);
        btnCancel.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                clearFields();
                menuPanel.setVisible(true);
                comboPanel.setVisible(false);
                railwayRegionPanel.setVisible(false);
                stationPanel.setVisible(false);
                actionPanel.setVisible(false);
                //setContentPane(box);
                pack();
            }
        });
        actionPanel.setVisible(false);

        clearFields();
        box.add(menuPanel);
        box.add(comboPanel);
        box.add(railwayRegionPanel);
        box.add(stationPanel);
        box.add(actionPanel);
        setContentPane(box);
        pack();
    }

    private static void save() {
        if(editMode) {
            if(railwayRegionMode) {
                oldRailwayRegion.setName(tfRailwayRegionName.getText());
                if (!RailwayRegionDAO.update(oldRailwayRegion)) {
                    JOptionPane.showMessageDialog(null, "Error: something went wrong!");
                }
            } else {
                oldStation.setName(tfStationName.getText());
                RailwayRegion cnt = RailwayRegionDAO.findByName(tfStationRailwayRegionName.getText());
                if(cnt == null) {
                    JOptionPane.showMessageDialog(null, "Error: no such railway region!");
                    return;
                }
                oldStation.setRailwayRegionId(cnt.getId());
                oldStation.setRailwayConnections(Long.parseLong(tfStationRailwayConnections.getText()));
                if (!StationDAO.update(oldStation)) {
                    JOptionPane.showMessageDialog(null, "Error: something went wrong!");
                }
            }
        } else {
            if (railwayRegionMode) {
                var railwayRegion = new RailwayRegion();
                railwayRegion.setName(tfRailwayRegionName.getText());
                if(RailwayRegionDAO.insert(railwayRegion)) {
                    comboRailwayRegion.addItem(railwayRegion.getName());
                }
            } else {
                var station = new Station();
                station.setName(tfStationName.getText());
                RailwayRegion cnt = RailwayRegionDAO.findByName(tfStationRailwayRegionName.getText());
                if(cnt == null) {
                    JOptionPane.showMessageDialog(null, "Error: no such railway region!");
                    return;
                }
                station.setRailwayRegionId(cnt.getId());
                station.setRailwayConnections(Long.parseLong(tfStationRailwayConnections.getText()));
                if(StationDAO.insert(station)) {
                    comboStation.addItem(station.getName());
                }
            }
        }
    }

    private static void delete() {
        if(editMode) {
            if(railwayRegionMode) {
                var list = StationDAO.findByRailwayRegionId(oldRailwayRegion.getId());
                for(Station c: list) {
                    comboStation.removeItem(c.getName());
                    StationDAO.delete(c);
                }
                RailwayRegionDAO.delete(oldRailwayRegion);
                comboRailwayRegion.removeItem(oldRailwayRegion.getName());

            } else {
                StationDAO.delete(oldStation);
                comboStation.removeItem(oldStation.getName());
            }
        }
    }

    private void fillComboBoxes() {
        comboRailwayRegion.removeAllItems();
        comboStation.removeAllItems();
        var regionalRailways = RailwayRegionDAO.findAll();
        var stations = StationDAO.findAll();
        for(RailwayRegion c: regionalRailways) {
            comboRailwayRegion.addItem(c.getName());
        }
        for(Station c: stations) {
            comboStation.addItem(c.getName());
        }
    }

    private static void clearFields() {
        tfRailwayRegionName.setText("");
        tfStationName.setText("");
        tfStationRailwayRegionName.setText("");
        tfStationRailwayConnections.setText("");
        oldRailwayRegion = null;
        oldStation = null;
    }

    private static void fillRailwayRegionFields() {
        if (oldRailwayRegion == null)
            return;
        tfRailwayRegionName.setText(oldRailwayRegion.getName());
    }
    private static void fillStationFields() {
        if(oldStation == null)
            return;
        RailwayRegion cnt = RailwayRegionDAO.findById(oldStation.getRailwayRegionId());
        tfStationName.setText(oldStation.getName());
        tfStationRailwayRegionName.setText(cnt.getName());
        tfStationRailwayConnections.setText(String.valueOf(oldStation.getRailwayConnections()));
    }

    public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException {
        JFrame myWindow = new UserInterface();
        myWindow.setVisible(true);
    }
}