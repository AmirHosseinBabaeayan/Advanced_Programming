using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tura.Models;
namespace Tura.Util
{
    class DFAMachineDebugger
    {
        DFAMachine ContainingMachine;
        public DFAMachineDebugger(DFAMachine m)
        {
            ContainingMachine = m;
        }

        public string GetFirstError()
        {
            string error = "";
            error = DebugEdgeInterference();
            if (error != "")
                return error;

            error = DebugTwoStartPoint();
            if (error != "")
                return error;

            return "";
        }

        string DebugTwoStartPoint()
        {
            bool StartPointFound = false;
            foreach (Vertex V in ContainingMachine.Vertices)
            {
                if (V.IsStartState && StartPointFound == false)
                    StartPointFound = true;

                else if (V.IsStartState && StartPointFound == true)
                {
                    return "There are more than one start points";
                }
            }
            return "";
        }

        string DebugEdgeInterference()
        {
            foreach (Edge<char> e in ContainingMachine.Edges)
            {
                foreach (Edge<char> E in ContainingMachine.Edges)
                {
                    if (AreEdgesInterfering(e, E))
                        return "Two edges from " + e.Source.Name + " are Interfering";
                }
            }
            return "";
        }

        bool AreEdgesInterfering(Edge<char> e1, Edge<char> e2)
        {
            if (e1 != e2 && e1.Source == e2.Source)
            {
                foreach (char c in e1.GetConditions)
                {
                    foreach (char C in e2.GetConditions)
                    { 
                        if (c.ToString() == C.ToString())
                            return true;
                    }
                }
                return false;
            }
            else
                return false;
        }
    }
}
