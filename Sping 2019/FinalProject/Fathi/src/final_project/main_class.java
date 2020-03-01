package final_project;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class main_class {
    public static void main(String []args)
    {
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                JFrame main_first_frame=new JFrame("automata theory");
                main_first_frame.setVisible(true);
                main_first_frame.setResizable(false);
                main_first_frame.setLocationRelativeTo(null);
                main_first_frame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

                JPanel main_first_frame_panel=new JPanel();
                main_first_frame_panel.setPreferredSize(new Dimension(500,500));
                GridLayout gridLayout_obj=new GridLayout(1,2);
                main_first_frame_panel.setLayout(gridLayout_obj);

                JButton dfa_machine_btn=new JButton("DFA");
                dfa_machine_btn.setFont(new Font("Arial",Font.BOLD,24));
                dfa_machine_btn.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        main_first_frame.setVisible(false);
                        DFA_Machine_class dfa_machine=new DFA_Machine_class();
                        dfa_machine.jframe_methods(main_first_frame);
                    }
                });

                JButton turing_machine_btn=new JButton("turing");
                turing_machine_btn.setFont(new Font("Arial",Font.BOLD,24));
                turing_machine_btn.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        main_first_frame.setVisible(false);
                        Touring_machine_class touring_machine=new Touring_machine_class();
                        touring_machine.jframe_methods(main_first_frame);
                    }
                });

                main_first_frame_panel.add(dfa_machine_btn);
                main_first_frame_panel.add(turing_machine_btn);

                main_first_frame.add(main_first_frame_panel);

                main_first_frame.pack();



            }
        });
    }
}
