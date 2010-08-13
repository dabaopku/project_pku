using System.Windows;
using System.Windows.Controls;
using System.Windows.Shapes;
using System.IO;
using System;
using System.Drawing;
using System.Windows.Media.Imaging;
using ShortCutLib;

namespace ThunderStarter
{
    /// <summary>
    /// winBrowserFile.xaml 的交互逻辑
    /// </summary>
    public partial class winBrowserFile : Window
    {      

        private object dummy = null;
        private string curPath="";

        #region OK
 
        public winBrowserFile()
            //构造函数
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
             //初始化
        {
            AddRootDirectory();
        }
        
        private void AddRootDirectory()
             //添加根目录
        {
            //桌面
            string str = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            treeDirectory.Items.Add(NewTreeViewItem(str));
            //我的文档
            str = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            treeDirectory.Items.Add(NewTreeViewItem(str));
            //系统磁盘
            string [] drivers=Directory.GetLogicalDrives();
            foreach (string s in drivers)
                treeDirectory.Items.Add(NewTreeViewItem(s));

            if (treeDirectory.HasItems)
            {
                TreeViewItem item=(TreeViewItem)treeDirectory.Items[0];
                curPath = (string)item.Header;
                item.IsExpanded = true;
                item.Focus();
            }
            ShowFileInThisDirectory(curPath);       
        }

        private void TreeNode_Expand(object sender,RoutedEventArgs e)
            //打开树节点
        {
            TreeViewItem item=(TreeViewItem)sender;
            if (item.Items.Count ==1 && item.Items[0] == dummy)
            {
                item.Focus();
                curPath = (string)item.Tag;
                ShowDirectoryInThisDirectory(item, curPath);
            }
        }

        private void TreeNode_Click(object sender, RoutedPropertyChangedEventArgs<object> e)
            //选中结点
        {
            TreeViewItem item = (sender as TreeView).SelectedItem as TreeViewItem;
            curPath = (string)item.Tag;
            this.Title = curPath;
            ShowFileInThisDirectory(curPath);
        }
       
        void ShowFileInThisDirectory(string Dir)
            //显示指定目录的文件
        {
            if (!Directory.Exists(Dir))
                return;
            treeFile.Items.Clear();
            string[] Files = { };
            try
            {
                Files = Directory.GetFiles(Dir);
            }
            catch(IOException) { }
            catch(UnauthorizedAccessException){}
            foreach (string s in Files)
            {
                if ( (File.GetAttributes(s) & FileAttributes.Hidden) == FileAttributes.Hidden)
                    continue;
                treeFile.Items.Add(NewListItem(s));
            }         
        }
       
        void ShowDirectoryInThisDirectory(TreeViewItem item,string Dir)
            //显示指定目录的子文件夹
        {
            if (!Directory.Exists(Dir))
                return;
            item.Items.Clear();
            string[] dirs = {};
            try
            {
                dirs = Directory.GetDirectories(Dir);
            }
            catch { }
            foreach (string s in dirs)
            {
                if ((new DirectoryInfo(s).Attributes & FileAttributes.Hidden) == FileAttributes.Hidden)
                    continue;
                item.Items.Add(NewTreeViewItem(s));
            }
        }
        
        TreeViewItem NewTreeViewItem(string path)
            //新建树节点
        {
            TreeViewItem retitem = new TreeViewItem();
            retitem.Header = System.IO.Path.GetFileName(path);
            if ((string)retitem.Header=="")
            {
                retitem.Header=path;
            }
            retitem.Tag = path;
            retitem.Items.Add(dummy);
            retitem.Expanded += TreeNode_Expand;
            return retitem;
        }
 
