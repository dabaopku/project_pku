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

namespace ThunderStarter
{
    class Global
    {
        static public object DataTransfer = null;    //数据中转站

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
                return "";
            ShellShortcut shortcut = new ShellShortcut(link);
            return shortcut.Path;
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
