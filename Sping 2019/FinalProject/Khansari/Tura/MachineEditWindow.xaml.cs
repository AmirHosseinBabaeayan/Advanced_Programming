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
using Tura.Util;
using System.Collections.Concurrent;
namespace Tura
{
    /// <summary>
    /// Interaction logic for MachineEditWindow.xaml
    /// </summary>
    public partial class MachineEditWindow : Window
    {
        bool ConnectionRequested = false;
        Vertex ConnectionRequestSource;
        public DFAMachine ContainingMachine;
        ConcurrentQueue<string> NotificationsQueue = new ConcurrentQueue<string>();
        public MachineEditWindow(DFAMachine containingmachine)
        {

            InitializeComponent();
            ContainingMachine = containingmachine;
            Title = "Edit machine: " + containingmachine.Name;
            Task.Run(NotificationChangeLoop);
            InvalidateMachineGraph();
        }

        void SetNotificationText(string text)
        {
            NotificationsQueue.Enqueue(text);
        }

        async void NotificationChangeLoop()
        {
            string currentnotif = "";
            while (true)
            {
                if (NotificationsQueue.TryDequeue(out currentnotif))
                {
                    NotifText.Dispatcher.Invoke(() =>
                    {
                        NotifText.Text = currentnotif;
                    });
                }
                else
                {
                    NotifText.Dispatcher.Invoke(() =>
                    {
                        NotifText.Text = "";
                    });
                }
                await Task.Delay(1000);
            }
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            ContainingMachine.Vertices.Add(new Vertex("V", new Point(20, 20)));
            InvalidateMachineGraph();
        }

        void InvalidateMachineGraph()
        {
            GraphGrid.Children.Clear();


            foreach (Edge<char> E in ContainingMachine.Edges)
            {
                EdgeControl EC = new EdgeControl(E);
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


        private void EdgeControl_RemoveEdge(object sender, Edge<char> e)
        {
            ContainingMachine.Edges.Remove(e);
            InvalidateMachineGraph();
        }

        private void Vc_MouseDown(object sender, MouseButtonEventArgs e)
        {
            VertexControl control = sender as VertexControl;
            if (ConnectionRequested)
            {
                if (ContainingMachine.Edges.Contains(new Edge<char>(ConnectionRequestSource, control.ContainingVertex, 'c'), new EdgeComparer<char>()))
                {
                    MessageBox.Show("Edge is already added", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    ConnectionRequested = false;
                    return;
                }
                ContainingMachine.Edges.Add(new Edge<char>(ConnectionRequestSource, control.ContainingVertex, 'c'));
                ConnectionRequested = false;
                InvalidateMachineGraph();
            }

        }

        private void Vc_ConnectRequest(object sender, Vertex e)
        {
            ConnectionRequested = true;
            ConnectionRequestSource = e;
        }

        private void StartMachineButton_Click(object sender, RoutedEventArgs e)
        {
            string input = InputTextBox.Text;
            if (InputTextBox.Text == "")
            {
                MessageBox.Show("No input is given to the machine.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            DFAMachineBroker broker = new DFAMachineBroker(ContainingMachine);
            try
            {
                broker.InitializeMachine();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return;
            }
            Vertex TempVertex = null;
            for (int i = 0; i < input.Length; i++)
            {
                try
                {
                    TempVertex = broker.Step(input[i], TempVertex);
                    if (TempVertex == null)
                    {
                        SetNotificationText("Cursor stopped on condition " + input[i]);
                        return;
                    }

                    input = TempVertex.RunVertex(input);
                    SetNotificationText("Cursor Went to " + TempVertex.Name);
                }
                catch (Exception ex)
                {
                    SetNotificationText("Error: " + ex.Message);
                    return;
                }
            }
            if (!TempVertex.IsFinishState)
                SetNotificationText("INPUT NOT ACCEPTED");

            else
                SetNotificationText("INPUT ACCEPTED");
        }

        private void OpenMachineMenuItem_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.OpenFileDialog dlg = new System.Windows.Forms.OpenFileDialog();
            dlg.DefaultExt = "dmf";
            dlg.Filter = "DFA machine file | *.dmf";
            try
            {
                if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    ContainingMachine = FileDAL.LoadDFAMachine(dlg.FileName);

                InvalidateMachineGraph();
            }
            catch
            {
                System.Windows.MessageBox.Show("There was a problem loading the machine. machine file may be corrupted.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void SaveMachineMenuItem_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.MenuItem item = sender as System.Windows.Controls.MenuItem;

            System.Windows.Forms.SaveFileDialog dlg = new System.Windows.Forms.SaveFileDialog();
            dlg.DefaultExt = "dmf";
            dlg.Filter = "DFA machine file | *.dmf";
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                FileDAL.SaveDFAMachine(ContainingMachine, dlg.FileName);
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

                ImportedMachine = FileDAL.LoadDFAMachine(dlg.FileName);

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

        private void QuickRunButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                SetNotificationText("Result: " + ContainingMachine.Run(InputTextBox.Text));
            } 
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void MultiInputRunButton_Click(object sender, RoutedEventArgs e)
        {
            MultiInputWindow multiInput = new MultiInputWindow(ContainingMachine);
            multiInput.ShowDialog();
        }

        public void PrintMachineMenuItem_Click(object sender, RoutedEventArgs e)
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