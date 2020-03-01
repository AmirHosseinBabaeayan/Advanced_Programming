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
using System.Collections.Concurrent;
using Tura.Util;

namespace Tura
{
    /// <summary>
    /// Interaction logic for TuringMachineEditWindow.xaml
    /// </summary>
    public partial class TuringMachineEditWindow : Window
    {
        TuringMachineTapeControl TapeControl;
        public TuringMachine ContainingMachine;
        bool ConnectionRequested = false;
        Vertex ConnectionRequestSource;

        public TuringMachineEditWindow(TuringMachine containingmachine)
        {
            InitializeComponent();
            ContainingMachine = containingmachine;
            Title = "Edit machine: " + containingmachine.Name;
            InvalidateMachineGraph();
            TapeControl = new TuringMachineTapeControl("") { Height = 100 };

            WindowGrid.Children.Add(TapeControl);
            TapeControl.ScrollToItem(0, true);

        }




        private void NewVertexMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ContainingMachine.Vertices.Add(new Vertex("V", new Point(20, 20)));
            InvalidateMachineGraph();
        }

        void InvalidateMachineGraph()
        {
            GraphGrid.Children.Clear();


            foreach (Edge<TuringCondition> E in ContainingMachine.Edges)
            {
                TuringEdgeControl EC = new TuringEdgeControl(E);
                EC.RemoveEdge += EdgeControl_RemoveEdge;
                GraphGrid.Children.Add(EC);
            }

            foreach (Vertex v in ContainingMachine.Vertices)
            {
                VertexControl vc = new VertexControl(v);
                vc.ConnectRequest += Vc_ConnectRequest;
                vc.RemoveVertex += Vc_RemoveVertex;
                vc.MouseDown += Vc_MouseDown;
                GraphGrid.Children.Add(vc);
            }


        }

        private void Vc_RemoveVertex(object sender, Vertex e)
        {
            ContainingMachine.RemoveVertex(e);
            InvalidateMachineGraph();
        }


        private void EdgeControl_RemoveEdge(object sender, Edge<TuringCondition> e)
        {
            ContainingMachine.Edges.Remove(e);
            InvalidateMachineGraph();
        }

        private void Vc_MouseDown(object sender, MouseButtonEventArgs e)
        {
            VertexControl control = sender as VertexControl;
            if (ConnectionRequested)
            {
                if (ContainingMachine.Edges.Contains(new Edge<TuringCondition>(ConnectionRequestSource, control.ContainingVertex, null), new EdgeComparer<TuringCondition>()))
                {
                    MessageBox.Show("Edge is already added", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    ConnectionRequested = false;
                    return;
                }
                ContainingMachine.Edges.Add(new Edge<TuringCondition>(ConnectionRequestSource, control.ContainingVertex, new TuringCondition()));
                ConnectionRequested = false;
                InvalidateMachineGraph();
            }

        }

        private void Vc_ConnectRequest(object sender, Vertex e)
        {
            ConnectionRequested = true;
            ConnectionRequestSource = e;
        }

        private async void StartMachineButton_Click(object sender, RoutedEventArgs e)
        {
            RunMachineStep(InputTextBox.Text);
        }

        async void RunMachineStep(string input)
        {
            int cursor = 0;
            TuringMachineBroker broker = new TuringMachineBroker(ContainingMachine);
            try
            {
                broker.InitializeMachine();
            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return;
            }
            TuringBrokerStepResult stepresult = new TuringBrokerStepResult(null, '\0', Transition.Right);

            do
            {
                try
                {
                    await TapeControl.ScrollToItem(cursor, true);
                    stepresult = broker.Step(input[cursor], stepresult.Destination);
                    if (stepresult == null)
                    {
                        return;
                    }
                    await Task.Delay(500);

                    input = input.Remove(cursor, 1);
                    input = input.Insert(cursor, stepresult.ReplaceBy.ToString());
                    input = stepresult.Destination.RunVertex(input);

                    TapeControl.ChangeInput(input);

                    if (stepresult.To == Transition.Right)
                    {
                        cursor++;
                        if (cursor >= input.Length)
                            input += "#";
                    }
                    else if (stepresult.To == Transition.Left)
                    {
                        cursor--;
                        if (cursor < 0)
                        {
                            input = "#" + input;
                            cursor = 0;
                            await TapeControl.ScrollToItem(1, false);
                        }
                    }

                    stepresult.Destination.InvokeActivation();

                }
                

                catch (Exception ex)
                {
                    //SetNotificationText("Error: " + ex.Message);
                    return;
                }
            } while (stepresult.Destination != null);

            TapeControl.ChangeInput(input);
        }

        private void InputTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            TapeControl.ChangeInput(InputTextBox.Text);
        }

