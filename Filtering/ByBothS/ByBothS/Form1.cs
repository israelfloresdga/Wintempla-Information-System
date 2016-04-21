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

namespace ByBothS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
			Text = "ByBothS";
			cb_Category.DropDownStyle = ComboBoxStyle.DropDownList;
			cb_Brand.DropDownStyle = ComboBoxStyle.DropDownList;
			lvItems.View = View.Details;

			lvItems.Columns.Add("Name", 150, HorizontalAlignment.Left);
			lvItems.Columns.Add("Model", 200, HorizontalAlignment.Left);
			lvItems.Columns.Add("Brand", 100, HorizontalAlignment.Left);
			lvItems.Columns.Add("Category", 150, HorizontalAlignment.Left);
			//
			SqlConnection conn = new SqlConnection(ByBothS.DatabaseInfo.GetConnectionInfo());
			SqlCommand cmd = null;
			SqlDataReader reader = null;
            cb_Category.DisplayMember = "displayData";
            cb_Category.ValueMember = "valueData";
            cb_Brand.DisplayMember = "displayData";
            cb_Brand.ValueMember = "valueData";
            //this.comboBox1.DataSource = "dataSet";

            try
            {
                /*cb Category*/
                conn.Open();
                cmd = new SqlCommand("SELECT category_id, descr FROM category", conn);
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    cb_Category.Items.Add(new ListItems(reader.GetInt32(0), reader["descr"].ToString()));
                }
                /*cb Brand*/
                //conn.Close();
                //conn.Open();
                reader.Close();
                cmd = new SqlCommand("SELECT brand_id, descr FROM brand", conn);
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    cb_Brand.Items.Add(new ListItems(reader.GetInt32(0), reader["descr"].ToString()));
                }
                cb_Category.SelectedIndex = 0;
                cb_Brand.SelectedIndex = 0;
                updateItems();
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
            finally
            {
                reader.Close();
                conn.Close();
				cb_Category.SelectedIndex = 0;
				cb_Brand.SelectedIndex = 0;
				updateItems();
            }
        }

        private void cb_Category_SelectedIndexChanged(object sender, EventArgs e)
        {
            updateItems();
        }

        private void cb_Brand_SelectedIndexChanged(object sender, EventArgs e)
        {
            updateItems();
        }

        private void updateItems()
        {
            if (cb_Brand.Items.Count == 0 | cb_Category.Items.Count == 0) return;
			if (cb_Category.SelectedIndex < 0 | cb_Brand.SelectedIndex < 0) return;
			int selectedIndex_Category = (int)cb_Category.SelectedIndex;
			int selectedIndex_Brand = (int)cb_Brand.SelectedIndex;
            int category_id = ((ListItems)cb_Category.Items[selectedIndex_Category]).ValueData;
			int brand_id = ((ListItems)cb_Brand.Items[selectedIndex_Brand]).ValueData;

			string sqlcmd = "SELECT item_id,  [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE category_id= ";
            sqlcmd += category_id.ToString();
			sqlcmd += " AND brand_id=";
			sqlcmd += brand_id.ToString();

			SqlConnection conn = new SqlConnection(ByBothS.DatabaseInfo.GetConnectionInfo());
			SqlDataReader reader = null;
			SqlCommand cmd = null;
			ListViewItem lvi = null;
			string[] colText = new string[4];
			int item_id;
			try
			{
				lvItems.Items.Clear();
				conn.Open();
				cmd = new SqlCommand(sqlcmd, conn);
				reader = cmd.ExecuteReader();
				while (reader.Read())
				{
					item_id = (int)reader["item_id"];
					colText[0] = reader["item descr"].ToString();
					colText[1] = reader["model"].ToString();
					colText[2] = reader["brand descr"].ToString();
					colText[3] = reader["category descr"].ToString();
					lvi = new ListViewItem(colText, 0, Color.Black, Color.White, this.Font);
					lvi.Tag = item_id; //Donde se guarda el id
					lvItems.Items.Add(lvi);
				}
			}
            catch (SqlException ex)
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
