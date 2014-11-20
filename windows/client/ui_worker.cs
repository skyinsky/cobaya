using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using DevExpress.LookAndFeel;

namespace cobaya
{
    class UiWorker
    {
        public UiWorker()
        {

        }

        public void Routine()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            DevExpress.Skins.SkinManager.EnableFormSkins();
            DevExpress.UserSkins.BonusSkins.Register();
            UserLookAndFeel.Default.SetSkinStyle("Caramel");

            //Application.Run(Info.check_form);
            Application.Run(new FlowForm());
        }
    }
}
