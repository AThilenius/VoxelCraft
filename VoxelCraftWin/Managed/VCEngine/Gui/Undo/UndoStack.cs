using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VCEngine
{
    public class UndoStack <T> where T: IUndoToken
    {
        private List<IUndoToken> m_tokenStack = new List<IUndoToken>();
        private int m_currentStackDepth;

        public void AddToken(T token)
        {
            // Flush the orphaned tokens and truncate if needed.
            // Note the tokens have already been undone.
            while (m_currentStackDepth < m_tokenStack.Count)
                m_tokenStack.RemoveAt(m_tokenStack.Count - 1);

            m_tokenStack.Add(token);
            m_currentStackDepth++;
        }

        public void UndoLast()
        {
            // Must have 1 token to perform an undo.
            if (m_currentStackDepth < 1)
                return;

            m_tokenStack[m_currentStackDepth - 1].UndoToken();
            m_currentStackDepth--;
        }

        public void ReDoLast()
        {
            // Must have a token above the current depth.
            if (m_currentStackDepth == m_tokenStack.Count)
                return;

            m_tokenStack[m_currentStackDepth /* +1 but this is count not index */ ].ReDoToken();
            m_currentStackDepth++;
        }

    }
}
