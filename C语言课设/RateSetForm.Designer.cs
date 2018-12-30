namespace C语言课设
{
    partial class RateSetForm
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
            this.mulSeekbar2 = new C语言课设.MulSeekbar();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // mulSeekbar2
            // 
            this.mulSeekbar2.Colors = new System.Drawing.Color[0];
            this.mulSeekbar2.Indexs = new int[0];
            this.mulSeekbar2.Location = new System.Drawing.Point(24, 71);
            this.mulSeekbar2.Name = "mulSeekbar2";
            this.mulSeekbar2.Names = new string[0];
            this.mulSeekbar2.Size = new System.Drawing.Size(430, 50);
            this.mulSeekbar2.TabIndex = 1;
            this.mulSeekbar2.Text = "mulSeekbar2";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(200, 155);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "确定";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // RateSetForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(482, 253);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.mulSeekbar2);
            this.Name = "RateSetForm";
            this.Text = "设置各项比例";
            this.ResumeLayout(false);

        }

        #endregion
        private MulSeekbar mulSeekbar2;
        private System.Windows.Forms.Button button1;
    }
}