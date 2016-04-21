namespace ByMulBrandS
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
			this.cblBrand = new System.Windows.Forms.ListView();
			this.SuspendLayout();
			// 
			// lvItems
			// 
			this.lvItems.Location = new System.Drawing.Point(146, 12);
			this.lvItems.Name = "lvItems";
			this.lvItems.Size = new System.Drawing.Size(639, 303);
			this.lvItems.TabIndex = 1;
			this.lvItems.UseCompatibleStateImageBehavior = false;
			// 
			// cblBrand
			// 
			this.cblBrand.Location = new System.Drawing.Point(12, 12);
			this.cblBrand.Name = "cblBrand";
			this.cblBrand.Size = new System.Drawing.Size(128, 303);
			this.cblBrand.TabIndex = 2;
			this.cblBrand.UseCompatibleStateImageBehavior = false;
			this.cblBrand.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.cblBrand_ItemChecked);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(797, 334);
			this.Controls.Add(this.cblBrand);
			this.Controls.Add(this.lvItems);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

        }

        #endregion

		private System.Windows.Forms.ListView lvItems;
		private System.Windows.Forms.ListView cblBrand;
    }
}

