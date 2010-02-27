using System;
using System.Windows;
using System.Data;
using System.Windows.Interop;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Windows.Threading;

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
            RegisterHotKey();
            CreateNotifyicon();
        }

        #region 托盘

        private ctrlNotifyIcon notifyicon;

        private void CreateNotifyicon()
            //创建托盘图标
        {
            notifyicon = new ctrlNotifyIcon();
            notifyicon.Icon.MouseClick += notifyicon_Click;
            CreateIconMenu();
        }

        private void notifyicon_Click(object sender, MouseEventArgs e)
            //显示窗口
        {
            if (e.Button == MouseButtons.Left)
            {
                this.ShowMe();
                notifyicon.Menu.HideMenu();
                notifyicon.Popup.HidePopup();
            }
        }
 
        private void CreateIconMenu()
            //创建菜单
        {
            notifyicon.Menu.AddMenuItem("打开主界面\twin+G", ShowMe);
            notifyicon.Menu.AddMenuItem( "立即搜索\twin+S", ShowSearch);
            notifyicon.Menu.AddMenuItem( "-", null);
            notifyicon.Menu.AddMenuItem( "退出程序\tAlt+F4", Quit);

        }

        #endregion

        #region OK

        #region 数据库

        private void ViewDataBase(object sender, RoutedEventArgs e)
            //查看数据库
        {
            this.Cursor = System.Windows.Input.Cursors.Wait;
            DataBase.ShowDataBase();
            this.Cursor = System.Windows.Input.Cursors.Arrow;
        }

        private void OptiMizeDataBase(object sender, RoutedEventArgs e)
            //压缩数据库
        {
            this.Cursor = System.Windows.Input.Cursors.Wait;
            DataBase.ZipDataBase();
            this.Cursor = System.Windows.Input.Cursors.Arrow;
        }

        private void CheckDataBase(object sender, RoutedEventArgs e)
            //检查数据库无效内容
        {
            this.Cursor = System.Windows.Input.Cursors.Wait;
            DataTable dt = DataBase.CheckDataBase();
            this.Cursor = System.Windows.Input.Cursors.Arrow;
            if (dt != null)
            {
                winShowDataBase newfrm = new winShowDataBase();
                newfrm.LoadData(dt);
                newfrm.ShowDialog();
            }
            else
                Global.ShowMessage("恭喜你!数据库正常!", "检查数据库");
            this.Cursor = System.Windows.Input.Cursors.Arrow;
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
            search.Activate();
            search.WindowState = WindowState.Normal;
        }
              
        void ShowSearch()
            //win+S 搜索
        {
            ShowSearch(null, null);
        }

        void ShowMe()
            //Win+G 窗口显示
        {
            this.Show();
            this.WindowState = WindowState.Normal;
            this.Activate();
        }

        #endregion
 

 //#region 托盘

       


 
        #region common methods
 
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


        private void ShowMe(object sender, RoutedEventArgs e)
            //显示主界面
        {
            ShowMe();
        }

      
        private void Window_Drop(object sender, System.Windows.DragEventArgs e)
        //拖放文件
        {
            winShortCut newform = new winShortCut(e);
            newform.Show();
        }
        
        private void Window_Closed(object sender, EventArgs e)
        //结束程序
        {
            notifyicon.Icon.Dispose();
            Close();
        }

        private void Window_StateChanged(object sender, EventArgs e)
        {
            if (this.WindowState == WindowState.Minimized)
            {
                this.Hide();
            }
        }
        #endregion


        #endregion        
    }
}
