import java.io.File;
import java.io.IOException;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

public class DOMParser {
    public static class SimpleErrorHandler implements ErrorHandler {
        public void warning(SAXParseException e) throws SAXException {
            System.out.println("Line " +e.getLineNumber() + ":");
            System.out.println(e.getMessage());
        }
        public void error(SAXParseException e) throws SAXException {
            System.out.println("Line " +e.getLineNumber() + ":");
            System.out.println(e.getMessage());
        }
        public void fatalError(SAXParseException e) throws SAXException {
            System.out.println("Line " +e.getLineNumber() + ":");
            System.out.println(e.getMessage());
        }
    }

    public static RailwaysMap parse(String path) throws ParserConfigurationException, SAXException, IOException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
        builder.setErrorHandler(new SimpleErrorHandler());
        Document doc = builder.parse(new File(path));
        doc.getDocumentElement().normalize();

        var map = new RailwaysMap();
        NodeList nodes = doc.getElementsByTagName("regionalRailway");

        for(int i = 0; i < nodes.getLength(); ++i) {
            Element n = (Element)nodes.item(i);
            var region = new RegionalRailway();
            region.setId(n.getAttribute("id"));
            region.setName(n.getAttribute("name"));
            map.addRegion(region);

        }

        nodes = doc.getElementsByTagName("station");
        for(int j =0; j < nodes.getLength(); ++j) {
            Element e = (Element) nodes.item(j);
            var station = new Station();
            station.setId(e.getAttribute("id"));
            station.setRegionId(e.getAttribute("regionId"));
            station.setName(e.getAttribute("name"));
            station.setRailwayConnections(Integer.parseInt(e.getAttribute("railwayConnections")));
            map.addStation(station);
        }

        return map;
    }

    public static void write(RailwaysMap map, String path) throws ParserConfigurationException, TransformerException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
        var doc = builder.newDocument();
        Element root = doc.createElement("map");
        doc.appendChild(root);

        var countries = map.getRegions();
        for(Map.Entry<String, RegionalRailway> entry : countries.entrySet()) {
            Element ctr = doc.createElement("regionalRailway");
            ctr.setAttribute("id", entry.getValue().getId());
            ctr.setAttribute("name", entry.getValue().getName());
            root.appendChild(ctr);

            for(Station station : entry.getValue().getStations()) {
                Element ct = doc.createElement("station");
                ct.setAttribute("id", station.getId());
                ct.setAttribute("regionId", station.getRegionId());
                ct.setAttribute("name", station.getName());
                ct.setAttribute("railwayConnections", String.valueOf(station.getRailwayConnections()));
                ctr.appendChild(ct);
            }
        }
        Source domSource = new DOMSource(doc);
        Result fileResult = new StreamResult(new File(path));
        TransformerFactory tfactory = TransformerFactory.newInstance();
        Transformer transformer = tfactory.newTransformer();
        transformer.setOutputProperty(OutputKeys.ENCODING,"UTF-8");
        transformer.setOutputProperty(OutputKeys.DOCTYPE_SYSTEM,"map.dtd");
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
        transformer.transform(domSource, fileResult);
    }

    public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException, TransformerException {
        var map = parse("map.xml");
        var station = new Station("id6","x2","Chernivtsi",15);
        map.addStation(station);
        write(map,"map.xml");
    }
}