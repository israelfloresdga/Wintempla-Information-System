using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace AddItemS
{
	public partial class AddItemSDlg : Form
	{
		public AddItemSDlg()
		{
			InitializeComponent();
		}

		private void AddItemSDlg_Load(object sender, EventArgs e)
		{
			Text = "Insert";
			//____________________________________________________Fill the category ddlist and the brand ddlist
			SqlConnection conn = new SqlConnection(DatabaseInfo.GetConnectionInfo());
			SqlCommand cmd = null;
			SqlDataReader reader = null;
			this.ddBrand.DisplayMember = "displayData";
			this.ddBrand.ValueMember = "valueData";
			this.ddCategory.DisplayMember = "displayData";
			this.ddCategory.ValueMember = "valueData";
			//this.comboBox1.DataSource = "dataSet";
			try
			{
				conn.Open();
				cmd = new SqlCommand("SELECT brand_id, descr FROM brand", conn);
				reader = cmd.ExecuteReader();
				while (reader.Read())
				{
					ddBrand.Items.Add(new ListItem(reader.GetInt32(0), reader["descr"].ToString()));
				}
				reader.Close();
				cmd = new SqlCommand("SELECT category_id, descr FROM category", conn);
				reader = cmd.ExecuteReader();
				while (reader.Read())
				{
					ddCategory.Items.Add(new ListItem(reader.GetInt32(0), reader["descr"].ToString()));
				}
				ddBrand.SelectedIndex = 0;
				ddCategory.SelectedIndex = 0;
			}
			catch (SqlException ex)
			{
				MessageBox.Show(ex.Message);
			}
			finally
			{
				reader.Close();
				conn.Close();
			}
		}

		private void buttonOk_Click(object sender, EventArgs e)
		{
			if (ddBrand.Items.Count == 0 | ddCategory.Items.Count==0) return;
			if (ddCategory.SelectedIndex < 0 | ddBrand.SelectedIndex < 0) return;
			int selectedIndexBrand = (int)ddBrand.SelectedIndex;
			int selectedIndexCategory = (int)ddCategory.SelectedIndex;
			//________________________________________Extract
			int brand_id = (int)ddBrand.SelectedIndex;
			int category_id = (int)ddCategory.SelectedIndex;
			string name= tbxName.Text;
			string model= tbxModel.Text;
			//________________________________________Validate (you may use regular expressions)
			if(name.Length<=2)
			{
				MessageBox.Show("ERROR","The item name must containt at least three characters");
				return;
			}
			if(model.Length<=2)
			{
				MessageBox.Show("ERROR","The item model must containt at least three characters");
				return;
			}
			string sqlcmd;
			sqlcmd = "INSERT INTO item (descr, model, brand_id, category_id) VALUES('";
			sqlcmd += name;
			sqlcmd += "','";
			sqlcmd += model;
			sqlcmd += "',";
			sqlcmd += brand_id.ToString();
			sqlcmd += ",";
			sqlcmd += category_id.ToString();
			sqlcmd += ")";
			//_________________________________________Insert
			SqlConnection conn = new SqlConnection(AddItemS.DatabaseInfo.GetConnectionInfo());
			SqlCommand cmd = null;
			int rows = 0;
			try
			{
				conn.Open();
				cmd = new SqlCommand(sqlcmd, conn);
				rows = cmd.ExecuteNonQuery();
				if (rows!=1)
				{
					MessageBox.Show(this, "Error: inserted rows");
				}
			}
			catch (SqlException ex)
			{
				MessageBox.Show(this,ex.Message,"ERROR");
			}
			//*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~++/
			finally
			{
				this.Close();
			}
		}

		private void buttonCancel_Click(object sender, EventArgs e)
		{
			this.Close();
		}
	}
}
