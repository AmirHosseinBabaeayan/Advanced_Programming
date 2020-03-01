package final_project;

import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.util.Pair;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.font.FontRenderContext;
import java.awt.font.GlyphVector;
import java.awt.geom.AffineTransform;
import java.awt.geom.QuadCurve2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.*;
import java.util.List;
@SuppressWarnings("Duplicates")
public class Touring_machine_class extends JFrame {
    private JPanel touring_panel;
    private JMenuBar touring_menue_bar;
    private JMenu menu_file,menue_help;
    private JMenuItem save_machine,open_machine,fast_run,multi_input_run,slow_run,save_as_img,help;
    private JToolBar touring_tools;
    private JButton insert_node,delete,graph_edge,none;
    private Dimension d;
    private List<Integer> start_states_container;

    enum States{non,inseert,edge,dele;}
    States state= States.non;

    private Map<Integer,Touring_states> touring_state_container;
    private List<Integer> touring_null_states;
    private Map<Pair<Integer,Integer>,econrel_touring> edge_container_type2;

    public Touring_machine_class()
    {
        start_states_container=new ArrayList<>();
        touring_state_container=new HashMap<>();
        touring_null_states=new ArrayList<>();
        edge_container_type2=new HashMap<>();
    }

    public void jframe_methods(JFrame jf_main)
    {
        this.setVisible(true);
        this.setTitle("Touring machine");
        this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        this.setResizable(false);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosed(WindowEvent e) {
                super.windowClosed(e);
                jf_main.setVisible(true);
            }
        });
        add_panel();
        add_menue_bar();
        add_jtoolbars();
        add_act_for_btns();
        add_panel_listener();
        this.pack();
    }

    private void add_panel()
    {
        touring_panel=new JPanel()
        {
            @Override
            public void paintComponent(Graphics g)
            {
                super.paintComponent(g);
                Graphics2D g2d=(Graphics2D)g;
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
                if(!touring_state_container.isEmpty())
                {
                    for(Map.Entry<Integer,Touring_states>itr:touring_state_container.entrySet())
                    {
                        BasicStroke basicStroke= (BasicStroke) g2d.getStroke();
                        if(itr.getValue().getstate()==1)
                        {
                            g2d.setColor(Color.RED);
                            g2d.fillOval(itr.getValue().x_axis-25,itr.getValue().y_axis-25,60,60);
                            g2d.setColor(Color.BLACK);
                            g2d.setStroke(new BasicStroke(5));
                            g2d.drawOval(itr.getValue().x_axis-25,itr.getValue().y_axis-25,60,60);
                            g2d.setStroke(basicStroke);
                        }
                        else if(itr.getValue().getstate()==2)
                        {
                            g2d.setColor(Color.GREEN);
                            g2d.fillOval(itr.getValue().x_axis-25,itr.getValue().y_axis-25,60,60);
                        }
                        else if(itr.getValue().getstate()==3)
                        {
                            g2d.setColor(new Color(100,0,50));
                            g2d.fillOval(itr.getValue().x_axis-25,itr.getValue().y_axis-25,60,60);
                            g2d.setColor(Color.BLACK);
                            g2d.setStroke(new BasicStroke(5));
                            g2d.drawOval(itr.getValue().x_axis-25,itr.getValue().y_axis-25,60,60);
                            g2d.setStroke(basicStroke);
                        }
                        else
                        {
                            g2d.setColor(Color.CYAN);
                            g2d.fillOval(itr.getValue().x_axis-25,itr.getValue().y_axis-25,60,60);
                        }
                    }
                    if(!edge_container_type2.isEmpty())
                    {
                        draw_edge_calculation(g2d);
                    }
                }
            }
        };
        touring_panel.setLayout(null);

        Toolkit toolkit=Toolkit.getDefaultToolkit();
        d=toolkit.getScreenSize();
        d.height-=70;
        touring_panel.setPreferredSize(d);
        this.add(touring_panel);
    }
    private void add_menue_bar()
    {
        touring_menue_bar=new JMenuBar();
        menu_file=new JMenu("File");
        menue_help=new JMenu("Help");
        save_machine=new JMenuItem("Save");
        save_machine.setAccelerator(KeyStroke.getKeyStroke('S',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        save_machine.addActionListener(new act_save_machine_btn());
        open_machine=new JMenuItem("Open");
        open_machine.setAccelerator(KeyStroke.getKeyStroke('O',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        open_machine.addActionListener(new act_open_machine_btn());
        fast_run=new JMenuItem("F Run");
        fast_run.setAccelerator(KeyStroke.getKeyStroke('r',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        fast_run.addActionListener(new act_run_btn());
        multi_input_run=new JMenuItem("Multi Input run");
        multi_input_run.setAccelerator(KeyStroke.getKeyStroke('M',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        multi_input_run.addActionListener(new act_multiInputRun());
        slow_run=new JMenuItem("Run");
        slow_run.setAccelerator(KeyStroke.getKeyStroke('P',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        slow_run.addActionListener(new act_slow_run());
        save_as_img=new JMenuItem("Save as image");
        save_as_img.setAccelerator(KeyStroke.getKeyStroke('i',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        save_as_img.addActionListener(new act_save_as_image());
        help=new JMenuItem("@Help");
        help.setAccelerator(KeyStroke.getKeyStroke('H',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        help.addActionListener(new act_help());
        menue_help.add(help);
        menu_file.add(open_machine);
        menu_file.add(save_machine);
        menu_file.add(fast_run);
        menu_file.add(multi_input_run);
        menu_file.add(slow_run);
        menu_file.add(save_as_img);
        touring_menue_bar.add(menu_file);
        touring_menue_bar.add(menue_help);
        touring_menue_bar.setBounds(0,0,d.width,20);

        touring_panel.add(touring_menue_bar);
    }
    private void add_jtoolbars()
    {
        touring_tools=new JToolBar("tools");
        insert_node=new JButton("node");
        insert_node.setToolTipText("click to insert node");
        delete=new JButton("delete");
        delete.setToolTipText("click to delete node and edge");
        graph_edge=new JButton("edge");
        graph_edge.setToolTipText("click to insert edge");
        none=new JButton("none");

        touring_tools.setLayout(new GridLayout(0,4));
        touring_tools.setBounds(0,20,d.width,50);
        touring_tools.setFloatable(false);


        touring_tools.add(insert_node);
        touring_tools.add(graph_edge);
        touring_tools.add(delete);
        touring_tools.add(none);
        touring_panel.add(touring_tools);
    }
    private void add_act_for_btns()
    {
        none.addActionListener(new act_none_btn());
        insert_node.addActionListener(new act_node_btn());
        graph_edge.addActionListener(new act_edge_btn());
        delete.addActionListener(new act_delete_btn());
    }
    private void add_panel_listener()
    {
        touring_panel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if(state==States.inseert)
                {
                    if(!touring_state_container.isEmpty())
                    {
                        if(allowed_spaces(e.getX(),e.getY()))
                        {
                            if(touring_null_states.isEmpty())
                            {
                                Touring_states state_obj=new Touring_states(e.getX(),e.getY(),touring_state_container.size()+1);
                                JPopupMenu main_menu=new JPopupMenu("options");
                                JMenuItem final_state=new JCheckBoxMenuItem("final state");
                                JMenuItem start_state=new JCheckBoxMenuItem("start state");
                                main_menu.add(final_state);
                                main_menu.add(start_state);
                                final_state.addActionListener(new ActionListener() {
                                    @Override
                                    public void actionPerformed(ActionEvent e) {
                                        if(final_state.isSelected())
                                        {

                                            state_obj.setState(1);//1 -> final
                                            touring_panel.repaint();

                                        }
                                        else
                                        {
                                            state_obj.setState(-1);//-1 -> not final
                                            touring_panel.repaint();

                                        }
                                    }
                                });
                                start_state.addActionListener(new ActionListener() {
                                    @Override
                                    public void actionPerformed(ActionEvent e) {
                                        if(start_state.isSelected())
                                        {
                                            state_obj.setState(2);//2 ->start
                                            touring_panel.repaint();
                                            start_states_container.add(state_obj.ID);
                                        }
                                        else
                                        {
                                            state_obj.setState(-2);//-2 ->not start
                                            touring_panel.repaint();
                                            start_states_container.remove(start_states_container.indexOf(state_obj.ID));
                                        }
                                    }
                                });
                                state_obj.set_methods();
                                state_obj.addMouseListener(new MouseAdapter() {
                                    @Override
                                    public void mouseClicked(MouseEvent e) {
                                        super.mouseClicked(e);
                                        if(state==States.dele)
                                        {
                                            delete_node_cleaner(state_obj.ID);
                                            touring_panel.remove(state_obj);
                                            touring_state_container.remove(state_obj.ID);
                                            touring_null_states.add(state_obj.ID);
                                            touring_panel.revalidate();
                                            touring_panel.repaint();
                                        }
                                        else if(state==States.non)
                                        {
                                            if(e.getButton()==MouseEvent.BUTTON3)
                                            {
                                                main_menu.show(state_obj,e.getX(),e.getY());
                                            }
                                        }
                                    }

                                    @Override
                                    public void mouseReleased(MouseEvent e) {
                                        super.mouseReleased(e);
                                        if(state==States.edge)
                                        {
                                            edge_insertion_allowed(state_obj,state_obj.x_axis+e.getX(),state_obj.y_axis+e.getY());
                                        }
                                    }
                                });
                                touring_state_container.put(state_obj.ID,state_obj);
                                touring_panel.add(state_obj);
                                touring_panel.repaint();
                            }
                            else
                            {
                                Collections.sort(touring_null_states);
                                //touring_null_states.
                                Touring_states state_obj=new Touring_states(e.getX(),e.getY(),touring_null_states.get(0));
                                touring_null_states.remove(0);
                                JPopupMenu main_menu=new JPopupMenu("options");
                                JMenuItem final_state=new JCheckBoxMenuItem("final state");
                                JMenuItem start_state=new JCheckBoxMenuItem("start state");
                                main_menu.add(final_state);
                                main_menu.add(start_state);
                                final_state.addActionListener(new ActionListener() {
                                    @Override
                                    public void actionPerformed(ActionEvent e) {
                                        if(final_state.isSelected())
                                        {

                                            state_obj.setState(1);//1 -> final
                                            touring_panel.repaint();

                                        }
                                        else
                                        {
                                            state_obj.setState(-1);//-1 -> not final
                                            touring_panel.repaint();

                                        }
                                    }
                                });
                                start_state.addActionListener(new ActionListener() {
                                    @Override
                                    public void actionPerformed(ActionEvent e) {
                                        if(start_state.isSelected())
                                        {
                                            state_obj.setState(2);//2 ->start
                                            touring_panel.repaint();
                                            start_states_container.add(state_obj.ID);
                                        }
                                        else
                                        {
                                            state_obj.setState(-2);//-2 ->not start
                                            touring_panel.repaint();
                                            start_states_container.remove(start_states_container.indexOf(state_obj.ID));
                                        }
                                    }
                                });
                                state_obj.set_methods();
                                state_obj.addMouseListener(new MouseAdapter() {
                                    @Override
                                    public void mouseClicked(MouseEvent e) {
                                        super.mouseClicked(e);
                                        if(state==States.dele)
                                        {
                                            delete_node_cleaner(state_obj.ID);
                                            touring_panel.remove(state_obj);
                                            touring_state_container.remove(state_obj.ID);
                                            touring_null_states.add(state_obj.ID);
                                            touring_panel.revalidate();
                                            touring_panel.repaint();
                                        }
                                        else if(state==States.non)
                                        {
                                            if(e.getButton()==MouseEvent.BUTTON3)
                                            {
                                                main_menu.show(state_obj,e.getX(),e.getY());
                                            }
                                        }
                                    }

                                    @Override
                                    public void mouseReleased(MouseEvent e) {
                                        super.mouseReleased(e);
                                        if(state==States.edge)
                                        {
                                            edge_insertion_allowed(state_obj,state_obj.x_axis+e.getX(),state_obj.y_axis+e.getY());
                                        }
                                    }
                                });
                                touring_state_container.put(state_obj.ID,state_obj);
                                touring_panel.add(state_obj);
                                touring_panel.repaint();
                            }
                        }
                    }
                    else
                    {
                        Touring_states state_obj=new Touring_states(e.getX(),e.getY(),1);
                        JPopupMenu main_menu=new JPopupMenu("options");
                        JMenuItem final_state=new JCheckBoxMenuItem("final state");
                        JMenuItem start_state=new JCheckBoxMenuItem("start state");
                        main_menu.add(final_state);
                        main_menu.add(start_state);
                        final_state.addActionListener(new ActionListener() {
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                if(final_state.isSelected())
                                {

                                    state_obj.setState(1);//1 -> final
                                    touring_panel.repaint();

                                }
                                else
                                {
                                    state_obj.setState(-1);//-1 -> not final
                                    touring_panel.repaint();

                                }
                            }
                        });
                        start_state.addActionListener(new ActionListener() {
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                if(start_state.isSelected())
                                {
                                    state_obj.setState(2);//2 ->start
                                    touring_panel.repaint();
                                    start_states_container.add(state_obj.ID);
                                }
                                else
                                {
                                    state_obj.setState(-2);//-2 ->not start
                                    touring_panel.repaint();
                                    start_states_container.remove(start_states_container.indexOf(state_obj.ID));
                                }
                            }
                        });
                        state_obj.set_methods();
                        state_obj.addMouseListener(new MouseAdapter() {
                            @Override
                            public void mouseClicked(MouseEvent e) {
                                super.mouseClicked(e);
                                if(state==States.dele)
                                {
                                    delete_node_cleaner(state_obj.ID);
                                    touring_panel.remove(state_obj);
                                    touring_state_container.remove(state_obj.ID);
                                    touring_null_states.add(state_obj.ID);
                                    touring_panel.revalidate();
                                    touring_panel.repaint();
                                }
                                else if(state==States.non)
                                {
                                    if(e.getButton()==MouseEvent.BUTTON3)
                                    {
                                        main_menu.show(state_obj,e.getX(),e.getY());
                                    }
                                }
                            }

                            @Override
                            public void mouseReleased(MouseEvent e) {
                                super.mouseReleased(e);
                                if(state==States.edge)
                                {
                                    edge_insertion_allowed(state_obj,state_obj.x_axis+e.getX(),state_obj.y_axis+e.getY());
                                }

                            }
                        });

                        touring_state_container.put(state_obj.ID,state_obj);
                        touring_panel.add(state_obj);
                        touring_panel.revalidate();
                        touring_panel.repaint();
                    }
                }
                if(state==States.dele)
                {
                    Iterator<Map.Entry<Pair<Integer,Integer>,econrel_touring>> itr=edge_container_type2.entrySet().iterator();
                    while (itr.hasNext())
                    {
                        Map.Entry<Pair<Integer,Integer>,econrel_touring> entry=itr.next();
                        double distance=Math.sqrt(Math.pow(entry.getValue().x_curved-e.getX(),2)+Math.pow(entry.getValue().y_curved-e.getY(),2));
                        if(distance<=10)
                        {
                            String str=JOptionPane.showInputDialog("input edge value you want to delete");
                            if(str==null||str.isEmpty()){break;}
                            String temp=entry.getValue().path_name;
                            if(temp.contains(str))
                            {
                                String res="";
                                for(String it:temp.split("-"))
                                {
                                    if(!it.equals(str))
                                    {
                                        res+="-"+it;
                                    }
                                }
                                if(!res.isEmpty())
                                {
                                    entry.getValue().edit_path_name(res.substring(1));
                                    delete_edge(entry.getKey().getKey(),entry.getKey().getValue(),1);
                                }
                                else
                                {
                                    itr.remove();
                                    delete_edge(entry.getKey().getKey(),entry.getKey().getValue(),2);
                                }
                                touring_state_container.get(entry.getKey().getKey()).delete_edge(entry.getKey().getValue(),str);
                                break;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        });
    }
    private void delete_edge(int index_obj1,int index_obj2,int s)
    {
        if(s==2)
        {
            if(edge_container_type2.get(new Pair<>(index_obj2,index_obj1))!=null)
            {
                edge_container_type2.get(new Pair<>(index_obj2,index_obj1)).set_state(1);
                edge_container_type2.get(new Pair<>(index_obj2,index_obj1)).calculation(touring_state_container.get(index_obj2).x_axis,touring_state_container.get(index_obj2).y_axis,touring_state_container.get(index_obj1).x_axis,touring_state_container.get(index_obj1).y_axis);
            }
        }
        touring_panel.revalidate();
        touring_panel.repaint();
    }
    private void edge_insertion_allowed(Touring_states obj,int x,int y)
    {
        double distance;
        for(Touring_states itr:touring_state_container.values())
        {
            distance=Math.pow(x-itr.x_axis,2)+Math.pow(y-itr.y_axis,2);
            distance=Math.sqrt(distance);
            if(distance<=30)
            {
                String str=JOptionPane.showInputDialog("hi");
                if(str==null||str.length()>3||str.length()<3){
                    break;}
                obj.set_edge(itr.ID,str);

                if(edge_container_type2.get(new Pair<>(obj.ID,itr.ID))!=null)
                {
                    String str2=edge_container_type2.get(new Pair<>(obj.ID,itr.ID)).path_name;
                    //str=itr.ID+str;
                    if(!str2.contains(str))
                    {
                        edge_container_type2.get(new Pair<>(obj.ID,itr.ID)).set_path_name(str);

                    }

                }
                else
                {
                    econrel_touring econrelTouring;
                    //str=itr.ID+str;
                    if(edge_container_type2.get(new Pair<>(itr.ID,obj.ID))!=null)
                    {
                        econrelTouring=new econrel_touring(str,2);
                        edge_container_type2.put(new Pair<>(obj.ID,itr.ID),econrelTouring);
                        econrelTouring.calculation(obj.x_axis,obj.y_axis,itr.x_axis,itr.y_axis);
                        edge_container_type2.get(new Pair<>(itr.ID,obj.ID)).set_state(2);
                        edge_container_type2.get(new Pair<>(itr.ID,obj.ID)).calculation(itr.x_axis,itr.y_axis,obj.x_axis,obj.y_axis);
                    }
                    else
                    {
                        econrelTouring=new econrel_touring(str,1);
                        edge_container_type2.put(new Pair<>(obj.ID,itr.ID),econrelTouring);
                        econrelTouring.calculation(obj.x_axis,obj.y_axis,itr.x_axis,itr.y_axis);
                    }

                }
                touring_panel.revalidate();//do1
                touring_panel.repaint();
                break;
            }
        }
    }
    private void delete_node_cleaner(int index)
    {
        if(start_states_container.contains(index))
        {
            start_states_container.remove(start_states_container.indexOf(index));
        }
        Iterator<Map.Entry<Pair<Integer,Integer>,econrel_touring>> itr=edge_container_type2.entrySet().iterator();
        while (itr.hasNext())
        {
            Map.Entry<Pair<Integer,Integer>,econrel_touring> entry=itr.next();
            if(entry.getKey().getKey()==index)
            {
                itr.remove();
            }
            else if(entry.getKey().getValue()==index)
            {
                itr.remove();
                for (String ch:entry.getValue().path_name.split("-"))//prob
                {
                    touring_state_container.get(entry.getKey().getKey()).deleted_node(ch.charAt(0),index);
                }
            }

        }

    }
    private boolean allowed_spaces(int x,int y) {
        for(Touring_states itr:touring_state_container.values())
        {
            double distance;
            distance=Math.pow(x-itr.x_axis,2)+Math.pow(y-itr.y_axis,2);
            distance=Math.sqrt(distance);
            if(distance<60)
            {
                return false;
            }
        }
        return true;
    }

    public void draw_edge_calculation(Graphics2D g2d)
    {
        for(Map.Entry<Pair<Integer,Integer>,econrel_touring> m:edge_container_type2.entrySet())
        {

            if(m.getValue().get_state()==2)
            {

                QuadCurve2D q=new QuadCurve2D.Double();
                q.setCurve(m.getValue().x1,m.getValue().y1,m.getValue().x_curved,m.getValue().y_curved,m.getValue().x2,m.getValue().y2);
                g2d.setColor(new Color(200,0,0));
                g2d.draw(q);

                Font font=new Font("Arial",Font.PLAIN,14);
                FontRenderContext fontRenderContext=g2d.getFontRenderContext();
                GlyphVector glyphVector=font.createGlyphVector(fontRenderContext,m.getValue().path_name);
                AffineTransform affineTransform=AffineTransform.getTranslateInstance(m.getValue().x_curved,m.getValue().y_curved);
                //affineTransform.rotate(Math.PI-deegre);
                Shape shape=glyphVector.getOutline();
                Shape transformed_shape=affineTransform.createTransformedShape(shape);
                g2d.setColor(Color.BLACK);
                g2d.fill(transformed_shape);
                g2d.drawLine(m.getValue().x1,m.getValue().y1,(int)Math.round(m.getValue().x1-10*Math.cos(Math.toRadians(20)+m.getValue().theta)),(int)Math.round(m.getValue().y1-10*Math.sin(Math.toRadians(20)+m.getValue().theta)));
                g2d.drawLine(m.getValue().x1,m.getValue().y1,(int)Math.round(m.getValue().x1-10*Math.cos(-Math.toRadians(20)+m.getValue().theta)),(int)Math.round(m.getValue().y1-10*Math.sin(-Math.toRadians(20)+m.getValue().theta)));
            }
            else if(m.getValue().get_state()==1)
            {
                g2d.setColor(new Color(200,0,0));
                g2d.drawLine(m.getValue().x1,m.getValue().y1,m.getValue().x2,m.getValue().y2);

                Font font=new Font("Arial",Font.PLAIN,14);
                FontRenderContext fontRenderContext=g2d.getFontRenderContext();
                GlyphVector glyphVector=font.createGlyphVector(fontRenderContext,m.getValue().path_name);
                AffineTransform affineTransform=AffineTransform.getTranslateInstance(m.getValue().x_curved,m.getValue().y_curved);
                //affineTransform.rotate(-Math.abs(deegre));
                Shape shape=glyphVector.getOutline();
                Shape transformed_shape=affineTransform.createTransformedShape(shape);
                g2d.setColor(Color.BLACK);
                g2d.fill(transformed_shape);
                g2d.drawLine(m.getValue().x1,m.getValue().y1,(int)Math.round(m.getValue().x1-10*Math.cos(Math.toRadians(20)+m.getValue().theta)),(int)Math.round(m.getValue().y1-10*Math.sin(Math.toRadians(20)+m.getValue().theta)));
                g2d.drawLine(m.getValue().x1,m.getValue().y1,(int)Math.round(m.getValue().x1-10*Math.cos(-Math.toRadians(20)+m.getValue().theta)),(int)Math.round(m.getValue().y1-10*Math.sin(-Math.toRadians(20)+m.getValue().theta)));
            }
        }
    }
    private class act_help implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            JFrame jf=new JFrame();
            try {
                jf.setVisible(true);
                jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
                JTextPane jta=new JTextPane();
                JScrollPane jsp=new JScrollPane(jta);
                jta.setPreferredSize(new Dimension(500, 500));
                jf.add(jsp,BorderLayout.CENTER);

                //jta.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);//rtl
                jta.setEditable(false);//editable
                Scanner sc=new Scanner(new File("help.txt"));
                StringBuilder sb=new StringBuilder();
                while(sc.hasNext())
                {
                    sb.append(sc.nextLine());
                    sb.append("\n");
                }
                jta.setBackground(new Color(0,0,0));
                Font f=new Font("Arial", Font.BOLD, 14);
                jta.setForeground(new Color(255,255,255));
                jta.setFont(f);
                jta.setText(sb.toString());

                jf.pack();
            } catch (Exception e) {
                // TODO: handle exception
                System.err.println(e.getMessage());
                jf.dispose();
            }
        }
    }
    private class act_save_as_image implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            JFileChooser jfc=new JFileChooser();
            jfc.setDialogTitle("save touring as img");
            if(jfc.showSaveDialog(null)==JFileChooser.APPROVE_OPTION);
            {
                try {
                    File file=jfc.getSelectedFile();
                    BufferedImage bufimg=new BufferedImage(touring_panel.getWidth(), touring_panel.getHeight(), BufferedImage.TYPE_INT_ARGB);
                    if(file!=null)
                    {
                        file=new File(file.toString());
                        Graphics2D g2d=bufimg.createGraphics();
                        touring_panel.paint(g2d);
                        g2d.drawImage(bufimg, touring_panel.getWidth(), touring_panel.getHeight(), touring_panel);
                        g2d.dispose();
                        ImageIO.write(bufimg, "png", file);
                    }
                }
                catch (Exception e)
                {
                    System.err.println(e.getMessage());
                }

            }
        }
    }
    private class act_save_machine_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            if(!touring_state_container.isEmpty())
            {
                try {
                    ObjectMapper mapper=new ObjectMapper();
                    save_obj_touring ob=new save_obj_touring();
                    ob.tsc=touring_state_container;
                    ob.tns=touring_null_states;
                    ob.ect2=edge_container_type2;
                    JFileChooser jfc=new JFileChooser();
                    jfc.setDialogTitle("save touring machine");
                    if(jfc.showSaveDialog(null)==JFileChooser.APPROVE_OPTION);
                    {
                        File file=jfc.getSelectedFile();
                        if(file!=null)
                        {
                            file=new File(file.toString()+".json");
                            mapper.writerWithDefaultPrettyPrinter().writeValue(file,ob);
                        }
                    }

                }
                catch (Exception ew)
                {
                    ew.printStackTrace();
                }
            }
        }
    }
    private class act_open_machine_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            if(touring_state_container.isEmpty()&&edge_container_type2.isEmpty()&&touring_null_states.isEmpty())
            {
                save_obj_touring sot;
                ObjectMapper mapper=new ObjectMapper();
                try {
                    JFileChooser jfc=new JFileChooser();
                    jfc.setDialogTitle("open touring machine");
                    if(jfc.showOpenDialog(null)==JFileChooser.APPROVE_OPTION)
                    {
                        File file=jfc.getSelectedFile();
                        if(file!=null)
                        {
                            sot=mapper.readValue(file,save_obj_touring.class);
                            if(!sot.tsc.isEmpty())
                            {
                                touring_state_container=sot.tsc;
                            }
                            if(!sot.tns.isEmpty())
                            {
                                touring_null_states=sot.tns;
                            }
                            if(!sot.ect2.isEmpty())
                            {
                                edge_container_type2=sot.ect2;
                            }

                            if(!touring_state_container.isEmpty())
                            {
                                for(Touring_states itr:touring_state_container.values())
                                {
                                    itr.set_methods();
                                    JPopupMenu main_menu=new JPopupMenu("options");
                                    JMenuItem final_state=new JCheckBoxMenuItem("final state");
                                    JMenuItem start_state=new JCheckBoxMenuItem("start state");
                                    main_menu.add(final_state);
                                    main_menu.add(start_state);
                                    if(itr.getstate()==1)
                                    {
                                        final_state.setSelected(true);
                                    }
                                    else if(itr.getstate()==2)
                                    {
                                        start_state.setSelected(true);
                                        start_states_container.add(itr.ID);
                                    }
                                    else if(itr.getstate()==3)
                                    {
                                        start_state.setSelected(true);
                                        final_state.setSelected(true);
                                        start_states_container.add(itr.ID);
                                    }

                                    final_state.addActionListener(new ActionListener() {
                                        @Override
                                        public void actionPerformed(ActionEvent e) {
                                            if(final_state.isSelected())
                                            {

                                                itr.setState(1);//1 -> final
                                                touring_panel.repaint();

                                            }
                                            else
                                            {
                                                itr.setState(-1);//-1 -> not final
                                                touring_panel.repaint();
                                            }
                                        }
                                    });
                                    start_state.addActionListener(new ActionListener() {
                                        @Override
                                        public void actionPerformed(ActionEvent e) {
                                            if(start_state.isSelected())
                                            {
                                                itr.setState(2);//2 ->start
                                                touring_panel.repaint();
                                                start_states_container.add(itr.ID);
                                            }
                                            else
                                            {
                                                itr.setState(-2);//-2 ->not start
                                                touring_panel.repaint();
                                                start_states_container.remove(start_states_container.indexOf(itr.ID));
                                            }
                                        }
                                    });
                                    itr.addMouseListener(new MouseAdapter() {
                                        @Override
                                        public void mouseClicked(MouseEvent e) {
                                            super.mouseClicked(e);
                                            if(state==States.dele)
                                            {
                                                delete_node_cleaner(itr.ID);//prob
                                                touring_panel.remove(itr);
                                                touring_state_container.remove(itr.ID);
                                                touring_null_states.add(itr.ID);
                                                touring_panel.repaint();
                                            }
                                            else if(state==States.non)
                                            {
                                                if(e.getButton()==MouseEvent.BUTTON3)
                                                {
                                                    main_menu.show(itr,e.getX(),e.getY());
                                                }
                                            }
                                        }

                                        @Override
                                        public void mouseReleased(MouseEvent e) {
                                            super.mouseReleased(e);
                                            if(state==States.edge)
                                            {
                                                edge_insertion_allowed(itr,itr.x_axis+e.getX(),itr.y_axis+e.getY());
                                            }
                                        }
                                    });
                                    touring_panel.add(itr);
                                }
                            }
                            touring_panel.revalidate();
                            touring_panel.repaint();
                        }
                    }
                }
                catch (Exception ew)
                {
                    ew.printStackTrace();
                }
            }
        }
    }
    private class act_run_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            String input=JOptionPane.showInputDialog("enter your input");
            if(input==null||input.isEmpty())
            {
                return;
            }
            ctrd obj=new ctrd(input);
            obj.run();
        }
    }
    private class act_slow_run implements ActionListener
    {
        private int counter=-1;
        private String in="";
        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            int indx=0;
            String sm=JOptionPane.showInputDialog(null,"input first state node number");
            if(sm!=null)
            {
                try {
                    indx=Integer.parseInt(sm);
                }
                catch (Exception eww)
                {
                    return;
                }

                if(!start_states_container.contains(indx))
                {
                    return;
                }
            }
            else
            {
                return;
            }
            in=JOptionPane.showInputDialog("enter your input");
            if(in==null||in.isEmpty())
            {
                return;
            }
            Queue<String> pos=new LinkedList<>();
            pos.add(start_states_container.get(0)+"-"+"0"+"-"+in);

            JFrame jf=new JFrame();
            jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
            jf.setVisible(true);

            JLabel lres=new JLabel();
            JComponent jc=new JComponent() {
                @Override
                public void paint(Graphics g) {
                    super.paint(g);
                    Graphics2D g2d=(Graphics2D)g;
                    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
                    if(!pos.isEmpty())
                    {
                        int coun=-1;
                        for(String str:pos)
                        {
                            coun++;
                            String sep[]=str.split("-");
                            if(touring_state_container.get(Integer.parseInt(sep[0])).getstate()==1||touring_state_container.get(Integer.parseInt(sep[0])).getstate()==3)
                            {
                                g2d.setColor(Color.RED);
                                g2d.fillOval(coun*200,0,60,60);
                                g2d.setColor(Color.BLACK);
                                g2d.drawString("V"+sep[0],coun*200+30,25);
                                g2d.drawLine(coun*200,0,coun*200,250);

                            }
                            else
                            {
                                g2d.setColor(new Color(255,255,0));
                                g2d.fillOval(coun*200,0,60,60);
                                g2d.setColor(Color.BLACK);
                                g2d.drawString("V"+sep[0],coun*200+30,25);
                                g2d.drawLine(coun*200,0,coun*200,250);
                            }

                            int andis=Integer.parseInt(sep[1]);
                            Font font=new Font("Arial",Font.PLAIN,14);
                            FontRenderContext fontRenderContext=g2d.getFontRenderContext();
                            int cnt=0;
                            for(int i=andis-4;i<andis+5;i++)
                            {
                                cnt++;
                                if(i<0)
                                {
                                    GlyphVector glyphVector=font.createGlyphVector(fontRenderContext,"#");
                                    AffineTransform affineTransform=AffineTransform.getTranslateInstance(50+coun*200+(cnt)*13,130);
                                    Shape shape=glyphVector.getOutline();
                                    Shape transformed_shape=affineTransform.createTransformedShape(shape);
                                    g2d.setColor(Color.BLACK);
                                    g2d.fill(transformed_shape);
                                }
                                else if(i>=sep[2].length())
                                {
                                    GlyphVector glyphVector=font.createGlyphVector(fontRenderContext,"#");
                                    AffineTransform affineTransform=AffineTransform.getTranslateInstance(50+coun*200+(cnt)*13,130);
                                    Shape shape=glyphVector.getOutline();
                                    Shape transformed_shape=affineTransform.createTransformedShape(shape);
                                    g2d.setColor(Color.BLACK);
                                    g2d.fill(transformed_shape);
                                }
                                else if(i==andis)
                                {
                                    GlyphVector glyphVector=font.createGlyphVector(fontRenderContext,sep[2].substring(andis,andis+1));
                                    AffineTransform affineTransform=AffineTransform.getTranslateInstance(50+coun*200+(cnt)*13,130);
                                    Shape shape=glyphVector.getOutline();
                                    Shape transformed_shape=affineTransform.createTransformedShape(shape);
                                    g2d.setColor(Color.RED);
                                    g2d.fill(transformed_shape);
                                }
                                else
                                {
                                    GlyphVector glyphVector=font.createGlyphVector(fontRenderContext,sep[2].substring(i,i+1));
                                    AffineTransform affineTransform=AffineTransform.getTranslateInstance(50+coun*200+(cnt)*13,130);
                                    Shape shape=glyphVector.getOutline();
                                    Shape transformed_shape=affineTransform.createTransformedShape(shape);
                                    g2d.setColor(Color.BLACK);
                                    g2d.fill(transformed_shape);
                                }
                            }
                        }
                    }
                }
            };

            jc.setPreferredSize(new Dimension(500,250));
            JScrollPane jsp=new JScrollPane(jc);
            jsp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
            jsp.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
            JButton jb=new JButton("Next");

            jb.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent actionEvent) {
                    if(lres.getText().isEmpty())
                    {
                        int sz=pos.size();
                        for(int i=0;i<sz;i++)
                        {
                            String s[]=pos.poll().split("-");
                            String res=touring_state_container.get(Integer.parseInt(s[0])).get_next_node(s[2].charAt(Integer.parseInt(s[1])));
                            if(touring_state_container.get(Integer.parseInt(s[0])).getstate()==1||touring_state_container.get(Integer.parseInt(s[0])).getstate()==3)
                            {
                                lres.setForeground(new Color(0,255,0));
                                lres.setText("Accept");

                                jc.setPreferredSize(new Dimension(100+pos.size()*200,250));
                                jc.revalidate();
                                jc.repaint();
                                jsp.revalidate();
                                jsp.repaint();

                                return;
                            }
                            if(!res.isEmpty())
                            {
                                for(String tmp:res.split("-"))
                                {
                                    String tmpsubs=tmp.substring(0,tmp.length()-2);
                                    if(touring_state_container.get(Integer.parseInt(tmpsubs)).getstate()==1||touring_state_container.get(Integer.parseInt(tmpsubs)).getstate()==3)
                                    {
                                        lres.setForeground(new Color(0,255,0));
                                        lres.setText("Accept");


                                        //return;
                                    }
                                    StringBuilder inp=new StringBuilder(s[2]);
                                    int head=Integer.parseInt(s[1]);
                                    inp.setCharAt(head,tmp.charAt(tmp.length()-2));
                                    if(tmp.charAt(tmp.length()-1)=='l'||tmp.charAt(tmp.length()-1)=='L')
                                    {
                                        head-=1;
                                        if(head==-1)
                                        {
                                            head=0;
                                            inp.insert(0,'#');
                                        }
                                    }
                                    else if(tmp.charAt(tmp.length()-1)=='r'||tmp.charAt(tmp.length()-1)=='R')
                                    {
                                        head+=1;
                                        if(head==inp.length())
                                        {
                                            inp.append('#');
                                        }
                                    }
                                    pos.add(tmpsubs+"-"+head+"-"+inp.toString());
                                }
                                /*jc.setPreferredSize(new Dimension(250,100+pos.size()*100));
                                jc.revalidate();
                                jc.repaint();
                                jsp.revalidate();
                                jsp.repaint();*/
                            }
                        }
                        if(pos.isEmpty())
                        {
                            lres.setForeground(new Color(255,0,0));
                            lres.setText("Reject");

                            jc.setPreferredSize(new Dimension(100+pos.size()*200,250));
                            jc.revalidate();
                            jc.repaint();
                            jsp.revalidate();
                            jsp.repaint();

                            return;
                        }
                        jc.setPreferredSize(new Dimension(100+pos.size()*200,250));
                        jc.revalidate();
                        jc.repaint();
                        jsp.revalidate();
                        jsp.repaint();
                    }
                    else
                    {
                        jf.dispose();
                    }
                }
            });

            jf.add(lres,BorderLayout.NORTH);
            jf.add(jsp,BorderLayout.CENTER);
            jf.add(jb,BorderLayout.SOUTH);
            jf.pack();
        }
    }
    private class ctrd implements Runnable
    {

        String input;
        public ctrd(String in)
        {
            input=in;
        }
        @Override
        public void run() {
            Queue<String> pos=new LinkedList<>();
            if (!start_states_container.isEmpty())
            {
                int indx=0;
                String sm=JOptionPane.showInputDialog(null,"input first state node number");
                if(sm!=null)
                {
                    try {
                        indx=Integer.parseInt(sm);
                    }
                    catch (Exception eww)
                    {
                        return;
                    }

                    if(!start_states_container.contains(indx))
                    {
                        return;
                    }
                }
                else
                {
                    return;
                }
                pos.add(start_states_container.get(start_states_container.indexOf(indx))+"-"+"0"+"-"+input);
                while (true)
                {
                    int sz=pos.size();
                    for(int i=0;i<sz;i++)
                    {
                        String s[]=pos.poll().split("-");
                        String res=touring_state_container.get(Integer.parseInt(s[0])).get_next_node(s[2].charAt(Integer.parseInt(s[1])));
                        if(touring_state_container.get(Integer.parseInt(s[0])).getstate()==1||touring_state_container.get(Integer.parseInt(s[0])).getstate()==3)
                        {
                            JOptionPane.showMessageDialog(null,"Accept\n\n"+"tape : "+s[2]);
                            return;
                        }
                        if(!res.isEmpty())
                        {
                            for(String tmp:res.split("-"))
                            {
                                String tmpsubs=tmp.substring(0,tmp.length()-2);
                                if(touring_state_container.get(Integer.parseInt(tmpsubs)).getstate()==1||touring_state_container.get(Integer.parseInt(tmpsubs)).getstate()==3)
                                {
                                    JOptionPane.showMessageDialog(null,"Accept\n\n"+"tape : "+s[2]);
                                    return;
                                }
                                StringBuilder inp=new StringBuilder(s[2]);
                                int head=Integer.parseInt(s[1]);
                                inp.setCharAt(head,tmp.charAt(tmp.length()-2));
                                if(tmp.charAt(tmp.length()-1)=='l'||tmp.charAt(tmp.length()-1)=='L')
                                {
                                    head-=1;
                                    if(head==-1)
                                    {
                                        head=0;
                                        inp.insert(0,'#');
                                    }
                                }
                                else if(tmp.charAt(tmp.length()-1)=='r'||tmp.charAt(tmp.length()-1)=='R')
                                {
                                    head+=1;
                                    if(head==inp.length())
                                    {
                                        inp.append('#');
                                    }
                                }
                                pos.add(tmpsubs+"-"+head+"-"+inp.toString());
                            }
                        }
                    }
                    if(pos.isEmpty())
                    {
                        JOptionPane.showMessageDialog(null,"Reject");
                        return;
                    }
                }
            }
        }
    }
    private class act_multiInputRun implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            try {
                List<JTextField>jtext_list=new ArrayList<>();
                List<JLabel> jlabel_list=new ArrayList<>();

                JFrame jf=new JFrame();
                jf.setVisible(true);
                jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
                jf.setResizable(false);
                JButton jb=new JButton("add (+)");
                JButton jb2=new JButton("remove (-)");
                JButton jb3=new JButton("Run");

                jf.add(jb3,BorderLayout.SOUTH);
                JPanel jp=new JPanel();
                jp.setPreferredSize(new Dimension(250, 200));
                jp.setLayout(null);
                JPanel jp2=new JPanel();
                jp2.setPreferredSize(new Dimension(250, 20));
                jp2.setLayout(new GridLayout(1,2));
                jp2.add(jb);
                jp2.add(jb2);
                jf.add(jp2,BorderLayout.NORTH);

                JScrollPane jsp=new JScrollPane(jp);
                jsp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
                jsp.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
                jf.add(jsp,BorderLayout.CENTER);

                jb.addActionListener(new ActionListener() {

                    @Override
                    public void actionPerformed(ActionEvent arg0) {
                        JTextField txt_obj=new JTextField();
                        JLabel lbl_obj=new JLabel();
                        txt_obj.setBounds(0, 10+jtext_list.size()*30, 160, 20);
                        lbl_obj.setBounds(160, 10+jlabel_list.size()*30, 90, 20);
                        lbl_obj.setVisible(true);
                        jlabel_list.add(lbl_obj);
                        jtext_list.add(txt_obj);
                        if(jlabel_list.size()>6)
                        {
                            jp.setPreferredSize(new Dimension(250, 200+jlabel_list.size()*30));
                        }
                        jp.add(txt_obj);
                        jp.add(lbl_obj);
                        jp.revalidate();
                        jp.repaint();
                        jsp.revalidate();
                        jsp.repaint();
                    }
                });
                jb2.addActionListener(new ActionListener() {

                    @Override
                    public void actionPerformed(ActionEvent arg0) {
                        // TODO Auto-generated method stub
                        if(!jtext_list.isEmpty())
                        {
                            jp.remove(jtext_list.get(jtext_list.size()-1));
                            jtext_list.remove(jtext_list.size()-1);
                            jp.remove(jlabel_list.get(jlabel_list.size()-1));
                            jlabel_list.remove(jlabel_list.size()-1);
                            if(jtext_list.size()>=6)
                            {
                                jp.setPreferredSize(new Dimension(250, 80+jlabel_list.size()*30));
                            }
                            jp.revalidate();
                            jp.repaint();
                            jsp.revalidate();
                            jsp.repaint();
                        }
                    }
                });
                jb3.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent actionEvent) {
                        if(!jlabel_list.isEmpty()&&!start_states_container.isEmpty())
                        {
                            for(JTextField txtobj:jtext_list)
                            {
                                if(!txtobj.getText().isEmpty())
                                {
                                    String input=txtobj.getText();
                                    trd_multirn thrd=new trd_multirn(jlabel_list.get(jtext_list.indexOf(txtobj)),input);
                                    thrd.run();
                                }
                            }
                        }
                    }
                });
                jf.pack();
            }
            catch (Exception e)
            {
                System.out.println(e.getMessage());
            }
        }
    }
    private class trd_multirn implements Runnable
    {

        private JLabel jlb;
        private String in;
        public trd_multirn(JLabel lblobj,String input)
        {
            this.in=input;
            this.jlb=lblobj;

        }
        @Override
        public void run() {

            Queue<String> pos=new LinkedList<>();
            pos.add(start_states_container.get(0)+"-"+"0"+"-"+in);
            while (true)
            {
                int sz=pos.size();
                for(int i=0;i<sz;i++)
                {
                    String s[]=pos.poll().split("-");
                    String res=touring_state_container.get(Integer.parseInt(s[0])).get_next_node(s[2].charAt(Integer.parseInt(s[1])));
                    if(touring_state_container.get(Integer.parseInt(s[0])).getstate()==1||touring_state_container.get(Integer.parseInt(s[0])).getstate()==3)
                    {
                        jlb.setForeground(new Color(0,255,0));
                        jlb.setText("Accept");
                        return;
                    }
                    if(!res.isEmpty())
                    {
                        for(String tmp:res.split("-"))
                        {
                            String tmpsubs=tmp.substring(0,tmp.length()-2);
                            if(touring_state_container.get(Integer.parseInt(tmpsubs)).getstate()==1||touring_state_container.get(Integer.parseInt(tmpsubs)).getstate()==3)
                            {
                                jlb.setForeground(new Color(0,255,0));
                                jlb.setText("Accept");
                                return;
                            }
                            StringBuilder inp=new StringBuilder(s[2]);
                            int head=Integer.parseInt(s[1]);
                            inp.setCharAt(head,tmp.charAt(tmp.length()-2));
                            if(tmp.charAt(tmp.length()-1)=='l'||tmp.charAt(tmp.length()-1)=='L')
                            {
                                head-=1;
                                if(head==-1)
                                {
                                    head=0;
                                    inp.insert(0,'#');
                                }
                            }
                            else if(tmp.charAt(tmp.length()-1)=='r'||tmp.charAt(tmp.length()-1)=='R')
                            {
                                head+=1;
                                if(head==inp.length())
                                {
                                    inp.append('#');
                                }
                            }
                            pos.add(tmpsubs+"-"+head+"-"+inp.toString());
                        }
                    }
                }
                if(pos.isEmpty())
                {
                    jlb.setForeground(new Color(255,0,0));
                    jlb.setText("Reject");
                    return;
                }
            }
        }
    }
    private class act_none_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            state=States.non;
        }
    }
    private class act_node_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            state=States.inseert;
        }
    }
    private class act_edge_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            state=States.edge;
        }
    }
    private class act_delete_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            state=States.dele;
        }
    }
}
