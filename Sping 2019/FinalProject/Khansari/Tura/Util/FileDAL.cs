using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tura.Models;
using Newtonsoft.Json;
using System.IO;

namespace Tura.Util
{
    static class FileDAL
    {
        public static void SaveProject(Project project)
        {
            JsonSerializer json = new JsonSerializer();
            string projstring = JsonConvert.SerializeObject(project);
            File.WriteAllText(project.FileDir, projstring);
        }

        public static Project LoadProject(string dir)
        {
            string content = File.ReadAllText(dir);
            Project p = JsonConvert.DeserializeObject<Project>(content);
            foreach (DFAMachine m in p.DFAMachines)
            {
                foreach (Edge<char> edge in m.Edges)
                    edge.GetConditions.RemoveAt(0);

                m.ReconstructRefs();
            }
            foreach (TuringMachine m in p.TuringMachines)
            {
                foreach (Edge<TuringCondition> edge in m.Edges)
                    edge.GetConditions.RemoveAt(0);

                m.ReconstructRefs();
            }
            return p;
        }



        public static TuringMachine LoadTuringMachine(string dir)
        {
            string content = File.ReadAllText(dir);
            var jset = new JsonSerializerSettings() { TypeNameHandling = TypeNameHandling.All };
            TuringMachine machine = JsonConvert.DeserializeObject<TuringMachine>(content, jset);

                foreach (Edge<TuringCondition> edge in machine.Edges)
                    edge.GetConditions.RemoveAt(0);

            machine.ReconstructRefs();
            return machine;
        }

        public static void SaveDFAMachine(DFAMachine machine, string dir)
        {
            JsonSerializer json = new JsonSerializer();
            string machinestr = JsonConvert.SerializeObject(machine);
            File.WriteAllText(dir, machinestr);
        }

        public static void SaveTuringMachine(TuringMachine machine, string dir)
        {
            var jset = new JsonSerializerSettings() { TypeNameHandling = TypeNameHandling.All };
            JsonSerializer json = new JsonSerializer();
            string machinestr = JsonConvert.SerializeObject(machine,jset);
            File.WriteAllText(dir, machinestr);
        }

        public static DFAMachine LoadDFAMachine(string dir)
        {
            string content = File.ReadAllText(dir);
            DFAMachine machine = JsonConvert.DeserializeObject<DFAMachine>(content);

            foreach (Edge<char> edge in machine.Edges)
                edge.GetConditions.RemoveAt(0);

            machine.ReconstructRefs();
            return machine;
        }    
      
    }
}
