using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data; //ADDED
using System.Data.SqlClient; //ADDED

namespace CategoryDropListWebS
{
    public partial class index : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            SqlConnection conn = new SqlConnection("server=ISRAELLSMT_M\\SQLExpress;database=circuit_city;Trusted_Connection=yes");
            SqlCommand cmd = null;

            try
            {
                conn.Open();
                cmd = new SqlCommand("SELECT category_id, descr FROM category", conn);
                DataSet dataSet = new DataSet();
                SqlDataAdapter dataAdapter = new SqlDataAdapter(cmd);
                dataAdapter.Fill(dataSet);
                this.DropDownList1.DataSource = dataSet;
                this.DropDownList1.DataValueField = "category_id";
                this.DropDownList1.DataTextField = "descr";
                this.DropDownList1.DataBind();
            }
            catch (SqlException ex)
            {
                //this.LabelError.Text= ex.Mesagge;
            }
            finally
            {
                conn.Close();
            }
        }
    }
}