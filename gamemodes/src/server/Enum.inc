/*      [ ПЕРЕМЕННЫЕ ДЛЯ СЕРВЕРА ]      */
/*      [ SERVER VARIABLES ]      */
enum ServerInfo
{
    MySQL:MySQL,
    Weather
}
new SInfo[ServerInfo];

/*      [ ПЕРЕМЕННЫЕ ТАЙМЕРА ДЛЯ СЕРВЕРА ]      */
/*      [ TIMER VARIABLES FOR THE SERVER ]      */
enum ServerTimerInfo
{
    Second
}
new STimerInfo[ServerTimerInfo];

/*      [ ПЕРЕМЕННЫЕ ВРЕМЕНИ ДЛЯ СЕРВЕРА ]      */
/*      [ TIME VARIABLES FOR THE SERVER ]      */
enum TimeInfo
{
    Hour,
    Minute,
    Second
}
new TInfo[TimeInfo];

/*      [ ПЕРЕМЕННЫЕ ДЛЯ ЗАРПЛАТЫ ]      */
/*      [ VARIABLES FOR SALARY ]      */
enum PayDayInfo
{
    bool:IsPassed
}
new PDInfo[PayDayInfo];