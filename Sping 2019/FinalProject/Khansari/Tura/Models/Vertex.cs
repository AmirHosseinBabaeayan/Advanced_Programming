using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Tura.Util;
namespace Tura.Models
{
    public class Vertex
    {
        public event EventHandler Activated;
        public event EventHandler VertexMoved;

        public Machine ContainingMachine;
        public bool ContainsMachine { get { return !(ContainingMachine == null); } }
        public string RunVertex(string input)
        {
            if (ContainsMachine)
                return ContainingMachine.Run(input);
                return input;
        }

        public Vertex(string name, Point location)
        {
            Rename(name);
            Location = location;
            isstartstate = false;
            isfinishstate = false;

            id = Rand.GetNext();
        }

        public void InvokeActivation()
        {
            Activated.Invoke(this, null);
        }

        public void Rename(string name)
        {
            Name = name;
        }
        public bool IsFinishState { set { if (isstartstate && value == true) isstartstate = !isstartstate; isfinishstate = value; } get { return isfinishstate; } }
        public bool IsStartState { set { if (isfinishstate && value == true) isfinishstate = !isfinishstate; isstartstate = value; } get { return isstartstate; } }
        bool isstartstate;
        bool isfinishstate;
        int id;

        public int ID { get { return id; } set { id = value; } }
        public string Name;
        Point location;
        public Point Location { set { location = value; if (VertexMoved != null) VertexMoved.Invoke(this, null); } get { return location; } }
    }
}
