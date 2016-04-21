namespace ByCategoryS
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
			this.label1 = new System.Windows.Forms.Label();
			this.ddCategory = new System.Windows.Forms.ComboBox();
			this.lvItems = new System.Windows.Forms.ListView();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(13, 13);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(49, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "Category";
			// 
			// ddCategory
			// 
			this.ddCategory.FormattingEnabled = true;
			this.ddCategory.Location = new System.Drawing.Point(68, 10);
			this.ddCategory.Name = "ddCategory";
			this.ddCategory.Size = new System.Drawing.Size(404, 21);
			this.ddCategory.TabIndex = 1;
			this.ddCategory.SelectedIndexChanged += new System.EventHandler(this.ddCategory_SelectedIndexChanged);
			// 
			// lvItems
			// 
			this.lvItems.Location = new System.Drawing.Point(16, 37);
			this.lvItems.Name = "lvItems";
			this.lvItems.Size = new System.Drawing.Size(746, 293);
			this.lvItems.TabIndex = 2;
			this.lvItems.UseCompatibleStateImageBehavior = false;
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(774, 342);
			this.Controls.Add(this.lvItems);
			this.Controls.Add(this.ddCategory);
			this.Controls.Add(this.label1);
			this.Name = "Form1";
			this.Text = "ByCategory";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox ddCategory;
		private System.Windows.Forms.ListView lvItems;
	}
}

