using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient; //<<ADDED

namespace CategoryDropListS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
			SqlConnection conn = new SqlConnection(DatabaseInfo.GetConnectionInfo());
            SqlCommand cmd = null;
            SqlDataReader reader = null;
            this.comboBox1.DisplayMember = "displayData";
            this.comboBox1.ValueMember = "valueData";
            //this.comboBox1.DataSource = "dataSet";
            try
            {
				conn.Open();
                cmd = new SqlCommand("SELECT category_id, descr FROM category", conn);
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    comboBox1.Items.Add(new ListItem(reader.GetInt32(0), reader["descr"].ToString()));
                }
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                reader.Close();
                conn.Close();
				comboBox1.SelectedItem = 0;
            }
        }
    }
}
