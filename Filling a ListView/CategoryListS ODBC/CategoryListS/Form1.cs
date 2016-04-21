using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.Odbc;

namespace CategoryListS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //_________________________________________________Column setup
            this.listViewCategory.View = View.Details;
            this.listViewCategory.Columns.Add("Category", 200, HorizontalAlignment.Left);
            //_________________________________________________Fill the list view
            OdbcConnection conn = new OdbcConnection("dsn=dsn_circuit_city");
            string data;
       
            try
            {
                conn.Open();
                string cmd = "SELECT category_id, descr FROM category";

                DataSet dataSet = new DataSet();
                OdbcDataAdapter adapter = new OdbcDataAdapter(cmd, conn);
                adapter.Fill(dataSet);

                if (dataSet.Tables.Count == 0) return;
                DataTable dataTable = dataSet.Tables[0];
                if (dataTable.Rows.Count == 0) return;
                foreach (DataRow dataRow in dataTable.Rows)
                {
                    data = System.Convert.ToString((int)dataRow["category_id"]);
                    this.listViewCategory.Items.Add(data, (string)dataRow["descr"], 0);
                }
            }
            catch (OdbcException ex)
            {
                MessageBox.Show(this, ex.Message, "Error");
                this.Text = ex.Message;
            }
            finally
            {
                conn.Close();
            }
        }
    }
}
