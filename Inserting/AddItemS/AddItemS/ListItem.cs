using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AddItemS
{
	public class ListItem
	{
		private int valueData;
		private string displayData;

		public ListItem(int valueData, string displayData)
		{
			this.valueData = valueData;
			this.displayData = displayData;
		}

		public string DisplayData
		{
			get { return displayData; }
		}

		public int ValueData
		{
			get { return valueData; }
		}
	}
}
