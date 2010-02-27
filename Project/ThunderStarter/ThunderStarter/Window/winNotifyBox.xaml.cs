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
using System.Collections;

namespace ThunderStarter
{
    /// <summary>
    /// winNotifyBox.xaml 的交互逻辑
    /// </summary>
    public partial class winNotifyBox : Window
    {
        public winNotifyBox()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            #if f
var screen = new System.Drawing.Rectangle();
            screen = System.Windows.Forms.Screen.GetWorkingArea(screen);
            this.Left = screen.Width - this.Width;
            this.Top = screen.Height - this.Height;
#endif
            SelectTop10();             
        }
        private void SelectTop10()
            //选择常用链接
        {
            string sql = ThunderStarter.Properties.Resources.strTop10;
            DataSet ds=DataBase.ExecuteQuery(sql);
            if(ds!=null && ds.Tables.Count>0)
            {
                foreach(DataRow dr in ds.Tables[0].Rows)
                {
                    Hashtable hs = new Hashtable(3);
                    hs.Add("Name", dr.ItemArray[0] as string);
                    hs.Add("Path", dr.ItemArray[1] as string);
                    hs.Add("ShortCut", dr.ItemArray[2] as string);
                    hs.Add("Rank", (int)dr.ItemArray[3]);
                    ctrlNotifyItem ni;
                   #if R
 try
                    {
#endif
                        ni = new ctrlNotifyItem(hs);
                    #if R
}
                    catch
                    {

                        continue;
                  
}
#endif
                    Container.Children.Add(ni);                    
                }
            }
        }

       

        private void Window_Deactivated(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
