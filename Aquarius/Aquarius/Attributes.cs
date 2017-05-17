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
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        List<DSAttributeWrapper> attributes_ = new List<DSAttributeWrapper>();
        public Attributes(DSHierarchyWrapper hierarchy)
        {
            InitializeComponent();
            hierarchy_ = hierarchy;  
        }
        private void Attributes_Load(object sender, EventArgs e)
        {
            attributes_ = hierarchy_.getAttributes();
            foreach (DSAttributeWrapper at in attributes_)
            {
                listBox1.Items.Add(at.getName());
            }
        }
    }
}
