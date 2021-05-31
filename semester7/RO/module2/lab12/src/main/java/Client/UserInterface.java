package Client;

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

import Common.Station;
import Common.RegionalRailway;
import org.xml.sax.SAXException;

public class UserInterface extends JFrame{
    private static Client client = null;
    private static RegionalRailway editedRegionalRailway = null;
    private static Station editedStation = null;

    private static boolean editMode = false;
    private static boolean regionalRailwayMode = true;

    private static JButton btnAddRegionalRailway = new JButton("Add Regional railway");
    private static JButton btnAddStation = new JButton("Add Station");
    private static JButton btnEdit= new JButton("Edit Data");
    private static JButton btnCancel= new JButton("Cancel");
    private static JButton btnSave= new JButton("Save");
    private static JButton btnDelete= new JButton("Delete");

    private static Box menuPanel = Box.createVerticalBox();
    private static Box actionPanel = Box.createVerticalBox();
    private static Box comboPanel = Box.createVerticalBox();
    private static Box stationPanel = Box.createVerticalBox();
    private static Box regionalRailwayPanel = Box.createVerticalBox();

    private static JComboBox comboRegionalRailway = new JComboBox();
    private static JComboBox comboStation = new JComboBox();

    private static JTextField tfRegionalRailwayName = new JTextField(30);
    private static JTextField tfStationName = new JTextField(30);
    private static JTextField tfStationRegionalRailwayName = new JTextField(30);
    private static JTextField tfStationRailwayConnections = new JTextField(30);

    private static JFrame frame;

