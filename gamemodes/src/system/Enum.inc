/*      [ ПЕРЕМЕННЫЕ ТРАНСПОРТА ]      */
/*      [ TRANSPORT VARIABLES ]      */
enum VehicleInfo
{
    ID,
    Model,
    Float:SpawnPosition[3],
    Float:SpawnRotation,
    Color1,
    Color2,
    Float:Fuel,
    Float:Health,
    Float:Speed,
    Float:Mileage,
    Text3D:Description,
    Text:Speedometer[6],
    
    bool:IsEngine,
    bool:IsLights,
    bool:IsDoorsClosed
}
new VInfo[MAX_VEHICLES][VehicleInfo];
new Vehicle_Count; // Количество созданного транспорта | Number of vehicles created

/*      [ ПЕРЕМЕННЫЕ ИНТЕРФЕЙСА (сервер) ]      */
/*      [ INTERFACE VARIABLES (server) ]      */
enum TextDrawInfo
{
    Text:Time
}
new TDInfo[TextDrawInfo];

/*      [ ПЕРЕМЕННЫЕ ИНТЕРФЕЙСА (игрок) ]      */
/*      [ INTERFACE VARIABLES (player) ]      */
enum PlayerTextDrawInfo
{
    PlayerText:Notification
}
new PTDInfo[MAX_PLAYERS][PlayerTextDrawInfo];