        ListBoxItem NewListItem(string path)
            //新建文件结点
        {
            if (!File.Exists(path))
                return null;

            ListBoxItem item = new ListBoxItem();
            item.Tag= path;
            //容器
            StackPanel sp = new StackPanel();
            sp.Orientation = Orientation.Horizontal;
            sp.Height = 50;
            sp.Width = 150;
            sp.Margin = new Thickness(5, 0, 5, 0);

            //标签
            TextBlock tb = new TextBlock();
            tb.TextWrapping = TextWrapping.Wrap;
            tb.VerticalAlignment = VerticalAlignment.Center;
            tb.Text = System.IO.Path.GetFileName(path);
            tb.Margin = new Thickness(3,0,0,0);
            tb.Width = 110;

            //图标
            #if f
string ext = System.IO.Path.GetExtension(path).TrimStart('.');//扩展名
            string ico = @"./Data/Icons/" + ext + ".bmp";
            ico = System.IO.Path.GetFullPath(ico);

            if (ext == "lnk" || ext == "exe" || ext == "ico")  //快捷方式 可执行程序 本身是图标
            {
                ico = @"./Data/Icons/" + System.IO.Path.GetFileNameWithoutExtension(path) + ".bmp";
                ico = System.IO.Path.GetFullPath(ico);
                if (!File.Exists(ico))
                {
                    try
                    {
                        Icon ic = new GetSystemIcon().GetIconByFileName(path);
                        Bitmap bm = ic.ToBitmap();

                        bm.Save(ico);
                    }
                    catch (Exception ex)
                    {
                        Global.ShowError(ex.Message);
                        return null;
                    }
                }
                    
            }
            else
            {
                if (!File.Exists(ico))
                {
                    try
                    {
                        if (!Directory.Exists(@"./Data/Icons/"))
                            Directory.CreateDirectory(@"./Data/Icons/");
                        Icon ic = new GetSystemIcon().GetIconByFileType("." + ext, true);
                        Bitmap bm = ic.ToBitmap();
                        bm.Save(ico);
                    }
                    catch
                    {
                        return null;
                    }
                }
            }
            //创建图标
            var image = new System.Windows.Controls.Image();
            image.Width = 32;
            image.Height = 32;
            image.Source = new BitmapImage(new Uri(ico));
#endif
            var image = Global.GetIcon(path,32,System.IO.Path.GetFileNameWithoutExtension(path));
            if (image != null && tb!=null)
            {
                sp.Children.Add(image);
                sp.Children.Add(tb);
                item.Content = sp;
                return item;
            }
            else return null;
        }

        #endregion

        private void SelectDirectory(object sender, RoutedEventArgs e)
            //传递文件夹
        {
            if (curPath!="")
            {
                Global.DataTransfer = curPath;
            }
            this.Close();
        }

        private void NewDirectory(object sender, RoutedEventArgs e)
            //新建文件夹
        {
            string path=curPath+@"\新建文件夹";
            //文件已存在
            if(Directory.Exists(path))
            {
                int i=1;
                while(true){
                    if(!Directory.Exists(path+i.ToString()))
                    {
                        path=path+i.ToString();
                        break;
                    }
                    i++;
                }
            }
            //创建文件夹
            try
            {
                Directory.CreateDirectory(path);
                curPath=path;
            }
            catch (System.Exception ex)
            {
                Global.ShowError(ex.Message, "创建文件夹");
            }
            //添加结点
            var item = NewTreeViewItem(path);
            var curitem=(TreeViewItem)treeDirectory.SelectedItem;
            if (curitem.Items.IndexOf(dummy)!=-1)
            {
                curitem.Items.Remove(dummy);
            }
            curitem.Items.Add(item);
            item.IsExpanded = true;
            item.Focus();
            
        }

        private void Cancle(object sender, RoutedEventArgs e)
            //取消
        {
            Close();
        }

        private void SelectFile(object sender, RoutedEventArgs e)
            //传递文件
        {
            if(treeFile.SelectedItem!=null){
                curPath = ((ListBoxItem)treeFile.SelectedItem).Tag.ToString();
                string extension = System.IO.Path.GetExtension(curPath);
                if (extension == ".lnk")  //快捷方式还原为实际路径
                {
                    curPath = Global.GetShortCutTarget(curPath);
                }
                Global.DataTransfer = curPath;
            }
            Close();
        }       

    }
}
