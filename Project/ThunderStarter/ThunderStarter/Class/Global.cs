using System.Data.OleDb;
using System.Windows;
using System;
using System.Data;
using Microsoft.International.Converters.PinYinConverter;
using System.Text.RegularExpressions;
using System.IO;
using JRO;
using IWshRuntimeLibrary;
using ShortCutLib;
using System.Collections;
using System.Windows.Controls;

namespace ThunderStarter
{
    class Global
    {
        static public object DataTransfer = null;    //数据中转站

        #region 提示
 
        static public void ShowError(string content)
        //显示错误
        {
            MessageBox.Show(content, "错误", MessageBoxButton.OK, MessageBoxImage.Error);
        }

        static public void ShowError(string content, string title)
        //显示错误
        {
            MessageBox.Show(content, "错误 - " + title, MessageBoxButton.OK, MessageBoxImage.Error);
        }

        static public void ShowMessage(string content)
        //显示信息
        {
            MessageBox.Show(content, "信息" , MessageBoxButton.OK, MessageBoxImage.Information);
        }

        static public void ShowMessage(string content, string title)
        //显示信息
        {
            MessageBox.Show(content, "信息 - " + title, MessageBoxButton.OK, MessageBoxImage.Information);
        }
 #endregion

        
        static public string CreateShortCut(Hashtable data)
            //创建快捷方式
        {
            //快捷方式存储目录
            if (!Directory.Exists(ThunderStarter.Properties.Resources.strLinkDir))
            {
                try
                {
                    Directory.CreateDirectory(ThunderStarter.Properties.Resources.strLinkDir);
                }
                catch (System.Exception ex)
                {
                    Global.ShowError("创建存储文件夹失败", "创建快捷方式");
                    throw ex;
                }
            }

            //快捷方式名称
            string name = data["Name"].ToString();
            name = name.GetHashCode().ToString()+".lnk";
            string fullname=ThunderStarter.Properties.Resources.strLinkDir+name;
  
            //新建快捷方式
            WshShell shell = new WshShell();
            IWshShortcut shortcut = (IWshShortcut)shell.CreateShortcut(fullname);

            shortcut.TargetPath = data["Path"].ToString();
            shortcut.WindowStyle = 1;
            if (data.ContainsKey("Detail"))
            {
                shortcut.Description = data["Detail"].ToString();
            }
            
            shortcut.Save();
            return name;
        }
       
        static public string GetShortCutTarget(string link)
            //获得快捷方式目标位置
        {
            if (!System.IO.File.Exists(link))
                return link;
            ShellShortcut shortcut = new ShellShortcut(link);
            if(shortcut.Path!=null && shortcut.Path!="")
            return shortcut.Path;
            else return link;
        }

