/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2020 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might "    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



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
   if (a_dir  [0] != '(') {
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
   if (a_dir   [0] != '(') {
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
   }
   /*---(overrides)----------------------*/
   if (a_dir   [0] == '(') {
      if      (strcmp (a_dir  , "(stdin)" ) == 0)  a_mode = 'r';
      else if (strcmp (a_dir  , "(stdout)") == 0)  a_mode = 'w';
      else if (strcmp (a_dir  , "(stderr)") == 0)  a_mode = 'w';
      else if (strcmp (a_dir  , "(clip)"  ) == 0)  strcpy (x_full, YSTR_CLIP);
      else {
         DEBUG_YENV   yLOG_note    ("file starts with '(', but is not defined");
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
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
   /*---(verify existance)---------------*/
   if (a_dir   [0] != '(') {
      rc = yENV_exists (x_full);
      DEBUG_YENV   yLOG_char    ("exists"    , rc);
      --rce;  if (rc == YENV_NONE) {
         if (strchr ("rR", a_mode) != NULL)  {
            DEBUG_YENV   yLOG_note    ("can not read non-existant files");
            DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      --rce;  if (strchr ("-rh", rc) == NULL) {
         DEBUG_YENV   yLOG_note    ("file must be new, regular, or hardlink only");
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(open)---------------------------*/
   if      (strcmp (a_dir  , "(stdin)" ) == 0)  f = stdin;
   else if (strcmp (a_dir  , "(stdout)") == 0)  f = stdout;
   else if (strcmp (a_dir  , "(stderr)") == 0)  f = stderr;
   else                                         f = fopen (x_full, x_mode);
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

char yENV_open_stdin          (FILE **b_file) { return yENV_open_full ("(stdin)" , '-', "(stdin)" , "", 'r', NULL, NULL, NULL, b_file); }
char yENV_open_stdout         (FILE **b_file) { return yENV_open_full ("(stdout)", '-', "(stdout)", "", 'w', NULL, NULL, NULL, b_file); }
char yENV_open_stderr         (FILE **b_file) { return yENV_open_full ("(stderr)", '-', "(stderr)", "", 'w', NULL, NULL, NULL, b_file); }

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
   if      (strcmp (a_label, "(stdin)" ) == 0 || *b_file == stdin )  ;
   else if (strcmp (a_label, "(stdout)") == 0 || *b_file == stdout)  ;
   else if (strcmp (a_label, "(stderr)") == 0 || *b_file == stderr)  ;
   else {
      rc = fclose (*b_file);
      DEBUG_YENV    yLOG_value   ("fclose"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
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
yenv_file__eof          (FILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;
   int         x_flags     =    0;
   int         x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_YENV   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(normal)-------------------------*/
   if (a_file != stdin) {
      DEBUG_YENV   yLOG_note    ("normal file");
      if (feof (a_file)) {
         DEBUG_YENV   yLOG_note    ("hit end-of-file");
         DEBUG_YENV   yLOG_exit    (__FUNCTION__);
         return RC_DONE;
      }
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
   }
   /*---(set stdin to non-blocking)------*/
   DEBUG_YENV   yLOG_note    ("make stdin non-blocking");
   x_flags = fcntl(0, F_GETFL, 0);
   rc = fcntl (stdin, F_SETFL, x_flags | O_NONBLOCK);
   DEBUG_YENV   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_note    ("can not set to non-blocking");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(test stdin for input)-----------*/
   DEBUG_YENV   yLOG_note    ("test for input on stdin");
   x_ch = getc (stdin);
   DEBUG_YENV   yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch == -1) {
      DEBUG_YENV   yLOG_note    ("stdin end-of-file");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return RC_DONE;
   }
   /*---(put stdin back to normal)-------*/
   DEBUG_YENV   yLOG_note    ("put stdin back to normal");
   ungetc (x_ch, stdin);
   rc = fcntl  (0, F_SETFL, x_flags);
   DEBUG_YENV   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_note    ("can not set to back to normal");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}


char
yenv_file__skip         (char a_recd [LEN_RECD], char c_empty, char c_comment, char c_leof)
{  /*---(design notes)-------------------*/
   /*
    *  return  0 = meant to skip                RC_SKIP
    *  return 99 = logical end of file          RC_EOF
    *  return  1 = accepted for processing      RC_POSITIVE
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_pre       [LEN_LABEL] = "";
   char        x_eof       =  '-';
   int         l           =    0;
   char        x_skip      =  '-';
   char        x_1st       =    0;
   char        x_2nd       =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YENV   yLOG_note    ("null record found");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check logical eof)--------------*/
   DEBUG_YENV   yLOG_char    ("c_leof"    , c_leof);
   if (c_leof == 'y') {
      DEBUG_YENV   yLOG_note    ("configured to check logical eof");
      /*---(prepare)---------------------*/
      strlcpy (x_pre, a_recd, LEN_LABEL);
      DEBUG_YENV   yLOG_info    ("x_pre"     , x_pre);
      l = strlen (x_pre);
      DEBUG_YENV   yLOG_value   ("l"         , l);
      /*---(check for bottom)------------*/
      if      (strncmp (a_recd, "# END-OF-FILE"   , 12) == 0)   x_eof  = 'y';
      else if (strncmp (a_recd, "## END-OF-FILE"  , 12) == 0)   x_eof  = 'y';
      else if (strncmp (a_recd, "# end-of-file"   , 12) == 0)   x_eof  = 'y';
      else if (strncmp (a_recd, "## end-of-file"  , 12) == 0)   x_eof  = 'y';
      else if (strncmp (a_recd, "# done, finito"  , 12) == 0)   x_eof  = 'y';
      else if (strncmp (a_recd, "## done, finito" , 12) == 0)   x_eof  = 'y';
      DEBUG_YENV   yLOG_char    ("x_eof"     , x_eof);
      if (x_eof == 'y') {
         DEBUG_YENV   yLOG_note    ("end of content found");
         DEBUG_YENV   yLOG_exit    (__FUNCTION__);
         return RC_DONE;
      }
      /*---(done)------------------------*/
   }
   /*---(check empty lines)--------------*/
   x_1st   = a_recd [0];
   DEBUG_YENV   yLOG_char    ("x_1st"     , x_1st);
   if (x_1st == '\0') {
      DEBUG_YENV   yLOG_char    ("c_empty"   , c_empty);
      if (c_empty  == 'y') {
         DEBUG_YENV   yLOG_note    ("return blank lines");
         DEBUG_YENV   yLOG_exit    (__FUNCTION__);
         return RC_POSITIVE;
      }
      DEBUG_YENV   yLOG_note    ("skip blank lines");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_SKIP;
   }
   /*---(check comments)-----------------*/
   DEBUG_YENV   yLOG_char    ("c_comment" , c_comment);
   if (x_1st == '#')  {
      if (c_comment == 'Y') {
         DEBUG_YENV   yLOG_note    ("set to RETURN all forms of comments");
         x_skip = '-';
      } else if (c_comment == 'y') {
         DEBUG_YENV   yLOG_note    ("set to SELECTIVELY show comments");
         x_2nd = a_recd [1];
         DEBUG_YENV   yLOG_char    ("x_2nd"     , x_2nd);
         switch (x_2nd) {
         case '>' :
            DEBUG_YENV   yLOG_note    ("allowing koios-style saved comments");
            x_skip = '-';
            break;
         case '@' :
            DEBUG_YENV   yLOG_note    ("allowing gyges-style exim configuraton");
            x_skip = '-';
            break;
         default  :
            DEBUG_YENV   yLOG_note    ("normal comment, skip");
            x_skip = 'y';
            break;
         }
      } else {
         DEBUG_YENV   yLOG_note    ("set to IGNORE all forms of comments");
         x_skip = 'y';
      }
      DEBUG_YENV   yLOG_char    ("x_skip"    , x_skip);
      if (x_skip == 'y') {
         DEBUG_YENV   yLOG_exit    (__FUNCTION__);
         return RC_SKIP;
      }
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
   }
   /*---(check short lines)--------------*/
   l = strlen (a_recd);
   DEBUG_YENV   yLOG_value   ("l"         , l);
   if (l <= 10) {
      DEBUG_YENV   yLOG_note    ("line too short (<= 10 chars)");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_SKIP;
   }
   /*---(default)------------------------*/
   DEBUG_YENV   yLOG_note    ("realistic line found");
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yENV_read               (FILE *a_file, char c_empty, char c_comment, char c_leof, char c_visible, int *b_read, int *b_accept, char b_curr [LEN_RECD], char r_prev [LEN_RECD], int *r_len)
{  /*---(design notes)-------------------*/
   /*
    *  c_empty    = y) return empty/short lines    , -) hides
    *  c_comment  = y) return comment lines (#)    , -) hides
    *  c_visible  = y) switch field markers (§)    , -) hides
    *
    */
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
   if (r_len    != NULL)  *r_len   = 0;
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
   rc = yenv_file__eof (a_file);
   --rce;  if (rc == RC_DONE) {
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
      rc = yenv_file__eof (a_file);
      if (rc == RC_DONE) {
         DEBUG_YENV   yLOG_note    ("hit end-of-file");
         if (b_curr   != NULL)  strlcpy (b_curr, "", LEN_RECD);
         if (b_read   != NULL)  *b_read   = x_line;;
         DEBUG_YENV   yLOG_exit    (__FUNCTION__);
         return RC_DONE;
      }
      /*---(handle)----------------------*/
      ++x_line;
      DEBUG_YENV   yLOG_value   ("x_line"    , x_line);
      x_len = strlen (x_recd);
      DEBUG_YENV   yLOG_value   ("length"    , x_len);
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      DEBUG_YENV   yLOG_info    ("x_recd"    , x_recd);
      /*---(filter)----------------------*/
      rc = yenv_file__skip (x_recd, c_empty, c_comment, c_leof);
      DEBUG_YENV   yLOG_value   ("skip"      , rc);
      if (rc == RC_SKIP)  continue;
      if (rc == RC_DONE) {
         DEBUG_YENV   yLOG_note    ("hit logical end-of-file");
         if (b_curr   != NULL)  strlcpy (b_curr, "", LEN_RECD);
         if (b_read   != NULL)  *b_read   = x_line;;
         DEBUG_YENV   yLOG_exit    (__FUNCTION__);
         return RC_DONE;
      }
      /*> DEBUG_YENV   yLOG_char    ("[0]"       , x_recd [0]);                       <*/
      /*> if (x_recd [0] == '\0') {                                                     <* 
       *>    DEBUG_YENV   yLOG_char    ("c_empty"   , c_empty);                         <* 
       *>    if (c_empty   != 'y') {                                                    <* 
       *>       DEBUG_YENV   yLOG_note    ("blank line, skipping");                     <* 
       *>       continue;                                                               <* 
       *>    }                                                                          <* 
       *> }                                                                             <* 
       *> if (x_recd [0] == '#') {                                                      <* 
       *>    DEBUG_YENV   yLOG_char    ("c_comment" , c_comment);                       <* 
       *>    if (c_comment != 'y') {                                                    <* 
       *>       DEBUG_YENV   yLOG_note    ("ignoring all comment lines, skipping");     <* 
       *>       continue;                                                               <* 
       *>    }                                                                          <* 
       *>    switch (x_recd [1]) {                                                      <* 
       *>    case '>' :                                                                 <* 
       *>       DEBUG_YENV   yLOG_note    ("allowing koios-style saved comments");      <* 
       *>       break;                                                                  <* 
       *>    case '@' :                                                                 <* 
       *>       DEBUG_YENV   yLOG_note    ("allowing gyges-style exim configuraton");   <* 
       *>       break;                                                                  <* 
       *>    default  :                                                                 <* 
       *>       if (c_comment != 'y') {                                                 <* 
       *>          DEBUG_YENV   yLOG_note    ("ignoring comment line, skipping");       <* 
       *>          continue;                                                            <* 
       *>       }                                                                       <* 
       *>       break;                                                                  <* 
       *>    }                                                                          <* 
       *> }                                                                             <* 
       *> if (x_len <= 10)  {                                                           <* 
       *>    DEBUG_YENV   yLOG_char    ("c_empty"   , c_empty);                         <* 
       *>    if (c_empty   != 'y') {                                                    <* 
       *>       DEBUG_YENV   yLOG_note    ("too short, skipping");                      <* 
       *>       continue;                                                               <* 
       *>    }                                                                          <* 
       *> }                                                                             <*/
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
   if (r_len    != NULL)  *r_len   = x_len;
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}


char yENV_read_all   (FILE *a_file, int *b_read, int *b_accept, char b_curr [LEN_RECD], char r_prev [LEN_RECD]) { return yENV_read  (a_file, 'y', 'y', '-', '-', b_read, b_accept, b_curr, r_prev, NULL); }
char yENV_read_easy  (FILE *a_file, char r_curr [LEN_RECD])                                                     { return yENV_read  (a_file, 'y', 'y', '-', '-', NULL, NULL, r_curr, NULL, NULL); }

