/*      [ МИНУТНЫЙ ТАЙМЕР ДЛЯ СЕРВЕРА ]      */
/*      [ A MINUTE TIMER FOR THE SERVER ]      */
function Timer_OnServerMinute()
{
    Time_Set();
    Weather_Set();
    return 1;
}