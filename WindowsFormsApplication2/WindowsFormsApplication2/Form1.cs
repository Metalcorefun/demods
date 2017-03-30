using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

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

        private void Form1_Load(object sender, EventArgs e)
        {
            

            dataGridView2.Columns[0].Width = 60;
            dataGridView2.Columns[1].Width = 100;
            dataGridView2.Columns[2].Width = 130;
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;

           
            dataGridView3.Columns[0].Width = 60;
            dataGridView3.Columns[1].Width = 100;
            dataGridView3.Columns[2].Width = 130;
            dataGridView3.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;

            dataGridView4.Columns[0].Width = 60;
            dataGridView4.Columns[1].Width = 100;
            dataGridView4.Columns[2].Width = 130;
            dataGridView4.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;

            //2

            dataGridView1.Columns[1].Width = 115;
            dataGridView1.Columns[2].Width = 85;

        }
    }
}
