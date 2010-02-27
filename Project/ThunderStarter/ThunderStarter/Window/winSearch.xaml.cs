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
using System.Data;
using System.Text.RegularExpressions;
using System.Collections;
using System.Diagnostics;

namespace ThunderStarter
{
    /// <summary>
    /// winSearch.xaml 的交互逻辑
    /// </summary>
    public partial class winSearch : Window
    {
        public winSearch()
        {
            InitializeComponent();
        }

       #region Events
            
        private void Exit(object sender, RoutedEventArgs e)
            //退出
        {
            Close();
        }

        private void DragWindow(object sender, MouseButtonEventArgs e)
            //拖动窗体
        {
            this.DragMove();
        }

        private void txtSearch_TextChanged(object sender, TextChangedEventArgs e)
            //更改输入框
        {
            this.Cursor = Cursors.Wait;
            Search(txtSearch.Text);
            this.Cursor = Cursors.Arrow;
        }
  
        private void Window_Load(object sender, RoutedEventArgs e)
            //窗体加载
        {
            txtSearch.Focus();             
        }
         
        private void Window_Drop(object sender, DragEventArgs e)
            //拖放文件
        {
            this.Cursor = Cursors.Wait;
            winShortCut newform = new winShortCut(e);
            newform.ShowDialog();
            this.Cursor = Cursors.Arrow;
        }
      
        private void txtSearch_KeyDown(object sender, KeyEventArgs e)
            //文本框按键
        {
            switch (e.Key)
            {
                case Key.Down:
                case Key.Up:
                    this.Cursor = Cursors.Wait;
                    if (Search(txtSearch.Text))
                    {
                        lstMatch.SelectedIndex = 0;
                        lstMatch.Focus();
                        PopUp.IsOpen = true;
                    }
                    this.Cursor = Cursors.Arrow;
                    break;
                case Key.Enter:
                case Key.Tab:
                    if (lstMatch.Items.Count > 0)
                    {
                        this.Cursor = Cursors.Wait;
                        Global.Execute(this,(DataRow)((ListBoxItem)lstMatch.Items[0]).Tag);
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
                        this.Cursor = Cursors.Wait;
                        Global.Execute(this,dr);
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
                this.Cursor = Cursors.Wait;
                Global.Execute(this,dr);
            }
        }

        private void MenuItemOpen_Click(object sender, RoutedEventArgs e)
            //右键打开
        {
            if (lstMatch.SelectedIndex >= 0)
            {
                DataRow dr = (DataRow)((ListBoxItem)lstMatch.SelectedItem).Tag;
                this.Cursor = Cursors.Wait;
                Global.Execute(this,dr);
            }
        }

        private void MenuItemEdit_Click(object sender, RoutedEventArgs e)
            //右键修改
        {
            if (lstMatch.SelectedIndex >= 0)
            {
                this.Cursor = Cursors.Wait;
                winShortCut newfrm = new winShortCut((DataRow)((ListBoxItem)lstMatch.SelectedItem).Tag);
                newfrm.ShowDialog();
                this.Cursor = Cursors.Arrow;
            }
        }

        private void MenuItemShowDatabase_Click(object sender, RoutedEventArgs e)
            //右键显示数据库
        {
            this.Cursor = Cursors.Wait;
            DataBase.ShowDataBase();
            this.Cursor = Cursors.Arrow;
        } 
        
        private void Escape(object sender, KeyEventArgs e)
            //esc关闭窗口
        {
            if (e.Key==Key.Escape)
            {
                Close();
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
 
        
              
        #endregion

       
    }
}
