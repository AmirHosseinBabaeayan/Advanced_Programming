using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tura.Models;
namespace Tura.Util
{
    class EdgeComparer<T> : IEqualityComparer<Edge<T>>
    {
        public bool Equals(Edge<T> x, Edge<T> y)
        {
            return (x.Source == y.Source && x.Destination == y.Destination);
        }

        public int GetHashCode(Edge<T> obj)
        {
            throw new NotImplementedException();
        }
    }
}
