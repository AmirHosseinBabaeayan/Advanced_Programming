using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tura.Models
{
    public class Edge<T>
    {

        public Edge(Vertex start, Vertex finish, T condition)
        {
            conditiongate = new List<T>();
            conditiongate.Add(condition);
            Source = start;
            Destination = finish;
            if (Source == Destination)
                SelfConnectedVertex = true;
            else SelfConnectedVertex = false;
        }

        public bool IsSelfConnected()
        {
            return SelfConnectedVertex;
        }

        public bool SetCondition(T c)
        {
            conditiongate.Add(c);

            return true;
        }

        public void ClearConditions()
        {
            conditiongate.Clear();
        }

        bool SelfConnectedVertex;
        Vertex source;
        Vertex destination;
        List<T> conditiongate;
        public List<T> GetConditions { get { return conditiongate; } }
        public string GetConditionsAsString {
            get
            {
                string st = "";
                foreach (T t in conditiongate)
                {
                   st += t.ToString() + '|';
                }

                st = st.TrimEnd('|');

                return st;
            }
        }
        public Vertex Source { set { source = value; SelfConnectedVertex = (source == destination); } get { return source; } }
        public Vertex Destination { set { destination = value; SelfConnectedVertex = (source == destination); } get { return destination; } }

    }
}
