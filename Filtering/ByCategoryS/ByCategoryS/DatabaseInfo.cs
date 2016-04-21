using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ByCategoryS
{
	class DatabaseInfo
	{
		public static string GetConnectionInfo()
		{
			return "server=ISRAELLSMT_M\\SQLEXPRESS;database=circuit_city;Trusted_Connection=yes";
			//Data Source=ISRAELLSMT_M\SQLEXPRESS;Initial Catalog=circuit_city;Integrated Security=True
		}
	}
}
