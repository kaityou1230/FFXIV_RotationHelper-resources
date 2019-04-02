using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FFXIV_RotationHelper_resources
{
    public partial class Form1 : Form
    {
        private OpenFileDialog fileDialog = new OpenFileDialog();
        private DBReader reader = new DBReader();
        private JSONBuilder builder = new JSONBuilder();

        private BackgroundWorker worker = new BackgroundWorker();

        public Form1()
        {
            InitializeComponent();

            worker.WorkerSupportsCancellation = true;
            worker.DoWork += Worker_DoWork;
            worker.RunWorkerCompleted += Worker_RunWorkerCompleted;
        }

        private void Worker_DoWork(object sender, DoWorkEventArgs e)
        {
            string path = e.Argument.ToString();
            ReadFile(path);
        }

        private void Worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            loadBtn.Enabled = true;
        }

        private void LoadBtn_Click(object sender, EventArgs e)
        {
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                loadBtn.Enabled = false;
                sourcePathTextBox.Text = fileDialog.FileName;
                worker.RunWorkerAsync(fileDialog.FileName);
            }
        }

        private void ReadFile(string path)
        {
            string content = File.ReadAllText(path);
            reader.Initialize(content);
            reader.Skip("var db={skills:{");

            builder.Start();
            {
                do
                {
                    string idx = reader.GetUntil(":", reader.Idx).Replace("\"", "");
                    string icon = reader.GetUntil(",", reader.FindIdx("icon:", reader.Idx)).Replace("\"", "");
                    string name = reader.GetUntil(",", reader.FindIdx("name:", reader.Idx)).Replace("\"", "");

                    builder.StartObject();
                    {
                        builder.AddField("idx", idx);
                        builder.AddField("icon", string.Format("http://ffxivrotations.com/icons/{0}.png", icon));
                        builder.AddField("name", name);
                    } builder.EndObject();
                } while (reader.SkipUntil("},", "}}") == 0);
            } builder.End();

            string jsonPath = Path.Combine(Path.GetDirectoryName(path), "db3.json");
            builder.Save(jsonPath);
        }
    }
}
