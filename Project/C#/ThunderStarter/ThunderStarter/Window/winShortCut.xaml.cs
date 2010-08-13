using System;
using System.Windows;
using System.Data.OleDb;
using System.IO;
using System.Diagnostics;
using System.Data;
using System.Text.RegularExpressions;
using System.Collections;
using ShortCutLib;

namespace ThunderStarter
{
    /// <summary>
    /// winShortCut.xaml 的交互逻辑
    /// </summary>
    public partial class winShortCut : Window
    {
        public winShortCut()
            //构造函数
        {
            InitializeComponent();
        }

        public winShortCut(DragEventArgs e)
            //拖放文件构造函数
        {
            InitializeComponent();
     
            txtPath.Text = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
            txtName.Text = Path.GetFileName(txtPath.Text);
            string extension = Path.GetExtension(txtPath.Text);
           
            if (extension==".lnk")  //快捷方式还原为实际路径
            {
                txtPath.Text = Global.GetShortCutTarget(txtPath.Text);
            }

            //提取文件描述
            if (File.Exists(txtPath.Text))
            {
                FileVersionInfo fvi = FileVersionInfo.GetVersionInfo(txtPath.Text);
                CFileInfo cfi = new CFileInfo(txtPath.Text);

                string s1 = "\n" + fvi.ProductName + "\n"+ fvi.Comments + "\n" ;
                string s2 = cfi.FileAuthor + "\n" + cfi.FileCategory + "\n" + cfi.FileComment
                    + "\n" + cfi.FileSubject + "\n" + cfi.FileTitle;
                txtDetail.Text = s1 + s2;
                txtDetail.Text = Regex.Replace(txtDetail.Text, "^\n|\n(?=\n)", "");
            }
            e.Effects = DragDropEffects.None;
        }

        public winShortCut(DataRow dr)
            //查看数据构造函数
        {
            InitializeComponent();
            txtName.Text = dr.ItemArray[(int)ShortCutTableCollum.Name].ToString();
            txtPath.Text = dr.ItemArray[(int)ShortCutTableCollum.Path].ToString();
            txtDetail.Text = dr.ItemArray[(int)ShortCutTableCollum.Detail].ToString();
            BrowserFile.Width=25;
            dr = null;
            btAdd.Content = "修改";
            btAdd.Click -= AddNew;
            btAdd.Click += Update;
        }

        private void Quit(object sender, RoutedEventArgs e)
            //退出
        {
            Close();
        }

        private void AddNew(object sender, RoutedEventArgs e)
            //添加记录
        {
            string sql = ThunderStarter.Properties.Resources.strAddShortCut;
            string s0 = DataBase.FormatString(txtName.Text);
            string s1 = DataBase.FormatString(txtPath.Text);
            string s2 = DataBase.FormatString(txtDetail.Text);
            string s3 = DataBase.FormatString(Path.GetFileNameWithoutExtension(txtPath.Text));
            string s4 = DataBase.FormatString(DataBase.PinYin(txtName.Text+txtDetail.Text));
            string s5 = "''";
            if (Path.HasExtension(txtPath.Text))
                s5 = DataBase.FormatString(Path.GetExtension(txtPath.Text).TrimStart('.'));
           //创建快捷方式
            string s6 = "";
            Hashtable hs = new Hashtable(3);
            hs.Add("Name", txtName.Text);
            hs.Add("Path", txtPath.Text);
            hs.Add("Detail", txtDetail.Text);
            s6 = DataBase.FormatString(Global.CreateShortCut(hs));
            string cmd = String.Format(sql, s0, s1, s2, s3, s4, s5,s6);
            DataBase.ExecuteNonQuery(cmd);
            this.Close();
        }

        private void Update(object sender, RoutedEventArgs e)
        //修改记录
        {
            //设置sql
            string sql = ThunderStarter.Properties.Resources.strUpdateShortCut;
            string s0 = DataBase.FormatString(txtName.Text);
            string s1 = DataBase.FormatString(txtDetail.Text);
            string s2 = DataBase.FormatString(txtPath.Text);
            string s3 = DataBase.PinYin(s0);
            string cmd = String.Format(sql, s0, s1, s2, s3);
            DataBase.ExecuteNonQuery(cmd);
            this.Close();
        }

        private void BrowserFile_Click(object sender, RoutedEventArgs e)
            //浏览文件(夹)
        {
            Global.DataTransfer = null;
            winBrowserFile browse = new winBrowserFile();
            browse.ShowDialog();
            if (Global.DataTransfer!=null)
            {
                txtPath.Text = Global.DataTransfer.ToString();
            }
        }

       

        
    }
}
