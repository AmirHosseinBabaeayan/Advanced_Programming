using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tura.Models;

namespace Tura.Util
{
    class DFAMachineBroker
    {
        DFAMachine ContainingMachine;
        bool Initialized = false;

        public DFAMachineBroker(DFAMachine machine)
        {
            ContainingMachine = machine;
        }

        public void InitializeMachine()
        {
            DFAMachineDebugger dbg = new DFAMachineDebugger(ContainingMachine);
            string error = dbg.GetFirstError();
            if (error != "")
                throw new InvalidOperationException(error);

            Initialized = true;
        }

        public string Run(string input)
        {
            if (input == "")
                throw new InvalidOperationException("No input is given to the machine.");
            Vertex TempVertex = null;
            foreach (char c in input)
            {
                try
                {
                    TempVertex = Step(c, TempVertex);
                    if (TempVertex == null)
                    {
                        return "";
                    }
                }
                catch (Exception ex)
                {
                    return "";
                }
            }
            if (TempVertex.IsFinishState)
                return "Input accepted(" + TempVertex.Name + ")";
            else
                return "Input rejected";
        }

        public Vertex GetStartState()
        {
            foreach (Vertex v in ContainingMachine.Vertices)
            {
                if (v.IsStartState)
                    return v;
            }
            return null;
        }

        public Vertex Step(char condition, Vertex sourcevertex)
        {
            if (!Initialized)
                throw new InvalidOperationException("Broker should be initialized first");

            if (sourcevertex == null)
                sourcevertex = GetStartState();

            foreach (Edge<char> e in ContainingMachine.Edges)
            {
                if (e.Source == sourcevertex && PassesConditions(e, condition))
                    return e.Destination;
            }
            return null;
        }

        bool PassesConditions(Edge<char> e, char val)
        {
            foreach (char c in e.GetConditions)
            {
                if (c == val)
                    return true;
            }
            return false;
        }
    }
}
