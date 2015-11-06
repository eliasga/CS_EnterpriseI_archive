<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="10008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
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
	<Item Name="NI-cRIO9024-CSE1" Type="RT CompactRIO">
		<Property Name="alias.name" Type="Str">NI-cRIO9024-CSE1</Property>
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
		<Property Name="target.server.tcp.enabled" Type="Bool">true</Property>
		<Property Name="target.server.tcp.paranoid" Type="Bool">true</Property>
		<Property Name="target.server.tcp.port" Type="UInt">3363</Property>
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
		<Item Name="subVIs" Type="Folder">
			<Item Name="IO (rescripted - do not edit)" Type="Folder">
				<Item Name="LgV2_IO Close.vi" Type="VI" URL="../LgV2_IO.llb/LgV2_IO Close.vi"/>
				<Item Name="LgV2_IO Init.vi" Type="VI" URL="../LgV2_IO.llb/LgV2_IO Init.vi"/>
				<Item Name="LgV2_IO Read.vi" Type="VI" URL="../LgV2_IO.llb/LgV2_IO Read.vi"/>
				<Item Name="LgV2_IO Ref.ctl" Type="VI" URL="../LgV2_IO.llb/LgV2_IO Ref.ctl"/>
				<Item Name="LgV2_IO Write.vi" Type="VI" URL="../LgV2_IO.llb/LgV2_IO Write.vi"/>
			</Item>
			<Item Name="LgV2_Base Rate Loop.vi" Type="VI" URL="../LgV2_IO.llb/LgV2_Base Rate Loop.vi"/>
		</Item>
		<Item Name="Chassis" Type="cRIO Chassis">
			<Property Name="crio.ProgrammingMode" Type="Str">fpga</Property>
			<Property Name="crio.ResourceID" Type="Str">RIO0</Property>
			<Property Name="crio.Type" Type="Str">cRIO-9113</Property>
			<Item Name="FPGA Target" Type="FPGA Target">
				<Property Name="AutoRun" Type="Bool">false</Property>
				<Property Name="configString.guid" Type="Str">{068FF6EC-1515-482A-8CB2-1A6BD97CF738}resource=/crio_Mod1/AI3;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{120393C7-FF81-4A60-AB0F-05EBD9A532C7}resource=/crio_Mod2/AO1;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{139576E1-6446-4460-ADBF-C45B502B2ADB}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO5;0;ReadMethodType=bool;WriteMethodType=bool{16998CEB-7FAB-4798-BD1F-20676F01B1EB}resource=/crio_Mod2/AO2;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{23404782-27DB-408F-9F37-74EAC21FA045}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO0;0;ReadMethodType=bool;WriteMethodType=bool{3C7E3D11-35A0-4EFF-B8C2-DFB686CAD37A}resource=/crio_Mod1/AI2;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{4043F84B-17FC-4CE4-AB84-F86BE720416E}resource=/crio_Mod2/AO0;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{41DF6828-18DD-4BFD-969E-B7DFFF997E90}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9263,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.HotSwapMode=0,cRIOModule.RsiAttributes=[crioConfig.End]{49D37717-4170-4062-A96E-7DAC4CC141C3}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO7:0;0;ReadMethodType=u8;WriteMethodType=u8{4D519DC3-5660-48F7-96B8-9197352D4001}resource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool{5B305195-598A-4A43-9352-BF3C7577744E}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO1;0;ReadMethodType=bool;WriteMethodType=bool{6390E271-A5AF-4DF3-9C8B-7A5C575DA0FA}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI3;0;ReadMethodType=bool{64C3ADB1-E63D-4FDF-A7EA-933D6071A7A3}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO6;0;ReadMethodType=bool;WriteMethodType=bool{7350D9D4-BEE9-4F92-A32D-9161F9C1FC4E}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO2;0;ReadMethodType=bool;WriteMethodType=bool{7A01E9ED-0E0F-440F-9BD5-560BCECE5FEF}resource=/Scan Clock;0;ReadMethodType=bool{7A1F643E-083A-4F46-BD57-C9D2EAABF15B}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI0;0;ReadMethodType=bool{7FA0CFE7-CEBD-4FCD-A1A4-96A834F26E17}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI2;0;ReadMethodType=bool{800D109A-17BF-4CC5-BB22-DE1D5B24F303}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI5;0;ReadMethodType=bool{843D0EF2-324D-415B-BA0B-38CF5FB4AA12}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO7;0;ReadMethodType=bool;WriteMethodType=bool{85B486FE-7A0E-46F4-BE0E-C41138E35828}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9215,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.RsiAttributes=[crioConfig.End]{92169994-1F97-45FE-A2EC-9100F727E48C}resource=/Chassis Temperature;0;ReadMethodType=i16{A271E72B-3776-4E43-A8FF-81BB5D62EB57}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO4;0;ReadMethodType=bool;WriteMethodType=bool{AD5C1C79-2FDF-4EF5-9475-FC57CDAD4410}resource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=bool{AEE429D0-5494-4774-AAD5-0F4209E35C42}resource=/crio_Mod1/AI0;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{C76D1B77-D7A8-47CD-8FCE-C970CFB3C175}ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000,000000;MaxFreq=40000000,000000;VariableFreq=0;NomFreq=40000000,000000;PeakPeriodJitter=250,000000;MinDutyCycle=50,000000;MaxDutyCycle=50,000000;Accuracy=100,000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E{C86668E1-AA31-4085-9C1D-30EFC5E8AA1C}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI5:0;0;ReadMethodType=u8{CEAFFDB7-F1B3-47A3-90D8-DA54198E80AE}ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO3;0;ReadMethodType=bool;WriteMethodType=bool{DBE8854B-9135-40CF-8AB3-CA77A29FBCAB}resource=/crio_Mod1/AI1;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{F1AE0C42-74C1-4F20-A1A0-A1D33404B58F}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI1;0;ReadMethodType=bool{F1EE4331-5E05-4347-BD88-66BE38A06390}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 4,crio.Type=NI 9474,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.NumSyncRegs=11111111,cRIOModule.RsiAttributes=[crioConfig.End]{F5E50330-E510-4F7F-B588-0460A11B3868}NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI4;0;ReadMethodType=bool{FB87E1F1-55A5-42FE-A5AB-B0C6774E9142}resource=/Sleep;0;ReadMethodType=bool;WriteMethodType=bool{FF2BBA7E-2ECC-4186-B92B-319A76A0E5BF}resource=/crio_Mod2/AO3;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctl{AA01316F-00FE-40D1-BF18-BAE69B4CCC89}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 3,crio.Type=NI 9411,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.NumSyncRegs=11111111,cRIOModule.RsiAttributes=[crioConfig.End]cRIO-9113/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_FAMILYVIRTEX5TARGET_TYPEFPGA</Property>
				<Property Name="configString.name" Type="Str">40 MHz Onboard ClockResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000,000000;MaxFreq=40000000,000000;VariableFreq=0;NomFreq=40000000,000000;PeakPeriodJitter=250,000000;MinDutyCycle=50,000000;MaxDutyCycle=50,000000;Accuracy=100,000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427EChassis Temperatureresource=/Chassis Temperature;0;ReadMethodType=i16cRIO-9113/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_FAMILYVIRTEX5TARGET_TYPEFPGAFPGA LEDresource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=boolMod1/AI0resource=/crio_Mod1/AI0;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod1/AI1resource=/crio_Mod1/AI1;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod1/AI2resource=/crio_Mod1/AI2;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod1/AI3resource=/crio_Mod1/AI3;0;ReadMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod1[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9215,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.RsiAttributes=[crioConfig.End]Mod2/AO0resource=/crio_Mod2/AO0;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod2/AO1resource=/crio_Mod2/AO1;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod2/AO2resource=/crio_Mod2/AO2;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod2/AO3resource=/crio_Mod2/AO3;0;WriteMethodType=vi.lib\LabVIEW Targets\FPGA\cRIO\shared\nicrio_FXP_Controls\nicrio_FXP_S_20_5.ctlMod2[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9263,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.HotSwapMode=0,cRIOModule.RsiAttributes=[crioConfig.End]Mod3/DI0NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI0;0;ReadMethodType=boolMod3/DI1NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI1;0;ReadMethodType=boolMod3/DI2NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI2;0;ReadMethodType=boolMod3/DI3NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI3;0;ReadMethodType=boolMod3/DI4NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI4;0;ReadMethodType=boolMod3/DI5:0NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI5:0;0;ReadMethodType=u8Mod3/DI5NumberOfSyncRegistersForReadInProject=Auto;resource=/crio_Mod3/DI5;0;ReadMethodType=boolMod3[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 3,crio.Type=NI 9411,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.NumSyncRegs=11111111,cRIOModule.RsiAttributes=[crioConfig.End]Mod4/DO0ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO0;0;ReadMethodType=bool;WriteMethodType=boolMod4/DO1ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO1;0;ReadMethodType=bool;WriteMethodType=boolMod4/DO2ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO2;0;ReadMethodType=bool;WriteMethodType=boolMod4/DO3ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO3;0;ReadMethodType=bool;WriteMethodType=boolMod4/DO4ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO4;0;ReadMethodType=bool;WriteMethodType=boolMod4/DO5ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO5;0;ReadMethodType=bool;WriteMethodType=boolMod4/DO6ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO6;0;ReadMethodType=bool;WriteMethodType=boolMod4/DO7:0ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO7:0;0;ReadMethodType=u8;WriteMethodType=u8Mod4/DO7ArbitrationForOutputData=NeverArbitrate;resource=/crio_Mod4/DO7;0;ReadMethodType=bool;WriteMethodType=boolMod4[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 4,crio.Type=NI 9474,cRIOModule.DIO3_0InitialDir=0,cRIOModule.DIO7_4InitialDir=0,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.NumSyncRegs=11111111,cRIOModule.RsiAttributes=[crioConfig.End]Scan Clockresource=/Scan Clock;0;ReadMethodType=boolSleepresource=/Sleep;0;ReadMethodType=bool;WriteMethodType=boolSystem Resetresource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool</Property>
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
						<Property Name="FPGA.PersistentID" Type="Str">{92169994-1F97-45FE-A2EC-9100F727E48C}</Property>
					</Item>
					<Item Name="FPGA LED" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/FPGA LED</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{AD5C1C79-2FDF-4EF5-9475-FC57CDAD4410}</Property>
					</Item>
					<Item Name="Scan Clock" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/Scan Clock</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{7A01E9ED-0E0F-440F-9BD5-560BCECE5FEF}</Property>
					</Item>
					<Item Name="Sleep" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/Sleep</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{FB87E1F1-55A5-42FE-A5AB-B0C6774E9142}</Property>
					</Item>
					<Item Name="System Reset" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/System Reset</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{4D519DC3-5660-48F7-96B8-9197352D4001}</Property>
					</Item>
				</Item>
				<Item Name="Mod1" Type="Folder">
					<Item Name="Mod1/AI0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod1/AI0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{AEE429D0-5494-4774-AAD5-0F4209E35C42}</Property>
					</Item>
					<Item Name="Mod1/AI1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod1/AI1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{DBE8854B-9135-40CF-8AB3-CA77A29FBCAB}</Property>
					</Item>
					<Item Name="Mod1/AI2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod1/AI2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{3C7E3D11-35A0-4EFF-B8C2-DFB686CAD37A}</Property>
					</Item>
					<Item Name="Mod1/AI3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod1/AI3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{068FF6EC-1515-482A-8CB2-1A6BD97CF738}</Property>
					</Item>
				</Item>
				<Item Name="Mod2" Type="Folder">
					<Item Name="Mod2/AO0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod2/AO0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{4043F84B-17FC-4CE4-AB84-F86BE720416E}</Property>
					</Item>
					<Item Name="Mod2/AO1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod2/AO1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{120393C7-FF81-4A60-AB0F-05EBD9A532C7}</Property>
					</Item>
					<Item Name="Mod2/AO2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod2/AO2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{16998CEB-7FAB-4798-BD1F-20676F01B1EB}</Property>
					</Item>
					<Item Name="Mod2/AO3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/crio_Mod2/AO3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{FF2BBA7E-2ECC-4186-B92B-319A76A0E5BF}</Property>
					</Item>
				</Item>
				<Item Name="Mod3" Type="Folder">
					<Item Name="Mod3/DI0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod3/DI0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{7A1F643E-083A-4F46-BD57-C9D2EAABF15B}</Property>
					</Item>
					<Item Name="Mod3/DI1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod3/DI1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{F1AE0C42-74C1-4F20-A1A0-A1D33404B58F}</Property>
					</Item>
					<Item Name="Mod3/DI2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod3/DI2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{7FA0CFE7-CEBD-4FCD-A1A4-96A834F26E17}</Property>
					</Item>
					<Item Name="Mod3/DI3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod3/DI3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{6390E271-A5AF-4DF3-9C8B-7A5C575DA0FA}</Property>
					</Item>
					<Item Name="Mod3/DI4" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod3/DI4</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{F5E50330-E510-4F7F-B588-0460A11B3868}</Property>
					</Item>
					<Item Name="Mod3/DI5" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod3/DI5</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{800D109A-17BF-4CC5-BB22-DE1D5B24F303}</Property>
					</Item>
					<Item Name="Mod3/DI5:0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="NumberOfSyncRegistersForReadInProject">
   <Value>Auto</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod3/DI5:0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{C86668E1-AA31-4085-9C1D-30EFC5E8AA1C}</Property>
					</Item>
				</Item>
				<Item Name="Mod4" Type="Folder">
					<Item Name="Mod4/DO0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{23404782-27DB-408F-9F37-74EAC21FA045}</Property>
					</Item>
					<Item Name="Mod4/DO1" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO1</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{5B305195-598A-4A43-9352-BF3C7577744E}</Property>
					</Item>
					<Item Name="Mod4/DO2" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO2</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{7350D9D4-BEE9-4F92-A32D-9161F9C1FC4E}</Property>
					</Item>
					<Item Name="Mod4/DO3" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO3</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{CEAFFDB7-F1B3-47A3-90D8-DA54198E80AE}</Property>
					</Item>
					<Item Name="Mod4/DO4" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO4</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{A271E72B-3776-4E43-A8FF-81BB5D62EB57}</Property>
					</Item>
					<Item Name="Mod4/DO5" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO5</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{139576E1-6446-4460-ADBF-C45B502B2ADB}</Property>
					</Item>
					<Item Name="Mod4/DO6" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO6</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{64C3ADB1-E63D-4FDF-A7EA-933D6071A7A3}</Property>
					</Item>
					<Item Name="Mod4/DO7" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO7</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{843D0EF2-324D-415B-BA0B-38CF5FB4AA12}</Property>
					</Item>
					<Item Name="Mod4/DO7:0" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="ArbitrationForOutputData">
   <Value>NeverArbitrate</Value>
   </Attribute>
   <Attribute name="resource">
   <Value>/crio_Mod4/DO7:0</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{49D37717-4170-4062-A96E-7DAC4CC141C3}</Property>
					</Item>
				</Item>
				<Item Name="40 MHz Onboard Clock" Type="FPGA Base Clock">
					<Property Name="FPGA.PersistentID" Type="Str">{C76D1B77-D7A8-47CD-8FCE-C970CFB3C175}</Property>
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
				<Item Name="Mod1" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 1</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9215</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{85B486FE-7A0E-46F4-BE0E-C41138E35828}</Property>
				</Item>
				<Item Name="Mod2" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 2</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9263</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.HotSwapMode" Type="Str">0</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{41DF6828-18DD-4BFD-969E-B7DFFF997E90}</Property>
				</Item>
				<Item Name="Mod3" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 3</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9411</Property>
					<Property Name="cRIOModule.DIO3_0InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.DIO7_4InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.NumSyncRegs" Type="Str">11111111</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{AA01316F-00FE-40D1-BF18-BAE69B4CCC89}</Property>
				</Item>
				<Item Name="Mod4" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 4</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9474</Property>
					<Property Name="cRIOModule.DIO3_0InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.DIO7_4InitialDir" Type="Str">0</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.NumSyncRegs" Type="Str">11111111</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{F1EE4331-5E05-4347-BD88-66BE38A06390}</Property>
				</Item>
				<Item Name="Dependencies" Type="Dependencies"/>
				<Item Name="Build Specifications" Type="Build"/>
			</Item>
		</Item>
		<Item Name="LgV2_Driver.vi" Type="VI" URL="../LgV2_Driver.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="ClearError.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tdmsutil.llb/ClearError.vi"/>
				<Item Name="Close File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Close File+.vi"/>
				<Item Name="compatCalcOffset.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatCalcOffset.vi"/>
				<Item Name="compatFileDialog.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatFileDialog.vi"/>
				<Item Name="compatOpenFileOperation.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatOpenFileOperation.vi"/>
				<Item Name="compatWriteText.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatWriteText.vi"/>
				<Item Name="Create Directory Recursive.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Create Directory Recursive.vi"/>
				<Item Name="Dflt Data Dir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Dflt Data Dir.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="Find First Error.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find First Error.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Get File Extension.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Get File Extension.vi"/>
				<Item Name="MD5Checksum core.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/MD5Checksum.llb/MD5Checksum core.vi"/>
				<Item Name="MD5Checksum File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/MD5Checksum.llb/MD5Checksum File.vi"/>
				<Item Name="MD5Checksum format message-digest.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/MD5Checksum.llb/MD5Checksum format message-digest.vi"/>
				<Item Name="MD5Checksum pad.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/MD5Checksum.llb/MD5Checksum pad.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="NI_SIT_ClientConnMngr.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/Simulation Interface/shared/ClientConnMngr/NI_SIT_ClientConnMngr.lvlib"/>
				<Item Name="NI_SIT_Data Log.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/Simulation Interface/driversupportVIs/logging/NI_SIT_Data Log.lvlib"/>
				<Item Name="NI_SIT_driversupportVIs.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/Simulation Interface/driversupportVIs/NI_SIT_driversupportVIs.lvlib"/>
				<Item Name="NI_SIT_Replay.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/Simulation Interface/driversupportVIs/replay/NI_SIT_Replay.lvlib"/>
				<Item Name="NI_SIT_sitctls.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/Simulation Interface/_sitctls/NI_SIT_sitctls.lvlib"/>
				<Item Name="NI_SIT_SITServer.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/Simulation Interface/_SITServer/NI_SIT_SITServer.lvlib"/>
				<Item Name="NI_SIT_util.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/Simulation Interface/util/NI_SIT_util.lvlib"/>
				<Item Name="Open_Create_Replace File.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/Open_Create_Replace File.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="sitfpga cRIO-9113 IO CSE.lvbitx" Type="Document" URL="/&lt;vilib&gt;/addons/Simulation Interface/_IOTypes/Plugins/NI-FPGA/FPGA Bitfiles/sitfpga cRIO-9113 IO CSE.lvbitx"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="Stop Timed Structure.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/TimedLoop/scheduler/LVUserAPI/Stop Timed Structure.vi"/>
				<Item Name="Synchronize Timed Structure Starts.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/TimedLoop/scheduler/LVUserAPI/Synchronize Timed Structure Starts.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Write File+ (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write File+ (string).vi"/>
			</Item>
			<Item Name="CA_CSE1_V1e_wo_LOSV2b_IO Close.vi" Type="VI" URL="../CA_CSE1_V1e_wo_LOSV2b_IO.llb/CA_CSE1_V1e_wo_LOSV2b_IO Close.vi"/>
			<Item Name="CA_CSE1_V1e_wo_LOSV2b_IO Init.vi" Type="VI" URL="../CA_CSE1_V1e_wo_LOSV2b_IO.llb/CA_CSE1_V1e_wo_LOSV2b_IO Init.vi"/>
			<Item Name="CA_CSE1_V1e_wo_LOSV2b_IO Read.vi" Type="VI" URL="../CA_CSE1_V1e_wo_LOSV2b_IO.llb/CA_CSE1_V1e_wo_LOSV2b_IO Read.vi"/>
			<Item Name="CA_CSE1_V1e_wo_LOSV2b_IO Ref.ctl" Type="VI" URL="../CA_CSE1_V1e_wo_LOSV2b_IO.llb/CA_CSE1_V1e_wo_LOSV2b_IO Ref.ctl"/>
			<Item Name="CA_CSE1_V1e_wo_LOSV2b_IO Write.vi" Type="VI" URL="../CA_CSE1_V1e_wo_LOSV2b_IO.llb/CA_CSE1_V1e_wo_LOSV2b_IO Write.vi"/>
			<Item Name="CustomIO.ctl" Type="VI" URL="../QTMDriver Ver2010/CustomIO.ctl"/>
			<Item Name="FP_FindElement.vi" Type="VI" URL="../QTMDriver Ver2010/FP_FindElement.vi"/>
			<Item Name="FP_InitCapture.vi" Type="VI" URL="../QTMDriver Ver2010/FP_InitCapture.vi"/>
			<Item Name="FP_QTMTelegram_MakeArray.vi" Type="VI" URL="../QTMDriver Ver2010/FP_QTMTelegram_MakeArray.vi"/>
			<Item Name="FP_QTMTelegram_Read.vi" Type="VI" URL="../QTMDriver Ver2010/FP_QTMTelegram_Read.vi"/>
			<Item Name="FP_QTMTelegram_Unpack.vi" Type="VI" URL="../QTMDriver Ver2010/FP_QTMTelegram_Unpack.vi"/>
			<Item Name="FP_QTMTelegram_Write.vi" Type="VI" URL="../QTMDriver Ver2010/FP_QTMTelegram_Write.vi"/>
			<Item Name="lvalarms.dll" Type="Document" URL="lvalarms.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="NiFpgaLv.dll" Type="Document" URL="NiFpgaLv.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="QTM ComonentType.ctl" Type="VI" URL="../QTMDriver Ver2010/QTM ComonentType.ctl"/>
			<Item Name="QTM Data Frame.ctl" Type="VI" URL="../QTMDriver Ver2010/QTM Data Frame.ctl"/>
			<Item Name="QTMDriver.vi" Type="VI" URL="../QTMDriver Ver2010/QTMDriver.vi"/>
			<Item Name="QTMTask.vi" Type="VI" URL="../QTMDriver Ver2010/QTMTask.vi"/>
			<Item Name="SIT Log Signal FG Op.ctl" Type="VI" URL="../../../../../../perforce/sit/trunk/src/VIs/logging/SIT Log Signal FG Op.ctl"/>
			<Item Name="SIT_TimingInterface.dll" Type="Document" URL="/&lt;nishared&gt;/System/SIT_TimingInterface.dll"/>
			<Item Name="SITs Model List.vi" Type="VI" URL="../../../../../../perforce/sit/trunk/src/VIs/SITs Model List.vi"/>
			<Item Name="SITs.dll" Type="Document" URL="/&lt;nishared&gt;/System/SITs.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
