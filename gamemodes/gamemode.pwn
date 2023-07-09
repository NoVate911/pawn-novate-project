/*

[ ============================== ]
   ПРОЧТИТЕ ПЕРЕД ЗАПУСКОМ МОДА
  READ BEFORE LAUNCHING THE MOD
[ ============================== ]

-- [ RUS ] --
Данная сборка была написана русским разработчиком.
Некоторый переведённый текст может отображаться с ошибками или же вовсе не будет переведён.

-- [ ENG ] --
This build was written by a Russian developer.
Some translated text may be displayed with errors or will not be translated at all.

*/

main(){}

/*      [ ПОДКЛЮЧЕНИЕ БИБЛИОТЕК(ИНКЛУДОВ) ]      */
/*      [ CONNECTING LIBRARIES (INCLUDS) ]      */
#include <a_samp>
#include "../include/a_mysql.inc"
#include "../include/md5.inc"
#include "../include/sscanf2.inc"
#include "../include/Pawn.CMD.inc"
#include "../include/Pawn.Regex.inc"
#include "../include/streamer.inc"
#include "../include/YSF.inc"
#include "../include/mdialog.inc"

/*      [ ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ И КОНФИГИ ]      */
/*      [ ADDITIONAL FUNCTIONS AND CONFIGS ]      */
#include "./src/config.inc"
#include "./src/utils.inc"

/*      [ СЕРВЕРНАЯ СТОРОНА ]      */
/*      [ SERVER SIDE ]      */
#include "./src/server/OnGameModeInit.inc"
#include "./src/server/OnGameModeExit.inc"

/*      [ КЛИЕНТСКАЯ СТОРОНА ]      */
/*      [ CLIENT SIDE ]      */
#include "./src/player/OnPlayerConnect.inc"
#include "./src/player/OnPlayerDisconnect.inc"