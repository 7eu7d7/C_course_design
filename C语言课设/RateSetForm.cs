using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace C语言课设
{
    public partial class RateSetForm : Form
    {
        public RateSetForm()
        {
            InitializeComponent();
            mulSeekbar2.setImage(Properties.Resources.ball);
            ManageForm.manage.initRates();
            mulSeekbar2.Indexs=new int[] { ManageForm.rates[0], ManageForm.rates[0]+ ManageForm.rates[1], ManageForm.rates[0] + ManageForm.rates[1] + ManageForm.rates[2] };
            mulSeekbar2.Colors=new Color[] {Color.FromArgb(0xff,0x66,0xcc,0xff), Color.FromArgb(0xff, 0xb2, 0x44, 0xfa) , Color.FromArgb(0xff, 0x28, 0xed, 0x21) };
            mulSeekbar2.Names = new string[] {"体重","肺活量","引体向上/仰卧起坐"};
        }

        private void button1_Click(object sender, EventArgs e)
        {
            List<int> temp = new List<int>();
            temp.Add(mulSeekbar2.Indexs[0]);
            temp.Add(mulSeekbar2.Indexs[1]-mulSeekbar2.Indexs[0]);
            temp.Add(mulSeekbar2.Indexs[2]-mulSeekbar2.Indexs[1]);
            ManageForm.sci.setRates(temp);
            ManageForm.manage.saveData();
            Close();
        }
    }
}
