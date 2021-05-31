import java.util.ArrayList;
import java.util.List;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.AllArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class RegionalRailway {
    private String id;
    private String name;
    private List<Station> stations = new ArrayList<>();
}