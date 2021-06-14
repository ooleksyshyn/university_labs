import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.AllArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Station {
    private String id;
    private String regionId;
    private String name;
    private int railwayConnections;
}