using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tura.Util
{
    public static class Rand
    {
        static Random random = new Random();
        public static int GetNext()
        {
            return random.Next();
        }
    }
}
