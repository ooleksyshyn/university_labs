import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.util.Map;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.xml.sax.SAXException;

public class UserInterface extends JFrame{
    private static RailwaysMap map;
    private static RegionalRailway regionOldName = null;
    private static Station stationOldName = null;

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
    private static JTextField tfStationConnections = new JTextField(30);

    private static JFrame frame;

    UserInterface(){
        super("Railway map");
        frame = this;
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                frame.dispose();
                try {
                    DOMParser.write(map,"src/map.xml");
                } catch (ParserConfigurationException | TransformerException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
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
        comboPanel.add(new JLabel("Railway region:"));
        comboPanel.add(comboRailwayRegion);
        comboRailwayRegion.addActionListener (new ActionListener () {
            public void actionPerformed(ActionEvent e) {
                String name = (String) comboRailwayRegion.getSelectedItem();
                regionOldName = map.getRegion(name);
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
                stationOldName = map.getStation(name);
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
        stationPanel.add(new JLabel("RailwayRegion Name:"));
        stationPanel.add(tfStationRailwayRegionName);
        stationPanel.add(new JLabel("Amount of railway connections:"));
        stationPanel.add(tfStationConnections);
        stationPanel.setVisible(false);

        // Railway Region Fields
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
                var oldname = regionOldName.getName();
                var newname = tfRailwayRegionName.getText();
                if (changeRailwayRegion(regionOldName) && !regionOldName.getName().equals(oldname)) {
                    comboRailwayRegion.removeItem(oldname);
                    comboRailwayRegion.addItem(newname);
                    comboRailwayRegion.setSelectedIndex(comboRailwayRegion.getItemCount()-1);
                }
            } else {
                var oldname = stationOldName.getName();
                var newname = tfStationRailwayRegionName.getText();
                if (changeStation(stationOldName) && !stationOldName.getName().equals(oldname)) {
                    comboStation.removeItem(oldname);
                    comboStation.addItem(newname);
                    comboStation.setSelectedIndex(comboStation.getItemCount()-1);
                }
            }
        } else {
            if (railwayRegionMode) {
                var regionalRailway = new RegionalRailway();
                map.generateId(regionalRailway);
                if(changeRailwayRegion(regionalRailway)) {
                    map.addRegion(regionalRailway);
                    comboRailwayRegion.addItem(regionalRailway.getName());
                }
            } else {
                var station = new Station();
                map.generateId(station);
                if(changeStation(station)) {
                    map.addStation(station);
                    comboStation.addItem(station.getName());
                }
            }
        }
    }
    private static boolean changeRailwayRegion(RegionalRailway c) {
        var newName = tfRailwayRegionName.getText();
        if(map.getRegion(newName) == null) {
            map.rename(c, newName);
            return true;
        }
        fillRailwayRegionFields();
        JOptionPane.showMessageDialog(null, "Error: this railway region already exists!");
        return false;
    }
    private static boolean changeStation(Station c) {
        var cnt = map.getRegion(tfStationRailwayRegionName.getText());
        if (cnt == null) {
            fillStationFields();
            JOptionPane.showMessageDialog(null, "Error: no such railway region!");
            return false;
        }
        var newName = tfStationName.getText();
        if(map.getStation(newName) == null)
            map.rename(c, newName);
        map.transferStation(c, cnt);
        c.setRailwayConnections(Integer.parseInt(tfStationConnections.getText()));
        return true;
    }

    private static void delete() {
        if(editMode) {
            if(railwayRegionMode) {
                map.removeRegion(regionOldName);
                for(Station c: regionOldName.getStations())
                    comboStation.removeItem(c.getName());
                comboRailwayRegion.removeItem(regionOldName.getName());
            } else {
                map.removeStation(stationOldName);
                comboStation.removeItem(stationOldName.getName());
            }
        }
    }

    private void fillComboBoxes() {
        comboRailwayRegion.removeAllItems();
        comboStation.removeAllItems();
        var regions = map.getRegions();
        for(Map.Entry<String, RegionalRailway> entry : regions.entrySet()) {
            comboRailwayRegion.addItem(entry.getValue().getName());
            for(Station station : entry.getValue().getStations()) {
                comboStation.addItem(station.getName());
            }
        }
    }

    private static void clearFields() {
        tfRailwayRegionName.setText("");
        tfStationName.setText("");
        tfStationRailwayRegionName.setText("");
        tfStationConnections.setText("");
        regionOldName = null;
        stationOldName = null;
    }

    private static void fillRailwayRegionFields() {
        if (regionOldName == null)
            return;
        tfRailwayRegionName.setText(regionOldName.getName());
    }
    private static void fillStationFields() {
        if(stationOldName == null)
            return;
        var regions = map.getRegions();
        tfStationName.setText(stationOldName.getName());
        tfStationRailwayRegionName.setText(regions.get(stationOldName.getRegionId()).getName());
        tfStationConnections.setText(String.valueOf(stationOldName.getRailwayConnections()));
    }

    public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException {
        map = DOMParser.parse("src/map.xml");
        JFrame myWindow = new UserInterface();
        myWindow.setVisible(true);
    }
}