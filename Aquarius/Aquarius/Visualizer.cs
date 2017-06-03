using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;
using DSCoreWrapper;

namespace Aquarius
{
    class Visualizer
    {
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
                for (int i = 0; i < 3; i++)
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
                while (true)
                {
                    if (point.Direction == "left")
                        point.Slider = new PointF(point.Slider.X - 50, point.Slider.Y);
                    else if (point.Direction == "right")
                        point.Slider = new PointF(point.Slider.X + 50, point.Slider.Y);
                    if (CheckIntersection(visual_table, begin, point.Slider).Slider.X == -1 && CheckIntersection(visual_table, begin, point.Slider).Slider.Y == -1 &&
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
            if (begin.X < end.X) //наклон вправо
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
        public void visualize(DSHierarchyWrapper hierarchy, Panel panel1, PictureBox pictureBox1, TrackBar trackBar1)
        {
            Image drawing;
            if (hierarchy.getAttributes().Count > 0 || hierarchy.getClassifiers().Count > 0)
            {
                int max_count = 0;
                List<List<VisualUnit>> visual_table = new List<List<VisualUnit>>();
                List<DSClassifierWrapper> classifiers = hierarchy.getClassifiers();
                List<DSAttributeWrapper> attributes = hierarchy.getAttributes();
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
                if (max_count > 0) drawing = new Bitmap(400 * max_count, 500 * (visual_table.Count + 1));
                else drawing = new Bitmap(400 * attributes.Count, 500);
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
                                trackBar1.Value = 0;
                                childs.Clear();
                            }
                        }
                    }
                    for (int i = 0; i < attributes.Count; i++)
                    {
                        PointF point = new PointF((drawing.Width / (attributes.Count * 2) - 25) + (drawing.Width / attributes.Count) * i, (500 * visual_table.Count) + 200);
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
                
                pictureBox1.Size = drawing.Size;
                pictureBox1.Image = drawing;
                pictureBox1.Focus();
            }
            else
            {
                if (pictureBox1.Image != null)
                {
                    Graphics g = Graphics.FromImage(pictureBox1.Image);
                    g.Clear(pictureBox1.BackColor);
                    g.Dispose();
                    
                    pictureBox1.Image = null;
                    pictureBox1.Size = panel1.Size;
                }
                trackBar1.Value = 0;
                trackBar1.Enabled = false;
            }
        }
    }
}
