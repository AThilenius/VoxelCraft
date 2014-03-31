using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace VCEngine
{
    public static class Resources
    {
        public enum LoadType
        {
            Immediate,
            AsyncHighPriority,
            AsyncMediumPriority,
            AsyncLowPriority,
            Default = AsyncMediumPriority
        }

        private static Object m_lock = new Object();
        private static Queue<Action> m_highQueue = new Queue<Action>();
        private static Queue<Action> m_mediumQueue = new Queue<Action>();
        private static Queue<Action> m_lowQueue = new Queue<Action>();

        static Resources()
        {
            Task.Factory.StartNew(() =>
                {

                    // Loading thread
                    while (true)
                    {
                        Action action;

                        lock(m_lock)
                        {
                            while ( m_highQueue.Count == 0 && m_mediumQueue.Count == 0 && m_lowQueue.Count == 0 )
                                Monitor.Wait(m_lock);

                            if (m_highQueue.Count > 0)
                                action = m_highQueue.Dequeue();

                            else
                            {
                                if (m_mediumQueue.Count > 0)
                                    action = m_mediumQueue.Dequeue();

                                else
                                    action = m_lowQueue.Dequeue();
                            }
                        }

                        action();
                    }

                });
        }

        public static void EnqueueFuture(LoadType loadType, Action action)
        {
            switch (loadType)
            {
                case LoadType.Immediate:
                    action();
                    break;

                case LoadType.AsyncHighPriority:
                    lock (m_lock)
                    {
                        m_highQueue.Enqueue(action);
                        Monitor.Pulse(m_lock);
                    }
                    break;

                case LoadType.AsyncMediumPriority:
                    lock (m_lock)
                    {
                        m_mediumQueue.Enqueue(action);
                        Monitor.Pulse(m_lock);
                    }
                    break;

                case LoadType.AsyncLowPriority:
                    lock (m_lock)
                    {
                        m_lowQueue.Enqueue(action);
                        Monitor.Pulse(m_lock);
                    }
                    break;
            }
        }

    }
}
