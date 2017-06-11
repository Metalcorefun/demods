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
        DataTable dt_training_set = new DataTable();
        DataTable dt_base_object = new DataTable();
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        DSClassifierWrapper classifier_ = new DSClassifierWrapper("");
        List<DSAttributeWrapper> attributes_ = new List<DSAttributeWrapper>();
        List<DSClassifierWrapper> childs_ = new List<DSClassifierWrapper>();
        List<DSClassWrapper> classes_ = new List<DSClassWrapper>();
        string isReliable;
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
        private void PopulateTypesTable(DataTable dt)
        {
            dt_types.Columns.Add("ID");
            dt_types.Columns.Add("Description");
            dt_types.Rows.Add("Fuzzy", "Базовый нечёткий классификатор");
            dt_types.Rows.Add("Regressive", "Чёткий классификатор(регрессионный анализ)");
        }
        private void Reliability()
        {
            if (classifier_.isSent())
            {
                if(hierarchy_.COM_IsReliable(classifier_)){ isReliable += "ОВ достоверна "; }
                else { isReliable += "ОВ не достоверна "; }
                isReliable += "( " + hierarchy_.COM_TCriterion(classifier_);
                if(hierarchy_.COM_IsReliable(classifier_)) { isReliable += " <= "; }
                else { isReliable += " >= "; }
                isReliable += hierarchy_.COM_TCriterionTable(classifier_) + " )";
                label7.Text = isReliable;
            }
        }
        private void Classifier_Load(object sender, EventArgs e)
        {
            Reliability();
            PopulateTypesTable(dt_types);
            comboBox1.DataSource = dt_types;
            comboBox1.ValueMember = "ID";
            comboBox1.DisplayMember = "Description";
            RefreshParameters();
            textBox1.Text = classifier_.getName();
        }
        private void RefreshParameters()
        {
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
            BuildTrainingSetTable(dataGridView1);
            BuildBaseObjectTable(dataGridView2);
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

        //Training Set Tab
        private void BuildTrainingSetTable(DataGridView dgw)
        {
            dt_training_set.Rows.Clear();
            dt_training_set.Columns.Clear();
            List<DSProbeWrapper> training_set = classifier_.getTrainingSet();
            foreach(DSAttributeWrapper attribute in attributes_)
            {
                dt_training_set.Columns.Add(new DataColumn(attribute.getName()));
            }
            foreach(DSClassWrapper Class in classes_)
            {
                dt_training_set.Columns.Add(new DataColumn(Class.getName(), System.Type.GetType("System.Double")));
            }
            
            foreach(DSProbeWrapper probe in training_set)
            {
                DataRow row = dt_training_set.NewRow();
                for(int i = 0; i < probe.getAttribValues().Count; i++)
                {
                    row[i] = probe.getAttribValues()[i].getValue();
                }
                for(int i = 0; i < probe.getClassMemFuncs().Count; i++)
                {
                    row[i + probe.getAttribValues().Count] = probe.getClassMemFuncs()[i].getMembershipFunction();
                }
                dt_training_set.Rows.Add(row);
            }
            dgw.DataSource = dt_training_set;
        }

        private void UpdateTrainingSetFromTable(DataGridView dgv)
        {
            classifier_.removeTrainingSet();
            foreach(DataRow dr in dt_training_set.Rows)
            {
                DSProbeWrapper probe = new DSProbeWrapper();
                List<AttribValueWrapper> attribValues = new List<AttribValueWrapper>();
                List<ClassMemFuncWrapper> classMemFuncs = new List<ClassMemFuncWrapper>();
                for(int i = 0; i < attributes_.Count; i++)
                {
                    AttribValueWrapper av = new AttribValueWrapper(attributes_[i], (string)dr[attributes_[i].getName()]);
                    attribValues.Add(av);
                }
                for (int i = 0; i < classes_.Count; i++)
                {
                    ClassMemFuncWrapper cm = new ClassMemFuncWrapper(classes_[i], Convert.ToDouble(dr[classes_[i].getName()]));
                    classMemFuncs.Add(cm);
                }
                probe.setAttribValues(attribValues);
                probe.setClassMemFuncs(classMemFuncs);
                classifier_.toTrainingSet(probe);
            }
        }
        private void button4_Click(object sender, EventArgs e)
        {
            UpdateTrainingSetFromTable(dataGridView1);
            BuildTrainingSetTable(dataGridView1);
        }

        //Base Object Tab
        private void BuildBaseObjectTable(DataGridView dgv)
        {
            dt_base_object.Rows.Clear();
            dt_base_object.Columns.Clear();
            dt_base_object.Columns.Add(new DataColumn("Признак", System.Type.GetType("System.String")));
            dt_base_object.Columns.Add(new DataColumn("Значение признака", System.Type.GetType("System.String")));
            List<AttribValueWrapper> baseObject_ = classifier_.getBaseObject();
            foreach(AttribValueWrapper av in baseObject_)
            {
                DataRow dr = dt_base_object.NewRow();
                dr[0] = av.getAttributeReference().getName();
                dr[1] = av.getValue();
                dt_base_object.Rows.Add(dr);
            }
            dgv.DataSource = dt_base_object;
            dgv.Columns[0].Width = 218; dgv.Columns[1].Width = 218;
        }

        private void UpdateBaseObjectFromTable(DataGridView dgv)
        {
            List<AttribValueWrapper> baseObject_ = classifier_.getBaseObject();
            foreach(DataRow dr in dt_base_object.Rows)
            {
                foreach(AttribValueWrapper av in baseObject_)
                {
                    if ((string)dr[0] == av.getAttributeReference().getName())
                        av.setValue((string)dr[1]);
                }
            }    
        }
       
        private void button5_Click(object sender, EventArgs e)
        {
            UpdateBaseObjectFromTable(dataGridView2);
            BuildBaseObjectTable(dataGridView2);
        }
    }
}
