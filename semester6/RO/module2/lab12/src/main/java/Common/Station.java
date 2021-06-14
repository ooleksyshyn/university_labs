package Common;


import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Station {
    private Long id;
    private Long regionalRailwayId;
    private String name;
    private Long railwayConnections;
}