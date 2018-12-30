using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace C语言课设
{
    public partial class MulSeekbar : Control
    {
        Image ball;
        int[] indexs = new int[0];
        Color[] cols = new Color[0];
        string[] names = new string[0];
        int ball_move = -1;
        int w, h,off_x,off_y;

        public int[] Indexs
        {
            get { return indexs; }
            set { indexs = value; }
        }
        public Color[] Colors
        {
            get { return cols; }
            set { cols = value; }
        }
        public string[] Names
        {
            get { return names; }
            set { names = value; }
        }

        public MulSeekbar()
        {
            InitializeComponent();
            
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            if (cols == null || indexs == null || names==null ||indexs.Length<=0||ball==null) return;
            off_y = 20;
            h = Height - 20;
            off_x = h / 2;
            w = Width - h;

            Graphics gra = e.Graphics;

            StringFormat format = new StringFormat();
            format.Alignment = StringAlignment.Center;
            format.LineAlignment = StringAlignment.Center;

            Rectangle rect = new Rectangle(off_x, off_y, w * indexs[0] / 100, h);
            gra.FillRectangle(new Pen(cols[0]).Brush, rect);
            gra.DrawString(names[0], new Font("Verdana", 8), new SolidBrush(Color.Black),rect,format);
            for (int i = 1; i < indexs.Length; i++)
            {
                rect = new Rectangle(off_x + w * indexs[i - 1] / 100, off_y, w * (indexs[i] - indexs[i - 1]) / 100, h);
                gra.FillRectangle(new Pen(cols[i]).Brush,rect);
                gra.DrawString(names[i], new Font("Verdana", 8), new SolidBrush(Color.Black), rect, format);
            }
            gra.FillRectangle(new Pen(cols[0]).Brush, off_x + w * indexs.Last() / 100, off_y, w * (100-indexs.Last()) / 100, h);
            for (int i = 0; i < indexs.Length; i++)
            {
                gra.DrawString(indexs[i]-(i==0?0:indexs[i-1])+"%", new Font("Verdana", 6), new SolidBrush(Color.Black), off_x + w * indexs[i] / 100 - off_x+ gra.MeasureString("" + indexs[i], new Font("Verdana", 6)).Width/4,off_y -10);
                gra.DrawImage(ball, off_x + w *indexs[i]/100 - off_x, off_y,h,h);
            }
        }

        private void MulSeekbar_MouseDown(object sender, MouseEventArgs e)
        {
            for (int i=0;i<indexs.Length;i++)
            {
                if(e.Y>0&&e.Y<Height&&Math.Abs(e.X - (off_x + w* indexs[i] / 100)) < off_x)
                {
                    ball_move = i;
                    break;
                }
            }
        }

        private void MulSeekbar_MouseUp(object sender, MouseEventArgs e)
        {
            ball_move = -1;
        }

        private void MulSeekbar_MouseMove(object sender, MouseEventArgs e)
        {
            if (ball_move != -1)
            {
                indexs[ball_move] = 100 * Math.Max(0, Math.Min(e.X-off_x,w)) / w;
                Refresh();
            }
        }
        public void setImage(Image img)
        {
            this.ball = img;
        }
        private double caldist(int x1,int y1,int x2,int y2)
        {
            return Math.Sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        }
    }
}
