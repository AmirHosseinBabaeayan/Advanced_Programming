package final_project;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.JsonSerializer;
import com.fasterxml.jackson.databind.SerializerProvider;
import javafx.util.Pair;

import java.io.IOException;
import java.util.Map;
//@SuppressWarnings("Duplicates")
public class touring_serializer extends JsonSerializer<save_obj_touring> {
    @Override
    public void serialize(save_obj_touring obj, JsonGenerator jsonGenerator, SerializerProvider serializerProvider) throws IOException {
        //jsonGenerator.writeStartObject();
        for(Touring_states st:obj.tsc.values())
        {
            jsonGenerator.writeStartObject();
            jsonGenerator.writeNumberField("ID",st.ID);
            jsonGenerator.writeNumberField("State",st.getstate());
            jsonGenerator.writeNumberField("x_axis",st.x_axis);
            jsonGenerator.writeNumberField("y_axis",st.y_axis);
            jsonGenerator.writeObjectField("ec",st.get_econ());
            jsonGenerator.writeEndObject();
        }
        jsonGenerator.writeStartObject();
        jsonGenerator.writeObjectField("null_state_li",obj.tns);
        jsonGenerator.writeEndObject();
        if(!obj.ect2.isEmpty())
        {
            for(Map.Entry<Pair<Integer,Integer>,econrel_touring> m:obj.ect2.entrySet())
            {
                jsonGenerator.writeStartObject();
                jsonGenerator.writeNumberField("node_num1",m.getKey().getKey());
                jsonGenerator.writeNumberField("node_num2",m.getKey().getValue());
                jsonGenerator.writeNumberField("ec_state",m.getValue().get_state());
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
            jsonGenerator.writeObjectField("null_node",null);
            jsonGenerator.writeEndObject();
        }
        //jsonGenerator.writeEndObject();
    }
}
