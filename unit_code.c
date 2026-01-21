/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"


static char   s_unit_home  [LEN_PATH]  = "";
static char   s_answer     [LEN_RECD]  = "";


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
yenv__dir_reset         (void)
{
   strcpy (s_answer, "");
   return 1;
}

char
yenv__dir_handler       (int a_read, int a_accept, int a_len, char a_name [LEN_HUND])
{
   char        t           [LEN_HUND] = "";
   sprintf (t, "%d,%d,%d,%s  ", a_read, a_accept, a_len, a_name);
   strlcat (s_answer, t, LEN_RECD);
   return 1;
}

char*
yenv__dir_show          (void)
{
   return s_answer;
}

