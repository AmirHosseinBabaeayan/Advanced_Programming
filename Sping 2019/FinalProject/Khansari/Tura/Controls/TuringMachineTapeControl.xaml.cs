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
using Tura.Controls;

namespace Tura.Controls
{
    /// <summary>
    /// Interaction logic for TuringMachineTapeControl.xaml
    /// </summary>
    public partial class TuringMachineTapeControl : UserControl
    {
        int CellsOffset;
        string InputString;
        public TuringMachineTapeControl(string input)
        {
            InitializeComponent();
            
            InputString = input;
            DrawCells(CellsOffset);
        }

        protected override void OnRender(DrawingContext drawingContext)
        {
            double CellWidth = (this.ActualHeight - 41);
            CellsOffset = (int)(this.ActualWidth / CellWidth / 2) + 1;
        }
        public void ChangeInput(string input)
        {
            
            InputString = input;
            DrawCells(CellsOffset);
        }

        void DrawCells(int offset)
        {
            double CellWidth = (this.ActualHeight - 41);
            CellsPanel.Children.Clear();

            for (int i = 0; i < offset; i++)
                CellsPanel.Children.Add(new TuringTapeCellControl('#') { Height = CellWidth, Width = CellWidth });

            foreach (char c in InputString)
            {
                CellsPanel.Children.Add(new TuringTapeCellControl(c) {Height = CellWidth, Width = CellWidth });
                
            }

            for (int i = 0; i < offset; i++)
                CellsPanel.Children.Add(new TuringTapeCellControl('#') { Height = CellWidth, Width = CellWidth });
        }

        private void UserControl_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            DrawCells(CellsOffset);
        }

        public async Task ScrollToItem(int index, bool animate)
        {
            double CellWidth = (this.ActualHeight - 43);


            if (CellsScrolViewer.ScrollableWidth < index * CellWidth)
            {
                CellsOffset++;
                DrawCells(CellsOffset);
            }

            if (!animate)
            {
                CellsScrolViewer.ScrollToHorizontalOffset(index * CellWidth + CellWidth / 2 + 10);
                return;
            }

            if (CellsScrolViewer.HorizontalOffset < index * CellWidth + CellWidth / 2)
            {
                for (double i = CellsScrolViewer.HorizontalOffset; i <= index * CellWidth + CellWidth / 2 + 10; i+=5)
                {
                    CellsScrolViewer.ScrollToHorizontalOffset(i);
                    await Task.Delay(15);
                }
            }
            else
            {
                for (double i = CellsScrolViewer.HorizontalOffset; i >= index * CellWidth + CellWidth / 2 + 10; i -= 5)
                {
                    CellsScrolViewer.ScrollToHorizontalOffset(i);
                    await Task.Delay(5);
                }
            }
        }
    }
}
