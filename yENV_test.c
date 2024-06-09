/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_quiet    (void)
{
   char       *x_args [2]  = { "yENV_unit","@@quiet" };
   yURG_logger (2, x_args);
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_loud     (void)
{
   char       *x_args [2]  = { "yENV_unit","@@kitchen" };
   yURG_logger (2, x_args);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yENV__unit_end      (void)
{
   yLOGS_end     ();
   return 0;
}
