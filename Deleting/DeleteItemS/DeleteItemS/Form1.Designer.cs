namespace DeleteItemS
{
	partial class Form1
	{
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		/// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Código generado por el Diseñador de Windows Forms

		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		private void InitializeComponent()
		{
			this.lvItems = new System.Windows.Forms.ListView();
			this.button_delete = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// lvItems
			// 
			this.lvItems.Location = new System.Drawing.Point(12, 12);
			this.lvItems.Name = "lvItems";
			this.lvItems.Size = new System.Drawing.Size(685, 356);
			this.lvItems.TabIndex = 0;
			this.lvItems.UseCompatibleStateImageBehavior = false;
			this.lvItems.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.lvItems_ItemSelectionChanged);
			// 
			// button_delete
			// 
			this.button_delete.Location = new System.Drawing.Point(703, 12);
			this.button_delete.Name = "button_delete";
			this.button_delete.Size = new System.Drawing.Size(75, 23);
			this.button_delete.TabIndex = 1;
			this.button_delete.Text = "Delete";
			this.button_delete.UseVisualStyleBackColor = true;
			this.button_delete.Click += new System.EventHandler(this.buttonDelete_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(790, 380);
			this.Controls.Add(this.button_delete);
			this.Controls.Add(this.lvItems);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ListView lvItems;
		private System.Windows.Forms.Button button_delete;
	}
}

