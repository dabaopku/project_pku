using System;
using System.Windows;
using System.Data;
using System.Windows.Interop;
using System.Windows.Forms;
using System.Collections.Generic;

namespace ThunderStarter
{
    /// <summary>
    /// winStart.xaml 的交互逻辑
    /// </summary>
    public partial class winStart : Window
    {
        public winStart()
        {
            InitializeComponent();            
        }
 
        private void Window_Load(object sender, RoutedEventArgs e)
            //窗体加载
        {
            NewNotifyIcon();
            RegisterHotKey();
        }

        #region OK

        #region 数据库

        private void ViewDataBase(object sender, RoutedEventArgs e)
            //查看数据库
        {
            DataBase.ShowDataBase();
        }

        private void OptiMizeDataBase(object sender, RoutedEventArgs e)
            //压缩数据库
        {
            DataBase.ZipDataBase();
        }

        private void CheckDataBase(object sender, RoutedEventArgs e)
            //检查数据库无效内容
        {
            DataTable dt=DataBase.CheckDataBase();
            if(dt!=null){
                winShowDataBase newfrm = new winShowDataBase();
                newfrm.LoadData(dt);
                newfrm.ShowDialog();
            }
        }

        #endregion

        #region 热键

        private void RegisterOneKey(out HotKey hk,HotKey.KeyFlags con,Keys k,HotKey.OnHotkeyEventHandeler ohk)
            //注册一个系统热键
        {
            hk = null;
            try
            {
                hk = new HotKey(this, con, k);
            }
            catch (Exception ex)
            {
                Global.ShowError(ex.Message,"注册热键");
            }
            hk.OnHotKey += ohk;

        }

        private void RegisterHotKey()
            //注册热键
        {
            HotKey hotkey;
            RegisterOneKey(out hotkey, HotKey.KeyFlags.MOD_WIN, Keys.G, ShowMe);
                //win+G 召出窗口
            RegisterOneKey(out hotkey, HotKey.KeyFlags.MOD_WIN, Keys.S, ShowSearch);
                //win+S 搜索窗口
        }
        
        private void ShowSearch(object sender, RoutedEventArgs e)
            //打开搜索窗口
        {
            winSearch search = new winSearch();
            search.Show();
            //search.Focus();
            search.Activate();
            search.WindowState = WindowState.Normal;
        }
              
        void ShowSearch()
            //win+S 搜索
        {
            ShowSearch(null, null);
        }

        void ShowMe()
            //Win+G 改变窗口显示状态
        {
            if (!this.IsVisible)
            {
                this.Show();
                this.WindowState = WindowState.Normal;
            }
            else
            {
                this.WindowState = WindowState.Minimized;
            }
        }

        #endregion
 
        #region 托盘

        NotifyIcon nticon= new NotifyIcon();    //窗体托盘

        private void Window_StateChanged(object sender, EventArgs e)
            //窗体最小化,隐藏并显示托盘
        {
            if (this.WindowState==WindowState.Minimized)
            {
                nticon.Visible = true;
                this.Hide();
            }
            else
            {
                nticon.Visible = false;
                this.Show();
            }
        }
        private void nticon_Click(object sender,MouseEventArgs e)
            //鼠标单击
        {
            if(e.Button==MouseButtons.Left)
            {
                nticon.Visible = false;
                this.Show();
                this.WindowState = WindowState.Normal;
            }
        }

        private ContextMenu cm = new ContextMenu();
        static private void NewMenuItem(ContextMenu cm,string txt,EventHandler eh)
        {
            MenuItem mi = new MenuItem();
            mi.Text = txt;
            mi.Click += eh;
            cm.MenuItems.Add(mi);
        }
        private void CreateIconMenu()
            //创建菜单
        {
            NewMenuItem(cm, "打开主界面\twin+G", ShowMe);
            NewMenuItem(cm, "立即搜索\twin+S", ShowSearch);
            NewMenuItem(cm, "-", null);
            NewMenuItem(cm, "退出程序\tAlt+F4", Quit);

        }
        private void NewNotifyIcon()
            //初始化托盘图标
        { 
            nticon.Icon = ThunderStarter.Properties.Resources.logo;
            nticon.Visible = false;
            nticon.Text="疾风启动";
            CreateIconMenu();
            nticon.ContextMenu = cm;
            nticon.MouseClick+=new MouseEventHandler(nticon_Click);
        }
 
        private void Quit(object sender, RoutedEventArgs e)
            //退出
        {
            Close();
        }

        private void Quit(object sender, EventArgs e)
            //退出
        {
            Close();
        }
       
        private void ShowMe(object sender, EventArgs e)
            //显示主界面
        {
            ShowMe();
        }
        private void ShowSearch(object sender, EventArgs e)
        //显示搜索界面
        {
            ShowSearch();
        }

        #endregion

        private void Window_Drop(object sender, System.Windows.DragEventArgs e)
            //拖放文件
        {
            winShortCut newform = new winShortCut(e);
            newform.Show();
        }


        #endregion

        private void Window_Closed(object sender, EventArgs e)
            //结束程序
        {
            nticon.Dispose();
            Close();
       }
              
       
    }
}
