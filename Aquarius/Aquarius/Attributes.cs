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
        private void Attributes_Load(object sender, EventArgs e)
        {
            RefreshAttributes();
            dt_types.Columns.Add("ID");
            dt_types.Columns.Add("Description");
            dt_types.Rows.Add("Numeric", "Числовой");
            dt_types.Rows.Add("Text", "Текстовый");
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

        
    }
}
