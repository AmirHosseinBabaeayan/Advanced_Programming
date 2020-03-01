package final_project;

import javafx.util.Pair;

import javax.swing.*;
import java.awt.*;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.sql.Array;
import java.util.*;
import java.util.List;

public class hii {
    public static void main(String args[])
    {

        /*int a2=3, b2=2;
        System.out.println((double) a2/b2);
        Set<Integer> s=new HashSet<>();
        s.add(1);
        s.add(4);
        s.add(2);
        s.add(2);
        s.remove(6);
        Set<Integer> s2=new HashSet<>();
        s2.add(6);
        s2.add(7);
        s2.add(8);
        System.out.println(s);
        Queue<Integer>q=new LinkedList<>();
        ((LinkedList<Integer>) q).addAll(0,s);
        System.out.println(q);
        ((LinkedList<Integer>) q).addAll(q.size(),s2);
        System.out.println(q.size());
        System.out.println(q);

        int a=3;
        int b=a;
        System.out.println(a+" "+b);
        a=4;
        System.out.println(a+" "+b);
        Set s3=new HashSet(s2);
        System.out.println(s3);
        s2.remove(6);
        System.out.println(s3);
        Map<Pair<Integer,Integer>,Pair<Set<Integer>,Pair<Integer,Integer>>> m=new HashMap<>();
        m.put(new Pair<>(1,1),new Pair<>(s2,new Pair<>(10,20)));
        m.put(new Pair<>(1,2),new Pair<>(s3,new Pair<>(20,30)));
        m.put(new Pair<>(2,1),new Pair<>(s,new Pair<>(100,110)));
        Pair p=new Pair(1,1);
        System.out.println(m.get(p).getKey());

       Map<Integer,String>map=new HashMap<>();
       map.put(1,"hi");
      // map.put(2,"hello");
      // map.put(3,"bye");
      // map.put(4,"good");
      //  map.put(5,"nigght");
       System.out.println(map);
       Iterator<Map.Entry<Integer,String>>itr=map.entrySet().iterator();
       while (itr.hasNext())
       {
           Map.Entry<Integer,String> ent=itr.next();
           //if(ent.getKey()==1)
           {
               itr.remove();
           }
       }
       System.out.println(map);

       System.out.println(Math.sin(Math.atan2(3,0)));

       String str="a";
       String str2=str.substring(0,0)+str.substring(1);
       if(str2.isEmpty())
       {
           System.out.println("ssa");
       }
        System.out.println(str2);
        System.out.println(str.indexOf('n'));

        String ss="v12";

        System.out.println( Integer.parseInt(ss.substring(1)));
        int aa=1;*/
        String str="abcdefghi";
        StringBuilder sb=new StringBuilder(str);
        for(String a:str.split(""))
        {
            System.out.println(a);
        }
    }


}
