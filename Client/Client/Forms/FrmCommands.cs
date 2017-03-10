using System;
using System.Windows.Forms;

namespace Chatterbox.Forms
{
    public partial class FrmCommands : Form
    {
        public FrmCommands()
        {
            InitializeComponent();
        }

        private void BtnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void FrmCommands_Load(object sender, EventArgs e)
        {

        }
    }
}
