#include <config.h>
#include <stdio.h>
#include <sys/types.h>
#include "system.h"
#include "assure.h"
#include "c-ctype.h"

/* The official name of this program (e.g., no 'g' prefix).  */
#define PROGRAM_NAME "echo"     //プログラム名を定義

#define AUTHORS \             //著者情報を定義
  proper_name ("Brian Fox"), proper_name ("Chet Ramey")

//DEFAULT_ECHO_TO_XPGが未定義の場合、falseに設定だけど、enum型だからfalseじゃなくても0ですね。
#ifndef DEFAULT_ECHO_TO_XPG
enum { DEFAULT_ECHO_TO_XPG = false };
#endif

/*
usage()の使い方
コマンドラインツールやスクリプトで、使い方（Usage）を表示するための関数。
主に引数が不正なときや --help オプションが指定されたときに呼び出される。
*/
void
usage (int status)
{
  //affirm マクロは、指定された条件式 E を評価し、その結果が偽の場合にプログラムを停止させる
  //デバッグ用のアサーション機能を提供。このマクロは、C++ 標準ライブラリの 
  //assert マクロをラップしたもの。
  /*
  assert.h の affirm マクロの定義
  #ifdef NDEBUG
  # define affirm(E) assume (E)
  #else
  # define affirm(E) assert (E)
  #endif
  */
  affirm (status == EXIT_SUCCESS);
  //affirm()は、引数の条件が真であれば何もせず以下のコードを実行し続けるが、
  //偽であればプログラムを停止させる。abort()関数を呼び出してプログラムを強制終了させる。
  printf (_("\
  Usage: %s [SHORT-OPTION]... [STRING]...\n\
  or:  %s LONG-OPTION\n\
  "), program_name, program_name);

//この _("...") の書き方は、GNU gettext による国際化（i18n）対応のためのマクロ。
//プログラムが多言語対応するために“翻訳してもらうべき文字列”としてマーク
//gettext()関数によって翻訳されることを期待しているってこと。

  fputs (_("\
  Echo the STRING(s) to standard output.\n\
  \n\
  -n             do not output the trailing newline\n\
  "), stdout);

//DEFAULT_ECHO_TO_XPGが真の場合、-eオプションがデフォルトで有効になる。
//まとめると、DEFAULT_ECHO_TO_XPGが真なら、-eオプションも-Eオプションも有効で
//DEFAULT_ECHO_TO_XPGが偽なら""でなにも表示しないってことかな。
//DEFAULT_ECHO_TO_XPG は、echo コマンドが POSIX（XPG）準拠の動作をするかどうかを判定するためのマクロ
//判定し、0(偽)か非0(真)が入るイメージ。
//echo の挙動を POSIX準拠（XPGモード）にするかどうかを決めるが、主に -e や -E オプションのデフォルト挙動に
//影響する。
//定義
//#ifndef DEFAULT_ECHO_TO_XPG
//enum { DEFAULT_ECHO_TO_XPG = false };
//#endif
//posixly_correctは、内部フラグで、POSIXモードが有効かどうかを判定する。getenv("POSIXLY_CORRECT")は、
//環境変数で POSIX モードを強制するのor判定となる。

  fputs (_(DEFAULT_ECHO_TO_XPG
           ? N_("\
  -e             enable interpretation of backslash escapes (default)\n\
  -E             disable interpretation of backslash escapes\n")
           : ""), stdout);
  
  
  fputs (_("\
  Echo the STRING(s) to standard output.\n\
  \n\
  -n             do not output the trailing newline\n\
  "), stdout);
  fputs (_(DEFAULT_ECHO_TO_XPG
           ? N_("\
  -e             enable interpretation of backslash escapes (default)\n\
  -E             disable interpretation of backslash escapes\n")
           : N_("\
  -e             enable interpretation of backslash escapes\n\
  -E             disable interpretation of backslash escapes (default)\n")),
         stdout);
  fputs (HELP_OPTION_DESCRIPTION, stdout);
  fputs (VERSION_OPTION_DESCRIPTION, stdout);
  fputs (_("\
\n\
If -e is in effect, the following sequences are recognized:\n\
\n\
"), stdout);
  fputs (_("\
  \\\\      backslash\n\
  \\a      alert (BEL)\n\
  \\b      backspace\n\
  \\c      produce no further output\n\
  \\e      escape\n\
  \\f      form feed\n\
  \\n      new line\n\
  \\r      carriage return\n\
  \\t      horizontal tab\n\
  \\v      vertical tab\n\
"), stdout);
  fputs (_("\
  \\0NNN   byte with octal value NNN (1 to 3 digits)\n\
  \\xHH    byte with hexadecimal value HH (1 to 2 digits)\n\
"), stdout);
  printf (USAGE_BUILTIN_WARNING, PROGRAM_NAME);
  fputs (_("\n\
Consider using the printf(1) command instead,\n\
as it avoids problems when outputting option-like strings.\n\
"), stdout);
  emit_ancillary_info (PROGRAM_NAME);
  exit (status);
}
//上記はusage()関数の定義で、コマンドラインツールの使い方を表示する。

static int
hextobin (unsigned char c)
{
  switch (c)
    {
    default: return c - '0';
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    }
}
//16進数文字を対応する10進数に変換する関数。
//例えば、'A'を10に、'F'を15に変換する。
//asciiコードを利用して変換を行っている。


