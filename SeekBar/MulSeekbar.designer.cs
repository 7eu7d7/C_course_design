namespace C语言课设
{
    partial class MulSeekbar
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // MulSeekbar
            // 
            //this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            //this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Name = "MulSeekbar";
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MulSeekbar_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MulSeekbar_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MulSeekbar_MouseUp);
            this.ResumeLayout(false);

        }

        #endregion
    }
}
