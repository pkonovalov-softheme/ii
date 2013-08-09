using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Text;
using System.Timers;
using System.Diagnostics;
using System.Drawing;

namespace ai3
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Form f1 = new Form1();
            Application.Run(f1);

            // wrap w = new wrap();
            // w.na4atOtbor();


        }

    }
}


