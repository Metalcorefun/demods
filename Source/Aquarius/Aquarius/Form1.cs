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
        int value = 0;
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        List<DSAttributeWrapper> attributes_ = new List<DSAttributeWrapper>();
        Visualizer artist = new Visualizer();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            pictureBox1.MouseWheel += new MouseEventHandler(picBox1_MouseWheel);
            this.WindowState = FormWindowState.Maximized;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            Image icon1 = new Bitmap(46, 46);
            Image icon2 = new Bitmap(46, 46);
            Image icon3 = new Bitmap(46, 46);
            PointF p1 = new PointF(23.0F, 3.0F);
            PointF p2 = new PointF(3.0F, 43.0F);
            PointF p3 = new PointF(43.0F, 43.0F);
            PointF[] points = { p1, p2, p3 };
            using (Graphics g = Graphics.FromImage(icon1))
            {
                g.DrawPolygon(new Pen(Color.Black, 2), points);
                g.FillPolygon(new SolidBrush(Color.SkyBlue), points);
            }
            pictureBox2.Image = icon1;
            using (Graphics g = Graphics.FromImage(icon2))
            {
                g.DrawPolygon(new Pen(Color.Black, 2), points);
                g.FillPolygon(new SolidBrush(Color.Silver), points);
            }
            pictureBox3.Image = icon2;
            using (Graphics g = Graphics.FromImage(icon3))
            {
                g.DrawEllipse(new Pen(Color.Black, 2), 10, 10, 26,26);
            }
            pictureBox4.Image = icon3;
            panel2.Visible = false;
        }

        private bool Dragging;
        private int xPos;
        private int yPos;
        private void pictureBox1_MouseUp(object sender, MouseEventArgs e) { Dragging = false; }
        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Dragging = true;
                xPos = e.X;
                yPos = e.Y;

            }
        }
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            Control c = sender as Control;
            if (Dragging && c != null)
            {
                c.Top = e.Y + c.Top - yPos;
                c.Left = e.X + c.Left - xPos;
            }
        }
        private void picBox1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta < 0)
            {
                if (trackBar1.Value - 10 >= trackBar1.Minimum)
                    trackBar1.Value -= 10;
            }
            else
            {
                if(trackBar1.Value + 10 <= trackBar1.Maximum)
                    trackBar1.Value += 10;
            }
        }
        private void trackBar1_Scroll(object sender, EventArgs e){ }
        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            if (trackBar1.Value >= 0)
            {
                if (trackBar1.Value > value)
                {
                    zoom(5*(trackBar1.Value - value));
                }
                else zoom(-5 * (value - trackBar1.Value));
                value = trackBar1.Value;
            }
            else if (trackBar1.Value < 0)
            {
                if (trackBar1.Value > value)
                {
                    zoom(5 * Math.Abs(trackBar1.Value - value));
                }
                else zoom(-5 * Math.Abs(value - trackBar1.Value));
                value = trackBar1.Value;
            }
        }
        private void zoom(int score)
        {
            pictureBox1.Height += score;
            pictureBox1.Width += score*2;
        }

        private void новыйПроектToolStripMenuItem_Click(object sender, EventArgs e)
        {
            hierarchy_.clear();
            artist.visualize(hierarchy_, panel1, pictureBox1, trackBar1);
        }

        private void открытьПроектToolStripMenuItem_Click(object sender, EventArgs e)
        {
            hierarchy_.clear();
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                filePath = openFileDialog1.FileName;
                if (hierarchy_.load(filePath)) artist.visualize(hierarchy_, panel1, pictureBox1, trackBar1);
                else MessageBox.Show("Ошибка открытия файла.", "Ошибка");
            } 
        }

        private void сохранитьПроектToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == "")
            {
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    filePath = saveFileDialog1.FileName;
                    if (!hierarchy_.save(filePath)) MessageBox.Show("Ошибка сохранения файла.", "Ошибка");
                }
            }
            else hierarchy_.save(filePath);
        }

        private void сохранитьКакToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                filePath = saveFileDialog1.FileName;
                hierarchy_.save(filePath);
            }
        }

        private void признакиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new Attributes(hierarchy_);
            f.ShowDialog();
            artist.visualize(hierarchy_, panel1, pictureBox1, trackBar1);
        }

        private void классыToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new Classes(hierarchy_);
            f.ShowDialog();
        }

        private void списокКомпонентовИерархииToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new HierarchyComponents(hierarchy_);
            f.ShowDialog();
            artist.visualize(hierarchy_, panel1, pictureBox1, trackBar1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!panel2.Visible)
            {
                panel2.Visible = true;
            }
            else panel2.Visible = false;
        }

        private void загрузитьТекущуюИерархиюВСистемуLinxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(hierarchy_.getClassifiers().Count > 0)
            {
                hierarchy_.COM_sendData();
                hierarchy_.COM_learn();
                сохранитьФайлПодсистемыОбученияLinxToolStripMenuItem.Enabled = true;
                сохранитьФайлПараметровШкалыКлассификацииLinxToolStripMenuItem.Enabled = true;
            }
            else MessageBox.Show("Иерархия классификаторов на данный момент не содержит ни одного компонента.", "Ошибка");            
            //if (!hierarchy_.COM_learn()) MessageBox.Show("Подсистема обучения Linx выявила ошибки в существующей иерархии классификаторов.");
        }

        private void сохранитьФайлПодсистемыОбученияLinxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog2.ShowDialog() == DialogResult.OK)
            {
                hierarchy_.COM_saveFOV(saveFileDialog2.FileName); 
            }
        }

        private void сохранитьФайлПараметровШкалыКлассификацииLinxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog3.ShowDialog() == DialogResult.OK)
            {
                hierarchy_.COM_saveFSC(saveFileDialog3.FileName);
            }
        }

        private void оПрограммеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new About();
            f.ShowDialog();
        }
    }
}
