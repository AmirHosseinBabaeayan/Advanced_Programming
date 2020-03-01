using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tura.Models
{
    class TuringBrokerStepResult
    {
        public Vertex Destination;
        public char ReplaceBy;
        public Transition To;

        public TuringBrokerStepResult(Vertex dest, char replaceby, Transition to)
        {
            Destination = dest;
            ReplaceBy = replaceby;
            To = to;
        }
    }
}
