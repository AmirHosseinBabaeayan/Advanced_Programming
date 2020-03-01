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
using Tura.Models;
namespace Tura
{
    /// <summary>
    /// Interaction logic for DFAConditionEditWindow.xaml
    /// </summary>
    public partial class DFAConditionEditWindow : Window
    {
        Edge<char> ContainingEdge;
        public DFAConditionEditWindow(Edge<char> e)
        {
            ContainingEdge = e;
            InitializeComponent();
            
            InitializeConditionItems();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            SaveConditionChanges();
            base.OnClosing(e);
        }

        TextBox CreateItemtextBox(char c)
        {
            TextBox t = new TextBox();
            t.MaxLength = 1;
            t.Text = c.ToString();
            t.Width = Width - 20;
            t.HorizontalAlignment = HorizontalAlignment.Center;
            t.Margin = new Thickness(0, 2, 0, 2);
            return t;
        }

        void InitializeConditionItems()
        {
            foreach (char c in ContainingEdge.GetConditions)
            {

                ConditionsPanel.Children.Add(CreateItemtextBox(c));
            }
        }


        bool SaveConditionChanges()
        {
            ContainingEdge.ClearConditions();

            foreach (TextBox t in ConditionsPanel.Children)
            {
                if (t.Text != "")
                    ContainingEdge.SetCondition(t.Text[0]);
            }
            return true;
        }

        private void AddItemButtonClick_Click(object sender, RoutedEventArgs e)
        {
            TextBox t = CreateItemtextBox('c');
            ConditionsPanel.Children.Add(t);
        }
    }
}
