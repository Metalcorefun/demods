using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public void addGridParam(string[] N, DataGridView Grid)
        {

            //пока столбцов не будет достаточное количество добавляем их

            while (N.Length > Grid.ColumnCount)
            {

                //если колонок нехватает добавляем их пока их будет хватать

                Grid.Columns.Add("", "2");

            }

            //заполняем строку

            Grid.Rows.Add(N);

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void tabPage2_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            

            dataGridView1.Columns[0].Width = 55;
            dataGridView1.Columns[1].Width = 50;
            dataGridView1.Columns[2].Width = 50;
            dataGridView1.Columns[3].Width = 65;
            dataGridView1.Columns[4].Width = 55;
            dataGridView1.Columns[5].Width = 72;
            dataGridView1.Columns[6].Width = 55;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;


            dataGridView2.Columns[0].Width = 70;
            dataGridView2.Columns[1].Width = 130;
            dataGridView2.Columns[2].Width = 60;
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;


            dataGridView3.Columns[0].Width = 70;
            dataGridView3.Columns[1].Width = 90;
            dataGridView3.Columns[2].Width = 100;
            dataGridView3.Columns[3].Width = 70;
            dataGridView3.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;


            dataGridView4.Columns[0].Width = 70;
            dataGridView4.Columns[1].Width = 50;
            dataGridView4.Columns[2].Width = 50;
            dataGridView4.Columns[3].Width = 100;
            dataGridView4.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
