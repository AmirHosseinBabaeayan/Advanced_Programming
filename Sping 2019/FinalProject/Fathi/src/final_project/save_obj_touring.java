package final_project;

import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
@JsonSerialize(using = touring_serializer.class)
@JsonDeserialize(using = touring_deserializer.class)
public class save_obj_touring {
    public Map<Integer,Touring_states> tsc;
    public List<Integer> tns;
    public Map<Pair<Integer,Integer>,econrel_touring> ect2;

    public save_obj_touring()
    {
        tsc=new HashMap<>();
        tns=new ArrayList<>();
        ect2=new HashMap<>();
    }
}
