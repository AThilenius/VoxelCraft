using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class DirectoryContextMenu : Menu
    {

        private DirectoryExporer m_dirExplorer;
        private DirectoryInfo m_dirInfo;
        private AcceptDenyDialog m_saveDialog;

        public DirectoryContextMenu( DirectoryExporer explorer)
        {
            m_dirExplorer = explorer;

            m_saveDialog = new AcceptDenyDialog("Folder Name:", "Accept", "Cancel");
            m_saveDialog.Accepted += m_saveDialog_Accepted;
            Control.MainControl.AddControl(m_saveDialog);

            AddItem("New Folder").Click += (s, a) =>
                {
                    m_saveDialog.Display();
                };

            AddItem("Delete").Click += (s, a) =>
                {
                    Directory.Delete(m_dirInfo.FullName);
                    m_dirExplorer.RefreshView();
                };
        }

        private void m_saveDialog_Accepted(object sender, EventArgs e)
        {
            String text = m_saveDialog.Field.Text.Trim();
            if (text == "")
                return;

            Directory.CreateDirectory(Path.Combine(m_dirInfo.FullName, text));
            m_dirExplorer.RefreshView();
        }

        public void Display(DirectoryInfo info)
        {
            m_dirInfo = info;
            Display();
        }

    }
}
