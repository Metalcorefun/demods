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
    public partial class Form1 : Form
    {
        string filePath;
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        OpenFileDialog openFileDialog = new OpenFileDialog();
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        List<DSAttributeWrapper> attributes_ = new List<DSAttributeWrapper>();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Maximized;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
        }

        private void новыйПроектToolStripMenuItem_Click(object sender, EventArgs e)
        {
            hierarchy_.clear();
        }

        private void открытьПроектToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            filePath = openFileDialog1.FileName;
            hierarchy_.load(filePath);
            attributes_ = hierarchy_.getAttributes();
        }

        private void сохранитьПроектToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == "")
            {
                saveFileDialog1.ShowDialog();
                filePath = saveFileDialog1.FileName;
            }
            hierarchy_.save(filePath);
        }

        private void сохранитьКакToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
            filePath = saveFileDialog1.FileName;
            hierarchy_.save(filePath);
        }

        private void признакиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new Attributes(hierarchy_);
            f.Show();
        }

        private void классыToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new Classes(hierarchy_);
            f.Show();
        }

        private void списокКомпонентовИерархииToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new HierarchyComponents(hierarchy_);
            f.Show();
        }
    }
}
