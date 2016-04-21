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

namespace DeleteItemS
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Text = "DeleteItemS";
		
			lvItems.View = View.Details;
			lvItems.FullRowSelect = true;
			lvItems.GridLines = true;
			lvItems.HideSelection = false;

			lvItems.Columns.Add("Name", 200, HorizontalAlignment.Left);
			lvItems.Columns.Add("Model", 120, HorizontalAlignment.Left);
			lvItems.Columns.Add("Brand", 120, HorizontalAlignment.Left);
			lvItems.Columns.Add("Category", 150, HorizontalAlignment.Left);
			//
			fillListView();
			button_delete.Enabled = false;
		}


		private void deleteItem()
		{
			int count = lvItems.Items.Count;
			string sqlcmd = null;
			string item_id= null;
			bool isFirst = true;
			for (int i = 0; i < count; i++)
			{
				if (lvItems.Items[i].Selected == true)
				{
					item_id = lvItems.Items[i].Tag.ToString();
					if (isFirst==true)//
					{
						isFirst = false;//
						sqlcmd = "DELETE FROM item WHERE item_id=";
						sqlcmd += item_id;
						//break;
					}
					else//
					{
						sqlcmd += "OR item_id=";
						sqlcmd += item_id;
					}
				}
			}
			if (sqlcmd == null) return;

			SqlConnection conn = new SqlConnection(DeleteItemS.DatabaseInfo.GetConnectionInfo());
			SqlCommand cmd = null;
			int rows = 0;
			try
			{
				conn.Open();
				cmd = new SqlCommand(sqlcmd, conn);
				rows = cmd.ExecuteNonQuery();
			}
			catch (SqlException ex)
			{
				MessageBox.Show(this,ex.Message,"ERROR");
			}
			finally
			{
				fillListView();
			}
		}

		private void lvItems_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
		{
			this.button_delete.Enabled = false;
			if (lvItems.SelectedIndices.Count > 0)
				this.button_delete.Enabled = true;
			else
				this.button_delete.Enabled = false;
		}

		private void buttonDelete_Click(object sender, EventArgs e)
		{
			this.button_delete.Enabled = false;
			//____________________________________________Ask the user for confirmation
			if(MessageBox.Show(this, "Are you sure you want to delete the item(s)", "Delete Item(s)",
				MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button1)!=DialogResult.Yes) return;

			deleteItem();
		}

		private void fillListView()
		{
			SqlConnection conn = new SqlConnection(DeleteItemS.DatabaseInfo.GetConnectionInfo());
			SqlDataReader reader = null;
			SqlCommand cmd = null;
			ListViewItem lvi = null;
			string[] colText = new string[4];
			int item_id;
			try
			{
				lvItems.Items.Clear();
				conn.Open();
				string sqlcmd = "SELECT item_id,  [item descr], model, [brand descr], [category descr] FROM vw_Item";
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
