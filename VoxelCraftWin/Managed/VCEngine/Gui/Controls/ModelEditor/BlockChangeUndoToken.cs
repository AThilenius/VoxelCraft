using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class BlockChangeUndoToken : IUndoToken
    {
        public World AffectedWorld;
        // Make a tuple for these?
        public List<Location> AffectedLocations = new List<Location>();
        public List<Color> OldColors = new List<Color>();
        public List<Color> NewColors = new List<Color>();

        public BlockChangeUndoToken(World world)
        {
            AffectedWorld = world;
        }

        public void AddBlock(Location loc, Color oldColor, Color newColor)
        {
            AffectedLocations.Add(loc);
            OldColors.Add(oldColor);
            NewColors.Add(newColor);
        }

        public void UndoToken()
        {
            for (int i = 0; i < AffectedLocations.Count; i++)
                AffectedWorld.SetBlock(AffectedLocations[i], new Block(OldColors[i]));

            AffectedWorld.ReBuild();
        }

        public void ReDoToken()
        {
            for (int i = 0; i < AffectedLocations.Count; i++)
                AffectedWorld.SetBlock(AffectedLocations[i], new Block(NewColors[i]));

            AffectedWorld.ReBuild();
        }
    }
}
