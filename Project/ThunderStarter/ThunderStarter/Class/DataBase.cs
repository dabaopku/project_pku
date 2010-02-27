using System;
using System.Data.OleDb;
using System.Data;
using System.IO;
using System.Collections;
using Microsoft.International.Converters.PinYinConverter;
using System.Text.RegularExpressions;

namespace ThunderStarter
{
    class DataBase
    {
        #region DataBase

        static OleDbConnection ConnectDatabase()
        //连接数据库
        {
            OleDbConnection conn = new OleDbConnection(global::ThunderStarter.Properties.Resources.strDataBaseConection);
            try
            {
                conn.Open();
            }
            catch (System.Exception ex)
            {
                Global.ShowError(ex.Message, "连接数据库");
                conn.Dispose();
                conn = null;
            }
            return conn;
        }

        static public void UpdateProperty(string Name, string property, string value)
        //更改单项值
        {
            string sql = ThunderStarter.Properties.Resources.strUpdateProperty;
            sql = String.Format(sql, property, DataBase.FormatString(value), DataBase.FormatString(Name));
            DataBase.ExecuteNonQuery(sql);
        }

        static public int ExecuteNonQuery(string sql)
        //执行非查询语句
        {
            OleDbConnection conn = DataBase.ConnectDatabase();
            if (conn == null)
                return -1;

            //执行sql
            OleDbCommand olc = new OleDbCommand(sql, conn);
            int retval = -1;
            try
            {
                retval = olc.ExecuteNonQuery();
            }
            catch (System.Exception ex)
            {
                Global.ShowError(ex.Message, "更新数据库");
                return -1;
            }
            finally
            {
                conn.Dispose();
            }
            return retval;
        }

        static public DataSet ExecuteQuery(string sql)
        //执行查询操作
        {
            OleDbConnection conn = DataBase.ConnectDatabase();
            if (conn == null)
                return null;

            DataSet ds = new DataSet();
            try
            {
                OleDbDataAdapter oda = new OleDbDataAdapter(sql, conn);
                oda.Fill(ds);
            }
            catch (System.Exception ex)
            {
                Global.ShowError(ex.Message, "数据库查询");
                ds = null;
            }
            finally
            {
                conn.Dispose();
            }
            GC.Collect();
            return ds;
        }

        static public void ShowDataBase()
        //显示数据库
        {
            string tmp = ThunderStarter.Properties.Resources.strShowDataBase;
            winShowDataBase newfrm = new winShowDataBase();
            newfrm.LoadData(tmp);
            newfrm.ShowDialog();
        }

        static public void ZipDataBase()
        //压缩数据库
        {

            //定义临时数据库的连接字符串
            string temp = Path.GetTempFileName() + ".mdb";
            string temp2 = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=\"" + temp + "\";Jet OLEDB:Engine Type=5";

            //创建一个JetEngineClass对象的实例
            JRO.JetEngine jt = new JRO.JetEngine();
            try
            {
                jt.CompactDatabase(ThunderStarter.Properties.Resources.strDataBaseConection, temp2);
            }
            catch (System.Exception ex)
            {
                Global.ShowError("压缩数据库失败!\r\n" + ex.Message);
            }


            try
            {
                System.IO.File.Copy(temp, ThunderStarter.Properties.Resources.strDataBaseName, true);
            }
            catch (System.Exception ex)
            {
                Global.ShowError("压缩数据库失败!\r\n" + ex.Message);
            }
            try
            {
                System.IO.File.Delete(temp);
            }
            catch { }

        }

        static public DataTable CheckDataBase()
        //查找无效数据
        {
            //检索3列,名称,路径和快捷方式,存入ds表,dt是错误记录表
            string sql = ThunderStarter.Properties.Resources.strGetNamePath;
            DataSet ds = DataBase.ExecuteQuery(sql);
            if (ds == null | ds.Tables.Count == 0)
                return null;
            DataTable dt = ds.Tables[0].Clone();

            //对每条记录
            foreach (DataRow dr in ds.Tables[0].Rows)
            {
                string name = dr.ItemArray[0].ToString();
                string path = dr.ItemArray[1].ToString();
                string link = dr.ItemArray[2].ToString();

                //先看绝对路径对么
                bool dirty = false;
                if (Path.GetExtension(path) == "")
                {
                    //文件夹
                    if (!Directory.Exists(path))
                    {
                        dirty = true;
                    }
                }
                else
                {
                    if (!System.IO.File.Exists(path))
                    {
                        dirty = true;
                    }
                }
                //绝对路径没问题
                if (!dirty)
                {
                    if (!System.IO.File.Exists(link))
                    //快捷方式不存在,修复快捷方式
                    {
                        Hashtable data = new Hashtable();
                        data.Add("Name", name);
                        data.Add("Path", path);
                        link = Global.CreateShortCut(data);
                        if (link != "")
                        {
                            //修复成功
                            DataBase.UpdateProperty(name, "ShortCut", link);
                        }
                        else
                        {
                            //修复失败
                            dt.Rows.Add(dr.ItemArray);
                        }
                    }
                    continue;
                }

                //试图用快捷方式修复
                if (System.IO.File.Exists(link))
                {
                    string realPath = Global.GetShortCutTarget(
                        ThunderStarter.Properties.Resources.strLinkDir + link);
                    if (realPath != "")
                    {
                        //修复成功
                        DataBase.UpdateProperty(name, "Path", realPath);
                        continue;
                    }
                }
                //写入出错列表中
                dt.Rows.Add(dr.ItemArray);
            }

            //反馈结果
            if (dt.Rows.Count > 0)
                return dt;
            else
            {
                dt.Dispose();
                return null;
            }
        }

        static public void SelectTop10(System.Windows.Controls.StackPanel sp)
        //选择常用链接
        {
            string sql = ThunderStarter.Properties.Resources.strTop10;
            DataSet ds = DataBase.ExecuteQuery(sql);
            if (ds != null && ds.Tables.Count > 0)
            {
                foreach (DataRow dr in ds.Tables[0].Rows)
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
                    sp.Children.Add(ni);
                }
            }
        }

        #endregion

        #region String        

        static public string FormatString(string s)
        //格式化字符串
        {
            return "'" + s.Replace("'", "").ToLower() + "'";
        }

        static public string PinYin(string s)
        //汉字转拼音
        {
            string retval = "";
            foreach (char c in s)
            {
                ChineseChar cc;
                try
                {
                    cc = new ChineseChar(c);
                    string tmp = cc.Pinyins[0];
                    tmp = Regex.Replace(tmp, "\\d+", "").ToLower();
                    retval += tmp;
                }
                catch
                {
                    retval += c.ToString();
                }
            }
            return retval;
        }

        #endregion
    }
}
