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
#include "./src/Config.inc"
#include "./src/Notification.inc"
#include "./src/Colors.inc"
#include "./src/String.inc"
#include "./src/Define.inc"
#include "./src/system/Define.inc"
#include "./src/system/initial_works/Define.inc"
#include "./src/server/Enum.inc"
#include "./src/Enum.inc"
#include "./src/system/Enum.inc"
#include "./src/system/initial_works/Enum.inc"

/*    [ СИСТЕМЫ ]    */
/*    [ SYSTEMS ]    */
#include "./src/system/Objects.inc"
#include "./src/system/Interiors.inc"
#include "./src/system/TextDraws.inc"
#include "./src/system/Database.inc"
#include "./src/system/Data.inc"
#include "./src/system/Animations.inc"
#include "./src/system/Authorization.inc"
#include "./src/system/Character.inc"
#include "./src/system/Kick.inc"
#include "./src/system/Chat.inc"
#include "./src/system/Vehicle.inc"
#include "./src/system/Time.inc"
#include "./src/system/Weather.inc"
#include "./src/system/PayDay.inc"
#include "./src/system/Level.inc"
#include "./src/system/AFK.inc"
#include "./src/system/Menu.inc"
#include "./src/system/Money.inc"
#include "./src/system/Freeze.inc"
#include "./src/system/Notification.inc"
#include "./src/system/initial_works/Loader.inc"
#include "./src/system/initial_works/Farmer.inc"
#include "./src/system/initial_works/Diver.inc"
#include "./src/system/initial_works/Init.inc"

/*    [ СЕРВЕРНАЯ СТОРОНА ]   */
/*    [ SERVER SIDE ]   */
#include "./src/server/timers/OnServerSecond.inc"
#include "./src/server/OnGameModeInit.inc"
#include "./src/server/OnGameModeExit.inc"

/*    [ КЛИЕНТСКАЯ СТОРОНА ]    */
/*    [ CLIENT SIDE ]   */
#include "./src/player/timers/OnPlayerSecond.inc"
#include "./src/player/OnPlayerConnect.inc"
#include "./src/player/OnPlayerDisconnect.inc"
#include "./src/player/OnPlayerText.inc"
#include "./src/player/OnPlayerClickMap.inc"
#include "./src/player/OnPlayerCommandPerformed.inc"
#include "./src/player/OnPlayerKeyStateChange.inc"
#include "./src/player/OnPlayerEnterDynamicCP.inc"

/*    [ КОМАНДЫ ]    */
/*    [ COMMANDS ]    */
#include "./src/commands/Player.inc"
#include "./src/commands/Admin.inc"