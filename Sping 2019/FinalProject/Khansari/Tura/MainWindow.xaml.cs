using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using System.Windows.Documents; 
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Tura.Models;
using Tura.Controls;
using Tura.Util;
using System.IO;
using System.Windows.Forms;

namespace Tura
{
    
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        Project ContainingProject;
        bool isprojectloaded;

        public bool IsProjectLoaded { set { isprojectloaded = value; MainPanel.Visibility = (value == true) ? Visibility.Visible : Visibility.Collapsed; MachineMenu.IsEnabled = value; CloseProjectMenuItem.IsEnabled = SaveAsMenuItem.IsEnabled = SaveProjectMenuItem.IsEnabled = value; } get { return isprojectloaded; } }
        public MainWindow()
        {
            InitializeComponent();
            InitializeWindow();
            Properties.Settings.Default.Reload();
            IsProjectLoaded = false;
            if (IsProjectLoaded)
            InvalidateMachinesGrid();
        }

        void InitializeWindow()
        {
            if (!Properties.Settings.Default.Activated)
            {
                Title = "Tura (Trial version)";
                AddTuringMachineMenuItem.IsEnabled = false;
            }
        }

        public void InvalidateMachinesGrid()
        {
            MachinesGrid.Children.Clear();
            foreach (DFAMachine machine in ContainingProject.DFAMachines)
            {
                MachineControl mc = new MachineControl(machine);
                mc.DeleteRequested += Mc_DeleteRequested;
                MachinesGrid.Children.Add(mc);
            }

            foreach (TuringMachine machine in ContainingProject.TuringMachines)
            {
                TuringMachineControl tmc = new TuringMachineControl(machine);
                tmc.DeleteRequested += Tmc_DeleteRequested; ;
                MachinesGrid.Children.Add(tmc);
            }
        }

        private void Tmc_DeleteRequested(object sender, EventArgs e)
        {
            TuringMachineControl machine = sender as TuringMachineControl;
            ContainingProject.TuringMachines.Remove(machine.ContainingMachine);
            InvalidateMachinesGrid();
        }

        private void Mc_DeleteRequested(object sender, EventArgs e)
        {
            MachineControl machine = sender as MachineControl;
            ContainingProject.DFAMachines.Remove(machine.ContainingMachine);
            InvalidateMachinesGrid();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.MenuItem item = sender as System.Windows.Controls.MenuItem;

            if (item.Header.ToString() == "DFA Machine")
                ContainingProject.DFAMachines.Add(new DFAMachine("New DFA Machine"));
            else if (item.Header.ToString() == "Turing Machine")
                ContainingProject.TuringMachines.Add(new TuringMachine("New Turing Machine"));

            InvalidateMachinesGrid();
        }

        private void OpenProjectMenuItem_Click(object sender, RoutedEventArgs e)
        {
            
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = "tpf";
            dlg.Filter = "Tura project file | *.tpf";
            try
            {
                if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    ContainingProject = FileDAL.LoadProject(dlg.FileName);
                else
                    return;

            InvalidateMachinesGrid();
            IsProjectLoaded = true;
                Title += " - " + ContainingProject.Name;
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show("There was a problem loading the project. project file may be corrupted", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void SaveProjectMenuItem_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.MenuItem item = sender as System.Windows.Controls.MenuItem;
            if (ContainingProject.FileDir == null | item.Header.ToString() == "Save _As")
            {
                SaveFileDialog dlg = new SaveFileDialog();
                dlg.DefaultExt = "TPF";
                dlg.Filter = "Turing project file | *.TPF";
                if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    ContainingProject.FileDir = dlg.FileName;

            }

            else
            {
                try
                {
                    FileDAL.SaveProject(ContainingProject);
                }
                catch
                {
                    System.Windows.MessageBox.Show("There was a problem saving the project, try using another directory.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
            
        }

        private void NewProjectMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ContainingProject = new Project();
            IsProjectLoaded = true;
        }

        private void CloseProjectMenuItem_Click(object sender, RoutedEventArgs e)
        {
            IsProjectLoaded = false;
            InitializeWindow();
        }

        private void SettingsMenuItem_Click(object sender, RoutedEventArgs e)
        {
            new SettingsWindow().Show();
            InitializeWindow();
        }
    }
}
