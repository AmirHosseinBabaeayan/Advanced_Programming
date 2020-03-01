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
using Tura.Util;

namespace Tura
{
    /// <summary>
    /// Interaction logic for SettingsWindow.xaml
    /// </summary>
    public partial class SettingsWindow : Window
    {
        bool ignoretextchange = false;
        public SettingsWindow()
        {
            InitializeComponent();
            RetrieveSettings();
        }

        void RetrieveSettings()
        {
            if (Properties.Settings.Default.ForeColor == "White")
                DarkThemeRadioButton.IsChecked = true;
            else
                LightThemeRadioButton.IsChecked = true;

            if (Properties.Settings.Default.Activated)
            {
                ActivationKeyTextBox.IsEnabled = false;
                ActivationKeyTextBox.Text = Properties.Settings.Default.ActivationKey;
                ActivateButton.IsEnabled = false;
            }
            else
            {
                ActivationKeyTextBox.IsEnabled = true;
                ActivateButton.IsEnabled = true;
            }
        }

        private void DarkThemeRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            SetDarkTheme();
        }

        void SetDarkTheme()
        {
            Properties.Settings.Default.ForeColor = "White";
            Properties.Settings.Default.BackColor = "Black";
            Properties.Settings.Default.Accent = "Gray";
        }

        private void LightThemeRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            SetLightTheme();
        }

        void SetLightTheme()
        {
            Properties.Settings.Default.ForeColor = "Black";
            Properties.Settings.Default.BackColor = "White";
            Properties.Settings.Default.Accent = "#f0f0f0";
        }

        protected override void OnClosed(EventArgs e)
        {
            Properties.Settings.Default.Save();
            base.OnClosed(e);
        }

        private void ActivationKeyTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ignoretextchange)
                return;
            ignoretextchange = true;
            int cur = ActivationKeyTextBox.SelectionStart;
            string key = ActivationKeyTextBox.Text;
            while (key.Contains('-'))
                key = key.Replace("-", "");

            key = key.ToUpper();
            for (int i = 4; i < key.Length; i+=5)
            {
                key = key.Insert(i, "-");
                cur++;
            }
            ActivationKeyTextBox.Text = key;
            ActivationKeyTextBox.SelectionStart = cur;
            ignoretextchange = false;
        }

        private void ActivateButton_Click(object sender, RoutedEventArgs e)
        {
            string key = ActivationKeyTextBox.Text;
            while (key.Contains('-'))
                key = key.Replace("-", "");
            TryActivateProgram(key);
        }

        public async void TryActivateProgram(string key)
        {
            ActivateButton.Dispatcher.Invoke(() =>
            {
                ActivateButton.IsEnabled = false;
                ActivationKeyTextBox.IsEnabled = false;
            });
            if (await ActivationManager.Activate(key))
            {
                ActivateButton.Dispatcher.Invoke(() =>
                {
                    Properties.Settings.Default.Activated = true;
                    Properties.Settings.Default.ActivationKey = key;
                    Properties.Settings.Default.Save();
                });

                MessageBox.Show("The program activated successfully.", "Success", MessageBoxButton.OK, MessageBoxImage.None);
            }
            else
            {
                MessageBox.Show("The activation key is not valid.", "Activation error", MessageBoxButton.OK, MessageBoxImage.Asterisk);
                ActivateButton.IsEnabled = true;
                ActivationKeyTextBox.IsEnabled = true;
            }
            RetrieveSettings();
        }
    }
}
