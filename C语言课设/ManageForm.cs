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
    public partial class ManageForm : Form
    {
        public static ScoreInterface sci = new ScoreInterface();//C语言提供的接口类
        public static ManageForm manage;//本类的一个对象
        public static int[] rates= {35,25,40};
        public ManageForm()
        {
            InitializeComponent();
            manage = this;
        }

        private void ManageForm_Load(object sender, EventArgs e)
        {
            //加载皮肤文件
            skinEngine1.SkinFile = System.Environment.CurrentDirectory + "\\Skins\\mp10.ssk";
            initRates();
            AddScores();
        }

        public void initRates()
        {
            List<int> temp=sci.getRates();
            for (int i = 0; i < 3; i++) rates[i] = temp[i];
        }
        public void AddScores()//设置成绩信息
        {
            for (int i = 0; i < 10; i++) dataGridView_user.Columns.Add(new DataGridViewTextBoxColumn());//为DataGridView添加列
            //设置列名
            dataGridView_user.Columns[0].HeaderText = "学号";
            dataGridView_user.Columns[1].HeaderText = "姓名";
            dataGridView_user.Columns[2].HeaderText = "性别";
            dataGridView_user.Columns[3].HeaderText = "体重";
            dataGridView_user.Columns[4].HeaderText = "体重得分";
            dataGridView_user.Columns[5].HeaderText = "肺活量";
            dataGridView_user.Columns[6].HeaderText = "肺活量得分";
            dataGridView_user.Columns[7].HeaderText = "引体向上/仰卧起坐";
            dataGridView_user.Columns[8].HeaderText = "引体向上/仰卧起坐得分";
            dataGridView_user.Columns[9].HeaderText = "总分";

            resetScores();
        }

        private void resetScores()//重置数据
        {
            List<Score> datas = sci.getMark();//获取数据库中的数据
            for (int i = 0; i < datas.Count; i++)
            {
                Score sc_item = datas[i];
                dataGridView_user.Rows.Add();//添加一行
                dataGridView_user.Rows[i].Cells[0].Value = sc_item.id;
                dataGridView_user.Rows[i].Cells[1].Value = sc_item.name;
                dataGridView_user.Rows[i].Cells[2].Value = sc_item.sex ? "女" : "男";
                dataGridView_user.Rows[i].Cells[3].Value = sc_item.weight;
                dataGridView_user.Rows[i].Cells[4].Value = sc_item.sc_weight;
                dataGridView_user.Rows[i].Cells[5].Value = sc_item.lung_capacity;
                dataGridView_user.Rows[i].Cells[6].Value = sc_item.sc_lung_capacity;
                dataGridView_user.Rows[i].Cells[7].Value = sc_item.up_body_situp;
                dataGridView_user.Rows[i].Cells[8].Value = sc_item.sc_up_body_situp;
                dataGridView_user.Rows[i].Cells[9].Value = sc_item.total;
                if (sc_item.total < 60) dataGridView_user.Rows[i].DefaultCellStyle.BackColor = Color.Red;
            }
        }
        private void removeAll()
        {
            //移除DataGridView中所有行
            dataGridView_user.Rows.Clear();
        }

        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        public void saveData()
        {
            if (tabControl1.SelectedIndex == 0)//当前为成绩界面
            {
                List<Score> users = new List<Score>();
                DataGridViewRowCollection row = dataGridView_user.Rows;

                //利用HashSet判断是否有重复学号
                List<int> uids = new List<int>();
                for (int i = 0; i < row.Count; i++)
                {
                    uids.Add(toInt(row[i].Cells[0].Value));
                }
                if (uids.Count != new HashSet<int>(uids).Count)//有重复的学号
                {
                    MessageBox.Show("学号不能重复");
                    return;
                }

                for (int i = 0; i < row.Count; i++)
                {
                    Score sc_item = new Score();
                    sc_item.id = toInt(dataGridView_user.Rows[i].Cells[0].Value);
                    sc_item.name = dataGridView_user.Rows[i].Cells[1].Value.ToString();
                    sc_item.sex = (dataGridView_user.Rows[i].Cells[2].Value.ToString()).Equals("男") ? false : true;
                    sc_item.weight = toFloat(dataGridView_user.Rows[i].Cells[3].Value);
                    sc_item.sc_weight = toInt(dataGridView_user.Rows[i].Cells[4].Value);
                    sc_item.lung_capacity = toInt(dataGridView_user.Rows[i].Cells[5].Value);
                    sc_item.sc_lung_capacity = toInt(dataGridView_user.Rows[i].Cells[6].Value);
                    sc_item.up_body_situp = toInt(dataGridView_user.Rows[i].Cells[7].Value);
                    sc_item.sc_up_body_situp = toInt(dataGridView_user.Rows[i].Cells[8].Value);
                    sc_item.total = toInt(dataGridView_user.Rows[i].Cells[9].Value);
                    users.Add(sc_item);
                }
                if (sci.setAll(users))
                {
                    MessageBox.Show("保存成功");
                    removeAll();
                    resetScores();
                }
                else
                    MessageBox.Show("保存失败");
            }
        }

        private void toolStripButton1_Click(object sender, EventArgs e)//工具栏保存按钮响应事件
        {
            saveData();
        }

        private void toolStripButton2_Click(object sender, EventArgs e)//工具栏删除按钮响应事件
        {
            if (tabControl1.SelectedIndex == 0)
            {
                dataGridView_user.Rows.Remove(dataGridView_user.CurrentRow);
            }
        }

        private void toolStripButton1_Click_1(object sender, EventArgs e)//工具栏添加按钮响应事件
        {
            if (tabControl1.SelectedIndex == 0)
            {
                dataGridView_user.Rows.Add();
            }
        }

        private void toolStripButton3_Click(object sender, EventArgs e)//工具栏查找按钮响应事件
        {
            if (tabControl1.SelectedIndex == 0)
            {
                new RateSetForm().Show();
            }
        }
        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            if (tabControl1.SelectedIndex == 0)
            {
                new SearchForm().Show();
            }
        }

        public int toInt(object obj)//将一个对象转换成int
        {
            return obj == null ? 0 : int.Parse(obj.ToString());
        }
        public float toFloat(object obj)//将一个对象转换成float
        {
            return obj == null ? 0 : float.Parse(obj.ToString());
        }

        
    }
}
