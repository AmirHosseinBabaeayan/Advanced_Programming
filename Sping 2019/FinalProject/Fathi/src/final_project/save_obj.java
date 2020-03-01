package final_project;

import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import com.fasterxml.jackson.annotation.*;

@JsonAutoDetect(fieldVisibility = JsonAutoDetect.Visibility.ANY)
@JsonSerialize(using = dfa_serializer.class)
@JsonDeserialize(using = dfa_deserializer.class)
public class save_obj {
    @JsonProperty("li")
    private List<DFA_states> li;
    @JsonProperty("ma")
    private Map<Pair<Integer,Integer>,edge_connection_relation> ma;
    public save_obj(){
        ma=new HashMap<>();
        li=new ArrayList<>();
    }
    @JsonSetter("ma")
    public void setMa(Map ins)
    {
        ma=ins;
    }
    @JsonGetter("ma")
    public Map getMa()
    {
        return ma;
    }
    @JsonSetter("li")
    public void setLi(List ins)
    {
        li=ins;
    }
    @JsonGetter("li")
    public List getLi()
    {
        return li;
    }
}