        static public Image GetIcon(string path ,int size,string name)
            //获得文件图标
        {
            //扩展名
            string ext = System.IO.Path.GetExtension(path).TrimStart('.');
            string ico = @"./Data/Icons/" + ext + ".bmp";
            ico = System.IO.Path.GetFullPath(ico);

            #region 快捷方式

            if (ext == "lnk" || ext == "exe" || ext == "ico")  //快捷方式 可执行程序 本身是图标
            {

                ico = @"./Data/Icons/" + name.GetHashCode().ToString() + ".bmp";
                ico = System.IO.Path.GetFullPath(ico);
                try
                {
                    if (!Directory.Exists(@"./Data/Icons/"))
                        Directory.CreateDirectory(@"./Data/Icons/");
                }
                catch(Exception ex) { throw ex; }

                if (!System.IO.File.Exists(ico))
                {
                    try
                    {
                        //System.Drawing.Icon ic = new GetSystemIcon().GetIconByFileName(path);
                        System.Drawing.Icon ic = CGetFileIcon.GetLargeIcon(path);
                        System.Drawing.Bitmap bm = ic.ToBitmap();

                        bm.Save(ico);
                    }
                    catch 
                    {
                        return null;
                    }
                }

            }
#endregion

            #region 文件夹        

            else if (ext == "")//文件夹
            {
                ico = @"./Data/Icons/" + name.GetHashCode().ToString() + ".bmp";
                ico = System.IO.Path.GetFullPath(ico);
                if (!System.IO.File.Exists(ico))
                {
                    try
                    {
                        ext = "folder";
                        if (System.IO.Path.GetFullPath(path) == System.IO.Path.GetPathRoot(path))
                        {
                            ext = "driver";
                        }
                        
                        System.Drawing.Icon ic = CGetFileIcon.GetLargeIcon(path);
                        System.Drawing.Bitmap bm = ic.ToBitmap();
                        bm.Save(ico);
                    }
                    catch
                    {
                        return null;
                    }
                }
            }
 #endregion
           
            #region 一般文件

            else
            {
                if (!System.IO.File.Exists(ico))
                {
#if R
 try
                    {
#endif
                        System.Drawing.Icon ic = CGetFileIcon.GetLargeIcon(path);
                        System.Drawing.Bitmap bm = ic.ToBitmap();
                        bm.Save(ico);
#if R
  }
                    catch
                    {
                        return null;
                    }
#endif
                }
            }
#endregion

            //创建图标
            var image = new System.Windows.Controls.Image();
            image.Width = (double)size;
            image.Height = (double)size ;
            image.Source = new System.Windows.Media.Imaging.BitmapImage(new Uri(ico));
            return image;
        }

        static public void Execute(Window parent, Hashtable hs)
            //运行程序
        {
#if R
 try
            {
#endif
                string path = hs["Path"].ToString();
                string name = hs["Name"].ToString();
                string shortcut = ThunderStarter.Properties.Resources.strLinkDir
                    + (string)hs["ShortCut"];
                int rank = (int)hs["Rank"] + 1;
                DataBase.UpdateProperty(name, "Rank", rank.ToString());

                //运行程序
                var pro = new System.Diagnostics.Process();
                if (System.IO.File.Exists(shortcut))
                {
                    pro.StartInfo.FileName = shortcut;
                }
                else pro.StartInfo.FileName = path;
#if R
      
            try
            {
#endif
                pro.Start();
#if R
 }
            catch (System.Exception ex)
            {
                Global.ShowError(ex.Message, "启动程序");
            }
#endif

                //试图修复快捷方式
                if (!System.IO.File.Exists(shortcut))
                {
                    if(!hs.ContainsKey("Detail"))
                        hs.Add("Detail", "");
                    string s = Global.CreateShortCut(hs);
                    if (s != null)
                    {
                        DataBase.UpdateProperty(name, "ShortCut", s);
                        shortcut = s;
                    }
             } 
#if R  
            }


            catch (System.Exception ex)
            {
                Global.ShowError(ex.Message, "启动程序");
                return;
            }
            finally
            {
#endif
            if(parent!=null)
                parent.Close();
#if R
 }
#endif
        }
        static public void Execute(Window parent,DataRow dr)
        {
            Hashtable hs = new Hashtable();
            hs.Add("Name", dr.ItemArray[(int)ShortCutTableCollum.Name].ToString());
            hs.Add("Path", dr.ItemArray[(int)ShortCutTableCollum.Path].ToString());
            hs.Add("ShortCut", dr.ItemArray[(int)ShortCutTableCollum.ShortCut].ToString());
            hs.Add("Detail", dr.ItemArray[(int)ShortCutTableCollum.Detail].ToString());
            hs.Add("Rank", (int)dr.ItemArray[(int)ShortCutTableCollum.Rank]);
            Execute(parent, hs);
        }
    }

    public enum ShortCutTableCollum
    {
        Name ,
        Path ,
        Detail ,
        Extension ,
        Type ,
        FileName ,
        Icon ,
        Dirty ,
        PinYin ,
        Rank ,
        ShortCut ,
    }
}
