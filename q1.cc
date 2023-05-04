#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Client_Server_Communication");

int main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);

  Time::SetResolution(Time::NS);

  NodeContainer nodes;
  nodes.Create(2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("7Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install(nodes);

  InternetStackHelper stack;
  stack.Install(nodes);

  Ipv4AddressHelper address;
  address.SetBase("10.10.10.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign(devices);

  UdpServerHelper server1(9000);
  ApplicationContainer serverApps1 = server1.Install(nodes.Get(1)); 
  serverApps1.Start(Seconds(1.0));
  serverApps1.Stop(Seconds(10.0));

  UdpClientHelper client1(interfaces.GetAddress(1), 9000);
  client1.SetAttribute("MaxPackets", UintegerValue(1));
  client1.SetAttribute("Interval", TimeValue(Seconds(1.0)));
  client1.SetAttribute("PacketSize", UintegerValue(1024));

UdpServerHelper server2(9001);
ApplicationContainer serverApps2 = server2.Install(nodes.Get(0)); 
serverApps2.Start(Seconds(1.0));
serverApps2.Stop(Seconds(10.0));

UdpClientHelper client2(interfaces.GetAddress(0), 9001);
client2.SetAttribute("MaxPackets", UintegerValue(1));
client2.SetAttribute("Interval", TimeValue(Seconds(1.0)));
client2.SetAttribute("PacketSize", UintegerValue(1024));

ApplicationContainer clientApps;
clientApps.Add(client1.Install(nodes.Get(0))); 
clientApps.Add(client2.Install(nodes.Get(1))); 
clientApps.Start(Seconds(2.0));

pointToPoint.EnablePcapAll("simple-client-server-communication");

Simulator::Stop(Seconds(10.0));
Simulator::Run();
Simulator::Destroy();

return 0;
}

