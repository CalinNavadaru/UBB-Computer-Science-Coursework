using System.IO;

namespace Laborator2
{
    partial class Form1
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
            this.tableParent = new System.Windows.Forms.DataGridView();
            this.tableChild = new System.Windows.Forms.DataGridView();
            this.btnDelete = new System.Windows.Forms.Button();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.BtnUpdate = new System.Windows.Forms.Button();
            this.textBoxAddName = new System.Windows.Forms.TextBox();
            this.btnAdd = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.tableParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tableChild)).BeginInit();
            this.SuspendLayout();
            // 
            // tableParent
            // 
            this.tableParent.SelectionChanged += TableParent_SelectionChanged;
            this.tableParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.tableParent.Location = new System.Drawing.Point(31, 21);
            this.tableParent.Name = "tableParent";
            this.tableParent.RowTemplate.Height = 24;
            this.tableParent.ShowEditingIcon = false;
            this.tableParent.Size = new System.Drawing.Size(611, 248);
            this.tableParent.TabIndex = 0;
            // 
            // tableChild
            // 
            this.tableChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.tableChild.Location = new System.Drawing.Point(31, 390);
            this.tableChild.Name = "tableChild";
            this.tableChild.RowTemplate.Height = 24;
            this.tableChild.Size = new System.Drawing.Size(611, 248);
            this.tableChild.TabIndex = 1;
            // 
            // btnDelete
            // 
            this.btnDelete.Location = new System.Drawing.Point(776, 63);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(199, 54);
            this.btnDelete.TabIndex = 2;
            this.btnDelete.Text = "Sterge Fiu";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(771, 191);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(199, 22);
            this.textBoxName.TabIndex = 3;
            // 
            // BtnUpdate
            // 
            this.BtnUpdate.Location = new System.Drawing.Point(771, 266);
            this.BtnUpdate.Name = "BtnUpdate";
            this.BtnUpdate.Size = new System.Drawing.Size(203, 55);
            this.BtnUpdate.TabIndex = 4;
            this.BtnUpdate.Text = "Actualizare";
            this.BtnUpdate.UseVisualStyleBackColor = true;
            this.BtnUpdate.Click += new System.EventHandler(this.BtnUpdate_Click);
            // 
            // textBoxAddName
            // 
            this.textBoxAddName.Location = new System.Drawing.Point(766, 476);
            this.textBoxAddName.Name = "textBoxAddName";
            this.textBoxAddName.Size = new System.Drawing.Size(203, 22);
            this.textBoxAddName.TabIndex = 5;
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(765, 555);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(209, 32);
            this.btnAdd.TabIndex = 6;
            this.btnAdd.Text = "Adaugare";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1065, 731);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.textBoxAddName);
            this.Controls.Add(this.BtnUpdate);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.tableChild);
            this.Controls.Add(this.tableParent);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.tableParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tableChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        private System.Windows.Forms.TextBox textBoxAddName;
        private System.Windows.Forms.Button btnAdd;

        private System.Windows.Forms.Button BtnUpdate;

        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.TextBox textBoxName;

        private System.Windows.Forms.DataGridView tableChild;

        private System.Windows.Forms.DataGridView tableParent;

        #endregion
    }
}