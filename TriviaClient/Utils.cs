using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows;

namespace TriviaClient
{
    internal static class Utils
    {
        public static List<T> GetChildComponents<T>(DependencyObject parent)
        {
            List<T> lst = new List<T>();

            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(parent); i++)
            {
                DependencyObject child = VisualTreeHelper.GetChild(parent, i);

                if (child is T button)
                {
                    lst.Add(button);
                }
                else
                {
                    lst.AddRange(GetChildComponents<T>(child));
                }
            }

            return lst;
        }
    }
}
