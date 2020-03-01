using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Tura
{
    /// <summary>
    /// Interaction logic for Intro.xaml
    /// </summary>
    public partial class Intro : Window
    {
        Timer t = new Timer();
        public Intro()
        {
            InitializeComponent();
            t.Elapsed += T_Elapsed;
            t.Interval = 3500;
            t.Start();
        }

        private void T_Elapsed(object sender, ElapsedEventArgs e)
        {
            this.Dispatcher.Invoke(() =>
            {

                this.Hide();
                t.Stop();
                MainWindow main = new MainWindow();
                main.Focus();
                main.ShowDialog();
                this.Close();
            });
          
        }

        private void T_Disposed(object sender, EventArgs e)
        {
           
        }
    }
}
