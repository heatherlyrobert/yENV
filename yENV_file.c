/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



char
yENV_open_full          (char a_label [LEN_LABEL], char c_force, char a_dir [LEN_PATH], char a_file [LEN_HUND], char a_mode, char r_mode [LEN_SHORT], char r_note [LEN_LABEL], char r_full [LEN_PATH], FILE **b_file)
{
   /*---(design notes)-------------------*/
   /*
    *  only allow openning exists files to avoid
    *  creating files with inappropriate permissions.
    *  use yENV_touch or yENV_audit to create.
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_full      [LEN_PATH]  = "";
   char        x_style     =  '-';
   char        x_mode      [LEN_SHORT] = "";
   char        x_note      [LEN_LABEL] = "";
   FILE       *f           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_mode  != NULL)  strcpy (r_mode , "");
   if (r_note  != NULL)  strcpy (r_note , "");
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label     == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_label"   , a_label);
   DEBUG_YENV   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir       == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_dir"     , a_dir);
   DEBUG_YENV   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file      == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_file"    , a_file);
   DEBUG_YENV   yLOG_char    ("a_mode"    , a_mode);
   --rce;  if (a_mode == 0 || strchr ("rRwW", a_mode) == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("b_file"    , b_file);
   --rce;  if (b_file      == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("*b_file"   , *b_file);
   --rce;  if (c_force != 'y' && *b_file != NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   *b_file = NULL;
   /*---(full name)----------------------*/
   rc = yENV_name_full (a_dir, a_file, &x_style, x_full);
   DEBUG_YENV   yLOG_value   ("full"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_char    ("x_style"   , x_style);
   --rce;  if (x_style != 'b') {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("x_full"    , x_full);
   /*---(verify existance)---------------*/
   rc = yENV_exists (x_full);
   DEBUG_YENV   yLOG_char    ("exists"    , rc);
   --rce;  if (rc == YENV_NONE) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (rc != YENV_REG && rc != YENV_HARD) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set mode)-----------------------*/
   DEBUG_YENV   yLOG_char    ("a_mode"    , a_mode);
   --rce;  switch (a_mode) {
   case 'r' :
      strlcpy (x_mode, "rt", LEN_SHORT);
      strlcpy (x_note, "reading as text"   , LEN_LABEL);
      break;
   case 'R' :
      strlcpy (x_mode, "rb", LEN_SHORT);
      strlcpy (x_note, "reading as binary" , LEN_LABEL);
      break;
   case 'w' :
      strlcpy (x_mode, "wt", LEN_SHORT);
      strlcpy (x_note, "writing as text"  , LEN_LABEL);
      break;
   case 'W' :
      strlcpy (x_mode, "wb", LEN_SHORT);
      strlcpy (x_note, "writing as binary", LEN_LABEL);
      break;
   case '-' :
      strlcpy (x_mode, "--", LEN_SHORT);
      strlcpy (x_note, "audit-only"       , LEN_LABEL);
      break;
   default  :
      DEBUG_YENV   yLOG_note    ("mode not understood");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("x_mode"    , x_mode);
   /*---(open)---------------------------*/
   f = fopen (x_full, x_mode);
   DEBUG_YENV   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_mode  != NULL)  strlcpy (r_mode , x_mode, LEN_SHORT);
   if (r_note  != NULL)  strlcpy (r_note , x_note, LEN_LABEL);
   if (r_full  != NULL)  strlcpy (r_full , x_full, LEN_PATH);
   if (b_file != NULL)  *b_file = f;
   /*---(message)------------------------*/
   yURG_msg ('-', "%s openned successfully (%c, %s, %s)", a_label, a_mode, x_mode, x_note);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yENV_open                (char a_dir [LEN_PATH], char a_file [LEN_HUND], char a_mode, FILE **b_file)
{
   return yENV_open_full ("file", '-', a_dir, a_file, a_mode, NULL, NULL, NULL, b_file);
}

char
yENV_close_full         (char a_label [LEN_LABEL], FILE **b_file, char c_sync)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label     == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_label"   , a_label);
   DEBUG_YENV   yLOG_point   ("b_file"    , b_file);
   --rce;  if (b_file      == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("*b_file"   , *b_file);
   --rce;  if (*b_file == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close file)---------------------*/
   rc = fclose (*b_file);
   DEBUG_YENV    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   *b_file = NULL;
   DEBUG_YENV   yLOG_point   ("*b_file"   , *b_file);
   /*---(sync)---------------------------*/
   if (c_sync == 'y')  sync ();
   /*---(message)------------------------*/
   yURG_msg ('-', "%s closed successfully", a_label);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yENV_close              (FILE **b_file)
{
   return yENV_close_full ("file", b_file, '-');
}

char
yENV_read               (FILE *a_file, char c_comment, char c_visible, int *b_read, int *b_accept, char b_curr [LEN_RECD], char r_prev [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_prev      [LEN_RECD]  = "";
   char        x_recd      [LEN_RECD]  = "";
   int         x_line      =    0;
   int         x_accept    =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (b_read   != NULL)  x_line   = *b_read;
   if (b_accept != NULL)  x_accept = *b_accept;
   if (r_prev   != NULL)  strcpy (r_prev, "");
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("b_curr"    , b_curr);
   --rce;  if (b_curr == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(rotate)-------------------------*/
   strlcpy (x_prev, b_curr, LEN_RECD);
   DEBUG_YENV   yLOG_info    ("x_prev"    , x_prev);
   /*---(check end-of-file)--------------*/
   --rce;  if (feof (a_file)) {
      DEBUG_YENV   yLOG_note    ("already at end-of-file");
      if (b_curr   != NULL)  strlcpy (b_curr, "", LEN_RECD);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read)------------------------*/
   --rce;  while (1) {
      /*---(get text)-----------------*/
      fgets  (x_recd, LEN_RECD, a_file);
      /*---(check end-of-file)--------*/
      if (feof (a_file)) {
         DEBUG_YENV   yLOG_note    ("hit end-of-file");
         if (b_curr   != NULL)  strlcpy (b_curr, "", LEN_RECD);
         if (b_read   != NULL)  *b_read   = x_line;;
         DEBUG_YENV   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      /*---(handle)----------------------*/
      ++x_line;
      DEBUG_YENV   yLOG_value   ("x_line"    , x_line);
      x_len = strlen (x_recd);
      DEBUG_YENV   yLOG_value   ("length"    , x_len);
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      DEBUG_YENV   yLOG_complex ("x_recd"    , "%3då%sæ", x_len, x_recd);
      /*---(filter)----------------------*/
      if (x_recd [0] == '\0') {
         DEBUG_YENV   yLOG_note    ("blank line");
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_YENV   yLOG_char    ("c_comment" , c_comment);
         if (c_comment == 'y') {
            DEBUG_YENV   yLOG_note    ("ignoring all comment lines");
            continue;
         }
         switch (x_recd [1]) {
         case '>' :
            DEBUG_YENV   yLOG_note    ("allowing koios-style saved comments");
            break;
         case '@' :
            DEBUG_YENV   yLOG_note    ("allowing gyges-style exim configuraton");
            break;
         default  :
            DEBUG_YENV   yLOG_note    ("ignoring comment line");
            continue;
            break;
         }
      }
      if (x_len <= 10)  {
         DEBUG_YENV   yLOG_note    ("too short, skipping");
         continue;
      }
      /*---(accept)----------------------*/
      ++x_accept;
      DEBUG_YENV   yLOG_value   ("x_accept"  , x_accept);
      break;
   }
   /*---(visible)---------------------*/
   if (c_visible == 'y') {
      for (i = 0; i < x_len; ++i)  if (x_recd [i] == '')  x_recd [i] = '§';
   }
   /*---(save-back)-------------------*/
   if (b_read   != NULL)  *b_read   = x_line;;
   if (b_accept != NULL)  *b_accept = x_accept;;
   if (b_curr   != NULL)  strlcpy (b_curr, x_recd, LEN_RECD);
   if (r_prev   != NULL)  strlcpy (r_prev, x_prev, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return 1;
}


