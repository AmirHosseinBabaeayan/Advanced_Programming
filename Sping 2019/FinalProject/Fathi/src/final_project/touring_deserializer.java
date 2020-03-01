package final_project;

import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.JsonToken;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.JsonDeserializer;
import javafx.util.Pair;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class touring_deserializer extends JsonDeserializer<save_obj_touring> {

    @Override
    public save_obj_touring deserialize(JsonParser jsonParser, DeserializationContext deserializationContext) throws IOException, JsonProcessingException {
        save_obj_touring object=new save_obj_touring();
        Map<Integer,Touring_states> o1;
        List<Integer> o2;
        Map<Pair<Integer,Integer>,econrel_touring> o3;
        int id=0,state=0,x_axis=0,y_axis=0,n_num1=0,n_num2=0,x1=0,x2=0,y1=0,y2=0,ec_state=0;
        double x_curve=0.0,y_curve=0.0,theta=0.0;
        String path;
        while (!jsonParser.isClosed())
        {
            JsonToken jsonToken=jsonParser.nextToken();
            if(JsonToken.FIELD_NAME.equals(jsonToken))
            {
                String str=jsonParser.currentName();
                if(str.equals("ID"))
                {
                    jsonParser.nextToken();
                    id=jsonParser.getValueAsInt();
                }
                else if(str.equals("State"))
                {
                    jsonParser.nextToken();
                    state=jsonParser.getValueAsInt();
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
                else if(str.equals("ec")) {
                    jsonParser.nextToken();
                    Map<String, String> mp = jsonParser.readValueAs(Map.class);
                    Touring_states ts=new Touring_states(x_axis,y_axis,id);
                    ts.set_s_state(state);
                    if(!mp.isEmpty())
                    {
                        Map<Character, String> ectouring=new HashMap<>();
                        for (Map.Entry<String, String> tmp : mp.entrySet())
                        {
                            ectouring.put(tmp.getKey().charAt(0),tmp.getValue());
                        }
                        ts.set_econ(ectouring);
                    }
                    object.tsc.put(ts.ID,ts);
                }
                else if(str.equals("null_state_li"))
                {
                    jsonParser.nextToken();
                    List<Integer> li=jsonParser.readValueAs(ArrayList.class);
                    if(!li.isEmpty())
                    {
                        object.tns=li;
                    }
                }
                else if(str.equals("node_num1"))
                {
                    jsonParser.nextToken();
                    n_num1=jsonParser.getValueAsInt();
                }
                else if(str.equals("node_num2"))
                {
                    jsonParser.nextToken();
                    n_num2=jsonParser.getValueAsInt();
                }
                else if(str.equals("ec_state"))
                {
                    jsonParser.nextToken();
                    ec_state=jsonParser.getValueAsInt();
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
                    x_curve=jsonParser.getValueAsDouble();
                }
                else if(str.equals("y_curved"))
                {
                    jsonParser.nextToken();
                    y_curve=jsonParser.getValueAsDouble();
                }
                else if(str.equals("theta"))
                {
                    jsonParser.nextToken();
                    theta=jsonParser.getValueAsDouble();
                }
                else if(str.equals("path_name"))
                {
                    jsonParser.nextToken();
                    path=jsonParser.getValueAsString();
                    econrel_touring estouring=new econrel_touring(path,ec_state);
                    estouring.theta=theta;
                    estouring.x1=x1;
                    estouring.y1=y1;
                    estouring.x2=x2;
                    estouring.y2=y2;
                    estouring.x_curved=x_curve;
                    estouring.y_curved=y_curve;
                    object.ect2.put(new Pair<>(n_num1,n_num2),estouring);
                }
            }
        }
        return object;
    }
}
