package final_project;

import javax.swing.*;
import java.awt.*;
import java.util.*;

public class DFA_states extends JLabel {
    final public int ID;
    final int x_axis,y_axis;
    String name;
    private int state=0;// 0 -> none    1->final      2->start     3->start , final

    private Map<Character, Set<Integer>> edge_container=new HashMap<>();

    public DFA_states(int x,int y,int name,int id)
    {
        ID=id;
        this.name="V"+Integer.toString(name);
        x_axis=x;
        y_axis=y;

    }
    public String toString()
    {
        String str=ID+" : "+edge_container;
        return str;
    }

    public Map get_econ()
    {
        return edge_container;
    }
    public void set_econ(Map m)
    {
        edge_container=m;
    }

    public void set_methods()
    {
        this.setBounds(x_axis,y_axis,30,10);
        this .setVisible(true);
        this.setBackground(Color.yellow);
        this.setOpaque(true);
        this.setText(name);
    }

    public void set_edge(int node_num,char ch)
    {
        Set<Integer> hs=new HashSet <>();
        if(edge_container.get(ch)!=null)
        {
            hs=edge_container.get(ch);
            hs.add(node_num);
        }
        else
        {
            hs.add(node_num);
            edge_container.put(ch,hs);
        }

    }
    public void setState(int a)
    {
        state+=a;
    }
    public void setStraightState(int a)
    {
        state=a;
    }

    public int getstate()
    {
        return state;
    }

    public void deleted_node(char ch,int index)
    {
        if(edge_container.get(ch)!=null)
        {

            edge_container.get(ch).remove(index);
        }
        if(edge_container.get(ch).isEmpty())
        {
            edge_container.remove(ch);
        }

    }
    public void delete_edge(char ch,int index)
    {
        edge_container.get(ch).remove(index);
        if(edge_container.get(ch).isEmpty())
        {
            edge_container.remove(ch);
        }
    }

    public Set<Integer> get_next_pos(char ch)
    {
        return edge_container.get(ch);
    }
}
