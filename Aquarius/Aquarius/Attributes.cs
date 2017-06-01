using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DSCoreWrapper;

namespace Aquarius
{
    public partial class Attributes : Form
    {
        DataTable dt_types = new DataTable();
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        List<DSAttributeWrapper> attributes_ = new List<DSAttributeWrapper>();
        public Attributes(DSHierarchyWrapper hierarchy)
        {
            InitializeComponent();
            hierarchy_ = hierarchy;  
        }
        private void PopulateTypesTable(DataTable dt)
        {
            dt.Columns.Add("ID");
            dt.Columns.Add("Description");
            dt.Columns.Add("Example");
            dt.Rows.Add("Numeric", "Цифровой", "Пример значения: { 1.0 }");
            dt.Rows.Add("NumArrayT", "Последовательность чисел (Расстояние по тенденции)", "Пример значения: { 1 2 3 4 }");
            dt.Rows.Add("NumArrayS", "Последовательность чисел (Расстояние по площади)", "Пример значения: { 1 2 3 4 }");
            dt.Rows.Add("FuzSetsO", "Нечёткие множества (коэфф.-т Охиаи)", "Пример значения: { 1(1.0) 2(1.0) 3(1.0) }");
            dt.Rows.Add("FuzSetsSC", "Нечёткие множества (коэфф.-т Серенсена-Чекановского)", "Пример значения: { 1(1.0) 2(1.0) 3(1.0) }");
            dt.Rows.Add("FuzzDistr", "Нечёткое распределение", "Пример значения: { 1(0.9) 2(0.8) 3(0.2) }");
            dt.Rows.Add("StatDistr", "Статистическое распределение", "Пример значения: { 1(0.2) 2(0.2) 3(0.2) 4(0.2) }");
            dt.Rows.Add("WeightStr", "Строка с весами каждой из букв", "Пример значения: { А(0.7) B(0.9) C(0.3) D(0.2) }");
            dt.Rows.Add("LogicUnit", "Логическая конструкция", "Пример значения: { A & B ! C }");
            dt.Rows.Add("FuzzyUnit", "Нечёткая логическая конструкция", "Пример значения: { A & B ! C }");
        }
        private void Attributes_Load(object sender, EventArgs e)
        {
            RefreshAttributes();
            PopulateTypesTable(dt_types);
            comboBox1.DataSource = dt_types;
            comboBox1.ValueMember = "ID";
            comboBox1.DisplayMember = "Description";
        }

        private void RefreshAttributes()
        {
            attributes_.Clear();
            attributes_ = hierarchy_.getAttributes();
            listBox1.Items.Clear();
            foreach (DSAttributeWrapper at in attributes_)
            {
                listBox1.Items.Add(at.getName());
            }
        }

        private void TurnRight(string action)
        {
            groupBox2.Enabled = true;
            if (action == "add")
            {
                button4.Enabled = true;
                button5.Enabled = false;
            }
            else if (action == "edit")
            {
                button4.Enabled = false;
                button5.Enabled = true;
            }
            groupBox3.Enabled = false;
            listBox1.Enabled = false;
        }

        private void TurnLeft()
        {
            groupBox3.Enabled = true;
            groupBox2.Enabled = false;
            listBox1.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            TurnRight("add");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                TurnRight("edit");
                textBox1.Text = attributes_[listBox1.SelectedIndex].getName();
                richTextBox1.Text = attributes_[listBox1.SelectedIndex].getDescription();
                foreach (DataRow dr in dt_types.Rows)
                {
                    if (dr["ID"].ToString() == attributes_[listBox1.SelectedIndex].getType())
                    {
                        comboBox1.SelectedValue = dr["ID"].ToString();
                    }
                }
            }
            catch(Exception)
            {
                MessageBox.Show("Признак не выбран из списка.");
                TurnLeft();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                hierarchy_.removeAttribute(attributes_[listBox1.SelectedIndex].getID());
                RefreshAttributes();
            }
            catch(Exception)
            {
                MessageBox.Show("Признак не выбран из списка");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {          
            hierarchy_.addAttribute(new DSAttributeWrapper(textBox1.Text, comboBox1.SelectedValue.ToString(), richTextBox1.Text));
            RefreshAttributes();
            TurnLeft();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            attributes_[listBox1.SelectedIndex].setName(textBox1.Text);
            attributes_[listBox1.SelectedIndex].setType(comboBox1.SelectedValue.ToString());
            attributes_[listBox1.SelectedIndex].setDescription(richTextBox1.Text);
            RefreshAttributes();
            TurnLeft();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            TurnLeft();
        }

        private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
        {
            label4.Text = dt_types.Rows[comboBox1.SelectedIndex]["Example"].ToString();
        }
    }
}
