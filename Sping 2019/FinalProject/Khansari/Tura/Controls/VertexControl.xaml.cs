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
    /// Interaction logic for VertexControl.xaml
    /// </summary>
    public partial class VertexControl : UserControl
    {
        public event EventHandler<Vertex> RemoveVertex;
        public event EventHandler<Vertex> ConnectRequest;
        bool Dragging = false;
        Point MouseLastPosition = new Point();
        public Vertex ContainingVertex;
        public VertexControl(Vertex containingvertex)
        {
            InitializeComponent();
            ContainingVertex = containingvertex;
            ContainingVertex.Activated += ContainingVertex_InvokeActivation;
            InitializeVertexControl();
        }

        private void ContainingVertex_InvokeActivation(object sender, EventArgs e)
        {
            ActivateControl();
        }

        public async void ActivateControl()
        {
            for (int i = 210; i > 0; i-=20)
            {
                MainEllipse.Dispatcher.Invoke(() =>
                {
                    MainEllipse.Fill = new SolidColorBrush(Color.FromRgb((byte)i, (byte)i, (byte)i));
                });
                await Task.Delay(1);
            }
            for (int i = 0; i < 210; i += 20)
            {
                MainEllipse.Dispatcher.Invoke(() =>
                {
                    MainEllipse.Fill = new SolidColorBrush(Color.FromRgb((byte)i, (byte)i, (byte)i));
                });
                await Task.Delay(1);
            }
        }

        void InitializeVertexControl()
        {
            
            MouseDown += VertexControl_MouseDown;
            MouseUp += VertexControl_MouseUp;
            MouseMove += VertexControl_MouseMove;
            InvalidateVertexControl();
        }

        void InvalidateVertexControl()
        {
            if (ContainingVertex.IsFinishState)
                FinishStateVisual.Visibility = Visibility.Visible;
            else
                FinishStateVisual.Visibility = Visibility.Collapsed;

            if (ContainingVertex.IsStartState)
            {
                StartStateVisual.Visibility = Visibility.Visible;
                FinishStateVisual.Visibility = Visibility.Visible;
            }
            else
            {
                StartStateVisual.Visibility = Visibility.Collapsed;
            }


            NameTextBlock.Text = ContainingVertex.Name;
            Margin = new Thickness(ContainingVertex.Location.X, ContainingVertex.Location.Y, 0, 0);
        }

        private void VertexControl_MouseMove(object sender, MouseEventArgs e)
        {
            CheckVertexMove();
        }

        private void VertexControl_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Dragging = false;
        }

        private void VertexControl_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MouseLastPosition = Mouse.GetPosition(this);
            Dragging = true;
        }

        private void CheckVertexMove()
        {
            if (Dragging)
            {
                Point p = Mouse.GetPosition(this);
                Margin = new Thickness(Margin.Left + (p.X - MouseLastPosition.X), Margin.Top + (p.Y - MouseLastPosition.Y), Margin.Right, Margin.Bottom);
                ContainingVertex.Location = new Point(Margin.Left, Margin.Top);
            }
        }

        private void ConnectTo_Click(object sender, RoutedEventArgs e)
        {
            ConnectRequest.Invoke(this, ContainingVertex);
        }

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            if (RemoveVertex != null)
                RemoveVertex.Invoke(this, ContainingVertex);
        }

        private void NameTextBlock_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ClickCount == 2)
            {
                NameTextBox.Visibility = Visibility.Visible;
                NameTextBox.Focus();
                e.Handled = true;
            }
        }

        private void NameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            ContainingVertex.Rename(NameTextBox.Text);
        }

        private void NameTextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            NameTextBox.Visibility = Visibility.Collapsed;
            InvalidateVertexControl();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            NameTextBox.Visibility = Visibility.Visible;
            NameTextBox.Focus();
            e.Handled = true;
        }

        private void MenuItem_Click_2(object sender, RoutedEventArgs e)
        {
            ContainingVertex.IsFinishState = !ContainingVertex.IsFinishState;
            InvalidateVertexControl();
        }

        private void MenuItem_Click_3(object sender, RoutedEventArgs e)
        {
            ContainingVertex.IsStartState = !ContainingVertex.IsStartState;
            InvalidateVertexControl();
        }

        private void MainEllipse_MouseDown(object sender, MouseButtonEventArgs e)
        {
        }
    }
}
