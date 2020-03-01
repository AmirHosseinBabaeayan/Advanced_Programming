using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tura.Models
{
    public class TuringCondition
    {
        public TuringCondition(char condition, char replaceby, Transition to)
        {
            Condition = condition;
            ReplaceBy = replaceby;
            To = to;
        }

        public TuringCondition()
        {
            Condition = 'c';
            ReplaceBy = '#';
            To = Transition.Right;
        }

        public override string ToString()
        {
            return Condition.ToString() + ", " + ReplaceBy.ToString() + ", " + ((To == Transition.Right) ? "R" : "L");
        }

        public char Condition;
        public char ReplaceBy;
        public Transition To;
    }

    public enum Transition { Left, Right, None };
}
