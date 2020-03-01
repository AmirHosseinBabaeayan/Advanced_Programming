package final_project;

//and this is magical power of java *_*

import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.geometry.Point2D;
import javafx.stage.FileChooser;
import javafx.util.Pair;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;
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
import java.lang.Math;

import static java.lang.Math.pow;

public class DFA_Machine_class extends JFrame {

    private JPanel dfa_panel;
    private JMenuBar dfa_menue_bar;
    private JMenu menu_file,menue_help;
    private JMenuItem save_machine,open_machine,fast_run,multi_input_run,slow_run,save_as_img,help;
    private JToolBar dfa_tools;
    private JButton insert_node,delete,graph_edge,none;
    private Dimension d;
    private List<Integer> start_states_container;
    
    enum States{non,inseert,edge,dele;}
    States state=States.non;

    private List <DFA_states> state_container=new ArrayList<>();
    private Map<Pair<Integer,Integer>,edge_connection_relation> edge_storage_type2;

    public DFA_Machine_class()
    {
        start_states_container=new ArrayList<>();
        edge_storage_type2=new HashMap<>();
    }


    public void jframe_methods(JFrame jf_main)
    {
        this.setVisible(true);
        this.setTitle("DFA machine");
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
        dfa_panel=new JPanel()
        {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d=(Graphics2D)g;
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
                if(!state_container.isEmpty())
                {
                    for(DFA_states itr:state_container)
                    {
                        if(itr!=null)
                        {
                            BasicStroke basicStroke= (BasicStroke) g2d.getStroke();
                            if(itr.getstate()==1)
                            {
                                g2d.setColor(Color.RED);
                                g2d.fillOval(itr.x_axis-25,itr.y_axis-25,60,60);
                                g2d.setColor(Color.BLACK);
                                g2d.setStroke(new BasicStroke(5));
                                g2d.drawOval(itr.x_axis-25,itr.y_axis-25,60,60);
                                g2d.setStroke(basicStroke);
                            }
                            else if(itr.getstate()==2)
                            {
                                g2d.setColor(Color.GREEN);
                                g2d.fillOval(itr.x_axis-25,itr.y_axis-25,60,60);
                            }
                            else if(itr.getstate()==3)
                            {
                                g2d.setColor(new Color(100,0,50));
                                g2d.fillOval(itr.x_axis-25,itr.y_axis-25,60,60);
                                g2d.setColor(Color.BLACK);
                                g2d.setStroke(new BasicStroke(5));
                                g2d.drawOval(itr.x_axis-25,itr.y_axis-25,60,60);
                                g2d.setStroke(basicStroke);
                            }
                            else
                            {
                                g2d.setColor(Color.CYAN);
                                g2d.fillOval(itr.x_axis-25,itr.y_axis-25,60,60);
                            }
                        }
                    }
                    if(!edge_storage_type2.isEmpty())
                    {
                        draw_edge_calculation(g2d);
                    }
                }

            }
        };
        dfa_panel.setLayout(null);

        Toolkit toolkit=Toolkit.getDefaultToolkit();
        d=toolkit.getScreenSize();
        d.height-=70;
        dfa_panel.setPreferredSize(d);

