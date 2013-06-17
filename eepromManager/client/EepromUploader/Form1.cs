using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace EepromUploader
{
    public partial class Form1 : Form
    {
        private string buffer;
        Boolean hasData = false;
        long ackCount = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            serialPort1.Open();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            buffer = serialPort1.ReadExisting();
            Debug.Write(buffer );
            hasData = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Write(textBox2.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            const int length = 32768;

            byte[] databuffer  = new byte[length];
            byte[] datasize = new byte[2];
            datasize[0] = 0x80;
            datasize[1] = 0x00;

            FileStream stream = new FileStream("C:\\Users\\chris.feltman\\Music\\Jealous Hearted Man.raw", FileMode.Open);


            for (int i = 0; i < length; i++)
            {
                databuffer[i] = (byte)stream.ReadByte();
            }
            stream.Close();

            // test upload
            buffer = "";
            // send size, wait for initial ACK
            serialPort1.Write(datasize, 0, 2);

            for (int i = 0; i < length; i++)
            {
                serialPort1.Write(databuffer, i, 1);
                Application.DoEvents();
            }

            // done

        }
    }
}
