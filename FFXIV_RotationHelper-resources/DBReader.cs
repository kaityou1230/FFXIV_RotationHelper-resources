using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FFXIV_RotationHelper_resources
{
    /*
    var db=
    {
        skills:
        {
            4096:
            {
                icon:"001072",
                help_html:"Increases the chance of obtaining an HQ item on your next gathering attempt by 10%. Does not increase chances for items which start at 0%.",
                recast_time:0,
                category:6,
                deprecated:null,
                radius:0,
                name:"Prune",
                level:58,
                cost:100,
                cast_time:0,
                cast_range:0
            },
        }
    }
    */
    public class DBReader
    {
        private string content;
        private int idx;
        public int Idx { get { return idx; } }

        public void Initialize(string text)
        {
            content = text;
            idx = 0;
        }

        public void Skip(string text)
        {
            int index = content.IndexOf(text, idx);
            if (index == idx)
            {
                idx += text.Length;
            }

#if DEBUG && LOG_VERBOSE
            StringBuilder builder = new StringBuilder();
            for (int i = index; i < text.Length; ++i)
            {
                builder.Append(content[i]);
            }

            Debug.WriteLine("Skipped : " + builder.ToString());
#endif
        }

        public int SkipUntil(params string[] param)
        {
            int minValue = content.Length;
            int minIdx = -1;
            for (int i = 0; i < param.Length; ++i)
            {
                int temp = content.IndexOf(param[i], idx);
                if (temp >= 0 && minValue > temp)
                {
                    minValue = temp;
                    minIdx = i;
                }
            }

#if DEBUG && LOG_VERBOSE
            StringBuilder builder = new StringBuilder();
            for (int i = idx; i < minValue; ++i)
            {
                builder.Append(content[i]);
            }
            builder.Append(param[minIdx]);

            Debug.WriteLine("Skipped : " + builder.ToString());
#endif

            idx = minValue + param[minIdx].Length;

            return minIdx;
        }

        public int FindIdx(string text, int startIdx)
        {
            int index = content.IndexOf(text, startIdx);
            if (index < 0)
            {
                throw new ArgumentException("Not Found " + text);
            }

            return index + text.Length;
        }

        public string GetUntil(string text, int startIdx)
        {
            int index = content.IndexOf(text, startIdx);
            if (index < 0)
            {
                throw new ArgumentException("Not Found " + text);
            }

            StringBuilder builder = new StringBuilder();
            for (int i = startIdx; i < index; ++i)
            {
                builder.Append(content[i]);
            }

#if DEBUG && LOG_VERBOSE
            Debug.WriteLine("Get : " + builder.ToString());
#endif

            return builder.ToString();
        }
    }
}
