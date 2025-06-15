using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lorapic_gui
{
    public partial class Form2 : Form
    {
        private const int MinAddress = 1;
        private const int MaxAddress = 254;
        private const int ResponseDelay = 100;  // Adjust this delay as needed

        private SerialPort _serialPort;
        private Queue<string> _responseQueue = new Queue<string>();
        public string SelectedPort { get; private set; }

        public Form2(string port)
        {
            InitializeComponent();
            SelectedPort = port;

            _serialPort = new SerialPort(SelectedPort, 9600);  // Adjust the baud rate as needed
            _serialPort.DataReceived += SerialPort_DataReceived;
            _serialPort.Open();

        }

        private void AppendText(string text)
        {
            richTextBoxOutput.AppendText(text);
            richTextBoxOutput.SelectionStart = richTextBoxOutput.Text.Length;
            richTextBoxOutput.ScrollToCaret();  // Scrolls the content to the caret position
        }


        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string response = _serialPort.ReadExisting();
            Invoke(new Action(() =>
            {
                AppendText($"Received: {response}\n");
                _responseQueue.Enqueue(response.Trim());
            }));
        }

        private async void Form2_Load(object sender, EventArgs e)
        {
            await PopulateInfo();
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (_serialPort != null && _serialPort.IsOpen)
            {
                _serialPort.Close();
            }
        }

        private async Task<string> WaitForResponse(string expectedPrefix)
        {
            string response = string.Empty;
            while (true)  // Continue indefinitely until a valid response is received
            {
                while (_responseQueue.Count == 0)
                {
                    await Task.Delay(10);  // Adjust this delay as needed
                }
                response = _responseQueue.Dequeue();
                if (response.StartsWith(expectedPrefix))
                {
                    break;  // Exit the loop if the response starts with the expected prefix
                }
            }
            return response;
        }

        private async void btnSend_Click(object sender, EventArgs e)
        {
            string sourceAddressText = textBoxSourceAddress.Text;
            if (string.IsNullOrEmpty(sourceAddressText))
            {
                AppendText("Please enter a source address.\n");
                return;
            }

            if (!int.TryParse(sourceAddressText, out int address) || address < 1 || address > 254)
            {
                AppendText("Invalid source address. Please enter a numeric value between 1 and 254.\n");
                return;
            }

            string commandToSend = $"set mac_address {address}";
            _serialPort.WriteLine(commandToSend);
            AppendText($"Sent: {commandToSend}\n");

            // Wait for the "Done" or "Error" response
            string acknowledgment = await WaitForResponse("Done");
            AppendText($"Acknowledgment: {acknowledgment}\n");

            if (acknowledgment == "Done")
            {
                // If acknowledgment is "Done", you can proceed to send the next command or update the UI
                // For example, you could call UpdateInfo() here if needed
                // await UpdateInfo();
            }
            else if (acknowledgment == "Error")
            {
                // Handle error acknowledgment if needed
            }

            await PopulateInfo();
        }


        private async void btnSendDest_Click(object sender, EventArgs e)
        {
            string destinationAddressText = textBoxDestinationAddress.Text;
            if (string.IsNullOrEmpty(destinationAddressText))
            {
                AppendText("Please enter a destination address.\n");
                return;
            }

            if (!int.TryParse(destinationAddressText, out int address) || address < 1 || address > 254)
            {
                AppendText("Invalid destination address. Please enter a numeric value between 1 and 254.\n");
                return;
            }

            string commandToSend = $"set dest_address {address}";
            _serialPort.WriteLine(commandToSend);
            AppendText($"Sent: {commandToSend}\n");

            await PopulateInfo();

        }

        private async void btnGet_Click(object sender, EventArgs e)
        {
            await PopulateInfo();
        }

        private async Task PopulateInfo()
        {
            string[] commands = { "get mac_address", "get frequency", "get data_rate", "get tx_power" };
            string[] expectedPrefixes = { "MAC Address:", "Frequency:", "Data Rate:", "TX Power:" };
            TextBox[] textBoxes = { textBoxMacAddress, textBoxFrequency, textBoxDataRate, textBoxTxPower };

            for (int i = 0; i < commands.Length; i++)
            {
                _serialPort.WriteLine(commands[i]);
                await Task.Delay(ResponseDelay);

                // Wait for the data response
                string response = await WaitForResponse(expectedPrefixes[i]);
                if (response.StartsWith(expectedPrefixes[i]))
                {
                    string value = response.Split(':').LastOrDefault()?.Trim();
                    textBoxes[i].Text = value;
                }
                else
                {
                    AppendText($"Unexpected response for {commands[i]}: {response}\n");
                }
            }
        }


    }
}
