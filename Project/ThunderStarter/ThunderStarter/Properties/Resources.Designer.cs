﻿//------------------------------------------------------------------------------
// <auto-generated>
//     此代码由工具生成。
//     运行时版本:2.0.50727.3603
//
//     对此文件的更改可能会导致不正确的行为，并且如果
//     重新生成代码，这些更改将会丢失。
// </auto-generated>
//------------------------------------------------------------------------------

namespace ThunderStarter.Properties {
    using System;
    
    
    /// <summary>
    ///   强类型资源类，用于查找本地化字符串等。
    /// </summary>
    // 此类是由 StronglyTypedResourceBuilder
    // 类通过类似于 ResGen 或 Visual Studio 的工具自动生成的。
    // 若要添加或移除成员，请编辑 .ResX 文件，然后重新运行 ResGen
    // (以 /str 作为命令选项)，或重新生成 VS 项目。
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "2.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   返回此类使用的缓存 ResourceManager 实例。
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("ThunderStarter.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   为使用此强类型资源类的所有资源查找
        ///   重写当前线程的 CurrentUICulture 属性。
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        internal static System.Drawing.Icon logo {
            get {
                object obj = ResourceManager.GetObject("logo", resourceCulture);
                return ((System.Drawing.Icon)(obj));
            }
        }
        
        /// <summary>
        ///   查找类似 INSERT INTO TShortCut
        ///( [Name],[Path],[Detail],[FileName],[PinYin],[Extension],[ShortCut] )
        ///VALUES ({0},{1},{2},{3},{4},{5},{6}) 的本地化字符串。
        /// </summary>
        internal static string strAddShortCut {
            get {
                return ResourceManager.GetString("strAddShortCut", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 Provider=Microsoft.Jet.OLEDB.4.0;Data Source=.\Data\DataBase.mdb;Persist Security Info=True 的本地化字符串。
        /// </summary>
        internal static string strDataBaseConection {
            get {
                return ResourceManager.GetString("strDataBaseConection", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 .\Data\DataBase.mdb 的本地化字符串。
        /// </summary>
        internal static string strDataBaseName {
            get {
                return ResourceManager.GetString("strDataBaseName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 SELECT [Name] AS 名称,[Path] AS 路径,[ShortCut] AS 快捷方式
        ///FROM TShortCut 的本地化字符串。
        /// </summary>
        internal static string strGetNamePath {
            get {
                return ResourceManager.GetString("strGetNamePath", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 .\Data\ShortCut\ 的本地化字符串。
        /// </summary>
        internal static string strLinkDir {
            get {
                return ResourceManager.GetString("strLinkDir", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 SELECT * FROM TShortCut
        ///WHERE ([Name] LIKE &apos;%{0}%&apos;) OR ([PinYin] LIKE &apos;%{0}%&apos;)
        /// OR ([FileName] LIKE &apos;%{0}%&apos;)  OR ([Detail] LIKE &apos;%{0}%&apos;)
        /// OR ([Extension] LIKE &apos;%{0}%&apos;)
        ///ORDER BY [Rank] DESC 的本地化字符串。
        /// </summary>
        internal static string strSearchShortCut {
            get {
                return ResourceManager.GetString("strSearchShortCut", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 SELECT [Name] AS 名称, [Path] AS 路径, [Detail] AS 描述,[Rank] AS 人气
        ///FROM TShortCut
        ///ORDER BY [Rank] DESC 的本地化字符串。
        /// </summary>
        internal static string strShowDataBase {
            get {
                return ResourceManager.GetString("strShowDataBase", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 UPDATE TShortCut
        ///SET [{0}]={1}
        ///WHERE [Name]={2} 的本地化字符串。
        /// </summary>
        internal static string strUpdateProperty {
            get {
                return ResourceManager.GetString("strUpdateProperty", resourceCulture);
            }
        }
        
        /// <summary>
        ///   查找类似 UPDATE TShortCut
        ///SET [Name]={0},[Detail]={1},[Path]={2},[PinYin]={3}
        ///WHERE [Name]={0} 的本地化字符串。
        /// </summary>
        internal static string strUpdateShortCut {
            get {
                return ResourceManager.GetString("strUpdateShortCut", resourceCulture);
            }
        }
    }
}