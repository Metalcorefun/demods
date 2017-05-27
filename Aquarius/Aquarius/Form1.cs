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
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        OpenFileDialog openFileDialog = new OpenFileDialog();
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        List<DSAttributeWrapper> attributes_ = new List<DSAttributeWrapper>();
        Image drawing;
        public Form1()
        {
            InitializeComponent();
        }

 
        private void Form1_Load(object sender, EventArgs e)
        {
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

        private struct VisualUnit
        {
            public VisualUnit(DSClassifierWrapper classifier)
            {
                classifier_ = classifier;
                points = new PointF[3];
                drown = false;
            }
            public void setPoints(PointF[] P)
            {
                for(int i = 0; i < 3; i++)
                {
                    points[i].X = P[i].X;
                    points[i].Y = P[i].Y;
                }
            }
            public DSClassifierWrapper classifier_;
            public PointF[] points;
            public bool drown;
        }
        private struct AdditionalPoint
        {
            private string direction_;
            private PointF slider_;
            public PointF Slider
            {
                get { return slider_; }
                set { slider_ = value; }
            }

            public string Direction
            {
                get { return direction_; }
                set { direction_ = value; }
            }
        }
        private PointF DrawBrokenLine(List<List<VisualUnit>> visual_table, PointF begin, PointF end)
        {
            AdditionalPoint point = CheckIntersection(visual_table, begin, end);
            if (point.Slider.X != -1 && point.Slider.Y != -1)
            {
                while(true)
                {
                    if(point.Direction == "left")
                        point.Slider = new PointF(point.Slider.X - 50, point.Slider.Y);
                    else if(point.Direction == "right")
                        point.Slider = new PointF(point.Slider.X + 50, point.Slider.Y);
                    if(CheckIntersection(visual_table, begin, point.Slider).Slider.X == -1 && CheckIntersection(visual_table, begin, point.Slider).Slider.Y == -1 &&
                        CheckIntersection(visual_table, point.Slider, end).Slider.X == -1 && CheckIntersection(visual_table, point.Slider, end).Slider.Y == -1)
                    {
                        return point.Slider;
                    }
                    
                }
            }
            return new PointF(-1, -1);

        }
        private AdditionalPoint CheckIntersection(List<List<VisualUnit>> visual_table, PointF begin, PointF end)
        {
            AdditionalPoint point = new AdditionalPoint();
            float k = -(begin.Y - end.Y) / (end.X - begin.X);
            float b = -(begin.X * end.Y - end.X * begin.Y) / (end.X - begin.X);
            PointF slider = begin;
            if(begin.X < end.X) //наклон вправо
            {
                while (slider.X < end.X && slider.Y > end.Y)
                {
                    foreach (List<VisualUnit> list in visual_table)
                    {
                        foreach (VisualUnit unit in list)
                        {
                            if (((slider.X - unit.points[0].X) * (unit.points[0].Y - unit.points[1].Y) - (slider.Y - unit.points[0].Y) * (unit.points[0].X - unit.points[1].X)) <= 0 &&
                               ((slider.X - unit.points[1].X) * (unit.points[1].Y - unit.points[2].Y) - (slider.Y - unit.points[1].Y) * (unit.points[1].X - unit.points[2].X)) <= 0 &&
                               ((slider.X - unit.points[2].X) * (unit.points[2].Y - unit.points[0].Y) - (slider.Y - unit.points[2].Y) * (unit.points[2].X - unit.points[0].X)) <= 0)
                            {
                                if (slider.X - unit.points[1].X < unit.points[2].X - slider.X)
                                    point.Direction = "left";
                                else
                                    point.Direction = "right";
                                point.Slider = slider;
                                return point;
                            }
                        }
                    }
                    slider.X += 1; slider.Y = k * slider.X + b;
                }
            }
            else //наклон влево
            {
                while (slider.X > end.X && slider.Y > end.Y)
                {
                    foreach (List<VisualUnit> list in visual_table)
                    {
                        foreach (VisualUnit unit in list)
                        {
                            if (((slider.X - unit.points[0].X) * (unit.points[0].Y - unit.points[1].Y) - (slider.Y - unit.points[0].Y) * (unit.points[0].X - unit.points[1].X)) <= 0 &&
                               ((slider.X - unit.points[1].X) * (unit.points[1].Y - unit.points[2].Y) - (slider.Y - unit.points[1].Y) * (unit.points[1].X - unit.points[2].X)) <= 0 &&
                               ((slider.X - unit.points[2].X) * (unit.points[2].Y - unit.points[0].Y) - (slider.Y - unit.points[2].Y) * (unit.points[2].X - unit.points[0].X)) <= 0)
                            {
                                if (slider.X - unit.points[1].X < unit.points[2].X - slider.X)
                                    point.Direction = "left";
                                else
                                    point.Direction = "right";
                                point.Slider = slider;
                                return point;
                            }
                        }
                    }
                    slider.X -= 1; slider.Y = k * slider.X + b;
                }
            }
            point.Slider = new PointF(-1, -1);
            point.Direction = "No direction";
            return point;
        }

        private void visualize()
        {
            if(hierarchy_.getAttributes().Count>0 && hierarchy_.getClassifiers().Count > 0)
            {
                int max_count = 0;
                List<List<VisualUnit>> visual_table = new List<List<VisualUnit>>();
                List<DSClassifierWrapper> classifiers = hierarchy_.getClassifiers();
                List<DSAttributeWrapper> attributes = hierarchy_.getAttributes();
                classifiers.Sort((x, y) => x.getLevel().CompareTo(y.getLevel()));
                foreach (DSClassifierWrapper cl in classifiers)
                {
                    if (cl.getLevel() > visual_table.Count)
                        visual_table.Add(new List<VisualUnit>());
                    visual_table[cl.getLevel() - 1].Add(new VisualUnit(cl));
                }
                foreach (List<VisualUnit> list in visual_table)
                {
                    if (list.Count > max_count)
                        max_count = list.Count;
                }
                drawing = new Bitmap(400 * max_count, 500 * (visual_table.Count + 1));
                for (int i = visual_table.Count - 1; i >= 0; i--)
                {
                    for (int j = 0; j < visual_table[i].Count; j++)
                    {
                        PointF p1 = new PointF((drawing.Width / (visual_table[i].Count * 2)) + (drawing.Width / (visual_table[i].Count) * j), 40.0F + 500 * (visual_table.Count - visual_table[i][j].classifier_.getLevel()));
                        PointF p2 = new PointF(p1.X - 80, 200.0F + 500 * (visual_table.Count - visual_table[i][j].classifier_.getLevel()));
                        PointF p3 = new PointF(p1.X + 80, 200.0F + 500 * (visual_table.Count - visual_table[i][j].classifier_.getLevel()));
                        PointF[] p = { p1, p2, p3 };
                        visual_table[i][j].setPoints(p);
                    }
                }

                using (Graphics g = Graphics.FromImage(drawing))
                {
                    foreach (List<VisualUnit> list in visual_table)
                    {
                        foreach (VisualUnit unit in list)
                        {
                            g.DrawPolygon(new Pen(Color.Black, 4), unit.points);
                            if (unit.classifier_.getType() == "Fuzzy")
                                g.FillPolygon(new SolidBrush(Color.SkyBlue), unit.points);
                            else if (unit.classifier_.getType() == "Regressive")
                                g.FillPolygon(new SolidBrush(Color.Silver), unit.points);
                            g.DrawString(unit.classifier_.getName(), new Font("Times New Roman", 16), new SolidBrush(Color.Black), unit.points[1].X, unit.points[1].Y - 25);
                            List<DSClassifierWrapper> childs = unit.classifier_.getChilds();
                            if (childs.Count > 0)
                            {
                                foreach (DSClassifierWrapper cl in childs)
                                {
                                    foreach (List<VisualUnit> l in visual_table)
                                    {
                                        foreach (VisualUnit u in l)
                                        {
                                            string name1 = u.classifier_.getID();
                                            string name2 = cl.getID();
                                            if (u.classifier_.getID() == cl.getID())
                                                g.DrawLine(new Pen(Color.Black, 3), new PointF(unit.points[1].X + 80, unit.points[2].Y), u.points[0]);
                                        }
                                    }
                                }
                                childs.Clear();
                            }
                        }
                    }
                    for (int i = 0; i < attributes.Count; i++)
                    {
                        PointF point = new PointF((drawing.Width / (attributes.Count * 2) - 25) + (drawing.Width / attributes.Count) * i, 500 * visual_table.Count);
                        g.DrawEllipse(new Pen(Color.Black, 3), new RectangleF(point, new SizeF(30.0F, 30.0F)));
                        g.DrawString(attributes[i].getName(), new Font("Times New Roman", 16), new SolidBrush(Color.Black), point.X - 50, point.Y + 55);
                        foreach (List<VisualUnit> l in visual_table)
                        {
                            foreach (VisualUnit u in l)
                            {
                                foreach (DSAttributeWrapper attr in u.classifier_.getAttributes())
                                {
                                    if (attr.getID() == attributes[i].getID())
                                    {
                                        PointF p = DrawBrokenLine(visual_table, new PointF(point.X + 15, point.Y), new PointF(u.points[1].X + 80, u.points[2].Y));
                                        if (p.X != -1 && p.Y != -1)
                                        {
                                            g.DrawLine(new Pen(Color.Black, 3), new PointF(point.X + 15, point.Y), p);
                                            g.DrawLine(new Pen(Color.Black, 3), p, new PointF(u.points[1].X + 80, u.points[2].Y));
                                        }
                                        else
                                            g.DrawLine(new Pen(Color.Black, 3), new PointF(point.X + 15, point.Y), new PointF(u.points[1].X + 80, u.points[2].Y));
                                    }
                                }
                            }
                        }
                    }
                    g.Dispose();
                }
                trackBar1.Enabled = true;
                pictureBox1.MouseWheel += new MouseEventHandler(picBox1_MouseWheel);
                pictureBox1.Size = drawing.Size;
                pictureBox1.Image = drawing;
                pictureBox1.Focus();
            }
            else
            {
                trackBar1.Enabled = false;
            }
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
        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            //if (trackBar1.Value >= 0)
            //{
            //    if (trackBar1.Value > value)
            //    {
            //        zoom(50);
            //    }
            //    else zoom(-50);
            //    value = trackBar1.Value;
            //}
            //else if(trackBar1.Value < 0)
            //{
            //    if (trackBar1.Value > value)
            //    {
            //        zoom(50);
            //    }
            //    else zoom(-50);
            //    value = trackBar1.Value;
            //}       
        }

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
        Image Zoom(Image img, Size size)
        {
            Bitmap zoomed = new Bitmap(img, img.Width + (img.Width * size.Width / 100), img.Height + (img.Height * size.Height / 100));
            Graphics g = Graphics.FromImage(zoomed);
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            return zoomed;
        }
        private void zoom(int score)
        {
            pictureBox1.Height += score;
            pictureBox1.Width += score*2;
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
            visualize();
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

        private void button1_Click(object sender, EventArgs e)
        {
            if (!panel2.Visible)
            {
                panel2.Visible = true;
            }
            else panel2.Visible = false;
        }
    }
}
