using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tura.Models
{
    class Project
    {
        public string Name;
        public List<TuringMachine> TuringMachines;
        public List<DFAMachine> DFAMachines;
        public string FileDir;

        public Project()
        {
            Name = "New Project";
            TuringMachines = new List<TuringMachine>();
            DFAMachines = new List<DFAMachine>();

        }
    }
}
