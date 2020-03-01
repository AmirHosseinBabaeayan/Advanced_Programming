using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using System.Windows.Shapes;
using Tura;
using Tura.Controls;
using Tura.Models;

namespace Tura
{
    /// <summary>
    /// Interaction logic for MultiInputWindow.xaml
    /// </summary>
    public partial class MultiInputWindow : Window
    {
        public Machine ContainingMachine;
        
        public MultiInputWindow(Machine machine)
        {
            InitializeComponent();
            ContainingMachine = machine;
        }

        protected override void OnClosing(CancelEventArgs e)
        {
        }


        MultiInputItem CreateItemtextBox()
        {
            MultiInputItem t = new MultiInputItem();
            t.Width = Width - 20;
            t.HorizontalAlignment = HorizontalAlignment.Center;
            t.Margin = new Thickness(0, 2, 0, 2);
            return t;
        }

        private void AddItemButtonClick_Click(object sender, RoutedEventArgs e)
        {
            MultiInputItem t = CreateItemtextBox();
            ConditionsPanel.Children.Add(t);
        }

        private void RunButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                foreach (MultiInputItem t in ConditionsPanel.Children)
                {
               
                    string input = t.GetInput();
                    t.SetOutput(ContainingMachine.Run(input));
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }
    }

}
