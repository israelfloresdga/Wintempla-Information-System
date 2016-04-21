using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;	//ADDED LINE

namespace ByCategoryS
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Text = "ByCategoryS";
			ddCategory.DropDownStyle = ComboBoxStyle.DropDownList;
			lvItems.View = View.Details;
			//
			lvItems.Columns.Add("Name",150, HorizontalAlignment.Left);
			lvItems.Columns.Add("Model", 200, HorizontalAlignment.Left);
			lvItems.Columns.Add("Brand", 100, HorizontalAlignment.Left);
			lvItems.Columns.Add("Category", 100, HorizontalAlignment.Left);
			//
			SqlConnection conn= new SqlConnection(ByCategoryS.DatabaseInfo.GetConnectionInfo());
			SqlCommand cmd= null;
			SqlDataReader reader= null;
			ddCategory.DisplayMember= "displayData";
			ddCategory.ValueMember= "valueData";
			try
			{
				conn.Open();
				cmd = new SqlCommand("SELECT category_id, descr FROM category", conn);
				reader = cmd.ExecuteReader();
				while (reader.Read())
				{
					ddCategory.Items.Add(new ListItem(reader.GetInt32(0), reader["descr"].ToString()));
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
				ddCategory.SelectedIndex = 0;
				updateItems();
			}
		}

		private void ddCategory_SelectedIndexChanged(object sender, EventArgs e)
		{
			updateItems();
		}

		private void updateItems()
		{
			if (ddCategory.Items.Count == 0) return;
			int selectedIndex = (int)ddCategory.SelectedIndex;
			if (selectedIndex < 0) return;
			int category_id = ((ListItem)ddCategory.Items[selectedIndex]).ValueData;

			string sqlcmd = "SELECT item_id,  [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE category_id= ";
			sqlcmd += category_id.ToString();
			SqlConnection conn = new SqlConnection(ByCategoryS.DatabaseInfo.GetConnectionInfo());
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
					//ddCategory.Items.Add(new ListItem(reader.GetInt32(0), reader["descr"].ToString()));
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
			}
		}
	}
}
