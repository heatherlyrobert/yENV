#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include    <string.h>       /* C_ANSI : printf, snprintf, fgets, fopen, ...  */
#include    <stdlib.h>       /* C_ANSI : exit                                 */

#include    <yLOG.h>
#include    <yURG.h>

#include    "yENV.h"
#include    "yENV_priv.h"

char
main             (int a_argc, char *a_argv [])
{
   yURG_msg_std (); yURG_msg_live ();  yURG_err_std ();  yURG_err_live ();
   yURG_msg ('.', P_ONELINE);
   yURG_msg ('.', "audit of s_scores table using åyenvæ");
   /*> yenv_score_clear ();                                                           <*/
   /*> return yenv_score_audit ();                                                    <*/
   /*> return ySCORE_audit ();                                                        <*/
   return 0;
}

