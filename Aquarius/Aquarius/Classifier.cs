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
    public partial class Classifier : Form
    {
        DataTable dt_types = new DataTable();
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        DSClassifierWrapper classifier_ = new DSClassifierWrapper("");
        List<DSAttributeWrapper> attributes_ = new List<DSAttributeWrapper>();
        List<DSClassifierWrapper> childs_ = new List<DSClassifierWrapper>();
        List<DSClassWrapper> classes_ = new List<DSClassWrapper>();
        public Classifier(DSHierarchyWrapper hierarchy)
        {
            InitializeComponent();
            hierarchy_ = hierarchy;
        }
        public Classifier(DSHierarchyWrapper hierarchy, DSClassifierWrapper classifier)
        {
            InitializeComponent();
            hierarchy_ = hierarchy;
            classifier_ = classifier;
        }
        private void Classifier_Load(object sender, EventArgs e)
        {
            dt_types.Columns.Add("ID");
            dt_types.Columns.Add("Description");
            dt_types.Rows.Add("Fuzzy", "Базовый нечёткий классификатор");
            dt_types.Rows.Add("Regressive", "Чёткий классификатор(регрессионный анализ)");
            comboBox1.DataSource = dt_types;
            comboBox1.ValueMember = "ID";
            comboBox1.DisplayMember = "Description";
            RefreshParameters();
        }
        private void RefreshParameters()
        {
            textBox1.Text = classifier_.getName();
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            attributes_ = classifier_.getAttributes();
            classes_ = classifier_.getClasses();
            childs_ = classifier_.getChilds();
            foreach (DSAttributeWrapper at in attributes_)
            {
                listBox1.Items.Add(at.getName());
            }
            foreach (DSClassWrapper cl in classes_)
            {
                listBox3.Items.Add(cl.getName());
            }
            foreach(DSClassifierWrapper ch in childs_)
            {
                listBox2.Items.Add(ch.getName());
            }
            numericUpDown1.Value = classifier_.getLevel();
            foreach (DataRow dr in dt_types.Rows)
            {
                if (dr["ID"].ToString() == classifier_.getType())
                {
                    comboBox1.SelectedValue = dr["ID"].ToString();
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            classifier_.setName(textBox1.Text);
            classifier_.setLevel(Convert.ToInt32(numericUpDown1.Value));
            classifier_.setType(comboBox1.SelectedValue.ToString());
            hierarchy_.addClassifier(classifier_);
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            classifier_.setName(textBox1.Text);
            classifier_.setLevel(Convert.ToInt32(numericUpDown1.Value));
            classifier_.setType(comboBox1.SelectedValue.ToString());
            this.Close();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            List<DSAttributeWrapper> attributes = hierarchy_.getAttributes();
            List<ToolStripMenuItem> items = new List<ToolStripMenuItem>();
            foreach(DSAttributeWrapper at in attributes)
            {
                if(check("attribute", at.getID()))
                {
                    ToolStripMenuItem item = new ToolStripMenuItem(at.getName());
                    item.Click += new EventHandler(delegate (Object o, EventArgs a)
                    {
                        classifier_.addAttribute(at);
                        RefreshParameters();
                    });
                    items.Add(item);
                }
            }
            contextMenuStrip1.Items.AddRange(items.ToArray());

            Point screenPoint = pictureBox1.PointToScreen(new Point(pictureBox1.Left, pictureBox1.Bottom));
            if (screenPoint.Y + contextMenuStrip1.Size.Height > Screen.PrimaryScreen.WorkingArea.Height)
            {
                contextMenuStrip1.Show(pictureBox1, new Point(0, -contextMenuStrip1.Size.Height));
            }
            else
            {
                contextMenuStrip1.Show(pictureBox1, new Point(0, pictureBox1.Height));
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            List<DSAttributeWrapper> attributes = hierarchy_.getAttributes();
            List<ToolStripMenuItem> items = new List<ToolStripMenuItem>();
            foreach (DSAttributeWrapper at in attributes)
            {
                if (!check("attribute", at.getID()))
                {
                    ToolStripMenuItem item = new ToolStripMenuItem(at.getName());
                    item.Click += new EventHandler(delegate (Object o, EventArgs a)
                    {
                        classifier_.removeAttribute(at.getID());
                        RefreshParameters();
                    });
                    items.Add(item);
                }
            }
            contextMenuStrip1.Items.AddRange(items.ToArray());

            Point screenPoint = pictureBox2.PointToScreen(new Point(pictureBox2.Left, pictureBox2.Bottom));
            if (screenPoint.Y + contextMenuStrip1.Size.Height > Screen.PrimaryScreen.WorkingArea.Height)
            {
                contextMenuStrip1.Show(pictureBox2, new Point(0, -contextMenuStrip1.Size.Height));
            }
            else
            {
                contextMenuStrip1.Show(pictureBox2, new Point(0, pictureBox2.Height));
            }
        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {
            List<DSClassifierWrapper> classifiers = hierarchy_.getClassifiers();
            List<ToolStripMenuItem> items = new List<ToolStripMenuItem>();
            foreach (DSClassifierWrapper cl in classifiers)
            {
                if (cl.getID() != classifier_.getID() && check("child", cl.getID()))
                {
                    ToolStripMenuItem item = new ToolStripMenuItem(cl.getName());
                    item.Click += new EventHandler(delegate (Object o, EventArgs a)
                    {
                        classifier_.addChild(cl);
                        RefreshParameters();
                    });
                    items.Add(item);
                }
            }
            contextMenuStrip1.Items.AddRange(items.ToArray());

            Point screenPoint = pictureBox4.PointToScreen(new Point(pictureBox4.Left, pictureBox4.Bottom));
            if (screenPoint.Y + contextMenuStrip1.Size.Height > Screen.PrimaryScreen.WorkingArea.Height)
            {
                contextMenuStrip1.Show(pictureBox4, new Point(0, -contextMenuStrip1.Size.Height));
            }
            else
            {
                contextMenuStrip1.Show(pictureBox4, new Point(0, pictureBox4.Height));
            }
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            List<DSClassifierWrapper> classifiers = hierarchy_.getClassifiers();
            List<ToolStripMenuItem> items = new List<ToolStripMenuItem>();
            foreach (DSClassifierWrapper cl in classifiers)
            {
                if (cl.getID() != classifier_.getID() && !check("child", cl.getID()))
                {
                    ToolStripMenuItem item = new ToolStripMenuItem(cl.getName());
                    item.Click += new EventHandler(delegate (Object o, EventArgs a)
                    {
                        classifier_.removeChild(cl.getID());
                        RefreshParameters();
                    });
                    items.Add(item);
                }
            }
            contextMenuStrip1.Items.AddRange(items.ToArray());

            Point screenPoint = pictureBox3.PointToScreen(new Point(pictureBox3.Left, pictureBox3.Bottom));
            if (screenPoint.Y + contextMenuStrip1.Size.Height > Screen.PrimaryScreen.WorkingArea.Height)
            {
                contextMenuStrip1.Show(pictureBox3, new Point(0, -contextMenuStrip1.Size.Height));
            }
            else
            {
                contextMenuStrip1.Show(pictureBox3, new Point(0, pictureBox3.Height));
            }
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {
            List<DSClassWrapper> classes = hierarchy_.getClasses();
            List<ToolStripMenuItem> items = new List<ToolStripMenuItem>();
            foreach (DSClassWrapper cl in classes)
            {
                if(check("class", cl.getID()))
                {
                    ToolStripMenuItem item = new ToolStripMenuItem(cl.getName());
                    item.Click += new EventHandler(delegate (Object o, EventArgs a)
                    {
                        classifier_.addClass(cl);
                        RefreshParameters();
                    });
                    items.Add(item);
                }
            }
            contextMenuStrip1.Items.AddRange(items.ToArray());
            Point screenPoint = pictureBox6.PointToScreen(new Point(pictureBox6.Left, pictureBox6.Bottom));
            if (screenPoint.Y + contextMenuStrip1.Size.Height > Screen.PrimaryScreen.WorkingArea.Height)
            {
                contextMenuStrip1.Show(pictureBox6, new Point(0, -contextMenuStrip1.Size.Height));
            }
            else
            {
                contextMenuStrip1.Show(pictureBox6, new Point(0, pictureBox6.Height));
            }
        }
        private void pictureBox5_Click(object sender, EventArgs e)
        {
            List<DSClassWrapper> classes = hierarchy_.getClasses();
            List<ToolStripMenuItem> items = new List<ToolStripMenuItem>();
            foreach (DSClassWrapper cl in classes)
            {
                if (!check("class", cl.getID()))
                {
                    ToolStripMenuItem item = new ToolStripMenuItem(cl.getName());
                    item.Click += new EventHandler(delegate (Object o, EventArgs a)
                    {
                        classifier_.removeClass(cl.getID());
                        RefreshParameters();
                    });
                    items.Add(item);
                }
            }
            contextMenuStrip1.Items.AddRange(items.ToArray());
            Point screenPoint = pictureBox5.PointToScreen(new Point(pictureBox5.Left, pictureBox5.Bottom));
            if (screenPoint.Y + contextMenuStrip1.Size.Height > Screen.PrimaryScreen.WorkingArea.Height)
            {
                contextMenuStrip1.Show(pictureBox5, new Point(0, -contextMenuStrip1.Size.Height));
            }
            else
            {
                contextMenuStrip1.Show(pictureBox5, new Point(0, pictureBox6.Height));
            }
        }

        private bool check(string mode, string id)
        {
            if(mode == "attribute")
            {
                foreach(DSAttributeWrapper at in attributes_)
                {
                    if (at.getID() == id)
                        return false;
                }
            }
            if (mode == "class")
            {
                foreach (DSClassWrapper cl in classes_)
                {
                    if (cl.getID() == id)
                        return false;
                }
            }
            if (mode == "child")
            {
                foreach (DSClassifierWrapper cl in childs_)
                {
                    if (cl.getID() == id)
                        return false;
                }
            }
            return true;
        }

        private void contextMenuStrip1_Closing(object sender, ToolStripDropDownClosingEventArgs e)
        {
            contextMenuStrip1.Items.Clear();
        }

        

        

        
    }
}
