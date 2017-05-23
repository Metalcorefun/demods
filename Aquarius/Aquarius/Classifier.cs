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
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        DSClassifierWrapper classifier_ = new DSClassifierWrapper();
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
        }
    }
}
