package final_project;

import static java.lang.Math.pow;

public class econrel_touring {
    private int state;
    public int x1,x2,y1,y2;
    public double x_curved,y_curved;
    public double theta;
    public String path_name;

    public econrel_touring(String str, int s)
    {
        state=s;
        path_name=str;
    }
    public void set_path_name(String str)
    {
        path_name+="-"+str;
    }
    public void edit_path_name(String str){path_name=str;}
    public void set_state(int s)
    {
        state=s;
    }
    public int get_state()
    {
        return state;
    }
    public void calculation(int x1_obj,int y1_obj,int x2_obj,int y2_obj)
    {
        int x=x2_obj-x1_obj;
        int y=y2_obj-y1_obj;
        double deegre=Math.atan2(y,x);

        x1=(int)Math.round(x2_obj+5-30*Math.cos(deegre));
        y1=(int)Math.round(y2_obj+5-30*Math.sin(deegre));

        x2=(int)Math.round(x1_obj+5+30*Math.cos(deegre));
        y2=(int)Math.round(y1_obj+5+30*Math.sin(deegre));

        if(x==0&y==0)
        {
            state=2;
            x_curved=(x1+x2)/2;
            y_curved=y2+(x2-x1)+10;
            theta=Math.atan2(y_curved-y1,x_curved-x1);
            return;
        }

        double distance=Math.sqrt(pow(x1-x2,2)+pow(y1-y2,2))/2;

        if(state==2)
        {
            double r=Math.sqrt(pow(distance,2)+1600);
            theta=deegre+Math.atan2(40,distance);

            x_curved=Math.round(x1-r*Math.cos(theta));
            y_curved=Math.round(y1-r*Math.sin(theta));
        }
        else if(state==1)
        {
            double r=Math.sqrt(pow(distance,2)+100);
            theta=deegre+Math.atan2(10,distance);

            x_curved=Math.round(x1-r*Math.cos(theta));
            y_curved=Math.round(y1-r*Math.sin(theta));

            theta=deegre;
        }
    }
}
