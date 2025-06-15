using System;
using System.IO.Ports;
using System.Windows.Forms;
using static System.Windows.Forms.DataFormats;

namespace lorapic_gui
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (comboBoxComPorts.SelectedItem != null)
            {
                string selectedPort = comboBoxComPorts.SelectedItem.ToString();
                Form2 form2 = new Form2(selectedPort);
                this.Hide();
                form2.ShowDialog();
                this.Close();
            }
            else
            {
                MessageBox.Show("Please select a COM port first.");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            comboBoxComPorts.Items.AddRange(ports);

        }
    }
}