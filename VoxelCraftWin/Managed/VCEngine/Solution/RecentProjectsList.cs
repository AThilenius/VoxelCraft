using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace VCEngine
{
    public class RecentProject
    {
        public String FullPath;
        public String Name;
    }

    public class RecentProjectsList
    {

        public SortedDictionary<DateTime, RecentProject> RecentProjects = new SortedDictionary<DateTime, RecentProject>();

    }
}
