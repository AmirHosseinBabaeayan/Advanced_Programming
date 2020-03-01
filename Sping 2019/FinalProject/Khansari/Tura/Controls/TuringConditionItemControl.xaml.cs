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
    /// Interaction logic for TuringConditionItemControl.xaml
    /// </summary>
    public partial class TuringConditionItemControl : UserControl
    {
        public TuringCondition ContainingCondition;
        public TuringConditionItemControl(TuringCondition condition)
        {
            InitializeComponent();
            ContainingCondition = condition;
            InitializeControl();
        }

        void InitializeControl()
        {
            ConditionTextBox.Text = ContainingCondition.Condition.ToString();
            ReplacingConditionTextBox.Text = ContainingCondition.ReplaceBy.ToString();
            TransitionComboBox.SelectedIndex = (int)ContainingCondition.To;

        }

        private void ReplacingConditionTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ReplacingConditionTextBox.Text != "")
            ContainingCondition.ReplaceBy = ReplacingConditionTextBox.Text[0];
        }

        private void ConditionTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ConditionTextBox.Text != "")
                ContainingCondition.Condition = ConditionTextBox.Text[0];
            else
                ContainingCondition.Condition = '\0';
        }

        private void TransitionComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ContainingCondition.To = (Transition)TransitionComboBox.SelectedIndex;
        }
    }
}
