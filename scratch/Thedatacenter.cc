#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/CONGARouting.h"
#include "ns3/CONGA-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("CONGARoutingExample");

int 
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);
 
  Time::SetResolution (Time::NS);
  printf("first\n");
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("Ipv4GlobalRouting", LOG_LEVEL_INFO);
  /*LogComponentEnable ("CONGAHelper", LOG_LEVEL_ALL);
  
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_ALL);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_ALL);
  LogComponentEnable ("Ipv4StaticRouting", LOG_LEVEL_ALL);
  
  LogComponentEnable ("CONGARoutingExample", LOG_LEVEL_ALL);
  LogComponentEnable ("CONGARouting", LOG_LEVEL_ALL);
 // LogComponentEnable ("CONGAHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("Ipv4AddressHelper", LOG_LEVEL_ALL);*/
  printf("second\n");

  NS_LOG_INFO ("Create nodes."); //创建节点
  NodeContainer c1;
  c1.Create (3);
  NodeContainer c3;
  c3.Create (3);

  printf("forth\n");
  InternetStackHelper internet;
  internet.Install(c1);//安装协议栈
  internet.Install(c3);
  //internet.Install (c2);

  Config::SetDefault("ns3::Ipv4GlobalRouting::CONGARouting",     BooleanValue(true)); // enable multi-path routing

 
  NodeContainer c2;
  c2.Create (3);
  internet.Install(c2);//安装开启CONGA的协议栈
  //使用容器承装节点
  //Config::SetDefault("ns3::Ipv4GlobalRouting::RandomEcmpRouting",     BooleanValue(true)); // enable multi-path routing
  printf("third\n");
  NodeContainer n0n3 = NodeContainer (c1.Get (0), c2.Get (0));
  NodeContainer n0n4 = NodeContainer (c1.Get (0), c2.Get (1));
  NodeContainer n0n5 = NodeContainer (c1.Get (0), c2.Get (2));
  NodeContainer n1n3 = NodeContainer (c1.Get (1), c2.Get (0));
  NodeContainer n1n4 = NodeContainer (c1.Get (1), c2.Get (1));
  NodeContainer n1n5 = NodeContainer (c1.Get (1), c2.Get (2));
  NodeContainer n2n3 = NodeContainer (c1.Get (2), c2.Get (0));
  NodeContainer n2n4 = NodeContainer (c1.Get (2), c2.Get (1));
  NodeContainer n2n5 = NodeContainer (c1.Get (2), c2.Get (2));

  
  
  printf("ninth\n");
  NS_LOG_INFO ("Create channels.");
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  printf("tenth\n");
  NetDeviceContainer d0d3 = p2p.Install (n0n3);
  NetDeviceContainer d0d4 = p2p.Install (n0n4);
  NetDeviceContainer d0d5 = p2p.Install (n0n5);
  NetDeviceContainer d1d3 = p2p.Install (n1n3);
  NetDeviceContainer d1d4 = p2p.Install (n1n4);
  NetDeviceContainer d1d5 = p2p.Install (n1n5);
  NetDeviceContainer d2d3 = p2p.Install (n2n3);
  NetDeviceContainer d2d4 = p2p.Install (n2n4);
  NetDeviceContainer d2d5 = p2p.Install (n2n5);

    printf("13th\n");
  NodeContainer n3n6=NodeContainer (c2.Get (0), c3.Get (0));
  NodeContainer n4n7=NodeContainer (c2.Get (1), c3.Get (1));
  NodeContainer n5n8=NodeContainer (c2.Get (2), c3.Get (2));
  NetDeviceContainer d3d6 = p2p.Install (n3n6);
  NetDeviceContainer d4d7 = p2p.Install (n4n7);
  NetDeviceContainer d5d8 = p2p.Install (n5n8);
  


  printf("11th\n");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  ipv4.Assign (d0d3);

  ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  ipv4.Assign (d0d4);

  ipv4.SetBase ("10.1.3.0", "255.255.255.0");
  ipv4.Assign (d0d5);

  ipv4.SetBase ("10.2.1.0", "255.255.255.0");
  ipv4.Assign (d1d3);

  ipv4.SetBase ("10.2.2.0", "255.255.255.0");
  ipv4.Assign (d1d4);

  ipv4.SetBase ("10.2.3.0", "255.255.255.0");
  ipv4.Assign (d1d5);

  ipv4.SetBase ("10.3.1.0", "255.255.255.0");
  ipv4.Assign (d2d3);

  ipv4.SetBase ("10.3.2.0", "255.255.255.0");
  ipv4.Assign (d2d4);

  ipv4.SetBase ("10.3.3.0", "255.255.255.0");
  ipv4.Assign (d2d5);

  
  printf("14th\n");
  ipv4.SetBase ("10.4.0.0", "255.255.255.0");
  printf("15th\n");
  Ipv4InterfaceContainer i3i6=ipv4.Assign (d3d6);

  ipv4.SetBase ("10.4.1.0", "255.255.255.0");
  ipv4.Assign (d4d7);

  ipv4.SetBase ("10.4.2.0", "255.255.255.0");
  ipv4.Assign (d5d8);


  printf("16th\n");
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();//用来计算全局路由表

  
  printf("17th\n");
  UdpEchoServerHelper echoServer (9999); //9是端口号
  printf("18th\n");
  ApplicationContainer serverApps = echoServer.Install (c3.Get (0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));
  printf("19th\n");
  UdpEchoClientHelper echoClient (i3i6.GetAddress(1), 9999);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (10));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
  
  printf("20th\n");
  ApplicationContainer clientApps = echoClient.Install (c3.Get (2));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));
  printf("21th\n");
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
