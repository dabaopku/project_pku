using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Data.OleDb;
using System.Data;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Collections;

namespace ThunderStarter
{
    /// <summary>
    /// winSearch.xaml 的交互逻辑
    /// </summary>
    public partial class winSearch : Window
    {               
        #region Events
       
        public winSearch()
            //构造函数
        {
            InitializeComponent();
        }

        private void txtSearch_TextChanged(object sender, TextChangedEventArgs e)
            //更改输入框
        {
            Search(txtSearch.Text); 
        }
  
        private void Window_Load(object sender, RoutedEventArgs e)
            //窗体加载
        {
            txtSearch.Focus();
             
        }
         
        private void Window_Drop(object sender, DragEventArgs e)
            //拖放文件
        {
            winShortCut newform = new winShortCut(e);
            newform.Show();
        }
      
        private void txtSearch_KeyDown(object sender, KeyEventArgs e)
            //文本框按键
        {
            switch (e.Key)
            {
                case Key.Down:
                case Key.Up:
                    if (Search(txtSearch.Text))
                    {
                        lstMatch.SelectedIndex = 0;
                        lstMatch.Focus();
                        PopUp.IsOpen = true;
                    }
                    break;
                case Key.Enter:
                case Key.Tab:
                    if (lstMatch.Items.Count > 0)
                    {
                        Execute((DataRow)((ListBoxItem)lstMatch.Items[0]).Tag);
                    }
                    break;
                default:
                    break;
            }

        }
        
        private void lstMatch_KeyDown(object sender, KeyEventArgs e)
            //弹出框按键
        {            
            switch (e.Key)
            {
                case Key.Down:  case Key.Up: case Key.Home:
                case Key.End:  case Key.PageDown: case Key.PageUp:
                    break;
                case Key.Enter: case Key.Space:
                case Key.Tab:
                    if (lstMatch.SelectedIndex>=0)
                    {
                        DataRow dr = (DataRow)((ListBoxItem)lstMatch.SelectedItem).Tag;
                        e.Handled = true;
                        txtSearch.Focus();
                        Execute(dr);
                        lstMatch.Items.Clear();
                    }
                    break;
                default:
                    txtSearch.Focus();
                    break;
            }
        }
 
        private void lstMatch_MouseClick(object sender, MouseButtonEventArgs e)
            //弹出框单击
        {
            if (lstMatch.SelectedIndex >= 0)
            {
                DataRow dr = (DataRow)((ListBoxItem)lstMatch.SelectedItem).Tag;
                txtSearch.Focus();
                Execute(dr);
                lstMatch.Items.Clear();
            }
        }

        private void MenuItemOpen_Click(object sender, RoutedEventArgs e)
            //右键打开
        {
            if (lstMatch.SelectedIndex >= 0)
            {
                DataRow dr = (DataRow)((ListBoxItem)lstMatch.SelectedItem).Tag;
                txtSearch.Focus();
                Execute(dr);
                lstMatch.Items.Clear();
            }
        }

        private void MenuItemEdit_Click(object sender, RoutedEventArgs e)
            //右键修改
        {
            if (lstMatch.SelectedIndex >= 0)
            {
                winShortCut newfrm = new winShortCut((DataRow)((ListBoxItem)lstMatch.SelectedItem).Tag);
                newfrm.ShowDialog();
            }
        }

        private void MenuItemShowDatabase_Click(object sender, RoutedEventArgs e)
            //右键显示数据库
        {
            DataBase.ShowDataBase();
        }
 
        private void Window_PreviewKeyDown(object sender, KeyEventArgs e)
            //esc 窗体关闭
        {
            switch(e.Key)
            {
                case Key.Escape:
                    this.Close();
                    break;
                default:
                    break;
            }
        } 

        #endregion
       
        #region Core

        bool Search(string keyWord)
         //检索匹配项
        {
            lstMatch.Items.Clear();
            string sql = ThunderStarter.Properties.Resources.strSearchShortCut;
            keyWord = keyWord.ToLower();
            keyWord = Regex.Replace(keyWord, "[\\[\\]']", "");
            sql = String.Format(sql, keyWord);

            DataSet ds = DataBase.ExecuteQuery(sql);
            if(ds!=null && ds.Tables.Count>0){
                foreach (DataRow dr in ds.Tables[0].Rows)
                {
                    ListBoxItem it = new ListBoxItem();
                    it.Tag = dr;
                    it.Content = dr.ItemArray[(int)ShortCutTableCollum.Name].ToString();
                    lstMatch.Items.Add(it);
                }
            }
            PopUp.IsOpen = true;
            return lstMatch.HasItems;
        }
 
        private void Execute( DataRow dr)
            //运行程序
        {            
            try
            {                
                string path = (string)dr.ItemArray[(int)ShortCutTableCollum.Path].ToString();
                string name = (string)dr.ItemArray[(int)ShortCutTableCollum.Name].ToString();
                string shortcut = ThunderStarter.Properties.Resources.strLinkDir
                    + (string)dr.ItemArray[(int)ShortCutTableCollum.ShortCut].ToString();
                int rank = (int)dr.ItemArray[(int)ShortCutTableCollum.Rank] + 1;
                DataBase.UpdateProperty(name, "Rank", rank.ToString());
                
                //运行程序
                Process pro = new Process();
                if (System.IO.File.Exists(shortcut))
                {
                    pro.StartInfo.FileName = shortcut;
                }
                else pro.StartInfo.FileName = path;
                pro.Start();

                //试图修复快捷方式
                if (!System.IO.File.Exists(shortcut))
                {
                    Hashtable data = new Hashtable();
                    data.Add("Name", name);
                    data.Add("Path", path);
                    string detail = (string)dr.ItemArray[(int)ShortCutTableCollum.Detail].ToString();
                    data.Add("Detail",detail);
                    string s=Global.CreateShortCut(data);
                    if (s != null)
                    {
                        DataBase.UpdateProperty(name, "ShortCut", s);
                        shortcut=s;
                    }
                }
            }
            catch (System.Exception ex)
            {
                Global.ShowError(ex.Message,"启动程序");
                return;
            }
            finally
            {
                this.Close();
            }
        }
              
        #endregion


    }
}
