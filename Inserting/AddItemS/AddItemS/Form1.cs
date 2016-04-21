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
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Text = "AddItemS";

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
		}

		private void buttonInsert_Click(object sender, EventArgs e)
		{
			AddItemSDlg dlg= new AddItemSDlg();
			dlg.ShowDialog();
			fillListView();
		}

		private void fillListView()
		{
			SqlConnection conn = new SqlConnection(AddItemS.DatabaseInfo.GetConnectionInfo());
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
