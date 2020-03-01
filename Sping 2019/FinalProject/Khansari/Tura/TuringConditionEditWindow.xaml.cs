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
using System.Windows.Shapes;
using Tura.Models;
using Tura.Controls;
namespace Tura
{
    /// <summary>
    /// Interaction logic for TuringConditionEditWindow.xaml
    /// </summary>
    public partial class TuringConditionEditWindow : Window
    {
        List<TuringCondition> ContainingCondition;
        public TuringConditionEditWindow(List<TuringCondition> condition)
        {
            ContainingCondition = condition;
            InitializeComponent();
            InitializeItemsPanel();
        }

        void InitializeItemsPanel()
        {
            foreach (TuringCondition t in ContainingCondition)
            {
               ConditionItemsPanel.Children.Add(new TuringConditionItemControl(t));
            }
        }

        private void AddNewItemButton_Click(object sender, RoutedEventArgs e)
        {
            ConditionItemsPanel.Children.Add(new TuringConditionItemControl(new TuringCondition()));
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            ContainingCondition.Clear();
            foreach (TuringConditionItemControl c in ConditionItemsPanel.Children)
            {
                if (c.ContainingCondition.Condition != '\0')
                    ContainingCondition.Add(c.ContainingCondition);
            }
        }
    }
}
