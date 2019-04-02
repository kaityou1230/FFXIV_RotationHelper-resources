using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FFXIV_RotationHelper_resources
{
    public class JSONBuilder
    {
        private StringBuilder content = new StringBuilder();
        private int indent = 0;

        private int objectCount = 0;
        private int fieldCount = 0;

        private readonly char newLine = '\n';
        private readonly string tab = "    ";

        private void AddIndent()
        {
            for (int i = 0; i < indent; ++i)
                content.Append(tab);
        }

        public void Start()
        {
            content.Clear();
            content.Append("[");
            content.Append(newLine);

            ++indent;
        }

        public void End()
        {
            if (objectCount > 0)
            {
                // Remove ","
                content.Remove(content.Length - 2, 1);
            }
            content.Append("]");
            content.Append(newLine);

            objectCount = 0;

#if DEBUG
            string[] lines = content.ToString().Split(newLine);
            for (int i = 0; i < lines.Length; ++i)
            {
                Debug.WriteLine(lines[i]);
            }
#endif
        }

        public void StartObject()
        {
            AddIndent();
            content.Append("{");
            content.Append(newLine);

            ++indent;
            ++objectCount;
            fieldCount = 0;
        }

        public void EndObject()
        {
            --indent;

            if (fieldCount > 0)
            {
                // Remove ","
                content.Remove(content.Length - 2, 1);
            }
            AddIndent();
            content.Append("},");
            content.Append(newLine);
        }

        public void AddField(string name, string value)
        {
            AddIndent();
            content.Append("\"");
            content.Append(name);
            content.Append("\" : \"");
            content.Append(value);
            content.Append("\",");
            content.Append(newLine);

            ++fieldCount;
        }

        public void Save(string path)
        {
            if (File.Exists(path))
            {
                File.Delete(path);
            }

            File.WriteAllText(path, content.ToString());
        }
    }
}
