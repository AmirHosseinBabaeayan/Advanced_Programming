package final_project;

import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.JsonToken;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.JsonDeserializer;
import javafx.util.Pair;

import java.io.IOException;
import java.util.*;

public class dfa_deserializer extends JsonDeserializer<save_obj> {
    @Override
    public save_obj deserialize(JsonParser jsonParser, DeserializationContext deserializationContext) throws IOException, JsonProcessingException {
        List<DFA_states> l=new ArrayList<>();
        save_obj so=new save_obj();
        int id=0,x_axis=0,y_axis=0,state=0,edge_num1=0,edge_num2=0,state_t2=0,x1=0,x2=0,y1=0,y2=0;
        double x_curved=0,y_curved=0,theta=0;
        String path_name;
        Map<String, Set<Integer>> mp;
        Map<Pair<Integer,Integer>,edge_connection_relation> econt2=new HashMap<>();
        while (!jsonParser.isClosed())
        {
            JsonToken jsonToken=jsonParser.nextToken();
            if(JsonToken.FIELD_NAME.equals(jsonToken))
            {
                String str=jsonParser.currentName();
                if(str.equals("is_null"))
                {
                    jsonParser.nextToken();
                    boolean b=jsonParser.getValueAsBoolean();
                    if(b) {l.add(null);}
                }
                else if(str.equals("id"))
                {
                    jsonParser.nextToken();
                    id=jsonParser.getValueAsInt();
                }
                else if(str.equals("x_axis"))
                {
                    jsonParser.nextToken();
                    x_axis=jsonParser.getValueAsInt();
                }
                else if(str.equals("y_axis"))
                {
                    jsonParser.nextToken();
                    y_axis=jsonParser.getValueAsInt();
                }
                else if(str.equals("state"))
                {
                    jsonParser.nextToken();
                    state=jsonParser.getValueAsInt();
                }
                else if(str.equals("edge_container"))
                {
                    jsonParser.nextToken();
                    mp=jsonParser.readValueAs(Map.class);
                    String fd=jsonParser.getValueAsString();
                    //jsonParser.ge
                    Map<Character, Set<Integer>> ec=new HashMap<>();
                    //int n=Integer.parseInt(name.substring(1));
                    DFA_states ob=new DFA_states(x_axis,y_axis,id,id);
                    ob.setStraightState(state);
                    if(!mp.isEmpty())
                    {
                        for (Map.Entry<String, Set<Integer>> m:mp.entrySet())
                        {
                            ec.put(m.getKey().charAt(0),new HashSet<Integer>(m.getValue()));
                        }
                    }
                    ob.set_econ(ec);
                    l.add(ob.ID-1,ob);
                }
                else if(str.equals("edge_num1"))
                {
                    jsonParser.nextToken();
                    edge_num1=jsonParser.getValueAsInt();
                }
                else if(str.equals("edge_num2"))
                {
                    jsonParser.nextToken();
                    edge_num2=jsonParser.getValueAsInt();
                }
                else if(str.equals("state_t2"))
                {
                    jsonParser.nextToken();
                    state_t2=jsonParser.getValueAsInt();
                }
                else if(str.equals("x1"))
                {
                    jsonParser.nextToken();
                    x1=jsonParser.getValueAsInt();
                }
                else if(str.equals("y1"))
                {
                    jsonParser.nextToken();
                    y1=jsonParser.getValueAsInt();
                }
                else if(str.equals("x2"))
                {
                    jsonParser.nextToken();
                    x2=jsonParser.getValueAsInt();
                }
                else if(str.equals("y2"))
                {
                    jsonParser.nextToken();
                    y2=jsonParser.getValueAsInt();
                }
                else if(str.equals("x_curved"))
                {
                    jsonParser.nextToken();
                    x_curved=jsonParser.getValueAsDouble();
                }
                else if(str.equals("y_curved"))
                {
                    jsonParser.nextToken();
                    y_curved=jsonParser.getValueAsDouble();
                }
                else if(str.equals("theta"))
                {
                    jsonParser.nextToken();
                    theta=jsonParser.getValueAsDouble();
                }
                else if(str.equals("path_name"))
                {
                    jsonParser.nextToken();
                    path_name=jsonParser.getText().trim();
                    edge_connection_relation ob=new edge_connection_relation(path_name,state_t2);
                    ob.x1=x1;
                    ob.x2=x2;
                    ob.y1=y1;
                    ob.y2=y2;
                    ob.x_curved=x_curved;
                    ob.y_curved=y_curved;
                    ob.theta=theta;
                    econt2.put(new Pair<>(edge_num1,edge_num2),ob);
                }
            }
        }
        so.setLi(l);
        so.setMa(econt2);
        return so;
    }
}
