package final_project;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.JsonSerializer;
import com.fasterxml.jackson.databind.SerializerProvider;
import javafx.util.Pair;

import java.io.IOException;
import java.util.List;
import java.util.Map;

public class dfa_serializer extends JsonSerializer<save_obj> {
    @Override
    public void serialize(save_obj obj, JsonGenerator jsonGenerator, SerializerProvider serializerProvider) throws IOException {
        List<DFA_states> list=obj.getLi();
        Map<Pair<Integer,Integer>,edge_connection_relation> map=obj.getMa();


        for(DFA_states state:list)
        {
            jsonGenerator.writeStartObject();

            if(state!=null)
            {
                jsonGenerator.writeBooleanField("is_null",false);
                jsonGenerator.writeNumberField("id",state.ID);
                jsonGenerator.writeNumberField("x_axis",state.x_axis);
                jsonGenerator.writeNumberField("y_axis",state.y_axis);
                jsonGenerator.writeNumberField("state",state.getstate());
                jsonGenerator.writeObjectField("edge_container",state.get_econ());
            }
            else
            {
                jsonGenerator.writeBooleanField("is_null",true);

            }
            jsonGenerator.writeEndObject();
        }


        if(!map.isEmpty())
        {
            for(Map.Entry<Pair<Integer,Integer>,edge_connection_relation> m:map.entrySet())
            {
                jsonGenerator.writeStartObject();
                jsonGenerator.writeNumberField("edge_num1",m.getKey().getKey());
                jsonGenerator.writeNumberField("edge_num2",m.getKey().getValue());
                jsonGenerator.writeNumberField("state_t2",m.getValue().get_state());
                jsonGenerator.writeNumberField("x1",m.getValue().x1);
                jsonGenerator.writeNumberField("y1",m.getValue().y1);
                jsonGenerator.writeNumberField("x2",m.getValue().x2);
                jsonGenerator.writeNumberField("y2",m.getValue().y2);
                jsonGenerator.writeNumberField("x_curved",m.getValue().x_curved);
                jsonGenerator.writeNumberField("y_curved",m.getValue().y_curved);
                jsonGenerator.writeNumberField("theta",m.getValue().theta);
                jsonGenerator.writeStringField("path_name",m.getValue().path_name);
                jsonGenerator.writeEndObject();

            }
        }
        else
        {

            jsonGenerator.writeStartObject();
            jsonGenerator.writeNullField("mp");
            jsonGenerator.writeEndObject();
        }

    }
}
