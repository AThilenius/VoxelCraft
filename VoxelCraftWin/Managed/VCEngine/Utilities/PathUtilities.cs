﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class PathUtilities
    {
        // Resources
        public static String ResourcesPath { get { return Path.Combine(Environment.CurrentDirectory, @"Resources"); } }
        public static String FontsPath { get { return Path.Combine(ResourcesPath, @"Fonts"); } }
        public static String ImagesPath { get { return Path.Combine(ResourcesPath, @"Images"); } }

        // Assets
        public static String AssetsPath { get { return Path.Combine(Environment.CurrentDirectory, @"Assets"); } }
        public static String MeshesPath { get { return Path.Combine(ResourcesPath, @"Meshes"); } }
    }
}
