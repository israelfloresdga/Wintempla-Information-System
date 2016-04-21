using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CalcSharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonCalculate_Click(object sender, EventArgs e)
        {
            double x = Convert.ToDouble(this.textBoxX.Text);
            double y = Convert.ToDouble(this.textBoxY.Text);
            double result = x + y;
            this.textBoxResult.Text = result.ToString();
        }
    }
}
