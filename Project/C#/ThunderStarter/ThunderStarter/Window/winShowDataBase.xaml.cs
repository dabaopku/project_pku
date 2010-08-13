using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Data.OleDb;
using System.Data;

namespace ThunderStarter
{
    /// <summary>
    /// winShowDataBase.xaml 的交互逻辑
    /// </summary>
    public partial class winShowDataBase : Window
    {
        public winShowDataBase()
        {
            InitializeComponent();
        }

        public void LoadData(string sql)
            //加载查询语句
        {
            DataSet ds = DataBase.ExecuteQuery(sql);
            if(ds!=null && ds.Tables.Count>0)
                dataGrid.ItemsSource = ds.Tables[0].DefaultView;         
        }

        public void LoadData(DataTable dt)
            //加载数据表
        {
            dataGrid.ItemsSource = dt.DefaultView;
        }
    }
}
