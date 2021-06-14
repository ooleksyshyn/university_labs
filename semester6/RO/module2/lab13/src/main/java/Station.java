import java.io.Serializable;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Station implements Serializable{
    private Long id;
    private Long regionalRailwayId;
    private String name;
    private Long railwayConnections;
}