        private void QuickRunButton_Click(object sender, RoutedEventArgs e)
        {
            TuringMachineBroker broker = new TuringMachineBroker(ContainingMachine);
            broker.InitializeMachine();
            MessageBox.Show("Machine Output: " + broker.Run(InputTextBox.Text), "Result", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void MultiInputRunButton_Click(object sender, RoutedEventArgs e)
        {
            new MultiInputWindow(ContainingMachine).ShowDialog();
        }

        private void OpenMachineMenuItem_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.OpenFileDialog dlg = new System.Windows.Forms.OpenFileDialog();
            dlg.DefaultExt = "tmf";
            dlg.Filter = "Turing machine file | *.tmf";
            try
            {
                if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    ContainingMachine = FileDAL.LoadTuringMachine(dlg.FileName);

                InvalidateMachineGraph();
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show("There was a problem loading the machine. machine file may be corrupted.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void SaveMahcineMenuItem_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.MenuItem item = sender as System.Windows.Controls.MenuItem;

            System.Windows.Forms.SaveFileDialog dlg = new System.Windows.Forms.SaveFileDialog();
            dlg.DefaultExt = "tmf";
            dlg.Filter = "Turing machine file | *.tmf";
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                FileDAL.SaveTuringMachine(ContainingMachine, dlg.FileName);
        }

        private void ImportDFAMachineMenuItem_Click(object sender, RoutedEventArgs e)
        {
            DFAMachine ImportedMachine;
            System.Windows.Forms.OpenFileDialog dlg = new System.Windows.Forms.OpenFileDialog();
            dlg.DefaultExt = "dmf";
            dlg.Filter = "DFA machine file | *.dmf";
            try
            {
                if (dlg.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                    return;

                   ImportedMachine  = FileDAL.LoadDFAMachine(dlg.FileName);

                Vertex MachineVertex = new Vertex(ImportedMachine.Name, new Point(20, 20));
                MachineVertex.ContainingMachine = ImportedMachine;
                ContainingMachine.Vertices.Add(MachineVertex);
                InvalidateMachineGraph();
            }
            catch
            {
                System.Windows.MessageBox.Show("There was a problem loading the machine. machine file may be corrupted.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ImportTuringMachineMenuItem_Click(object sender, RoutedEventArgs e)
        {
            TuringMachine ImportedMachine;
            System.Windows.Forms.OpenFileDialog dlg = new System.Windows.Forms.OpenFileDialog();
            dlg.DefaultExt = "tmf";
            dlg.Filter = "Turing machine file | *.tmf";
            try
            {
                if (dlg.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                    return;

                ImportedMachine = FileDAL.LoadTuringMachine(dlg.FileName);

                Vertex MachineVertex = new Vertex(ImportedMachine.Name, new Point(20, 20));
                MachineVertex.ContainingMachine = ImportedMachine;
                ContainingMachine.Vertices.Add(MachineVertex);
                InvalidateMachineGraph();
            }
            catch
            {
                System.Windows.MessageBox.Show("There was a problem loading the machine. machine file may be corrupted.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void PrintMachineMenuItem_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                PrintDialog printer = new PrintDialog();
                printer.PrintVisual(GraphGrid, "");
            }
            catch (Exception ex)
            {
                MessageBox.Show("There was a problem printing the machine graph: " + ex.Message, "Error", MessageBoxButton.OK);
            }
        }
    }
}
