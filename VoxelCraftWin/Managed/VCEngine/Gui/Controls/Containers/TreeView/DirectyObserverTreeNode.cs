using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Permissions;
using System.Text;

namespace VCEngine
{
    /// <summary>
    /// Used to construct and entire tree from a system directory.
    /// </summary>
    public class DirectoryObserverTreeNode : TreeNode
    {
        public override bool IsExpanded { get { return ExpandButton.IsExpanded; } }
        public override bool IsLeaf { get { return !ExpandButton.Visible; } }
        public ExpandButton ExpandButton;
        public ImageView Icon;
        public Label Label;
        public Boolean IncludeFiles;

        private FileSystemWatcher m_dirWatcher = new FileSystemWatcher();

        [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
        public DirectoryObserverTreeNode(String label, String path, Boolean includeFiles)
        {
            // Expand Button
            ExpandButton = new VCEngine.ExpandButton();
            base.AddControl(ExpandButton);
            ExpandButton.OnExpand += (s, a) => Expand();
            ExpandButton.OnCollapse += (s, a) => Collapse();

            // Label
            Label = new VCEngine.Label(label);
            base.AddControl(Label);
            Label.IsEventPassthrough = true;
            Label.TextAlignment = VCEngine.Label.TextAlignments.Center;

            //Image
            Icon = new ImageView();
            base.AddControl(Icon);
            Icon.ImagePath = @"Icons\Folder.DDS";
            Icon.IsEventPassthrough = true;

            DoubleClick += (s, a) =>
                {
                    if (ExpandButton.Visible)
                        ExpandButton.ToggleExpandContract();
                };

            ClientHeight = 40;

            // ReSize
            Resize += (s, a) => ReBuildLayout();

            // Load Directory
            LoadDirRecurse(new DirectoryInfo(path), this, includeFiles);
        }

        protected override void Draw()
        {
            ExpandButton.Frame = new Rectangle(10, Height - ClientHeight + (ClientHeight / 2) - 4, 8, 8);
            Icon.Frame = new Rectangle(30, Height - ClientHeight + (ClientHeight / 2) - 17, 34, 34);
            Label.Frame = new Rectangle(0, Height - ClientHeight + 0, Width, ClientHeight);

            ExpandButton.Visible = m_childrenLTI.Count != 0;

            Gui.DrawBackgroundEmpty(ClientScreenFrame, false);
            Gui.DrawRectangle(new Rectangle(ClientScreenFrame.X, ClientScreenFrame.Y + ClientHeight, Width, 1), new Color(153, 153, 153, 255));
        }

        private void LoadDirRecurse(DirectoryInfo directory, TreeNode parent, bool includeFile)
        {
            // Add directories in this directory
            foreach (DirectoryInfo dInfo in directory.GetDirectories())
            {
                IconLabelTreeNode treeViewItem = new IconLabelTreeNode(dInfo.Name);
                treeViewItem.UserData = dInfo;

                parent.AddControl(treeViewItem);

                // Depth first
                LoadDirRecurse(dInfo, treeViewItem, includeFile);
            }

            if (includeFile)
            {
                // Add files in this directory, add callbacks
                foreach (FileInfo fInfo in directory.GetFiles())
                {
                    IconLabelTreeNode treeViewItem = new IconLabelTreeNode(fInfo.Name);
                    treeViewItem.UserData = fInfo;
                    treeViewItem.Icon.ImagePath = @"Icons\Cube 256.DDS";

                    parent.AddControl(treeViewItem);
                }
            }

        }


    }
}
