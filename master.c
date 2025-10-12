


char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_quiet    (void)
{
   char       *x_args [1]  = { "yENV" };
   /*> yenv_score_clear ();                                                           <*/
   /*> ySCORE_init (s_audits);                                                        <*/
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
yENV__unit_loud     (void)
{
   char       *x_args [4]  = { "yENV_unit","@@kitchen", "@@file", "@@yenv" };
   yURG_logger (4, x_args);
   yURG_urgs   (4, x_args);
   /*> yenv_score_clear ();                                                           <*/
   /*> ySCORE_init (s_audits);                                                        <*/
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yENV__unit_end      (void)
{
   yLOGS_end     ();
   return 0;
}