int
main (int argc, char **argv)　//main関数の定義**はポインタのポインタ、配列argvの各要素は文字列へのポインタ
{
  bool display_return = true;   //display_return変数をtrueに初期化
  bool posixly_correct = !!getenv ("POSIXLY_CORRECT");  //環境変数POSIXLY_CORRECTが設定されているかどうかを
                                                        //判定し、真偽値に変換している。
                                                        //!!は二重否定で、ポインタの有無を真偽値に変換する
                                                        //C言語特有のやつ（そうゆうものと覚えるしかない）　
  bool allow_options =
    (! posixly_correct
     || (! DEFAULT_ECHO_TO_XPG && 1 < argc && streq (argv[1], "-n")));
  //streq()は、2つの文字列が等しいかどうかを比較する関数。system.hで定義されている。
  //allow_options変数は、オプションの解析を許可するかどうかを判定する。
  //POSIXモードが有効でない場合、または、DEFAULT_ECHO_TO_XPGが偽で
  //かつ最初の引数が-nの場合にtrueになる。

  
  bool do_v9 = DEFAULT_ECHO_TO_XPG;
  //do_v9変数は、バックスラッシュエスケープシーケンスの解釈を有効にするかどうかを判定する。
  //DEFAULT_ECHO_TO_XPGの値に基づいて初期化される。この場合は、falseになる。

  initialize_main (&argc, &argv);
  //initialize_main()関数は、プログラムの初期化を行う。今回の場合、引数の整備などを行う。
  //具体的には、ロケールの設定や、プログラム名の設定などを行う。
  //system.hで定義されているが、汎用的なことで実装されているが、Linux環境での
  //動作では何もしないところが多い。

  set_program_name (argv[0]);
  //プログラム名を設定している。argv[0]には実行されたプログラムの名前が入っている。

  setlocale (LC_ALL, "");
  //ロケールを設定している。LC_ALLは、すべてのロケールカテゴリを設定することを意味する。
  //""は、環境変数に基づいてロケールを設定する意味。
  
  bindtextdomain (PACKAGE, LOCALEDIR);
//このあとに続く textdomain(PACKAGE); によって、実際に使う翻訳ドメインが決まります。
//setlocale(LC_ALL, "");
//bindtextdomain(PACKAGE, LOCALEDIR);
//textdomain(PACKAGE);
  textdomain (PACKAGE);

  atexit (close_stdout);

  

  if (allow_options && argc == 2)
      //allow_optionsが真で、引数が2つだけの場合（プログラム名と1つの引数）
  {
      {
      if (streq (argv[1], "--help"))
        usage (EXIT_SUCCESS);
        //--helpオプションが指定された場合、usage()関数を呼び出して使い方を表示し、正常終了する。

      if (streq (argv[1], "--version"))
      //--versionオプションが指定された場合、バージョン情報を表示し、正常終了する。
        {
          version_etc (stdout, PROGRAM_NAME, PACKAGE_NAME, Version, AUTHORS,
                       (char *) nullptr);
          return EXIT_SUCCESS;
        }
    }

  argc--;
  argv++;

  }
  
  if (allow_options)
  {
    while (argc > 0 && *argv[0] == '-')
      {
        char const *temp = argv[0] + 1;
        size_t i;

        
        for (i = 0; temp[i]; i++)
          switch (temp[i])
            {
            case 'e': case 'E': case 'n':
              break;
            default:
              goto just_echo;
            }

        if (i == 0)
          goto just_echo;

 
        while (*temp)
          switch (*temp++)
            {
            case 'e':
              do_v9 = true;
              break;

            case 'E':
              do_v9 = false;
              break;

            case 'n':
              display_return = false;
              break;
            }

        argc--;
        argv++;
      }
  }
just_echo:

  if (do_v9 || posixly_correct)
    {
      while (argc > 0)
        {
          char const *s = argv[0];
          unsigned char c;

          while ((c = *s++))
            {
              if (c == '\\' && *s)
                {
                  switch (c = *s++)
                    {
                    case 'a': c = '\a'; break;
                    case 'b': c = '\b'; break;
                    case 'c': return EXIT_SUCCESS;
                    case 'e': c = '\x1B'; break;
                    case 'f': c = '\f'; break;
                    case 'n': c = '\n'; break;
                    case 'r': c = '\r'; break;
                    case 't': c = '\t'; break;
                    case 'v': c = '\v'; break;
                    case 'x':
                      {
                        unsigned char ch = *s;
                        if (! c_isxdigit (ch))
                          goto not_an_escape;
                        s++;
                        c = hextobin (ch);
                        ch = *s;
                        if (c_isxdigit (ch))
                          {
                            s++;
                            c = c * 16 + hextobin (ch);
                          }
                      }
                      break;
                    case '0':
                      c = 0;
                      if (! ('0' <= *s && *s <= '7'))
                        break;
                      c = *s++;
                      FALLTHROUGH;
                    case '1': case '2': case '3':
                    case '4': case '5': case '6': case '7':
                      c -= '0';
                      if ('0' <= *s && *s <= '7')
                        c = c * 8 + (*s++ - '0');
                      if ('0' <= *s && *s <= '7')
                        c = c * 8 + (*s++ - '0');
                      break;
                    case '\\': break;

                    not_an_escape:
                    default:  putchar ('\\'); break;
                    }
                }
              putchar (c);
            }
          argc--;
          argv++;
          if (argc > 0)
            putchar (' ');
        }
    }
  else
    {
      while (argc > 0)
        {
          fputs (argv[0], stdout);
          argc--;
          argv++;
          if (argc > 0)
            putchar (' ');
        }
    }

  if (display_return)
    putchar ('\n');
  return EXIT_SUCCESS;
}
