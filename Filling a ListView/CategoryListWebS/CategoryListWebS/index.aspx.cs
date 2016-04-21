using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CategoryListWebS
{
    public partial class index : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            System.Data.SqlClient.SqlConnection conn =
                new System.Data.SqlClient.SqlConnection(DatabaseInfo.GetConnectionInfo());
            System.Data.SqlClient.SqlCommand cmd = null;

            try
            {
                conn.Open();
                cmd = new System.Data.SqlClient.SqlCommand("SELECT category_id, descr FROM category", conn);
                System.Data.DataSet dataSet = new System.Data.DataSet();
                System.Data.SqlClient.SqlDataAdapter daUser = new System.Data.SqlClient.SqlDataAdapter(cmd);
                daUser.Fill(dataSet);
                this.GridView1.DataSource = dataSet;
                this.GridView1.AutoGenerateColumns = true;
                this.GridView1.DataBind();
            }
            catch (System.Data.SqlClient.SqlException ex)
            {
                //this.LabelError.Text= ex.Messsage;
            }
            finally
            {
                conn.Close();
            }
        }
    }
}