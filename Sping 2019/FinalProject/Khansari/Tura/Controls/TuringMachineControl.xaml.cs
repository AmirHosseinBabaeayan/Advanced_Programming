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
using Tura.Models;

namespace Tura.Controls
{
    /// <summary>
    /// Interaction logic for TuringMachineControl.xaml
    /// </summary>
    public partial class TuringMachineControl : UserControl
    {
        public event EventHandler DeleteRequested;
        public TuringMachine ContainingMachine;
        bool Dragging = false;
        Point MouseLastPosition;

        public TuringMachineControl(TuringMachine containingmachine)
        {
            InitializeComponent();

            Margin = new Thickness(containingmachine.Location.X, containingmachine.Location.Y, 0, 0);

            ContainingMachine = containingmachine;
            MouseDoubleClick += MachineControl_MouseDoubleClick;
            MachineName.Text = containingmachine.Name;
            MouseDown += MachineControl_MouseDown;
            MouseMove += MachineControl_MouseMove;
            MouseUp += MachineControl_MouseUp;
        }


        private void MachineControl_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Dragging = false;
        }

        private void MachineControl_MouseMove(object sender, MouseEventArgs e)
        {

            if (Dragging)
            {
                Point p = Mouse.GetPosition(this);
                Margin = new Thickness(Margin.Left + (p.X - MouseLastPosition.X), Margin.Top + (p.Y - MouseLastPosition.Y), Margin.Right, Margin.Bottom);
                ContainingMachine.Location.X = Margin.Left;
                ContainingMachine.Location.Y = Margin.Top;

            }

        }

        private void MachineControl_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MouseLastPosition = Mouse.GetPosition(this);
            Dragging = true;
        }

        private void MachineControl_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            TuringMachineEditWindow editwindow = new TuringMachineEditWindow(ContainingMachine);
            editwindow.ShowDialog();
            ContainingMachine = editwindow.ContainingMachine;
            Dragging = false;
            e.Handled = true;
        }

        private void MachineNameTextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            MachineNameTextBox.Visibility = Visibility.Collapsed;
            MachineName.Text = ContainingMachine.Name;
        }

        private void MachineNameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            ContainingMachine.Name = MachineNameTextBox.Text;
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            MachineNameTextBox.Visibility = Visibility.Visible;
            MachineNameTextBox.Focus();
            MachineNameTextBox.Text = ContainingMachine.Name;
            e.Handled = true;
        }

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            if (DeleteRequested != null)
            {
                DeleteRequested.Invoke(this, null);
            }
        }
    }
}
