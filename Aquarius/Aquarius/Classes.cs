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
    public partial class Classes : Form
    {
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        List<DSClassWrapper> classes_ = new List<DSClassWrapper>();
        public Classes(DSHierarchyWrapper hierarchy)
        {
            InitializeComponent();
            hierarchy_ = hierarchy;
        }

        private void Classes_Load(object sender, EventArgs e)
        {
            RefreshClasses();
            
        }
        private void RefreshClasses()
        {
            classes_.Clear();
            classes_ = hierarchy_.getClasses();
            listBox1.Items.Clear();
            foreach (DSClassWrapper cl in classes_)
            {
                listBox1.Items.Add(cl.getName());
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
                textBox1.Text = classes_[listBox1.SelectedIndex].getName();
                richTextBox1.Text = classes_[listBox1.SelectedIndex].getDescription();
            }
            catch (Exception)
            {
                MessageBox.Show("Класс не выбран из списка.");
                TurnLeft();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                hierarchy_.removeClass(classes_[listBox1.SelectedIndex].getID());
                RefreshClasses();
            }
            catch (Exception)
            {
                MessageBox.Show("Класс не выбран из списка");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            hierarchy_.addClass(new DSClassWrapper(textBox1.Text, richTextBox1.Text));
            RefreshClasses();
            TurnLeft();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            classes_[listBox1.SelectedIndex].setName(textBox1.Text);
            classes_[listBox1.SelectedIndex].setDescription(richTextBox1.Text);
            RefreshClasses();
            TurnLeft();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            TurnLeft();
        }
    }
}
