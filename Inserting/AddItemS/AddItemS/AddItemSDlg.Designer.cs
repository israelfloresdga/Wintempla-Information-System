namespace AddItemS
{
	partial class AddItemSDlg
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.tbxName = new System.Windows.Forms.TextBox();
			this.tbxModel = new System.Windows.Forms.TextBox();
			this.ddBrand = new System.Windows.Forms.ComboBox();
			this.ddCategory = new System.Windows.Forms.ComboBox();
			this.buttonOk = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(13, 12);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(35, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "Name";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(13, 38);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(36, 13);
			this.label2.TabIndex = 1;
			this.label2.Text = "Model";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(13, 65);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(35, 13);
			this.label3.TabIndex = 2;
			this.label3.Text = "Brand";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(13, 92);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(49, 13);
			this.label4.TabIndex = 3;
			this.label4.Text = "Category";
			// 
			// tbxName
			// 
			this.tbxName.Location = new System.Drawing.Point(68, 9);
			this.tbxName.Name = "tbxName";
			this.tbxName.Size = new System.Drawing.Size(278, 20);
			this.tbxName.TabIndex = 4;
			// 
			// tbxModel
			// 
			this.tbxModel.Location = new System.Drawing.Point(67, 35);
			this.tbxModel.Name = "tbxModel";
			this.tbxModel.Size = new System.Drawing.Size(279, 20);
			this.tbxModel.TabIndex = 5;
			// 
			// ddBrand
			// 
			this.ddBrand.FormattingEnabled = true;
			this.ddBrand.Location = new System.Drawing.Point(67, 62);
			this.ddBrand.Name = "ddBrand";
			this.ddBrand.Size = new System.Drawing.Size(279, 21);
			this.ddBrand.TabIndex = 6;
			// 
			// ddCategory
			// 
			this.ddCategory.FormattingEnabled = true;
			this.ddCategory.Location = new System.Drawing.Point(68, 89);
			this.ddCategory.Name = "ddCategory";
			this.ddCategory.Size = new System.Drawing.Size(278, 21);
			this.ddCategory.TabIndex = 7;
			// 
			// buttonOk
			// 
			this.buttonOk.Location = new System.Drawing.Point(67, 137);
			this.buttonOk.Name = "buttonOk";
			this.buttonOk.Size = new System.Drawing.Size(75, 23);
			this.buttonOk.TabIndex = 8;
			this.buttonOk.Text = "Ok";
			this.buttonOk.UseVisualStyleBackColor = true;
			this.buttonOk.Click += new System.EventHandler(this.buttonOk_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.Location = new System.Drawing.Point(149, 136);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 23);
			this.buttonCancel.TabIndex = 9;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
			// 
			// AddItemSDlg
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(371, 186);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOk);
			this.Controls.Add(this.ddCategory);
			this.Controls.Add(this.ddBrand);
			this.Controls.Add(this.tbxModel);
			this.Controls.Add(this.tbxName);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Name = "AddItemSDlg";
			this.Text = "AddItemSDlg";
			this.Load += new System.EventHandler(this.AddItemSDlg_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox tbxName;
		private System.Windows.Forms.TextBox tbxModel;
		private System.Windows.Forms.ComboBox ddBrand;
		private System.Windows.Forms.ComboBox ddCategory;
		private System.Windows.Forms.Button buttonOk;
		private System.Windows.Forms.Button buttonCancel;
	}
}