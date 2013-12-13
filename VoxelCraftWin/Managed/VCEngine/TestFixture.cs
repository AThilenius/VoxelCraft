using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class TestFixture
    {

        internal static void OnStart()
        {
            Font.GetFont("Calibri", 8);

            //Label testBase = new Label("This is a test string to show depth");
            //testBase.Font = Font.GetFont("Cambria", 24);
            //Control.MainControl.AddControl(testBase);
            //testBase.Frame = new Rectangle(50, 100, testBase.Frame.Width, testBase.Frame.Height);

            //Menu testMenu = new Menu();
            //testBase.AddControl(testMenu);
            //testMenu.AddItem("Item One");
            //testMenu.AddItem("Item Two");
            //testMenu.AddItem("Very Long Item 3");
            //testMenu.DisplayAt(new Point(150, 0));
        }

        public static void PerUpdate()
        {
        }

        public static void LatePerUpdate()
        {
            Font.GetFont("Cambria", 24).DrawString("This is a test string to show depth", new Point(50, 100), Color.Black);
            Gui.DrawRectangle(new Rectangle(100, 50, 200, 200), Color.ControlRed);
        }


    }
}
