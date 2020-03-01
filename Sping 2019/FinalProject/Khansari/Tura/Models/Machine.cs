using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Tura.Models
{
    public abstract class Machine
    {
        public string Name;
        public Point Location;
        public List<Vertex> Vertices;
        public MachineClass Class;
        public void RemoveVertex(Vertex V)
        {
            Vertices.Remove(V);
            PurgeOrphanEdges();
        }
        public abstract string Run(string input);
        public abstract void ReconstructRefs();

        public abstract void PurgeOrphanEdges();
    }



    public enum MachineClass { DFA, Turing }
}
