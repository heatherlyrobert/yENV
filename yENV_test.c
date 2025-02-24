/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_quiet    (void)
{
   char       *x_args [1]  = { "yENV" };
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_loud     (void)
{
   char       *x_args [3]  = { "yENV_unit","@@kitchen", "@@file" };
   yURG_logger (3, x_args);
   yURG_urgs   (3, x_args);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yENV__unit_end      (void)
{
   yLOGS_end     ();
   return 0;
}