    UserInterface(){
        super("Railway Map");
        frame = this;
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                frame.dispose();
                client.disconnect();
                System.exit(0);
            }
        });
        Box box = Box.createVerticalBox();

        // Menu
        menuPanel.add(btnAddRegionalRailway);
        btnAddRegionalRailway.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent event) {
                editMode = false;
                regionalRailwayMode = true;
                menuPanel.setVisible(false);
                comboPanel.setVisible(false);
                regionalRailwayPanel.setVisible(true);
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
                regionalRailwayMode = false;
                menuPanel.setVisible(false);
                comboPanel.setVisible(false);
                regionalRailwayPanel.setVisible(false);
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
                regionalRailwayPanel.setVisible(false);
                stationPanel.setVisible(false);
                actionPanel.setVisible(true);
                //setContentPane(box);
                pack();
            }
        });

        // ComboBoxes
        comboPanel.add(new JLabel("RegionalRailway:"));
        comboPanel.add(comboRegionalRailway);
        comboRegionalRailway.addActionListener (new ActionListener () {
            public void actionPerformed(ActionEvent e) {
                String name = (String) comboRegionalRailway.getSelectedItem();
                editedRegionalRailway =client.regionalRailwayFindByName((String) comboRegionalRailway.getSelectedItem());
                regionalRailwayMode = true;
                regionalRailwayPanel.setVisible(true);
                stationPanel.setVisible(false);
                fillRegionalRailwayFields();
                //setContentPane(box);
                pack();
            }
        });
        comboPanel.add(new JLabel("Station:"));
        comboPanel.add(comboStation);
        comboStation.addActionListener (new ActionListener () {
            public void actionPerformed(ActionEvent e) {
                String name = (String) comboStation.getSelectedItem();
                editedStation = client.stationFindByName((String) comboStation.getSelectedItem());
                regionalRailwayMode = false;
                regionalRailwayPanel.setVisible(false);
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
        stationPanel.add(new JLabel("Regional railway Name:"));
        stationPanel.add(tfStationRegionalRailwayName);
        stationPanel.add(new JLabel("Railway connections:"));
        stationPanel.add(tfStationRailwayConnections);
        stationPanel.setVisible(false);

        // RegionalRailway Fields
        regionalRailwayPanel.add(new JLabel("Name:"));
        regionalRailwayPanel.add(tfRegionalRailwayName);
        regionalRailwayPanel.setVisible(false);

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
                regionalRailwayPanel.setVisible(false);
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
        box.add(regionalRailwayPanel);
        box.add(stationPanel);
        box.add(actionPanel);
        setContentPane(box);
        pack();
    }

    private static void save() {
        if(editMode) {
            if(regionalRailwayMode) {
                String previousName = editedRegionalRailway.getName();
                editedRegionalRailway.setName(tfRegionalRailwayName.getText());
                if (client.regionalRailwayUpdate(editedRegionalRailway)) {
                    if (!previousName.equals(editedRegionalRailway.getName())) {
                        comboRegionalRailway.addItem(editedRegionalRailway.getName());
                        comboRegionalRailway.removeItem(previousName);
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Error: something went wrong!");
                }
            } else {
                String previousName = editedStation.getName();
                editedStation.setName(tfStationName.getText());
                RegionalRailway cnt = client.regionalRailwayFindByName(tfStationRegionalRailwayName.getText());
                if(cnt == null) {
                    JOptionPane.showMessageDialog(null, "Error: no such regional railway!");
                    return;
                }
                editedStation.setRegionalRailwayId(cnt.getId());
                editedStation.setRailwayConnections(Long.parseLong(tfStationRailwayConnections.getText()));
                if (client.stationUpdate(editedStation)) {
                    if (!previousName.equals(editedStation.getName())) {
                        comboStation.addItem(editedStation.getName());
                        comboStation.removeItem(previousName);
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Error: something went wrong!");
                }
            }
        } else {
            if (regionalRailwayMode) {
                var regionalRailway = new RegionalRailway();
                regionalRailway.setName(tfRegionalRailwayName.getText());
                if(client.regionalRailwayInsert(regionalRailway)) {
                    comboRegionalRailway.addItem(regionalRailway.getName());
                }
            } else {
                var station = new Station();
                station.setName(tfStationName.getText());
                RegionalRailway cnt = client.regionalRailwayFindByName(tfStationRegionalRailwayName.getText());
                if(cnt == null) {
                    JOptionPane.showMessageDialog(null, "Error: no such regional railway!");
                    return;
                }
                station.setRegionalRailwayId(cnt.getId());
                station.setRailwayConnections(Long.parseLong(tfStationRailwayConnections.getText()));
                if(client.stationInsert(station)) {
                    comboStation.addItem(station.getName());
                }
            }
        }
    }

    private static void delete() {
        if(editMode) {
            if(regionalRailwayMode) {
                var list = client.stationFindByRegionalRailwayId(editedRegionalRailway.getId());
                for(Station c: list) {
                    comboStation.removeItem(c.getName());
                    client.stationDelete(c);
                }
                client.regionalRailwayDelete(editedRegionalRailway);
                comboRegionalRailway.removeItem(editedRegionalRailway.getName());

            } else {
                client.stationDelete(editedStation);
                comboStation.removeItem(editedStation.getName());
            }
        }
    }

    private void fillComboBoxes() {
        comboRegionalRailway.removeAllItems();
        comboStation.removeAllItems();
        var regionalRailways = client.regionalRailwayAll();
        var stations = client.stationAll();
        for(RegionalRailway c: regionalRailways) {
            comboRegionalRailway.addItem(c.getName());
        }
        for(Station c: stations) {
            comboStation.addItem(c.getName());
        }
    }

    private static void clearFields() {
        tfRegionalRailwayName.setText("");
        tfStationName.setText("");
        tfStationRegionalRailwayName.setText("");
        tfStationRailwayConnections.setText("");
        editedRegionalRailway = null;
        editedStation = null;
    }

    private static void fillRegionalRailwayFields() {
        if (editedRegionalRailway == null)
            return;
        tfRegionalRailwayName.setText(editedRegionalRailway.getName());
    }
    private static void fillStationFields() {
        if(editedStation == null)
            return;
        RegionalRailway cnt = client.regionalRailwayFindById(editedStation.getRegionalRailwayId());
        tfStationName.setText(editedStation.getName());
        tfStationRegionalRailwayName.setText(cnt.getName());
        tfStationRailwayConnections.setText(String.valueOf(editedStation.getRailwayConnections()));
    }

    public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException {
        client = new Client("localhost",12345);
        JFrame myWindow = new UserInterface();
        myWindow.setVisible(true);
    }
}