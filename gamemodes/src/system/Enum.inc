/*      [ ПЕРЕМЕННЫЕ ТРАНСПОРТА ]      */
/*      [ TRANSPORT VARIABLES ]      */
enum VehicleInfo
{
    ID,
    Model,
    Float:Position[3],
    Float:Rotation,
    Color1,
    Color2,
    Float:Fuel,
    Float:Health,
    Text3D:Description,
    
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