        this.add(dfa_panel);
    }

    private void add_menue_bar()
    {
        dfa_menue_bar=new JMenuBar();
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
        slow_run.setAccelerator(KeyStroke.getKeyStroke('p',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        slow_run.addActionListener(new act_Frun());
        save_as_img=new JMenuItem("Save as img");
        save_as_img.setAccelerator(KeyStroke.getKeyStroke('i',Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        save_as_img.addActionListener(new act_save_dfa_as_img());
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
        dfa_menue_bar.add(menu_file);
        dfa_menue_bar.add(menue_help);
        dfa_menue_bar.setBounds(0,0,d.width,20);

        dfa_panel.add(dfa_menue_bar);
    }

    private void add_jtoolbars()
    {
        dfa_tools=new JToolBar("tools");
        insert_node=new JButton("node");
        insert_node.setToolTipText("click to insert node");
        delete=new JButton("delete");
        delete.setToolTipText("click to delete node and edge");
        graph_edge=new JButton("edge");
        graph_edge.setToolTipText("click to insert edge");
        none=new JButton("none");

        dfa_tools.setLayout(new GridLayout(0,4));
        dfa_tools.setBounds(0,20,d.width,50);
        dfa_tools.setFloatable(false);


        dfa_tools.add(insert_node);
        dfa_tools.add(graph_edge);
        dfa_tools.add(delete);
        dfa_tools.add(none);
        dfa_panel.add(dfa_tools);
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
        dfa_panel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if(state==States.inseert)
                {
                    /*g.drawLine(0,0,d.width+e.getX()-e.getXOnScreen(),d.height+e.getY()-e.getYOnScreen());*/

                    if(!state_container.isEmpty())
                    {
                        if(allowed_spaces(e.getX(),e.getY()))
                        {
                            boolean is_null=false;
                            int counter=0;
                            for(DFA_states itr:state_container)
                            {
                                counter++;
                                if(itr==null)
                                {
                                    is_null=true;
                                    itr=new DFA_states(e.getX(),e.getY(),counter,counter);
                                    itr.set_methods();

                                    JPopupMenu main_menu=new JPopupMenu("options");
                                    JMenuItem final_state=new JCheckBoxMenuItem("final state");
                                    JMenuItem start_state=new JCheckBoxMenuItem("start state");
                                    main_menu.add(final_state);
                                    main_menu.add(start_state);
                                    DFA_states obj=itr;
                                    final_state.addActionListener(new ActionListener() {
                                        @Override
                                        public void actionPerformed(ActionEvent e) {
                                            if(final_state.isSelected())
                                            {

                                                obj.setState(1);//1 -> final
                                                dfa_panel.repaint();

                                            }
                                            else
                                            {
                                                obj.setState(-1);//-1 -> not final
                                                dfa_panel.repaint();
                                            }
                                        }
                                    });
                                    start_state.addActionListener(new ActionListener() {
                                        @Override
                                        public void actionPerformed(ActionEvent e) {
                                            if(start_state.isSelected())
                                            {
                                                obj.setState(2);//2 ->start
                                                dfa_panel.repaint();
                                                start_states_container.add(obj.ID);
                                            }
                                            else
                                            {
                                                obj.setState(-2);//-2 ->not start
                                                dfa_panel.repaint();
                                                start_states_container.remove(start_states_container.indexOf(obj.ID));
                                            }
                                        }
                                    });
                                    itr.addMouseListener(new MouseAdapter() {
                                        @Override
                                        public void mouseClicked(MouseEvent e) {
                                            super.mouseClicked(e);
                                            if(state==States.dele)
                                            {
                                                delete_node_cleaner(obj.ID);
                                                dfa_panel.remove(obj);
                                                state_container.set(obj.ID-1,null);
                                                dfa_panel.repaint();
                                            }
                                            else if(state==States.non)
                                            {
                                                if(e.getButton()==MouseEvent.BUTTON3)
                                                {
                                                    main_menu.show(obj,e.getX(),e.getY());
                                                }
                                            }
                                        }

                                        @Override
                                        public void mouseReleased(MouseEvent e) {
                                            super.mouseReleased(e);
                                            if(state==States.edge)
                                            {
                                                edge_insertion_allowed(obj,obj.x_axis+e.getX(),obj.y_axis+e.getY());
                                            }
                                        }
                                    });
                                    state_container.set(counter-1,itr);
                                    dfa_panel.add(itr);
                                    dfa_panel.repaint();
                                    break;
                                }
                            }
                            if(!is_null)
                            {
                                DFA_states state_obj=new DFA_states(e.getX(),e.getY(),state_container.size()+1,state_container.size()+1);
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
                                            dfa_panel.repaint();

                                        }
                                        else
                                        {
                                            state_obj.setState(-1);//-1 -> not final
                                            dfa_panel.repaint();

                                        }
                                    }
                                });
                                start_state.addActionListener(new ActionListener() {
                                    @Override
                                    public void actionPerformed(ActionEvent e) {
                                        if(start_state.isSelected())
                                        {
                                            state_obj.setState(2);//2 ->start
                                            dfa_panel.repaint();
                                            start_states_container.add(state_obj.ID);
                                        }
                                        else
                                        {
                                            state_obj.setState(-2);//-2 ->not start
                                            dfa_panel.repaint();
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
                                            dfa_panel.remove(state_obj);
                                            state_container.set(state_obj.ID-1,null);
                                            dfa_panel.repaint();
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
                                state_container.add(state_obj);
                                dfa_panel.add(state_obj);
                                dfa_panel.repaint();
                            }
                        }
                    }
                    else
                    {
                        DFA_states state_obj=new DFA_states(e.getX(),e.getY(),1,1);
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
                                    dfa_panel.repaint();

                                }
                                else
                                {
                                    state_obj.setState(-1);//-1 -> not final
                                    dfa_panel.repaint();

                                }
                            }
                        });
                        start_state.addActionListener(new ActionListener() {
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                if(start_state.isSelected())
                                {
                                    state_obj.setState(2);//2 ->start
                                    dfa_panel.repaint();
                                    start_states_container.add(state_obj.ID);
                                }
                                else
                                {
                                    state_obj.setState(-2);//-2 ->not start
                                    dfa_panel.repaint();
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
                                    dfa_panel.remove(state_obj);
                                    state_container.set(state_obj.ID-1,null);
                                    dfa_panel.repaint();
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
                        state_container.add(state_obj);
                        dfa_panel.add(state_obj);
                        dfa_panel.repaint();
                    }
                }

                if(state==States.dele)
                {
                    Iterator<Map.Entry<Pair<Integer,Integer>,edge_connection_relation>> itr=edge_storage_type2.entrySet().iterator();
                    while (itr.hasNext())
                    {
                        Map.Entry<Pair<Integer,Integer>,edge_connection_relation> entry=itr.next();
                        double distance=Math.sqrt(Math.pow(entry.getValue().x_curved-e.getX(),2)+Math.pow(entry.getValue().y_curved-e.getY(),2));
                        if(distance<=10)
                        {
                            String str=JOptionPane.showInputDialog("input edge value you want to delete");
                            if(str==null||str.isEmpty()){break;}
                            String temp=entry.getValue().path_name;
                            int pos=temp.indexOf(str.charAt(0));
                            if(pos!=-1)
                            {

                                temp=temp.substring(0,pos)+temp.substring(pos+1);
                                if(!temp.isEmpty())
                                {
                                    entry.getValue().edit_path_name(temp);
                                    delete_edge(entry.getKey().getKey(),entry.getKey().getValue(),1);
                                }
                                else
                                {
                                    itr.remove();
                                    delete_edge(entry.getKey().getKey(),entry.getKey().getValue(),2);
                                }
                                state_container.get(entry.getKey().getKey()-1).delete_edge(str.charAt(0),entry.getKey().getValue());
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
    private boolean allowed_spaces(int x,int y)
    {
        for(DFA_states itr:state_container)
        {
            if(itr!=null)
            {
                double distance;
                distance=Math.pow(x-itr.x_axis,2)+Math.pow(y-itr.y_axis,2);
                distance=Math.sqrt(distance);
                if(distance<60)
                {
                    return false;
                }
            }

        }
        return true;
    }

    private void edge_insertion_allowed(DFA_states obj,int x,int y)
    {
        double distance;
        for(DFA_states itr:state_container)
        {
            if(itr!=null)
            {
                distance=Math.pow(x-itr.x_axis,2)+Math.pow(y-itr.y_axis,2);
                distance=Math.sqrt(distance);
                if(distance<=30)
                {
                    String str=JOptionPane.showInputDialog("hi");
                    if(str==null||str.isEmpty()||str.length()>1){
                        break;}
                    obj.set_edge(itr.ID,str.charAt(0));

                    if(edge_storage_type2.get(new Pair<>(obj.ID,itr.ID))!=null)
                    {
                        String str2=edge_storage_type2.get(new Pair<>(obj.ID,itr.ID)).path_name;
                        if(!str2.contains(str))
                        {
                            edge_storage_type2.get(new Pair<>(obj.ID,itr.ID)).set_path_name(str);

                        }

                    }
                    else
                    {
                        edge_connection_relation edgeConnectionRelation;

                        if(edge_storage_type2.get(new Pair<>(itr.ID,obj.ID))!=null)
                        {
                            edgeConnectionRelation=new edge_connection_relation(str,2);
                            edge_storage_type2.put(new Pair<>(obj.ID,itr.ID),edgeConnectionRelation);
                            edgeConnectionRelation.calculation(obj.x_axis,obj.y_axis,itr.x_axis,itr.y_axis);
                            edge_storage_type2.get(new Pair<>(itr.ID,obj.ID)).set_state(2);
                            edge_storage_type2.get(new Pair<>(itr.ID,obj.ID)).calculation(itr.x_axis,itr.y_axis,obj.x_axis,obj.y_axis);
                        }
                        else
                        {
                            edgeConnectionRelation=new edge_connection_relation(str,1);
                            edge_storage_type2.put(new Pair<>(obj.ID,itr.ID),edgeConnectionRelation);
                            edgeConnectionRelation.calculation(obj.x_axis,obj.y_axis,itr.x_axis,itr.y_axis);
                        }

                    }
                    dfa_panel.revalidate();//do1
                    dfa_panel.repaint();
                    break;
                }
            }
        }
    }

    private void delete_node_cleaner(int index)
    {
        Iterator<Map.Entry<Pair<Integer,Integer>,edge_connection_relation>> itr=edge_storage_type2.entrySet().iterator();
        while (itr.hasNext())
        {
            if(start_states_container.contains(index))
            {
                start_states_container.remove(start_states_container.indexOf(index));
            }
            Map.Entry<Pair<Integer,Integer>,edge_connection_relation> entry=itr.next();
            if(entry.getKey().getKey()==index)
            {
                itr.remove();
            }
            else if(entry.getKey().getValue()==index)
            {
                itr.remove();
                for (char ch:entry.getValue().path_name.toCharArray())
                {
                    state_container.get(entry.getKey().getKey()-1).deleted_node(ch,index);
                }
            }
        }
    }
    private void delete_edge(int index_obj1,int index_obj2,int s)
    {
        if(s==2)
        {
            if(edge_storage_type2.get(new Pair<>(index_obj2,index_obj1))!=null)
            {
                edge_storage_type2.get(new Pair<>(index_obj2,index_obj1)).set_state(1);
                edge_storage_type2.get(new Pair<>(index_obj2,index_obj1)).calculation(state_container.get(index_obj2-1).x_axis,state_container.get(index_obj2-1).y_axis,state_container.get(index_obj1-1).x_axis,state_container.get(index_obj1-1).y_axis);
            }
        }
        dfa_panel.revalidate();
        dfa_panel.repaint();
    }
    public void draw_edge_calculation(Graphics2D g2d)
    {
        for(Map.Entry<Pair<Integer,Integer>,edge_connection_relation> m:edge_storage_type2.entrySet())
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
    private void disable_all()
    {
        dfa_panel.setEnabled(false);
        dfa_tools.setEnabled(false);
        dfa_menue_bar.setEnabled(false);
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
                jta.setFont(f);
                jta.setForeground(new Color(255,255,255));
                jta.setText(sb.toString());

                jf.pack();
            } catch (Exception e) {
                // TODO: handle exception
                System.err.println(e.getMessage());
                jf.dispose();
            }
        }
    }
    private class act_save_dfa_as_img implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            JFileChooser jfc=new JFileChooser();
            jfc.setDialogTitle("save dfa as img");
            if(jfc.showSaveDialog(null)==JFileChooser.APPROVE_OPTION);
            {
                try {
                    File file=jfc.getSelectedFile();
                    BufferedImage bufimg=new BufferedImage(dfa_panel.getWidth(), dfa_panel.getHeight(), BufferedImage.TYPE_INT_ARGB);
                    if(file!=null)
                    {
                        file=new File(file.toString());
                        Graphics2D g2d=bufimg.createGraphics();
                        dfa_panel.paint(g2d);
                        g2d.drawImage(bufimg, dfa_panel.getWidth(), dfa_panel.getHeight(), dfa_panel);
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
    private class act_node_btn implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {

            state=States.inseert;
        }
    }

    private class act_delete_btn implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e) {

            state=States.dele;
        }
    }

    private class act_none_btn implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e) {

            state=States.non;
        }
    }

    private class act_edge_btn implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e) {

            state=States.edge;
        }
    }

    private class act_run_btn implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            String input=JOptionPane.showInputDialog("enter your input");
            if(input!=null)
            {
                Calculation_thread trd=new Calculation_thread(input);
                trd.run();
            }
        }
    }
    private class act_save_machine_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent e) {
            if(!state_container.isEmpty())
            {
            try {
                ObjectMapper mapper=new ObjectMapper();
                save_obj ob=new save_obj();
                ob.setLi(state_container);
                ob.setMa(edge_storage_type2);
                JFileChooser jfc=new JFileChooser();
                jfc.setDialogTitle("save dfa machine");
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
            Queue<Integer> pos=new LinkedList<>();
            pos.add(start_states_container.get(0));
            int size=pos.size();
            for(char ch:in.toCharArray())
            {
                for(int i=0;i<size;i++)
                {
                    int index=pos.poll();
                    if(state_container.get(index-1).get_next_pos(ch)!=null)
                    {
                        ((LinkedList<Integer>)pos).addAll(pos.size(),state_container.get(index-1).get_next_pos(ch));
                    }
                }
                if(pos.isEmpty())
                {
                    jlb.setForeground(new Color(255,0,0));
                    jlb.setText("Reject");
                    return;
                }
            }
            boolean res=false;
            for(int a:pos)
            {
                if(state_container.get(a-1).getstate()==1||state_container.get(a-1).getstate()==3)
                {
                    res=true;
                    jlb.setForeground(new Color(0,255,0));
                    jlb.setText("Accept");
                    return;
                }
            }
            if(!res)
            {
                jlb.setForeground(new Color(255,0,0));
                jlb.setText("Reject");
            }
        }
    }

    private class act_Frun implements ActionListener
    {
        private int counter=-1;
        private String in="";

        private boolean fnd=false;
        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            if(!start_states_container.isEmpty())
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
                in=JOptionPane.showInputDialog("enter your input");
                if(in==null||in.isEmpty())
                {
                    return;
                }

                Queue<Integer> pos=new LinkedList<>();
                pos.add(start_states_container.get(start_states_container.indexOf(indx)));
                Map<Pair<Integer,Integer>,Character> pntob=new HashMap<>();


                JFrame jf=new JFrame();
                jf.setVisible(true);
                jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

                JLabel lres=new JLabel();
                JComponent jp=new JComponent(){
                    @Override
                    public void paint(Graphics g) {
                        Graphics2D g2d=(Graphics2D)g;//super.paint(g)
                        if(!pntob.isEmpty())
                        {
                            int cnt=-1;
                            for(Map.Entry<Pair<Integer,Integer>,Character> mtp:pntob.entrySet())
                            {
                                cnt++;
                                int n1=mtp.getKey().getKey();
                                int n2=mtp.getKey().getValue();
                                if(state_container.get(n1-1).getstate()==1||state_container.get(n1-1).getstate()==3)
                                {
                                    g2d.setColor(new Color(255,0,0));
                                    g2d.fillOval(0,cnt*60,60,60);
                                    g2d.setColor(new Color(0,0,0));
                                    g2d.drawString("V"+n1,25,25+cnt*60);
                                }
                                else
                                {
                                    g2d.setColor(new Color(255,255,0));
                                    g2d.fillOval(0,cnt*60,60,60);
                                    g2d.setColor(new Color(0,0,0));
                                    g2d.drawString("V"+n1,25,25+cnt*60);
                                }
                                if(state_container.get(n2-1).getstate()==1||state_container.get(n2-1).getstate()==3)
                                {
                                    g2d.setColor(new Color(255,0,0));
                                    g2d.fillOval(430,cnt*60,60,60);
                                    g2d.setColor(new Color(0,0,0));
                                    g2d.drawString("V"+n2,455,25+cnt*60);
                                }
                                else
                                {
                                    g2d.setColor(new Color(255,255,0));
                                    g2d.fillOval(430,cnt*60,60,60);
                                    g2d.setColor(new Color(0,0,0));
                                    g2d.drawString("V"+n2,455,25+cnt*60);
                                }
                                g2d.setColor(new Color(0,0,0));
                                g2d.drawLine(60,30+cnt*60,430,30+cnt*60);
                                g2d.drawString(mtp.getValue().toString(),250,25+cnt*60);
                            }
                        }
                    }
                };
                jp.setPreferredSize(new Dimension(500,500));
                JScrollPane jsp=new JScrollPane(jp);
                jsp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
                jsp.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
                JButton jb=new JButton("Next");



                jb.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent actionEvent) {
                        counter++;
                        pntob.clear();
                        if(counter<in.length()&&!fnd)
                        {
                            int size=pos.size();
                            char ch=in.charAt(counter);
                            for(int i=0;i<size;i++) {
                                int index = pos.poll();
                                if (state_container.get(index - 1).get_next_pos(ch) != null) {
                                    Set<Integer> stmp = state_container.get(index - 1).get_next_pos(ch);
                                    for (int asd : stmp) {
                                        pntob.put(new Pair<>(index, asd),ch); }
                                    ((LinkedList<Integer>) pos).addAll(pos.size(), stmp);
                                }
                            }
                            jp.setPreferredSize(new Dimension(500,60+pntob.size()*60));
                            if(pos.isEmpty())
                            {
                                fnd=true;
                                lres.setForeground(new Color(255,0,0));
                                lres.setText("Reject");
                                jp.revalidate();
                                jp.repaint();
                                jsp.revalidate();
                                jsp.repaint();

                                return;
                            }
                            if(counter==in.length()-1)
                            {
                                boolean res=false;
                                for(int a:pos)
                                {
                                    if(state_container.get(a-1).getstate()==1||state_container.get(a-1).getstate()==3)
                                    {
                                        res=true;
                                        fnd=true;
                                        lres.setForeground(new Color(0,200,0));
                                        lres.setText("Accept");

                                        jp.revalidate();
                                        jp.repaint();
                                        jsp.revalidate();
                                        jsp.repaint();
                                        return;
                                    }
                                }
                                if(!res)
                                {
                                    fnd=true;
                                    lres.setForeground(new Color(255,0,0));
                                    lres.setText("Reject");

                                    jp.revalidate();
                                    jp.repaint();
                                    jsp.revalidate();
                                    jsp.repaint();
                                    return;
                                }
                            }

                            jp.revalidate();
                            jp.repaint();
                            jsp.revalidate();
                            jsp.repaint();
                        }
                        else
                        {
                            counter=-1;
                            fnd=false;
                            jf.dispose();
                        }
                    }
                });

                jf.add(lres,BorderLayout.NORTH);
                jf.add(jb,BorderLayout.SOUTH);
                jf.add(jsp,BorderLayout.CENTER);
                jf.pack();

            }
        }
    }
    private class act_open_machine_btn implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent e) {

            if(state_container.isEmpty()&&edge_storage_type2.isEmpty())
            {
                state_container.clear();
                edge_storage_type2.clear();
                save_obj ob;
                ObjectMapper mapper=new ObjectMapper();
                try {
                    JFileChooser jfc=new JFileChooser();
                    jfc.setDialogTitle("open dfa machine");
                    if(jfc.showOpenDialog(null)==JFileChooser.APPROVE_OPTION)
                    {
                        File file=jfc.getSelectedFile();
                        if(file!=null)
                        {
                            ob=mapper.readValue(file,save_obj.class);
                            state_container=ob.getLi();
                            edge_storage_type2=ob.getMa();
                            for (DFA_states itr:state_container)
                            {
                                if(itr!=null)
                                {
                                    itr.set_methods();
                                    JPopupMenu main_menu=new JPopupMenu("options");
                                    JMenuItem final_state=new JCheckBoxMenuItem("final state");
                                    JMenuItem start_state=new JCheckBoxMenuItem("start state");
                                    main_menu.add(final_state);
                                    main_menu.add(start_state);
                                    //final_state.setSelected(true); prob?
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
                                                dfa_panel.repaint();

                                            }
                                            else
                                            {
                                                itr.setState(-1);//-1 -> not final
                                                dfa_panel.repaint();
                                            }
                                        }
                                    });
                                    start_state.addActionListener(new ActionListener() {
                                        @Override
                                        public void actionPerformed(ActionEvent e) {
                                            if(start_state.isSelected())
                                            {
                                                itr.setState(2);//2 ->start
                                                dfa_panel.repaint();
                                                start_states_container.add(itr.ID);
                                            }
                                            else
                                            {
                                                itr.setState(-2);//-2 ->not start
                                                dfa_panel.repaint();
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
                                                dfa_panel.remove(itr);
                                                state_container.set(itr.ID-1,null);
                                                dfa_panel.repaint();
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
                                    dfa_panel.add(itr);
                                }
                            }
                            dfa_panel.revalidate();
                            dfa_panel.repaint();
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
    private class Calculation_thread implements Runnable
    {
        private String in;
        private Queue<Integer> pos=new LinkedList<>();
        @Override
        public void run() {
            if(!start_states_container.isEmpty())
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
                pos.add(start_states_container.get(start_states_container.indexOf(indx)));
                int size=pos.size();
                for(char ch:in.toCharArray())
                {
                    for(int i=0;i<size;i++)
                    {
                        int index=pos.poll();
                        if(state_container.get(index-1).get_next_pos(ch)!=null)
                        {
                            ((LinkedList<Integer>)pos).addAll(pos.size(),state_container.get(index-1).get_next_pos(ch));
                        }
                    }
                    if(pos.isEmpty())
                    {
                        JOptionPane.showMessageDialog(null,"Reject");
                        return;
                    }
                }
                boolean res=false;
                for(int a:pos)
                {
                    if(state_container.get(a-1).getstate()==1||state_container.get(a-1).getstate()==3)
                    {
                        res=true;
                        JOptionPane.showMessageDialog(null,"Accept");
                        break;
                    }
                }
                if(!res)
                {
                    JOptionPane.showMessageDialog(null,"Reject");
                }
            }


        }
        public Calculation_thread(String input)
        {
            in=input;
        }
    }
}
