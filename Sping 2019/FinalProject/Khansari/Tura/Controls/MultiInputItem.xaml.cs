using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Tura.Controls
{
    /// <summary>
    /// Interaction logic for MultiInputItem.xaml
    /// </summary>
    public partial class MultiInputItem : UserControl
    {
        public MultiInputItem()
        {
            InitializeComponent();
        }

        public void SetOutput(string output)
        {
            OutputTextBox.Text = output;
        }

        public string GetInput()
        {
            return InputTextBox.Text;
        }
    }
}
