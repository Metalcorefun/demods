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
            classes_ = hierarchy_.getClasses();
            foreach (DSClassWrapper cl in classes_)
            {
                listBox1.Items.Add(cl.getName());
            }
        }
    }
}
