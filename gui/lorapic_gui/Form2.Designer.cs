namespace lorapic_gui
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            textBoxSourceAddress = new TextBox();
            btnSend = new Button();
            richTextBoxOutput = new RichTextBox();
            label1 = new Label();
            groupBox1 = new GroupBox();
            btnGet = new Button();
            label5 = new Label();
            label4 = new Label();
            label3 = new Label();
            label2 = new Label();
            textBoxTxPower = new TextBox();
            textBoxDataRate = new TextBox();
            textBoxFrequency = new TextBox();
            textBoxMacAddress = new TextBox();
            label6 = new Label();
            btnSendDest = new Button();
            textBoxDestinationAddress = new TextBox();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // textBoxSourceAddress
            // 
            textBoxSourceAddress.Location = new Point(164, 52);
            textBoxSourceAddress.Name = "textBoxSourceAddress";
            textBoxSourceAddress.Size = new Size(64, 23);
            textBoxSourceAddress.TabIndex = 0;
            // 
            // btnSend
            // 
            btnSend.Location = new Point(234, 51);
            btnSend.Name = "btnSend";
            btnSend.Size = new Size(57, 24);
            btnSend.TabIndex = 1;
            btnSend.Text = "Send";
            btnSend.UseVisualStyleBackColor = true;
            btnSend.Click += btnSend_Click;
            // 
            // richTextBoxOutput
            // 
            richTextBoxOutput.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            richTextBoxOutput.Location = new Point(12, 342);
            richTextBoxOutput.Name = "richTextBoxOutput";
            richTextBoxOutput.Size = new Size(798, 336);
            richTextBoxOutput.TabIndex = 2;
            richTextBoxOutput.Text = "";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            label1.Location = new Point(43, 54);
            label1.Name = "label1";
            label1.Size = new Size(118, 21);
            label1.TabIndex = 3;
            label1.Text = "Source Address";
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(btnGet);
            groupBox1.Controls.Add(label5);
            groupBox1.Controls.Add(label4);
            groupBox1.Controls.Add(label3);
            groupBox1.Controls.Add(label2);
            groupBox1.Controls.Add(textBoxTxPower);
            groupBox1.Controls.Add(textBoxDataRate);
            groupBox1.Controls.Add(textBoxFrequency);
            groupBox1.Controls.Add(textBoxMacAddress);
            groupBox1.Location = new Point(546, 23);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(227, 235);
            groupBox1.TabIndex = 4;
            groupBox1.TabStop = false;
            groupBox1.Text = "groupBox1";
            // 
            // btnGet
            // 
            btnGet.Location = new Point(137, 195);
            btnGet.Name = "btnGet";
            btnGet.Size = new Size(57, 24);
            btnGet.TabIndex = 8;
            btnGet.Text = "Get";
            btnGet.UseVisualStyleBackColor = true;
            btnGet.Click += btnGet_Click;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(26, 162);
            label5.Name = "label5";
            label5.Size = new Size(56, 15);
            label5.TabIndex = 7;
            label5.Text = "TX Power";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(26, 117);
            label4.Name = "label4";
            label4.Size = new Size(57, 15);
            label4.TabIndex = 6;
            label4.Text = "Data Rate";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(26, 79);
            label3.Name = "label3";
            label3.Size = new Size(62, 15);
            label3.TabIndex = 5;
            label3.Text = "Frequency";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 42);
            label2.Name = "label2";
            label2.Size = new Size(88, 15);
            label2.TabIndex = 4;
            label2.Text = "Source Address";
            // 
            // textBoxTxPower
            // 
            textBoxTxPower.Location = new Point(94, 154);
            textBoxTxPower.Name = "textBoxTxPower";
            textBoxTxPower.Size = new Size(100, 23);
            textBoxTxPower.TabIndex = 3;
            // 
            // textBoxDataRate
            // 
            textBoxDataRate.Location = new Point(94, 114);
            textBoxDataRate.Name = "textBoxDataRate";
            textBoxDataRate.Size = new Size(100, 23);
            textBoxDataRate.TabIndex = 2;
            // 
            // textBoxFrequency
            // 
            textBoxFrequency.Location = new Point(94, 76);
            textBoxFrequency.Name = "textBoxFrequency";
            textBoxFrequency.Size = new Size(100, 23);
            textBoxFrequency.TabIndex = 1;
            // 
            // textBoxMacAddress
            // 
            textBoxMacAddress.Location = new Point(94, 39);
            textBoxMacAddress.Name = "textBoxMacAddress";
            textBoxMacAddress.Size = new Size(100, 23);
            textBoxMacAddress.TabIndex = 0;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            label6.Location = new Point(12, 84);
            label6.Name = "label6";
            label6.Size = new Size(149, 21);
            label6.TabIndex = 7;
            label6.Text = "Destination Address";
            // 
            // btnSendDest
            // 
            btnSendDest.Location = new Point(234, 81);
            btnSendDest.Name = "btnSendDest";
            btnSendDest.Size = new Size(57, 24);
            btnSendDest.TabIndex = 6;
            btnSendDest.Text = "Send";
            btnSendDest.UseVisualStyleBackColor = true;
            btnSendDest.Click += btnSendDest_Click;
            // 
            // textBoxDestinationAddress
            // 
            textBoxDestinationAddress.Location = new Point(164, 82);
            textBoxDestinationAddress.Name = "textBoxDestinationAddress";
            textBoxDestinationAddress.Size = new Size(64, 23);
            textBoxDestinationAddress.TabIndex = 5;
            // 
            // Form2
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(822, 699);
            Controls.Add(label6);
            Controls.Add(btnSendDest);
            Controls.Add(textBoxDestinationAddress);
            Controls.Add(groupBox1);
            Controls.Add(label1);
            Controls.Add(richTextBoxOutput);
            Controls.Add(btnSend);
            Controls.Add(textBoxSourceAddress);
            Name = "Form2";
            Text = "Form2";
            Load += Form2_Load;
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox textBoxSourceAddress;
        private Button btnSend;
        private RichTextBox richTextBoxOutput;
        private Label label1;
        private GroupBox groupBox1;
        private Label label5;
        private Label label4;
        private Label label3;
        private Label label2;
        private TextBox textBoxTxPower;
        private TextBox textBoxDataRate;
        private TextBox textBoxFrequency;
        private TextBox textBoxMacAddress;
        private Label label6;
        private Button btnSendDest;
        private TextBox textBoxDestinationAddress;
        private Button btnGet;
    }
}