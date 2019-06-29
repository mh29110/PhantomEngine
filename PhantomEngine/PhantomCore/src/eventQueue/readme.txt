using namespace Phantom::EventQueue;
struct TickEvent : Event
{
    TickEvent() : Event(EVT_TICK), time_(0)
    {}
   ~TickEvent()
     {}
    time_t time_;
 };
class UIClass
{
public:
     UIClass()
     {
     }

    ~UIClass()
     {
     }

     int OnEvent(Event *evt)
     {
         TickEvent *tickEvt = (TickEvent*)evt;
         printf("uiclass event, time now: %d", (int)tickEvt->time_);
         return 0;
     }
};
int main()
{
	EventHandler *eh = new EventHandler();
	auto& em = EventManager::Instance();
	em.AddEventHandler(0,eh );
	em.AddEventHandler(0,eh );
	em.AddEventHandler(0,eh );
	em.AddEventHandler(1,eh );
	em.AddEventHandler(2,eh );

	Event evt(0);
	em.DispatchEvent(&evt);

	TickEvent tickEvt;
	UIClass ui;
	ClassBasedEventHandler<UIClass> evthandler(&ui, &UIClass::OnEvent);
	em.AddEventHandler(EventId::EVT_TICK, &evthandler);
	em.DispatchEvent(&tickEvt);
	em.RemoveEventHandler(EVT_TICK, &evthandler);
	return 0;
} 