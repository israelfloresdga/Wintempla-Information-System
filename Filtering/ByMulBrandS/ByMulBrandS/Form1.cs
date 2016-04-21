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

namespace ByMulBrandS
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Text = "ByMulBrandS";
			cblBrand.CheckBoxes = true;
			cblBrand.View = View.Details;
			cblBrand.Columns.Add("Brand", 150, HorizontalAlignment.Left);
			//cblBrand.HeaderStyle = ColumnHeaderStyle.None; //Oculta la columna

			lvItems.View = View.Details;
			lvItems.Columns.Add("Name", 200, HorizontalAlignment.Left);
			lvItems.Columns.Add("Model", 120, HorizontalAlignment.Left);
			lvItems.Columns.Add("Brand", 120, HorizontalAlignment.Left);
			lvItems.Columns.Add("Category", 150, HorizontalAlignment.Left);
			//
			SqlConnection conn = new SqlConnection(ByMulBrandS.DatabaseInfo.GetConnectionInfo());
			SqlCommand cmd = null;
			SqlDataReader reader = null;
			ListViewItem lvi = null;
			int item_id;
			string[] colCBList = new string[1];
			string[] colLVItems = new string[4];
			//
			try
			{
				conn.Open();
				cmd = new SqlCommand("SELECT brand_id, descr FROM brand", conn);
				reader = cmd.ExecuteReader();
				while (reader.Read())
				{
					item_id = (int)reader["brand_id"];
					colCBList[0] = reader["descr"].ToString();
					lvi = new ListViewItem(colCBList, 0, Color.Black, Color.White, this.Font);
					lvi.Tag = item_id; //Donde se guarda el id
					cblBrand.Items.Add(lvi);
				}
				reader.Close();
				cmd = new SqlCommand("SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item", conn);
				reader = cmd.ExecuteReader();
				while (reader.Read())
				{
					item_id = (int)reader["item_id"];
					colLVItems[0] = reader["item descr"].ToString();
					colLVItems[1] = reader["model"].ToString();
					colLVItems[2] = reader["brand descr"].ToString();
					colLVItems[3] = reader["category descr"].ToString();
					lvi = new ListViewItem(colLVItems, 0, Color.Black, Color.White, this.Font);
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
	
		private string buildSqlQuery()
		{
			int itemCount = cblBrand.Items.Count;
			int count = 0;
			int index;
			string sqlcmd= "";
			for (index=0; index<itemCount; index++)
			{
				if (cblBrand.Items[index].Checked== true) count++;
			}
			if(count==0) return "";
			else
			{
				bool isFirst= true;
				for(index=0; index<itemCount; index++)
				{
					if(cblBrand.Items[index].Checked==true)
					{
						string brand_id = cblBrand.Items[index].Tag.ToString();
						if(isFirst==true)
						{
							isFirst= false;
							sqlcmd= "SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE brand_id= ";
							sqlcmd+= brand_id;
						}
						else
						{
							sqlcmd+= " OR brand_id= ";
							sqlcmd+= brand_id;
						}
					}
				}
			}
			return sqlcmd;
		}

		private void updateItems()
		{
			string query = buildSqlQuery();
			if (query.Length==0)
			{
				lvItems.Items.Clear();
				return;
			}

			SqlConnection conn = new SqlConnection(ByMulBrandS.DatabaseInfo.GetConnectionInfo());
			SqlCommand sqlcmd = null;
			SqlDataReader reader = null;
			ListViewItem lvi = null;
			string[] colText = new string[4];
			int item_id;
			try
			{
				conn.Open();
				lvItems.Items.Clear();
				sqlcmd = new SqlCommand(query, conn);
				reader = sqlcmd.ExecuteReader();
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

		private void cblBrand_ItemChecked(object sender, ItemCheckedEventArgs e)
		{
			updateItems();
		}

	}
}
