<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="10008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
	<Item Name="NI-cRIO9024-ARIF" Type="RT CompactRIO">
		<Property Name="alias.name" Type="Str">NI-cRIO9024-ARIF</Property>
		<Property Name="alias.value" Type="Str">192.168.0.77</Property>
		<Property Name="CCSymbols" Type="Str">TARGET_TYPE,RT;OS,VxWorks;CPU,PowerPC;</Property>
		<Property Name="crio.family" Type="Str">901x</Property>
		<Property Name="host.ResponsivenessCheckEnabled" Type="Bool">true</Property>
		<Property Name="host.ResponsivenessCheckPingDelay" Type="UInt">5000</Property>
		<Property Name="host.ResponsivenessCheckPingTimeout" Type="UInt">1000</Property>
		<Property Name="host.TargetCPUID" Type="UInt">2</Property>
		<Property Name="host.TargetOSID" Type="UInt">14</Property>
		<Property Name="target.cleanupVisa" Type="Bool">false</Property>
		<Property Name="target.FPProtocolGlobals_ControlTimeLimit" Type="Int">300</Property>
		<Property Name="target.getDefault-&gt;WebServer.Port" Type="Int">80</Property>
		<Property Name="target.getDefault-&gt;WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.IOScan.Faults" Type="Str"></Property>
		<Property Name="target.IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="target.IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="target.IOScan.Period" Type="UInt">10000</Property>
		<Property Name="target.IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="target.IOScan.Priority" Type="UInt">0</Property>
		<Property Name="target.IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="target.IsRemotePanelSupported" Type="Bool">true</Property>
		<Property Name="target.RTCPULoadMonitoringEnabled" Type="Bool">true</Property>
		<Property Name="target.RTTarget.ApplicationPath" Type="Path">/c/ni-rt/startup/startup.rtexe</Property>
		<Property Name="target.RTTarget.EnableFileSharing" Type="Bool">true</Property>
		<Property Name="target.RTTarget.IPAccess" Type="Str">+*</Property>
		<Property Name="target.RTTarget.LaunchAppAtBoot" Type="Bool">false</Property>
		<Property Name="target.RTTarget.VIPath" Type="Path">/c/ni-rt/startup</Property>
		<Property Name="target.server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.tcp.access" Type="Str">+*</Property>
		<Property Name="target.server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="target.server.tcp.paranoid" Type="Bool">true</Property>
		<Property Name="target.server.tcp.port" Type="Int">3363</Property>
		<Property Name="target.server.tcp.serviceName" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.tcp.serviceName.default" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.vi.access" Type="Str">+*</Property>
		<Property Name="target.server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="target.server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.WebServer.Enabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogEnabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogPath" Type="Path">/c/ni-rt/system/www/www.log</Property>
		<Property Name="target.WebServer.Port" Type="Int">80</Property>
		<Property Name="target.WebServer.RootPath" Type="Path">/c/ni-rt/system/www</Property>
		<Property Name="target.WebServer.TcpAccess" Type="Str">c+*</Property>
		<Property Name="target.WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.WebServer.ViAccess" Type="Str">+*</Property>
		<Property Name="target.webservices.SecurityAPIKey" Type="Str">PqVr/ifkAQh+lVrdPIykXlFvg12GhhQFR8H9cUhphgg=:pTe9HRlQuMfJxAG6QCGq7UvoUpJzAzWGKy5SbZ+roSU=</Property>
		<Property Name="target.webservices.ValidTimestampWindow" Type="Int">15</Property>
		<Property Name="TargetOSID" Type="Str">VxWorks-PPC603</Property>
		<Item Name="Chassis" Type="cRIO Chassis">
			<Property Name="crio.ProgrammingMode" Type="Str">fpga</Property>
			<Property Name="crio.ResourceID" Type="Str">RIO0</Property>
			<Property Name="crio.Type" Type="Str">cRIO-9113</Property>
			<Item Name="FPGA Target 2" Type="FPGA Target">
				<Property Name="AutoRun" Type="Bool">false</Property>
				<Property Name="configString.guid" Type="Str">{08A208A6-DA88-4E73-9FDC-1A3E571C57E2}resource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=bool{09631846-BD1C-49DD-AE3B-30202151973D}resource=/crio_NI 9263/AO1;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{0D1F87B5-8B92-4409-851D-241EFE23F057}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7:0;0;ReadMethodType=u8;WriteMethodType=u8{0F4AB459-A0D7-4846-B587-BCDEB7BC34AC}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 3,crio.Type=NI 9411,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]{15BE58EC-27DB-4267-8ACD-3A5DD4542E58}resource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool{19C49C7D-38CC-40C9-BEAA-F4EF73D0EEAE}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO1;0;ReadMethodType=bool;WriteMethodType=bool{1B515483-D1A3-41C1-B5EE-B115EDF85079}resource=/crio_NI 9263/AO0;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{1BCDE0C1-C33E-4D34-AB43-CDAA784A7703}resource=/crio_NI 9263/AO3;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{1D90EB2B-2DAC-4C99-A160-2EEC2599D234}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI2;0;ReadMethodType=bool{23AB3A57-29CF-4662-B6D7-3D76E738DC3B}resource=/crio_NI 9215/AI3;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{27F54602-5045-4184-B484-F52AA876C68A}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO4;0;ReadMethodType=bool;WriteMethodType=bool{2B47D78F-8BD4-40CF-850A-282A440901FE}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7;0;ReadMethodType=bool;WriteMethodType=bool{31D3AB8C-D2E5-4969-A755-C7A252BF4854}resource=/crio_NI 9215/AI1;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{3498FDCF-F3F3-4535-92B9-55548B6AD6A3}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5:0;0;ReadMethodType=u8{3784902D-3371-4505-B821-DC5949B300C9}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9215[crioConfig.End]{3C022F47-9751-4AB5-9B0A-3FCCC5E39411}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5;0;ReadMethodType=bool{42119AF4-9C78-48F8-BFA6-B417145462D4}resource=/crio_NI 9215/AI0;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{6F0FF7EC-A0B7-4BDC-8235-6D91ED49FD9F}resource=/Scan Clock;0;ReadMethodType=bool{76BB9AEB-00E8-4B9E-943E-E70A33C4C7F1}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI4;0;ReadMethodType=bool{89C85781-51D1-4BEF-A7AD-2541CA974248}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO6;0;ReadMethodType=bool;WriteMethodType=bool{8B4C25DC-BFA6-4D1B-B922-8CD464D96DC6}resource=/Chassis Temperature;0;ReadMethodType=i16{9AE7A37E-4643-40E1-AF43-FD611CDFD9D9}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO0;0;ReadMethodType=bool;WriteMethodType=bool{9F6E80A1-814D-4819-A440-C0BC9E2E1ED9}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI0;0;ReadMethodType=bool{A843A5F2-3D5B-4065-9530-AEEF11DA701B}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI3;0;ReadMethodType=bool{B0CC8976-A4F5-418F-A021-20E6DCA1FF71}ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000,000000;MaxFreq=40000000,000000;VariableFreq=0;NomFreq=40000000,000000;PeakPeriodJitter=250,000000;MinDutyCycle=50,000000;MaxDutyCycle=50,000000;Accuracy=100,000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E{BB767B71-1DF6-4E7D-9B8F-B6580B5D337D}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI1;0;ReadMethodType=bool{C389C551-8D17-4600-9280-9922E8D72328}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO5;0;ReadMethodType=bool;WriteMethodType=bool{C5F7AF79-AB69-4A71-AFDD-E5A68E99E01D}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9263,cRIOModule.HotSwapMode=0[crioConfig.End]{C9D076B4-F69F-4897-BFA1-9A67C222D394}resource=/crio_NI 9263/AO2;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{D5969B7D-6768-4D51-B60E-1161B2C469DA}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO2;0;ReadMethodType=bool;WriteMethodType=bool{DB06D17C-BB88-4A47-AE2F-BD5C30BB3DDC}resource=/Sleep;0;ReadMethodType=bool;WriteMethodType=bool{DC9E2F6A-0A29-46C6-969F-6C0B1AB9C82C}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 4,crio.Type=NI 9474,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]{E2961915-C5C2-4A41-BFBE-D956688480CF}resource=/crio_NI 9215/AI2;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{E686BD08-B055-4F55-9BFC-764584EA3E45}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO3;0;ReadMethodType=bool;WriteMethodType=boolcRIO-9113/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_FAMILYVIRTEX5TARGET_TYPEFPGA</Property>
				<Property Name="configString.name" Type="Str">40 MHz Onboard ClockResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000,000000;MaxFreq=40000000,000000;VariableFreq=0;NomFreq=40000000,000000;PeakPeriodJitter=250,000000;MinDutyCycle=50,000000;MaxDutyCycle=50,000000;Accuracy=100,000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427EChassis Temperatureresource=/Chassis Temperature;0;ReadMethodType=i16cRIO-9113/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_FAMILYVIRTEX5TARGET_TYPEFPGAFPGA LEDresource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=boolNI 9215/AI0resource=/crio_NI 9215/AI0;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215/AI1resource=/crio_NI 9215/AI1;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215/AI2resource=/crio_NI 9215/AI2;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215/AI3resource=/crio_NI 9215/AI3;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9215[crioConfig.End]NI 9263/AO0resource=/crio_NI 9263/AO0;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263/AO1resource=/crio_NI 9263/AO1;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263/AO2resource=/crio_NI 9263/AO2;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263/AO3resource=/crio_NI 9263/AO3;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9263,cRIOModule.HotSwapMode=0[crioConfig.End]NI 9411/DI0NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI0;0;ReadMethodType=boolNI 9411/DI1NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI1;0;ReadMethodType=boolNI 9411/DI2NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI2;0;ReadMethodType=boolNI 9411/DI3NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI3;0;ReadMethodType=boolNI 9411/DI4NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI4;0;ReadMethodType=boolNI 9411/DI5:0NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5:0;0;ReadMethodType=u8NI 9411/DI5NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5;0;ReadMethodType=boolNI 9411[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 3,crio.Type=NI 9411,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]NI 9474/DO0ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO0;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO1ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO1;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO2ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO2;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO3ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO3;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO4ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO4;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO5ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO5;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO6ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO6;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO7:0ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7:0;0;ReadMethodType=u8;WriteMethodType=u8NI 9474/DO7ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7;0;ReadMethodType=bool;WriteMethodType=boolNI 9474[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 4,crio.Type=NI 9474,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]Scan Clockresource=/Scan Clock;0;ReadMethodType=boolSleepresource=/Sleep;0;ReadMethodType=bool;WriteMethodType=boolSystem Resetresource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool</Property>
				<Property Name="NI.LV.FPGA.CompileConfigString" Type="Str">cRIO-9113/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_FAMILYVIRTEX5TARGET_TYPEFPGA</Property>
				<Property Name="NI.LV.FPGA.Version" Type="Int">5</Property>
				<Property Name="Resource Name" Type="Str">RIO0</Property>
				<Property Name="Target Class" Type="Str">cRIO-9113</Property>
				<Property Name="Top-Level Timing Source" Type="Str">40 MHz Onboard Clock</Property>
				<Property Name="Top-Level Timing Source Is Default" Type="Bool">true</Property>
				<Item Name="Chassis I/O" Type="Folder">
					<Item Name="Chassis Temperature" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/Chassis Temperature</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{8B4C25DC-BFA6-4D1B-B922-8CD464D96DC6}</Property>
					</Item>
					<Item Name="FPGA LED" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/FPGA LED</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{08A208A6-DA88-4E73-9FDC-1A3E571C57E2}</Property>
					</Item>
					<Item Name="Scan Clock" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/Scan Clock</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{6F0FF7EC-A0B7-4BDC-8235-6D91ED49FD9F}</Property>
					</Item>
					<Item Name="Sleep" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/Sleep</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{DB06D17C-BB88-4A47-AE2F-BD5C30BB3DDC}</Property>
					</Item>
					<Item Name="System Reset" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/System Reset</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{15BE58EC-27DB-4267-8ACD-3A5DD4542E58}</Property>
					</Item>
				</Item>
				<Item Name="NI 9215" Type="Folder">
					<Item Name="NI 9215/AI0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9215/AI0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{42119AF4-9C78-48F8-BFA6-B417145462D4}</Property>
					</Item>
					<Item Name="NI 9215/AI1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9215/AI1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{31D3AB8C-D2E5-4969-A755-C7A252BF4854}</Property>
					</Item>
					<Item Name="NI 9215/AI2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9215/AI2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{E2961915-C5C2-4A41-BFBE-D956688480CF}</Property>
					</Item>
					<Item Name="NI 9215/AI3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9215/AI3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{23AB3A57-29CF-4662-B6D7-3D76E738DC3B}</Property>
					</Item>
				</Item>
				<Item Name="NI 9263" Type="Folder">
					<Item Name="NI 9263/AO0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9263/AO0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{1B515483-D1A3-41C1-B5EE-B115EDF85079}</Property>
					</Item>
					<Item Name="NI 9263/AO1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9263/AO1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{09631846-BD1C-49DD-AE3B-30202151973D}</Property>
					</Item>
					<Item Name="NI 9263/AO2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9263/AO2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{C9D076B4-F69F-4897-BFA1-9A67C222D394}</Property>
					</Item>
					<Item Name="NI 9263/AO3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_NI 9263/AO3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{1BCDE0C1-C33E-4D34-AB43-CDAA784A7703}</Property>
					</Item>
				</Item>
				<Item Name="NI 9411" Type="Folder">
					<Item Name="NI 9411/DI0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9411/DI0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{9F6E80A1-814D-4819-A440-C0BC9E2E1ED9}</Property>
					</Item>
					<Item Name="NI 9411/DI1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9411/DI1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{BB767B71-1DF6-4E7D-9B8F-B6580B5D337D}</Property>
					</Item>
					<Item Name="NI 9411/DI2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9411/DI2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{1D90EB2B-2DAC-4C99-A160-2EEC2599D234}</Property>
					</Item>
					<Item Name="NI 9411/DI3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9411/DI3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{A843A5F2-3D5B-4065-9530-AEEF11DA701B}</Property>
					</Item>
					<Item Name="NI 9411/DI4" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9411/DI4</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{76BB9AEB-00E8-4B9E-943E-E70A33C4C7F1}</Property>
					</Item>
					<Item Name="NI 9411/DI5" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9411/DI5</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{3C022F47-9751-4AB5-9B0A-3FCCC5E39411}</Property>
					</Item>
					<Item Name="NI 9411/DI5:0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9411/DI5:0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{3498FDCF-F3F3-4535-92B9-55548B6AD6A3}</Property>
					</Item>
				</Item>
				<Item Name="NI 9474" Type="Folder">
					<Item Name="NI 9474/DO0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{9AE7A37E-4643-40E1-AF43-FD611CDFD9D9}</Property>
					</Item>
					<Item Name="NI 9474/DO1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{19C49C7D-38CC-40C9-BEAA-F4EF73D0EEAE}</Property>
					</Item>
					<Item Name="NI 9474/DO2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{D5969B7D-6768-4D51-B60E-1161B2C469DA}</Property>
					</Item>
					<Item Name="NI 9474/DO3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{E686BD08-B055-4F55-9BFC-764584EA3E45}</Property>
					</Item>
					<Item Name="NI 9474/DO4" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO4</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{27F54602-5045-4184-B484-F52AA876C68A}</Property>
					</Item>
					<Item Name="NI 9474/DO5" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO5</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{C389C551-8D17-4600-9280-9922E8D72328}</Property>
					</Item>
					<Item Name="NI 9474/DO6" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO6</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{89C85781-51D1-4BEF-A7AD-2541CA974248}</Property>
					</Item>
					<Item Name="NI 9474/DO7" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO7</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{2B47D78F-8BD4-40CF-850A-282A440901FE}</Property>
					</Item>
					<Item Name="NI 9474/DO7:0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_NI 9474/DO7:0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{0D1F87B5-8B92-4409-851D-241EFE23F057}</Property>
					</Item>
				</Item>
				<Item Name="40 MHz Onboard Clock" Type="FPGA Base Clock">
					<Property Name="FPGA.PersistentID" Type="Str">{B0CC8976-A4F5-418F-A021-20E6DCA1FF71}</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig" Type="Str">ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000,000000;MaxFreq=40000000,000000;VariableFreq=0;NomFreq=40000000,000000;PeakPeriodJitter=250,000000;MinDutyCycle=50,000000;MaxDutyCycle=50,000000;Accuracy=100,000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.Accuracy" Type="Dbl">100</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.ClockSignalName" Type="Str">Clk40</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.MaxDutyCycle" Type="Dbl">50</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.MaxFrequency" Type="Dbl">40000000</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.MinDutyCycle" Type="Dbl">50</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.MinFrequency" Type="Dbl">40000000</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.NominalFrequency" Type="Dbl">40000000</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.PeakPeriodJitter" Type="Dbl">250</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.ResourceName" Type="Str">40 MHz Onboard Clock</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.SupportAndRequireRuntimeEnableDisable" Type="Bool">false</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.TopSignalConnect" Type="Str">Clk40</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig.VariableFrequency" Type="Bool">false</Property>
					<Property Name="NI.LV.FPGA.Valid" Type="Bool">true</Property>
					<Property Name="NI.LV.FPGA.Version" Type="Int">4</Property>
				</Item>
				<Item Name="NI 9215" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 1</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9215</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{3784902D-3371-4505-B821-DC5949B300C9}</Property>
				</Item>
				<Item Name="NI 9263" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 2</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9263</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.HotSwapMode" Type="Str">0</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{C5F7AF79-AB69-4A71-AFDD-E5A68E99E01D}</Property>
				</Item>
				<Item Name="NI 9411" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 3</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9411</Property>
					<Property Name="cRIOModule.DIO3_0InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.DIO7_4InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.NumSyncRegs" Type="Str">11111111</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{0F4AB459-A0D7-4846-B587-BCDEB7BC34AC}</Property>
				</Item>
				<Item Name="NI 9474" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 4</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9474</Property>
					<Property Name="cRIOModule.DIO3_0InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.DIO7_4InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.NumSyncRegs" Type="Str">11111111</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{DC9E2F6A-0A29-46C6-969F-6C0B1AB9C82C}</Property>
				</Item>
				<Item Name="sit IO cRIO.vi" Type="VI" URL="/&lt;vilib&gt;/addons/Simulation Interface/_IOTypes/Plugins/NI-FPGA/FPGA IO Source/sit IO cRIO.vi">
					<Property Name="configString.guid" Type="Str">{08A208A6-DA88-4E73-9FDC-1A3E571C57E2}resource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=bool{09631846-BD1C-49DD-AE3B-30202151973D}resource=/crio_NI 9263/AO1;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{0D1F87B5-8B92-4409-851D-241EFE23F057}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7:0;0;ReadMethodType=u8;WriteMethodType=u8{0F4AB459-A0D7-4846-B587-BCDEB7BC34AC}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 3,crio.Type=NI 9411,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]{15BE58EC-27DB-4267-8ACD-3A5DD4542E58}resource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool{19C49C7D-38CC-40C9-BEAA-F4EF73D0EEAE}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO1;0;ReadMethodType=bool;WriteMethodType=bool{1B515483-D1A3-41C1-B5EE-B115EDF85079}resource=/crio_NI 9263/AO0;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{1BCDE0C1-C33E-4D34-AB43-CDAA784A7703}resource=/crio_NI 9263/AO3;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{1D90EB2B-2DAC-4C99-A160-2EEC2599D234}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI2;0;ReadMethodType=bool{23AB3A57-29CF-4662-B6D7-3D76E738DC3B}resource=/crio_NI 9215/AI3;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{27F54602-5045-4184-B484-F52AA876C68A}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO4;0;ReadMethodType=bool;WriteMethodType=bool{2B47D78F-8BD4-40CF-850A-282A440901FE}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7;0;ReadMethodType=bool;WriteMethodType=bool{31D3AB8C-D2E5-4969-A755-C7A252BF4854}resource=/crio_NI 9215/AI1;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{3498FDCF-F3F3-4535-92B9-55548B6AD6A3}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5:0;0;ReadMethodType=u8{3784902D-3371-4505-B821-DC5949B300C9}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9215[crioConfig.End]{3C022F47-9751-4AB5-9B0A-3FCCC5E39411}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5;0;ReadMethodType=bool{42119AF4-9C78-48F8-BFA6-B417145462D4}resource=/crio_NI 9215/AI0;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{6F0FF7EC-A0B7-4BDC-8235-6D91ED49FD9F}resource=/Scan Clock;0;ReadMethodType=bool{76BB9AEB-00E8-4B9E-943E-E70A33C4C7F1}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI4;0;ReadMethodType=bool{89C85781-51D1-4BEF-A7AD-2541CA974248}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO6;0;ReadMethodType=bool;WriteMethodType=bool{8B4C25DC-BFA6-4D1B-B922-8CD464D96DC6}resource=/Chassis Temperature;0;ReadMethodType=i16{9AE7A37E-4643-40E1-AF43-FD611CDFD9D9}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO0;0;ReadMethodType=bool;WriteMethodType=bool{9F6E80A1-814D-4819-A440-C0BC9E2E1ED9}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI0;0;ReadMethodType=bool{A843A5F2-3D5B-4065-9530-AEEF11DA701B}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI3;0;ReadMethodType=bool{B0CC8976-A4F5-418F-A021-20E6DCA1FF71}ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000,000000;MaxFreq=40000000,000000;VariableFreq=0;NomFreq=40000000,000000;PeakPeriodJitter=250,000000;MinDutyCycle=50,000000;MaxDutyCycle=50,000000;Accuracy=100,000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E{BB767B71-1DF6-4E7D-9B8F-B6580B5D337D}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI1;0;ReadMethodType=bool{C389C551-8D17-4600-9280-9922E8D72328}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO5;0;ReadMethodType=bool;WriteMethodType=bool{C5F7AF79-AB69-4A71-AFDD-E5A68E99E01D}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9263,cRIOModule.HotSwapMode=0[crioConfig.End]{C9D076B4-F69F-4897-BFA1-9A67C222D394}resource=/crio_NI 9263/AO2;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{D5969B7D-6768-4D51-B60E-1161B2C469DA}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO2;0;ReadMethodType=bool;WriteMethodType=bool{DB06D17C-BB88-4A47-AE2F-BD5C30BB3DDC}resource=/Sleep;0;ReadMethodType=bool;WriteMethodType=bool{DC9E2F6A-0A29-46C6-969F-6C0B1AB9C82C}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 4,crio.Type=NI 9474,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]{E2961915-C5C2-4A41-BFBE-D956688480CF}resource=/crio_NI 9215/AI2;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{E686BD08-B055-4F55-9BFC-764584EA3E45}ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO3;0;ReadMethodType=bool;WriteMethodType=boolcRIO-9113/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_FAMILYVIRTEX5TARGET_TYPEFPGA</Property>
					<Property Name="configString.name" Type="Str">40 MHz Onboard ClockResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000,000000;MaxFreq=40000000,000000;VariableFreq=0;NomFreq=40000000,000000;PeakPeriodJitter=250,000000;MinDutyCycle=50,000000;MaxDutyCycle=50,000000;Accuracy=100,000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427EChassis Temperatureresource=/Chassis Temperature;0;ReadMethodType=i16cRIO-9113/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_FAMILYVIRTEX5TARGET_TYPEFPGAFPGA LEDresource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=boolNI 9215/AI0resource=/crio_NI 9215/AI0;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215/AI1resource=/crio_NI 9215/AI1;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215/AI2resource=/crio_NI 9215/AI2;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215/AI3resource=/crio_NI 9215/AI3;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9215[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9215[crioConfig.End]NI 9263/AO0resource=/crio_NI 9263/AO0;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263/AO1resource=/crio_NI 9263/AO1;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263/AO2resource=/crio_NI 9263/AO2;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263/AO3resource=/crio_NI 9263/AO3;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlNI 9263[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9263,cRIOModule.HotSwapMode=0[crioConfig.End]NI 9411/DI0NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI0;0;ReadMethodType=boolNI 9411/DI1NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI1;0;ReadMethodType=boolNI 9411/DI2NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI2;0;ReadMethodType=boolNI 9411/DI3NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI3;0;ReadMethodType=boolNI 9411/DI4NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI4;0;ReadMethodType=boolNI 9411/DI5:0NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5:0;0;ReadMethodType=u8NI 9411/DI5NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_NI 9411/DI5;0;ReadMethodType=boolNI 9411[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 3,crio.Type=NI 9411,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]NI 9474/DO0ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO0;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO1ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO1;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO2ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO2;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO3ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO3;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO4ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO4;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO5ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO5;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO6ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO6;0;ReadMethodType=bool;WriteMethodType=boolNI 9474/DO7:0ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7:0;0;ReadMethodType=u8;WriteMethodType=u8NI 9474/DO7ArbitrationForOutputData=NeverArbitrate;resource=/crio_NI 9474/DO7;0;ReadMethodType=bool;WriteMethodType=boolNI 9474[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 4,crio.Type=NI 9474,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.NumSyncRegs=11111111[crioConfig.End]Scan Clockresource=/Scan Clock;0;ReadMethodType=boolSleepresource=/Sleep;0;ReadMethodType=bool;WriteMethodType=boolSystem Resetresource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool</Property>
					<Property Name="NI.LV.FPGA.InterfaceBitfile" Type="Str">C:\Program Files\National Instruments\LabVIEW 2010\vi.lib\addons\Simulation Interface\_IOTypes\Plugins\NI-FPGA\FPGA IO Source\FPGA Bitfiles\sitfpgacRIO9113I_FPGATarget2_sitIOcRIOARIFv2_5A2669E6.lvbitx</Property>
				</Item>
				<Item Name="Dependencies" Type="Dependencies">
					<Item Name="vi.lib" Type="Folder">
						<Item Name="SIT FPGA Check for Lateness.vi" Type="VI" URL="/&lt;vilib&gt;/addons/Simulation Interface/_IOTypes/Plugins/NI-FPGA/FPGA IO Source/SIT FPGA Check for Lateness.vi"/>
						<Item Name="SIT FPGA PWM In.vi" Type="VI" URL="/&lt;vilib&gt;/addons/Simulation Interface/_IOTypes/Plugins/NI-FPGA/FPGA IO Source/SIT FPGA PWM In.vi"/>
						<Item Name="SIT FPGA PWM Out.vi" Type="VI" URL="/&lt;vilib&gt;/addons/Simulation Interface/_IOTypes/Plugins/NI-FPGA/FPGA IO Source/SIT FPGA PWM Out.vi"/>
					</Item>
				</Item>
				<Item Name="Build Specifications" Type="Build">
					<Item Name="sit IO cRIO ARIFv2" Type="{F4C5E96F-7410-48A5-BB87-3559BC9B167F}">
						<Property Name="BuildSpecDecription" Type="Str"></Property>
						<Property Name="BuildSpecName" Type="Str">sit IO cRIO ARIFv2</Property>
						<Property Name="Comp.BitfileName" Type="Str">sitfpgacRIO9113I_FPGATarget2_sitIOcRIOARIFv2_5A2669E6.lvbitx</Property>
						<Property Name="Comp.MaxFanout" Type="Int">-1</Property>
						<Property Name="Comp.RunWhenLoaded" Type="Bool">false</Property>
						<Property Name="Comp.Version.Build" Type="Int">0</Property>
						<Property Name="Comp.Version.Fix" Type="Int">0</Property>
						<Property Name="Comp.Version.Major" Type="Int">1</Property>
						<Property Name="Comp.Version.Minor" Type="Int">0</Property>
						<Property Name="Comp.Xilinx.DesignStrategy" Type="Str">balanced</Property>
						<Property Name="Comp.Xilinx.MapEffort" Type="Str">high(timing)</Property>
						<Property Name="Comp.Xilinx.ParEffort" Type="Str">standard</Property>
						<Property Name="Comp.Xilinx.SynthEffort" Type="Str">normal</Property>
						<Property Name="Comp.Xilinx.SynthGoal" Type="Str">speed</Property>
						<Property Name="Comp.Xilinx.UseRecommended" Type="Bool">true</Property>
						<Property Name="DefaultBuildSpec" Type="Bool">true</Property>
						<Property Name="DestinationDirectory" Type="Path">FPGA Bitfiles</Property>
						<Property Name="ProjectPath" Type="Path">/C/Program Files/National Instruments/LabVIEW 2010/vi.lib/addons/Simulation Interface/_IOTypes/Plugins/NI-FPGA/FPGA IO Source/sitfpga cRIO9113 IO.lvproj</Property>
						<Property Name="RelativePath" Type="Bool">true</Property>
						<Property Name="SupportDownload" Type="Bool">true</Property>
						<Property Name="SupportResourceEstimation" Type="Bool">true</Property>
						<Property Name="TargetName" Type="Str">FPGA Target 2</Property>
						<Property Name="TopLevelVI" Type="Ref">/NI-cRIO9024-ARIF/Chassis/FPGA Target 2/sit IO cRIO.vi</Property>
					</Item>
					<Item Name="sit IO cRIO9113" Type="{F4C5E96F-7410-48A5-BB87-3559BC9B167F}">
						<Property Name="BuildSpecDecription" Type="Str"></Property>
						<Property Name="BuildSpecName" Type="Str">sit IO cRIO9113</Property>
						<Property Name="Comp.BitfileName" Type="Str">sitfpgacRIO9113I_FPGATarget2_sitIOcRIO9113_5FD5A5EF.lvbitx</Property>
						<Property Name="Comp.MaxFanout" Type="Int">-1</Property>
						<Property Name="Comp.RunWhenLoaded" Type="Bool">false</Property>
						<Property Name="Comp.Version.Build" Type="Int">0</Property>
						<Property Name="Comp.Version.Fix" Type="Int">0</Property>
						<Property Name="Comp.Version.Major" Type="Int">1</Property>
						<Property Name="Comp.Version.Minor" Type="Int">0</Property>
						<Property Name="Comp.Xilinx.DesignStrategy" Type="Str">balanced</Property>
						<Property Name="Comp.Xilinx.MapEffort" Type="Str">high(timing)</Property>
						<Property Name="Comp.Xilinx.ParEffort" Type="Str">standard</Property>
						<Property Name="Comp.Xilinx.SynthEffort" Type="Str">normal</Property>
						<Property Name="Comp.Xilinx.SynthGoal" Type="Str">speed</Property>
						<Property Name="Comp.Xilinx.UseRecommended" Type="Bool">true</Property>
						<Property Name="DefaultBuildSpec" Type="Bool">true</Property>
						<Property Name="DestinationDirectory" Type="Path">FPGA Bitfiles</Property>
						<Property Name="ProjectPath" Type="Path">/C/Program Files/National Instruments/LabVIEW 2010/vi.lib/addons/Simulation Interface/_IOTypes/Plugins/NI-FPGA/FPGA IO Source/sitfpga cRIO9113 IO.lvproj</Property>
						<Property Name="RelativePath" Type="Bool">true</Property>
						<Property Name="SupportDownload" Type="Bool">true</Property>
						<Property Name="SupportResourceEstimation" Type="Bool">true</Property>
						<Property Name="TargetName" Type="Str">FPGA Target 2</Property>
						<Property Name="TopLevelVI" Type="Ref"></Property>
					</Item>
				</Item>
			</Item>
		</Item>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
