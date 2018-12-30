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
    public partial class SearchForm : Form
    {
        public SearchForm()
        {
            InitializeComponent();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            DataGridViewRowCollection row = ManageForm.manage.dataGridView_user.Rows;
            for (int i = 0; i < row.Count; i++)
            {
                if (row[i].Cells[1].Value.ToString().Equals(textBox1.Text))//查找名称并选中该条记录
                {
                    row[i].Selected=true;
                }
                else
                {
                    row[i].Selected = false;
                }
            }
            Close();
        }
    }
}
