/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



char
yENV_open_full          (char a_label [LEN_LABEL], char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_mode [LEN_SHORT], char r_note [LEN_LABEL], char r_full [LEN_PATH], FILE **b_file)
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
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
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
   --rce;  if (*b_file != NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
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
   DEBUG_YENV   yLOG_point   ("*b_file"   , *b_file);
   /*---(message)------------------------*/
   yURG_msg ('-', "%s openned successfully (%c, %s, %s)", a_label, a_mode, x_mode, x_note);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yENV_open                (char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, FILE **b_file)
{
   return yENV_open_full ("file", a_dir, a_file, a_mode, NULL, NULL, NULL, b_file);
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
   return yENV_close_full ('-', "file", b_file);
}

