using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ByBothS
{
	class DatabaseInfo
	{
		public static string GetConnectionInfo()
		{
			return "server=ISRAELLSMT_M\\SQLEXPRESS;database=circuit_city;Trusted_Connection=yes";
		}
	}
}
