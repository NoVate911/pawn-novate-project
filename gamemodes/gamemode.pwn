/*

[ ============================== ]
   ПРОЧТИТЕ ПЕРЕД ЗАПУСКОМ МОДА
  READ BEFORE LAUNCHING THE MOD
[ ============================== ]

-- [ RUS ] --
Данная сборка была написана русским разработчиком.
Некоторый переведённый текст может отображаться с ошибками или же вовсе не будет переведён.

Если появились неизвестные символы, то откройте проект с кодировкой "Windows 1251 (cp1251)".

-- [ ENG ] --
This build was written by a Russian developer.
Some translated text may be displayed with errors or will not be translated at all.

If unknown characters appear, then open the project with the encoding "Windows 1251 (cp1251)".

*/

main(){}

/*    [ ПОДКЛЮЧЕНИЕ БИБЛИОТЕК(ИНКЛУДОВ) ]   */
/*    [ CONNECTING LIBRARIES (INCLUDS) ]    */
#include <a_samp>
#include "../include/a_mysql.inc"
#include "../include/md5.inc"
#include "../include/sscanf2.inc"
#include "../include/crashdetect.inc"
#include "../include/Pawn.CMD.inc"
#include "../include/Pawn.Regex.inc"
#include "../include/streamer.inc"
#include "../include/YSF.inc"
#include "../include/mdialog.inc"
#include "../include/foreach.inc"

/*    [ КОНФИГИ ]    */
/*    [ CONFIGS ]    */
#include "./src/config.inc"
#include "./src/notification.inc"
#include "./src/colors.inc"
#include "./src/define.inc"
#include "./src/string.inc"
#include "./src/enum.inc"
#include "./src/utils.inc"

/*    [ СИСТЕМЫ ]    */
/*    [ SYSTEMS ]    */
#include "./src/system/Database.inc"
#include "./src/system/Authorization.inc"
#include "./src/system/Character.inc"
#include "./src/system/Kick.inc"
#include "./src/system/Chat.inc"

/*    [ СЕРВЕРНАЯ СТОРОНА ]   */
/*    [ SERVER SIDE ]   */
#include "./src/server/OnGameModeInit.inc"
#include "./src/server/OnGameModeExit.inc"

/*    [ КЛИЕНТСКАЯ СТОРОНА ]    */
/*    [ CLIENT SIDE ]   */
#include "./src/player/timers/OnPlayerConnect.inc"
#include "./src/player/timers/OnPlayerSecond.inc"
#include "./src/player/OnPlayerConnect.inc"
#include "./src/player/OnPlayerDisconnect.inc"
#include "./src/player/OnPlayerText.inc"
#include "./src/player/OnPlayerClickMap.inc"

/*    [ КОМАНДЫ ]    */
/*    [ COMMANDS ]    */
#include "./src/commands/player.inc"
#include "./src/commands/admin.inc"