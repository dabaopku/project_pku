using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace VisualCSS_DABAO
{
    public partial class frmMain : Form
    {
        static public string path = "d:\\test\\";
        static public string htmlContent = "";
        static public string bodyContent = "";
        static public int curTabNum = 0;
        public frmMain()
        {
            InitializeComponent();
        }

        private void txtCSS_TextChanged(object sender, EventArgs e)
        {
            RefreshBrowser();
            txtCSS.Focus();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            tabCss.TabPages.Clear();
            newFile();
            FormatCSS();
            RefreshBrowser();
        }
        private void RefreshBrowser()
        {
            if (!Directory.Exists(path))
                Directory.CreateDirectory(path);

            StreamWriter streamWriter = null;
            streamWriter = File.CreateText(OpenedFile.names[curTabNum] + ".css");
            streamWriter.Write(txtCSS.Text);
            streamWriter.Flush();
            streamWriter.Close();

            if (txtContent.Text.Trim() != "")
                bodyContent = txtContent.Text;
            htmlContent = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><link href=\"" + OpenedFile.names[curTabNum] + ".css\" \" rel=\"stylesheet\" type=\"text/css\"></head><body>" + bodyContent + "</body></html>";
            streamWriter = File.CreateText(OpenedFile.names[curTabNum] + ".html");
            streamWriter.Write(htmlContent);
            streamWriter.Flush();
            streamWriter.Close();
            //  browser.Stop();
            //  browser.Url = null;
            browser.Navigate(new Uri(OpenedFile.names[curTabNum] + ".html"));
            //  browser.Url = new Uri("http:\\\\www."+curTabNum.ToString()+".com");
            txttest.Text = browser.Url.ToString() + "  " + (OpenedFile.names[curTabNum] + ".html");
            browser.Refresh();
        }

        private void FormatCSS()
        {
            int curPos = txtCSS.SelectionStart;
            curPos = txtCSS.GetLineFromCharIndex(curPos);
            int LineNum = txtCSS.Lines.Count();
            bool margin = false;
            string newContent = "";
            for (int i = 0; i < LineNum; i++)
            {
                string curLine = txtCSS.Lines[i];
                curLine = curLine.Trim(' ');
                curLine = curLine + "\n";
                int pos;
                if (!margin)
                {
                    pos = curLine.IndexOf('{');
                    if (pos != -1)
                        margin = true;
                    newContent += curLine;
                }
                else
                {
                    pos = curLine.IndexOf('}');
                    if (pos != -1)
                    {
                        margin = false;
                        newContent += curLine;
                    }
                    else
                    {
                        newContent += "    " + curLine;
                    }
                }
            }
            txtCSS.Text = newContent;
            curPos = txtCSS.GetFirstCharIndexFromLine(curPos);
            txtCSS.Select(curPos, 0);

        }
        private void txtCSS_KeyUp(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    FormatCSS();
                    break;

            }
            Refresh();

        }
        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
#if false
            if (File.Exists(cssFileName))
            {
                try
                {
                    File.Delete(cssFileName);
                }
                catch
                {
                    return;
                }
            }
            if (File.Exists(htmlFileName))
            {
                try
                {
                    File.Delete(htmlFileName);
                }
                catch
                {
                    return;
                }
            }
             try
            {
                Directory.Delete(path);
            }
            catch (System.Exception ex)
            {
            }
#endif
        }
        private void newFile()
        {
            OpenedFile.num++;
            int n = OpenedFile.num;
            string s = OpenedFile.newFilename + n.ToString();
            OpenedFile.shortnames.Add(s);
            string s2 = path + s;
            OpenedFile.names.Add(s2);

            tabCss.TabPages.Add(s);
            TabPage t = tabCss.TabPages[tabCss.TabPages.Count - 1];
            t.Name = s;
            tabCss.SelectTab(s);
            curTabNum = tabCss.TabPages.IndexOf(t);
            txtCSS.Parent = t;
            txtCSS.Text = OpenedFile.newCSSContent;
        }

        private void menuNew_Click(object sender, EventArgs e)
        {
            newFile();
        }

        private void menuOpen_CLICK(object sender, EventArgs e)
        {

        }

        private void tabCss_Selected(object sender, TabControlEventArgs e)
        {
            if (tabCss.TabPages.Count > 0)
            {
                txtCSS.Parent = tabCss.SelectedTab;
                curTabNum = tabCss.TabPages.IndexOf(tabCss.SelectedTab);
                RefreshBrowser();
            }
        }

    }
}
