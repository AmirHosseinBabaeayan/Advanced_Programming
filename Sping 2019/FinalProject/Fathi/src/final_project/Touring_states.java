package final_project;

import javax.swing.*;
import java.awt.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class Touring_states extends JLabel {

    private int state = 0;
    public final int x_axis, y_axis, ID;
    String name;

    private Map<Character, String> edgecontainer = new HashMap<>();

    public Touring_states(int x, int y, int id) {
        this.ID = id;
        this.name = "V" + id;
        this.x_axis = x;
        this.y_axis = y;
    }

    public int getstate() {
        return state;
    }

    public Map get_econ() {
        return edgecontainer;
    }
    public void set_econ(Map m)
    {
        edgecontainer=m;
    }

    public void set_methods() {
        this.setBounds(x_axis, y_axis, 30, 10);
        this.setVisible(true);
        this.setBackground(Color.yellow);
        this.setOpaque(true);
        this.setText(name);
    }

    public void delete_edge(int index, String pn) {
        String temp = index + pn.substring(1);
        String res = "";
        for (String s : edgecontainer.get(pn.charAt(0)).split("-")) {
            if (!s.equals(temp)) {
                res += "-" + s;
            }
        }
        if (res.isEmpty()) {
            edgecontainer.remove(pn.charAt(0));
        } else {
            edgecontainer.replace(pn.charAt(0), res.substring(1));
        }
    }

    public String get_next_node(char ch) {
        if (edgecontainer.get(ch) != null) {
            return edgecontainer.get(ch);
        } else {
            return "";
        }
    }

    public void set_edge(int node_num, String str) {
        if (edgecontainer.get(str.charAt(0)) != null) {
            String res = node_num + str.substring(1);
            if (!edgecontainer.get(str.charAt(0)).contains(res)) {
                res += "-" + edgecontainer.get(str.charAt(0));
                edgecontainer.replace(str.charAt(0), res);
            }
        } else {
            String res = node_num + str.substring(1);
            edgecontainer.put(str.charAt(0), res);
        }
    }

    public void deleted_node(char ch, int index) {
        if (edgecontainer.get(ch) != null) {
            String res = "";
            for (String temp : edgecontainer.get(ch).split("-")) {
                if (Integer.parseInt(temp.substring(0, 1)) != index) {
                    res += "-" + temp;
                }
            }
            if (!res.isEmpty()) {
                edgecontainer.replace(ch, res.substring(1));
            } else {
                edgecontainer.remove(ch);
            }
        }
    }

    public void setState(int a) {
        state += a;
    }

    public void set_s_state(int a)
    {
        this.state=a;
    }
    public String toString()
    {
        String str=ID+" : "+edgecontainer;
        return str;
    }

}
