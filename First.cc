#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
using namespace ns3;
NS_LOG_COMPONENT_DEFINE
("FirstScriptExample");
int main(int argc,char * argv[])
{
LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_INFO);
LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);
NodeContainer nodes;
nodes.Create(2);
PointToPointHelper pointTopoint;
pointTopoint.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
pointTopoint.SetChannelAttribute("Delay",StringValue("2ms"));
NetDeviceContainer devices;
devices=pointTopoint.Install(nodes);
InternetStackHelper internet;
internet.Install(nodes);
Ipv4AddressHelper address;
address.SetBase("10.1.1.0","255.255.255.0");
Ipv4InterfaceContainer interfaces=address.Assign(devices);


UdpEchoServerHelper echoServer(9);
ApplicationContainer serverApps=echoServer.Install(nodes.Get(1));
serverApps.Start(Seconds(1.0));
serverApps.Stop(Seconds(10.0)); 


UdpEchoClientHelper echoClient(interfaces.GetAddress(1),9);
echoClient.SetAttribute("MaxPackets",UintegerValue(1));
echoClient.SetAttribute("Interval",TimeValue(Seconds(3.0)));
echoClient.SetAttribute("PacketSize",UintegerValue(1024));
ApplicationContainer clientApps=echoClient.Install(nodes.Get(0));
clientApps.Start(Seconds(2.0));
clientApps.Stop(Seconds(10.0));


Simulator::Run();
Simulator::Destroy();
return 0;
}

