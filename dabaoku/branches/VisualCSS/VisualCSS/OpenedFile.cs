using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VisualCSS_DABAO
{
    class OpenedFile
    {
        static public int num = 0;
        static public List<string> names = new List<string>();
        static public List<string> shortnames = new List<string>();
        public const string newFilename = "未命名";
        static public int curFile = -1;
        public const string newCSSContent = "p{\nfont-size:25px;\ncolor:red;\n}";

    }
}
