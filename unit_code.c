/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"


static char   s_unit_home  [LEN_PATH]  = "";


char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_quiet        (void)
{
   getcwd (s_unit_home, LEN_PATH);
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_loud         (void)
{
   char       *x_args [4]  = { "yENV_unit","@@kitchen", "@@file", "@@yenv" };
   getcwd (s_unit_home, LEN_PATH);
   yURG_logger (4, x_args);
   yURG_urgs   (4, x_args);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yENV__unit_end          (void)
{
   yLOGS_end     ();
   chdir (s_unit_home);
   return 0;
}

char
yENV__unit_handler      (int a_read, int a_accept, char a_name [LEN_HUND])
{
}
