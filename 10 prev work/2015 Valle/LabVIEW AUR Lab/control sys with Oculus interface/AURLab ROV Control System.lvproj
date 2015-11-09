﻿<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="14008000">
	<Property Name="SMProvider.SMVersion" Type="Int">201310</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
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
		<Item Name="Library" Type="Folder">
			<Item Name="Helping Routines" Type="Folder">
				<Property Name="NI.SortType" Type="Int">3</Property>
				<Item Name="AutoParameter Guidance Omega.vi" Type="VI" URL="../Library/Helping Routines/AutoParameter Guidance Omega.vi"/>
				<Item Name="Error Calculations.vi" Type="VI" URL="../Library/Helping Routines/Error Calculations.vi"/>
				<Item Name="eta2cont (SubVI).vi" Type="VI" URL="../Library/Kinematics/eta2cont (SubVI).vi"/>
				<Item Name="Get Set Point (SubVI).vi" Type="VI" URL="../Library/Helping Routines/Get Set Point (SubVI).vi"/>
				<Item Name="get_set_point (SubVI).vi" Type="VI" URL="../Library/Helping Routines/get_set_point (SubVI).vi"/>
				<Item Name="LQR.vi" Type="VI" URL="../Library/Helping Routines/LQR.vi"/>
				<Item Name="Mass 2 Coriolis.vi" Type="VI" URL="../Library/Helping Routines/Mass 2 Coriolis.vi"/>
				<Item Name="Rad 2 PI-PI Scalar.vi" Type="VI" URL="../Library/Helping Routines/Rad 2 PI-PI Scalar.vi"/>
				<Item Name="Rad 2 PI-PI Vector.vi" Type="VI" URL="../Library/Helping Routines/Rad 2 PI-PI Vector.vi"/>
				<Item Name="Rad 2 PI-PI.vi" Type="VI" URL="../Library/Helping Routines/Rad 2 PI-PI.vi"/>
				<Item Name="Read Node Name.vi" Type="VI" URL="../Library/Helping Routines/Read Node Name.vi"/>
				<Item Name="ReconnectionProcedureArray.vi" Type="VI" URL="../Library/Helping Routines/ReconnectionProcedureArray.vi"/>
				<Item Name="ReconnectProcedureScalar.vi" Type="VI" URL="../Library/Helping Routines/ReconnectProcedureScalar.vi"/>
				<Item Name="ReconnectProcedure.vi" Type="VI" URL="../Library/Helping Routines/ReconnectProcedure.vi"/>
				<Item Name="Scan Token Generator.vi" Type="VI" URL="../Library/Helping Routines/Scan Token Generator.vi"/>
				<Item Name="Sperre telebuf 30k (SubVI).vi" Type="VI" URL="../Library/Helping Routines/Sperre telebuf 30k (SubVI).vi"/>
				<Item Name="Sperre thrust alloc Minerva.vi" Type="VI" URL="../Library/Helping Routines/Sperre thrust alloc Minerva.vi"/>
				<Item Name="Sperre thrust alloc Neptune.vi" Type="VI" URL="../Library/Helping Routines/Sperre thrust alloc Neptune.vi"/>
				<Item Name="String to Matrix (Diag).vi" Type="VI" URL="../Library/Helping Routines/String to Matrix (Diag).vi"/>
				<Item Name="String to Matrix (Norm).vi" Type="VI" URL="../Library/Helping Routines/String to Matrix (Norm).vi"/>
				<Item Name="String to Matrix.vi" Type="VI" URL="../Library/Helping Routines/String to Matrix.vi"/>
				<Item Name="String to Vector.vi" Type="VI" URL="../Library/Helping Routines/String to Vector.vi"/>
				<Item Name="ToggleSwitch.vi" Type="VI" URL="../Library/Helping Routines/ToggleSwitch.vi"/>
				<Item Name="True once (SubVI).vi" Type="VI" URL="../Library/Helping Routines/True once (SubVI).vi"/>
				<Item Name="Sperre telebuf Minerva 27 Bytes (Sub VI).vi" Type="VI" URL="../Library/Helping Routines/Sperre telebuf Minerva 27 Bytes (Sub VI).vi"/>
			</Item>
			<Item Name="Integrators" Type="Folder">
				<Item Name="Integrator 4DOF PID (SubVI).vi" Type="VI" URL="../Library/Integrator/Integrator 4DOF PID (SubVI).vi"/>
				<Item Name="Integrator 6DOF PID (SubVI).vi" Type="VI" URL="../Library/Integrator/Integrator 6DOF PID (SubVI).vi"/>
				<Item Name="Integrator trapez scalar.vi" Type="VI" URL="../Library/Integrator/Integrator trapez scalar.vi"/>
				<Item Name="Integrator trapez vector.vi" Type="VI" URL="../Library/Integrator/Integrator trapez vector.vi"/>
				<Item Name="Integrator Trapez.vi" Type="VI" URL="../Library/Integrator/Integrator Trapez.vi"/>
			</Item>
			<Item Name="Kinematics" Type="Folder">
				<Item Name="Eta_Euler2Eta_Quart.vi" Type="VI" URL="../Library/Kinematics/Eta_Euler2Eta_Quart.vi"/>
				<Item Name="Eta_Quart2Eta_Euler.vi" Type="VI" URL="../Library/Kinematics/Eta_Quart2Eta_Euler.vi"/>
				<Item Name="EtaTransformation.vi" Type="VI" URL="../Library/Kinematics/EtaTransformation.vi"/>
				<Item Name="euler2q.vi" Type="VI" URL="../Library/Kinematics/euler2q.vi"/>
				<Item Name="J Library.vi" Type="VI" URL="../Library/Kinematics/J Library.vi"/>
				<Item Name="J_euler.vi" Type="VI" URL="../Library/Kinematics/J_euler.vi"/>
				<Item Name="J_quart.vi" Type="VI" URL="../Library/Kinematics/J_quart.vi"/>
				<Item Name="Jdot.vi" Type="VI" URL="../Library/Kinematics/Jdot.vi"/>
				<Item Name="Jinv_euler.vi" Type="VI" URL="../Library/Kinematics/Jinv_euler.vi"/>
				<Item Name="Jinv_quart.vi" Type="VI" URL="../Library/Kinematics/Jinv_quart.vi"/>
				<Item Name="Jtrans_euler.vi" Type="VI" URL="../Library/Kinematics/Jtrans_euler.vi"/>
				<Item Name="Jtrans_quart.vi" Type="VI" URL="../Library/Kinematics/Jtrans_quart.vi"/>
				<Item Name="mapAngleToContrSubVi.vi" Type="VI" URL="../Library/Kinematics/mapAngleToContrSubVi.vi"/>
				<Item Name="q2euler.vi" Type="VI" URL="../Library/Kinematics/q2euler.vi"/>
				<Item Name="RotationMartix.vi" Type="VI" URL="../Library/Kinematics/RotationMartix.vi"/>
				<Item Name="RotationMatrix6DOF.vi" Type="VI" URL="../Library/Kinematics/RotationMatrix6DOF.vi"/>
				<Item Name="RotationMatrixQuaternions.vi" Type="VI" URL="../Library/Kinematics/RotationMatrixQuaternions.vi"/>
				<Item Name="rotmat 4DOF.vi" Type="VI" URL="../Library/Kinematics/rotmat 4DOF.vi"/>
				<Item Name="rotmat 6DOF.vi" Type="VI" URL="../Library/Kinematics/rotmat 6DOF.vi"/>
				<Item Name="SkewMatrix.vi" Type="VI" URL="../Library/Kinematics/SkewMatrix.vi"/>
				<Item Name="SkewMatrix3DOF.vi" Type="VI" URL="../Library/Kinematics/SkewMatrix3DOF.vi"/>
				<Item Name="SkewMatrix6DOF.vi" Type="VI" URL="../Library/Kinematics/SkewMatrix6DOF.vi"/>
				<Item Name="TransformationMatrix.vi" Type="VI" URL="../Library/Kinematics/TransformationMatrix.vi"/>
				<Item Name="TransformationMatrixEuler.vi" Type="VI" URL="../Library/Kinematics/TransformationMatrixEuler.vi"/>
				<Item Name="TransformationMatrixQuaternions.vi" Type="VI" URL="../Library/Kinematics/TransformationMatrixQuaternions.vi"/>
				<Item Name="transrotmat 4DOF.vi" Type="VI" URL="../Library/Kinematics/transrotmat 4DOF.vi"/>
				<Item Name="transrotmat 6DOF.vi" Type="VI" URL="../Library/Kinematics/transrotmat 6DOF.vi"/>
			</Item>
			<Item Name="Njord-GUI Info exchange" Type="Folder">
				<Item Name="update GUI KF tuning.vi" Type="VI" URL="../Library/Njord-GUI Info exchange/update GUI KF tuning.vi"/>
				<Item Name="update GUI nonlinPID tuning.vi" Type="VI" URL="../Library/Njord-GUI Info exchange/update GUI nonlinPID tuning.vi"/>
			</Item>
			<Item Name="Signal Processing" Type="Folder">
				<Item Name="Alt_input (SubVI).vi" Type="VI" URL="../Library/Signal Processing/Alt_input (SubVI).vi"/>
				<Item Name="Alt_IO (SubVI).vi" Type="VI" URL="../Library/Signal Processing/Alt_IO (SubVI).vi"/>
				<Item Name="APOS_IO (SubVI).vi" Type="VI" URL="../Library/Signal Processing/APOS_IO (SubVI).vi"/>
				<Item Name="cocoord (SubVI).vi" Type="VI" URL="../Library/Signal Processing/cocoord (SubVI).vi"/>
				<Item Name="Configure sub-VI.vi" Type="VI" URL="../Library/Signal Processing/Configure sub-VI.vi"/>
				<Item Name="CRIO write (SubVI).vi" Type="VI" URL="../Library/Signal Processing/CRIO write (SubVI).vi"/>
				<Item Name="DG convert (SubVI).vi" Type="VI" URL="../Library/Signal Processing/DG convert (SubVI).vi"/>
				<Item Name="DG in (SubVI).vi" Type="VI" URL="../Library/Signal Processing/DG in (SubVI).vi"/>
				<Item Name="DVL convert (SubVI).vi" Type="VI" URL="../Library/Signal Processing/DVL convert (SubVI).vi"/>
				<Item Name="DVL_2_QUAD (SubVI).vi" Type="VI" URL="../Library/Signal Processing/DVL_2_QUAD (SubVI).vi"/>
				<Item Name="Input convert (SubVI).vi" Type="VI" URL="../Library/Signal Processing/Input convert (SubVI).vi"/>
				<Item Name="JS chair get (SubVI).vi" Type="VI" URL="../Library/Signal Processing/JS chair get (SubVI).vi"/>
				<Item Name="MRU_IO (SubVI).vi" Type="VI" URL="../Library/Signal Processing/MRU_IO (SubVI).vi"/>
				<Item Name="MRU_SP (SubVI).vi" Type="VI" URL="../Library/Signal Processing/MRU_SP (SubVI).vi"/>
				<Item Name="MRUinput subvi.vi" Type="VI" URL="../Library/Signal Processing/MRUinput subvi.vi"/>
				<Item Name="MT MOD (SubVI).vi" Type="VI" URL="../Library/Signal Processing/MT MOD (SubVI).vi"/>
				<Item Name="MT MOD 100 (SubVI).vi" Type="VI" URL="../Library/Signal Processing/MT MOD 100 (SubVI).vi"/>
				<Item Name="MT_DATA_TRANS(SubVI).vi" Type="VI" URL="../Library/Signal Processing/MT_DATA_TRANS(SubVI).vi"/>
				<Item Name="MT_GET old.vi" Type="VI" URL="../Library/Signal Processing/MT_GET old.vi"/>
				<Item Name="MT_GET.vi" Type="VI" URL="../Library/Signal Processing/MT_GET.vi"/>
				<Item Name="MT_GET_100.vi" Type="VI" URL="../Library/Signal Processing/MT_GET_100.vi"/>
				<Item Name="NAVI_IO 2 (SubVI).vi" Type="VI" URL="../Library/Signal Processing/NAVI_IO 2 (SubVI).vi"/>
				<Item Name="NAVIpacinput subvi 30k.vi" Type="VI" URL="../Library/Signal Processing/NAVIpacinput subvi 30k.vi"/>
				<Item Name="NAVIpacinput subvi.vi" Type="VI" URL="../Library/Signal Processing/NAVIpacinput subvi.vi"/>
				<Item Name="Origin_SP (SubVI).vi" Type="VI" URL="../Library/Signal Processing/Origin_SP (SubVI).vi"/>
				<Item Name="Port 3_IO (SubVI).vi" Type="VI" URL="../Library/Signal Processing/Port 3_IO (SubVI).vi"/>
				<Item Name="ROV_IO 2 (SubVI).vi" Type="VI" URL="../Library/Signal Processing/ROV_IO 2 (SubVI).vi"/>
				<Item Name="ROV_IO 30k (SubVI).vi" Type="VI" URL="../Library/Signal Processing/ROV_IO 30k (SubVI).vi"/>
				<Item Name="ROVinput 30k subvi.vi" Type="VI" URL="../Library/Signal Processing/ROVinput 30k subvi.vi"/>
				<Item Name="ROVinput subvi.vi" Type="VI" URL="../Library/Signal Processing/ROVinput subvi.vi"/>
				<Item Name="search_string (SubVI).vi" Type="VI" URL="../Library/Signal Processing/search_string (SubVI).vi"/>
				<Item Name="Set Length.vi" Type="VI" URL="../Library/Signal Processing/Set Length.vi"/>
				<Item Name="Signal IO (SubVI).vi" Type="VI" URL="../Library/Signal Processing/Signal IO (SubVI).vi"/>
				<Item Name="Signal IO (SubVI)_SIL.vi" Type="VI" URL="../Library/Signal Processing/Signal IO (SubVI)_SIL.vi"/>
				<Item Name="SP BC (SubVI).vi" Type="VI" URL="../Library/Signal Processing/SP BC (SubVI).vi"/>
				<Item Name="SP_mod (SubVI).vi" Type="VI" URL="../Library/Signal Processing/SP_mod (SubVI).vi"/>
				<Item Name="SSB get(SubVI).vi" Type="VI" URL="../Library/Signal Processing/SSB get(SubVI).vi"/>
				<Item Name="TCP write (SubVI).vi" Type="VI" URL="../Library/Signal Processing/TCP write (SubVI).vi"/>
			</Item>
			<Item Name="Text Files Routines" Type="Folder">
				<Item Name="writeToFile.vi" Type="VI" URL="../Library/Text Files Routines/writeToFile.vi"/>
			</Item>
		</Item>
		<Item Name="Reference Models" Type="Folder">
			<Item Name="Reference Mode Tracking.vi" Type="VI" URL="../Reference Models/Reference Mode Tracking.vi"/>
			<Item Name="Reference Model Altitude.vi" Type="VI" URL="../Reference Models/Reference Model Altitude.vi"/>
			<Item Name="Reference Model DP.vi" Type="VI" URL="../Reference Models/Reference Model DP.vi"/>
			<Item Name="Reference Model Joystick.vi" Type="VI" URL="../Reference Models/Reference Model Joystick.vi"/>
			<Item Name="Reference Model(SubVI).vi" Type="VI" URL="../Reference Models/Reference Model(SubVI).vi"/>
			<Item Name="Reference Model.vi" Type="VI" URL="../Reference Models/Reference Model.vi"/>
		</Item>
		<Item Name="Simulator" Type="Folder">
			<Item Name="Simulator" Type="Folder"/>
		</Item>
		<Item Name="Testing" Type="Folder" URL="../Testing">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Controller Library.lvlib" Type="Library" URL="../Controller Library.lvlib"/>
		<Item Name="Guidance Library.lvlib" Type="Library" URL="../Guidance Library.lvlib"/>
		<Item Name="Logdata (SubVI).vi" Type="VI" URL="../Logdata (SubVI).vi"/>
		<Item Name="mainVI_SIL.vi" Type="VI" URL="../mainVI_SIL.vi"/>
		<Item Name="Njord Control System.vi" Type="VI" URL="../Njord Control System.vi"/>
		<Item Name="Observer Library.lvlib" Type="Library" URL="../Observer Library.lvlib"/>
		<Item Name="Sensors.lvlib" Type="Library" URL="../Sensors.lvlib"/>
		<Item Name="Supervisor.lvclass" Type="LVClass" URL="../Supervisor/Supervisor.lvclass"/>
		<Item Name="TestingVI.vi" Type="VI" URL="../TestingVI.vi"/>
		<Item Name="Thrust Allocation.lvclass" Type="LVClass" URL="../Thrust Allocation/Thrust Allocation.lvclass"/>
		<Item Name="Thruster.lvclass" Type="LVClass" URL="../Thruster/Thruster.lvclass"/>
		<Item Name="Vessel.lvclass" Type="LVClass" URL="../ROV/Vessel.lvclass"/>
		<Item Name="Wait2write (SubVI).vi" Type="VI" URL="../Library/Helping Routines/Wait2write (SubVI).vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="_2DArrToArrWfms.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_2DArrToArrWfms.vi"/>
				<Item Name="_ArrWfmsTo1DInterleave.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_ArrWfmsTo1DInterleave.vi"/>
				<Item Name="_ArrWfmsTo2DArr.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_ArrWfmsTo2DArr.vi"/>
				<Item Name="_ArrWfmsToData.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_ArrWfmsToData.vi"/>
				<Item Name="_FormatFromData (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (DBL).vi"/>
				<Item Name="_FormatFromData (I16).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (I16).vi"/>
				<Item Name="_FormatFromData (I32).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (I32).vi"/>
				<Item Name="_FormatFromData (SGL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (SGL).vi"/>
				<Item Name="_FormatFromData (U8).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (U8).vi"/>
				<Item Name="_FormatFromData.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData.vi"/>
				<Item Name="_Get Sound Error From Return Value.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_Get Sound Error From Return Value.vi"/>
				<Item Name="Acquire Input Data.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Acquire Input Data.vi"/>
				<Item Name="Acquire Semaphore.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Acquire Semaphore.vi"/>
				<Item Name="AddNamedRendezvousPrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/AddNamedRendezvousPrefix.vi"/>
				<Item Name="AddNamedSemaphorePrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/AddNamedSemaphorePrefix.vi"/>
				<Item Name="Attitude Indicator.xctl" Type="XControl" URL="/&lt;vilib&gt;/robotics/Controls/Attitude Indicator/Attitude Indicator.xctl"/>
				<Item Name="Bit-array To Byte-array.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Bit-array To Byte-array.vi"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="CenterRectInBnds.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/CenterRectInBnds.vi"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Check Path.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Path.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Close Input Device.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Close Input Device.vi"/>
				<Item Name="closeJoystick.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/closeJoystick.vi"/>
				<Item Name="closeKeyboard.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/closeKeyboard.vi"/>
				<Item Name="closeMouse.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/closeMouse.vi"/>
				<Item Name="Color to RGB.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/colorconv.llb/Color to RGB.vi"/>
				<Item Name="Compass Indicator.xctl" Type="XControl" URL="/&lt;vilib&gt;/robotics/Controls/Compass Indicator/Compass Indicator.xctl"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Create Mask By Alpha.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Create Mask By Alpha.vi"/>
				<Item Name="Create Mask.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Create Mask.vi"/>
				<Item Name="Create New Rendezvous.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Create New Rendezvous.vi"/>
				<Item Name="Create Rendezvous.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Create Rendezvous.vi"/>
				<Item Name="Destroy A Rendezvous.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Destroy A Rendezvous.vi"/>
				<Item Name="Destroy Rendezvous.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Destroy Rendezvous.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Directory of Top Level VI.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Directory of Top Level VI.vi"/>
				<Item Name="Draw Arc.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Arc.vi"/>
				<Item Name="Draw Circle by Radius.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Draw Circle by Radius.vi"/>
				<Item Name="Draw Flattened Pixmap.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Flattened Pixmap.vi"/>
				<Item Name="Draw Multiple Lines.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Multiple Lines.vi"/>
				<Item Name="Draw Point.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Point.vi"/>
				<Item Name="Draw Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Rect.vi"/>
				<Item Name="Draw Text at Point.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Text at Point.vi"/>
				<Item Name="Draw Text in Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Text in Rect.vi"/>
				<Item Name="DWDT Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/DWDTOps.llb/DWDT Error Code.vi"/>
				<Item Name="Dynamic To Waveform Array.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/transition.llb/Dynamic To Waveform Array.vi"/>
				<Item Name="Empty Picture" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Empty Picture"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrorDescriptions.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/ErrorDescriptions.vi"/>
				<Item Name="errorList.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/errorList.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="ex_BuildTextVarProps.ctl" Type="VI" URL="/&lt;vilib&gt;/express/express output/BuildTextBlock.llb/ex_BuildTextVarProps.ctl"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="FixBadRect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/FixBadRect.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="FormatTime String.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/FormatTime String.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get File Extension.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Get File Extension.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetNamedRendezvousPrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/GetNamedRendezvousPrefix.vi"/>
				<Item Name="GetNamedSemaphorePrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/GetNamedSemaphorePrefix.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Hilite Color.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Hilite Color.vi"/>
				<Item Name="imagedata.ctl" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/imagedata.ctl"/>
				<Item Name="Initialize Joystick.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Initialize Joystick.vi"/>
				<Item Name="Internecine Avoider.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tcp.llb/Internecine Avoider.vi"/>
				<Item Name="joystickAcquire.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/joystickAcquire.vi"/>
				<Item Name="keyboardAcquire.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/keyboardAcquire.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVCursorListTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVCursorListTypeDef.ctl"/>
				<Item Name="lvpidtkt.dll" Type="Document" URL="/&lt;vilib&gt;/addons/control/pid/lvpidtkt.dll"/>
				<Item Name="LVPositionTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVPositionTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="mouseAcquire.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/mouseAcquire.vi"/>
				<Item Name="NI_3D Picture Control.lvlib" Type="Library" URL="/&lt;vilib&gt;/picture/3D Picture Control/NI_3D Picture Control.lvlib"/>
				<Item Name="NI_AAL_Angle.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AAL_Angle.lvlib"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
				<Item Name="NI_AngleManipulation.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/AngleManip/NI_AngleManipulation.lvlib"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_Matrix.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/Matrix/NI_Matrix.lvlib"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="NI_PID__prctrl compat.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/control/pid/NI_PID__prctrl compat.lvlib"/>
				<Item Name="NI_PID_pid.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/control/pid/NI_PID_pid.lvlib"/>
				<Item Name="NI_Robotics_Attitude Picture.lvlib" Type="Library" URL="/&lt;vilib&gt;/robotics/Controls/Attitude Indicator/Attitude Picture/NI_Robotics_Attitude Picture.lvlib"/>
				<Item Name="NI_Robotics_Compass Picture.lvlib" Type="Library" URL="/&lt;vilib&gt;/robotics/Controls/Compass Indicator/Compass Picture/NI_Robotics_Compass Picture.lvlib"/>
				<Item Name="NI_Robotics_Control Utilities.lvlib" Type="Library" URL="/&lt;vilib&gt;/robotics/Controls/Utilities/NI_Robotics_Control Utilities.lvlib"/>
				<Item Name="NI_XML.lvlib" Type="Library" URL="/&lt;vilib&gt;/xml/NI_XML.lvlib"/>
				<Item Name="Normalize Waveform.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/WDTOps.llb/Normalize Waveform.vi"/>
				<Item Name="Not A Rendezvous.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Not A Rendezvous.vi"/>
				<Item Name="Not A Semaphore.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Not A Semaphore.vi"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Obtain Semaphore Reference.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Obtain Semaphore Reference.vi"/>
				<Item Name="Path To Command Line String.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/Path To Command Line String.vi"/>
				<Item Name="PathToUNIXPathString.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/CFURL.llb/PathToUNIXPathString.vi"/>
				<Item Name="PCT Pad String.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/PCT Pad String.vi"/>
				<Item Name="Picture to Pixmap.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Picture to Pixmap.vi"/>
				<Item Name="POffsetRect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/POffsetRect.vi"/>
				<Item Name="Point2Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/Point2Rect.vi"/>
				<Item Name="Query Input Devices.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Query Input Devices.vi"/>
				<Item Name="Read JPEG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Read JPEG File.vi"/>
				<Item Name="Read PNG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/png.llb/Read PNG File.vi"/>
				<Item Name="Real Matrix NI_Silver.ctl" Type="VI" URL="/&lt;vilib&gt;/silver_ctls/ArrayMatrixCluster/Real Matrix NI_Silver.ctl"/>
				<Item Name="RectCentroid.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/RectCentroid.vi"/>
				<Item Name="Release Semaphore Reference.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Release Semaphore Reference.vi"/>
				<Item Name="Release Semaphore.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Release Semaphore.vi"/>
				<Item Name="Release Waiting Procs.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Release Waiting Procs.vi"/>
				<Item Name="RemoveNamedRendezvousPrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/RemoveNamedRendezvousPrefix.vi"/>
				<Item Name="RemoveNamedSemaphorePrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/RemoveNamedSemaphorePrefix.vi"/>
				<Item Name="Rendezvous Name &amp; Ref DB Action.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Rendezvous Name &amp; Ref DB Action.ctl"/>
				<Item Name="Rendezvous Name &amp; Ref DB.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Rendezvous Name &amp; Ref DB.vi"/>
				<Item Name="Rendezvous RefNum" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Rendezvous RefNum"/>
				<Item Name="RendezvousDataCluster.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/RendezvousDataCluster.ctl"/>
				<Item Name="RGB to Color.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/colorconv.llb/RGB to Color.vi"/>
				<Item Name="Sampling Mode.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sampling Mode.ctl"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Semaphore RefNum" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Semaphore RefNum"/>
				<Item Name="Semaphore Refnum Core.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Semaphore Refnum Core.ctl"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set Pen State.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Set Pen State.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="Sound Data Format.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Data Format.ctl"/>
				<Item Name="Sound File Close.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Close.vi"/>
				<Item Name="Sound File Info (refnum).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Info (refnum).vi"/>
				<Item Name="Sound File Position.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Position.ctl"/>
				<Item Name="Sound File Read (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Read (DBL).vi"/>
				<Item Name="Sound File Read Open.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Read Open.vi"/>
				<Item Name="Sound File Read Simple.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Read Simple.vi"/>
				<Item Name="Sound File Refnum.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Refnum.ctl"/>
				<Item Name="Sound Output Clear.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Clear.vi"/>
				<Item Name="Sound Output Configure.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Configure.vi"/>
				<Item Name="Sound Output Start.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Start.vi"/>
				<Item Name="Sound Output Task ID.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Task ID.ctl"/>
				<Item Name="Sound Output Wait.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Wait.vi"/>
				<Item Name="Sound Output Write (DBL Single).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (DBL Single).vi"/>
				<Item Name="Sound Output Write (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (DBL).vi"/>
				<Item Name="Sound Output Write (I16).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (I16).vi"/>
				<Item Name="Sound Output Write (I32).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (I32).vi"/>
				<Item Name="Sound Output Write (SGL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (SGL).vi"/>
				<Item Name="Sound Output Write (U8).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (U8).vi"/>
				<Item Name="Sound Output Write Simple (DBL1).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write Simple (DBL1).vi"/>
				<Item Name="Sound Output Write Simple (DBL2).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write Simple (DBL2).vi"/>
				<Item Name="Sound Output Write Simple.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write Simple.vi"/>
				<Item Name="Sound Output Write.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write.vi"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="subDisplayMessage.vi" Type="VI" URL="/&lt;vilib&gt;/express/express output/DisplayMessageBlock.llb/subDisplayMessage.vi"/>
				<Item Name="subElapsedTime.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/subElapsedTime.vi"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="subPlayWaveform.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/PlayWaveformSource.llb/subPlayWaveform.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="TCP Listen Internal List.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tcp.llb/TCP Listen Internal List.vi"/>
				<Item Name="TCP Listen List Operations.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/tcp.llb/TCP Listen List Operations.ctl"/>
				<Item Name="TCP Listen.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tcp.llb/TCP Listen.vi"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="Unflatten Pixmap.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pixmap.llb/Unflatten Pixmap.vi"/>
				<Item Name="Validate Semaphore Size.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Validate Semaphore Size.vi"/>
				<Item Name="Version To Dotted String.vi" Type="VI" URL="/&lt;vilib&gt;/_xctls/Version To Dotted String.vi"/>
				<Item Name="Wait at Rendezvous.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/rendezvs.llb/Wait at Rendezvous.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="XControlSupport.lvlib" Type="Library" URL="/&lt;vilib&gt;/_xctls/XControlSupport.lvlib"/>
			</Item>
			<Item Name="About.vi" Type="VI" URL="../Graphical User Interface/About.vi"/>
			<Item Name="AltitudeDialog.vi" Type="VI" URL="../Graphical User Interface/AltitudeDialog.vi"/>
			<Item Name="AltitudePlots.vi" Type="VI" URL="../Graphical User Interface/AltitudePlots.vi"/>
			<Item Name="Camera Control.vi" Type="VI" URL="../Graphical User Interface/Camera Control.vi"/>
			<Item Name="CameraControlHelp.vi" Type="VI" URL="../Graphical User Interface/CameraControlHelp.vi"/>
			<Item Name="Change Map Range.vi" Type="VI" URL="../Graphical User Interface/Change Map Range.vi"/>
			<Item Name="CJ (SubVI).vi" Type="VI" URL="../Guidance/Constant Jerk Guidance/CJ (SubVI).vi"/>
			<Item Name="CJ Theta (SubVI).vi" Type="VI" URL="../Guidance/Constant Jerk Guidance/CJ Theta (SubVI).vi"/>
			<Item Name="CJG output (SubVI).vi" Type="VI" URL="../Guidance/Constant Jerk Guidance/CJG output (SubVI).vi"/>
			<Item Name="CJG param (SubVI).vi" Type="VI" URL="../Guidance/Constant Jerk Guidance/CJG param (SubVI).vi"/>
			<Item Name="Collecting Unit.vi" Type="VI" URL="../Graphical User Interface/Collecting Unit.vi"/>
			<Item Name="Control go.ctl" Type="VI" URL="../Graphical User Interface/Control go.ctl"/>
			<Item Name="ControlPanelHelp.vi" Type="VI" URL="../Graphical User Interface/ControlPanelHelp.vi"/>
			<Item Name="Create Joystick Message.vi" Type="VI" URL="../Graphical User Interface/Create Joystick Message.vi"/>
			<Item Name="Desired vector (SubVI).vi" Type="VI" URL="../Guidance/Constant Jerk Guidance/Desired vector (SubVI).vi"/>
			<Item Name="DialogMenu.rtm" Type="Document" URL="../Graphical User Interface/DialogMenu.rtm"/>
			<Item Name="Dist Dir (SubVI).vi" Type="VI" URL="../Guidance/Constant Jerk Guidance/Dist Dir (SubVI).vi"/>
			<Item Name="DOMUserDefRef.dll" Type="Document" URL="DOMUserDefRef.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="DP Options.vi" Type="VI" URL="../Graphical User Interface/DP Options.vi"/>
			<Item Name="DP Panel.vi" Type="VI" URL="../Graphical User Interface/DP Panel.vi"/>
			<Item Name="DPButtonsHelp.vi" Type="VI" URL="../Graphical User Interface/DPButtonsHelp.vi"/>
			<Item Name="DPHelp.vi" Type="VI" URL="../Graphical User Interface/DPHelp.vi"/>
			<Item Name="DPModesHelp.vi" Type="VI" URL="../Graphical User Interface/DPModesHelp.vi"/>
			<Item Name="EasterEgg.vi" Type="VI" URL="../Graphical User Interface/EasterEgg.vi"/>
			<Item Name="ECFPlot.vi" Type="VI" URL="../Graphical User Interface/ECFPlot.vi"/>
			<Item Name="Empty Panel 2.vi" Type="VI" URL="../Graphical User Interface/Empty Panel 2.vi"/>
			<Item Name="Empty Panel.vi" Type="VI" URL="../Graphical User Interface/Empty Panel.vi"/>
			<Item Name="Empty Tuning Panel.vi" Type="VI" URL="../Graphical User Interface/Empty Tuning Panel.vi"/>
			<Item Name="Extra Buttons.vi" Type="VI" URL="../Graphical User Interface/Extra Buttons.vi"/>
			<Item Name="Find CS Path.vi" Type="VI" URL="../Graphical User Interface/Useful Routines/Find CS Path.vi"/>
			<Item Name="General.vi" Type="VI" URL="../Graphical User Interface/General.vi"/>
			<Item Name="get_set_point_vec (SubVI).vi" Type="VI" URL="../Library/Helping Routines/get_set_point_vec (SubVI).vi"/>
			<Item Name="Graphical User Interface - Frigg.vi" Type="VI" URL="../Graphical User Interface/Graphical User Interface - Frigg.vi"/>
			<Item Name="GraphView.vi" Type="VI" URL="../Graphical User Interface/GraphView.vi"/>
			<Item Name="GUI_Menu.rtm" Type="Document" URL="../Graphical User Interface/GUI_Menu.rtm"/>
			<Item Name="HeadingMod.vi" Type="VI" URL="../Graphical User Interface/HeadingMod.vi"/>
			<Item Name="Help Center.vi" Type="VI" URL="../Graphical User Interface/Help Center.vi"/>
			<Item Name="HMI Panel.vi" Type="VI" URL="../Graphical User Interface/HMI Panel.vi"/>
			<Item Name="Joystick Mapping Function.vi" Type="VI" URL="../Graphical User Interface/Joystick Mapping Function.vi"/>
			<Item Name="Joystick Options.vi" Type="VI" URL="../Graphical User Interface/Joystick Options.vi"/>
			<Item Name="JoystickButtonHelp.vi" Type="VI" URL="../Graphical User Interface/JoystickButtonHelp.vi"/>
			<Item Name="JoystickHelp.vi" Type="VI" URL="../Graphical User Interface/JoystickHelp.vi"/>
			<Item Name="JoystickManipulatorButtonHelp.vi" Type="VI" URL="../Graphical User Interface/JoystickManipulatorButtonHelp.vi"/>
			<Item Name="KalmanFilterObserverTuningPanel.vi" Type="VI" URL="../Graphical User Interface/KalmanFilterObserverTuningPanel.vi"/>
			<Item Name="LawnMower pattern INPUT dialog.vi" Type="VI" URL="../Graphical User Interface/LawnMower pattern INPUT dialog.vi"/>
			<Item Name="Light Panel.vi" Type="VI" URL="../Graphical User Interface/Light Panel.vi"/>
			<Item Name="LightPanelHelp.vi" Type="VI" URL="../Graphical User Interface/LightPanelHelp.vi"/>
			<Item Name="LinearPidTuningPanel.vi" Type="VI" URL="../Graphical User Interface/LinearPidTuningPanel.vi"/>
			<Item Name="LogStringCreator.vi" Type="VI" URL="../Graphical User Interface/LogStringCreator.vi"/>
			<Item Name="LogThrustStringCreator.vi" Type="VI" URL="../Graphical User Interface/LogThrustStringCreator.vi"/>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
			<Item Name="lvinput.dll" Type="Document" URL="/&lt;resource&gt;/lvinput.dll"/>
			<Item Name="lvsound2.dll" Type="Document" URL="/&lt;resource&gt;/lvsound2.dll"/>
			<Item Name="Manipulator Panel.vi" Type="VI" URL="../Graphical User Interface/Manipulator Panel.vi"/>
			<Item Name="ManipulatorPanelHelp.vi" Type="VI" URL="../Graphical User Interface/ManipulatorPanelHelp.vi"/>
			<Item Name="Map Visualization.vi" Type="VI" URL="../Graphical User Interface/Map Visualization.vi"/>
			<Item Name="MapOwnWindow.vi" Type="VI" URL="../Graphical User Interface/MapOwnWindow.vi"/>
			<Item Name="MapVHelp.vi" Type="VI" URL="../Graphical User Interface/MapVHelp.vi"/>
			<Item Name="MTiPlots.vi" Type="VI" URL="../Graphical User Interface/MTiPlots.vi"/>
			<Item Name="NiFpgaLv.dll" Type="Document" URL="NiFpgaLv.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="NonLinearPidTuningPanel.vi" Type="VI" URL="../Graphical User Interface/NonLinearPidTuningPanel.vi"/>
			<Item Name="OOI In Dialog.vi" Type="VI" URL="../Graphical User Interface/Objects Of Interest/OOI In Dialog.vi"/>
			<Item Name="Options Panel.vi" Type="VI" URL="../Graphical User Interface/Options Panel.vi"/>
			<Item Name="Port Configuration Options.vi" Type="VI" URL="../Graphical User Interface/Port Configuration Options.vi"/>
			<Item Name="Port1 IO (30k) (SubVI).vi" Type="VI" URL="../Library/Signal Processing/Port1 IO (30k) (SubVI).vi"/>
			<Item Name="PositionPlotInterval.vi" Type="VI" URL="../Graphical User Interface/PositionPlotInterval.vi"/>
			<Item Name="PositionPlots.vi" Type="VI" URL="../Graphical User Interface/PositionPlots.vi"/>
			<Item Name="Power Instruments.vi" Type="VI" URL="../Graphical User Interface/Power Instruments.vi"/>
			<Item Name="Read Attitude Msg.vi" Type="VI" URL="../Graphical User Interface/Read Attitude Msg.vi"/>
			<Item Name="Read Input String.vi" Type="VI" URL="../Graphical User Interface/Read Input String.vi"/>
			<Item Name="Read OOI List.vi" Type="VI" URL="../Graphical User Interface/Objects Of Interest/Read OOI List.vi"/>
			<Item Name="Read Ship States.vi" Type="VI" URL="../Graphical User Interface/Read Ship States.vi"/>
			<Item Name="ReadAltitudeMsg.vi" Type="VI" URL="../Graphical User Interface/ReadAltitudeMsg.vi"/>
			<Item Name="ReadThrusterMsg.vi" Type="VI" URL="../Graphical User Interface/ReadThrusterMsg.vi"/>
			<Item Name="Restart Procedure.vi" Type="VI" URL="../Graphical User Interface/Restart Procedure.vi"/>
			<Item Name="SetOriginPanel.vi" Type="VI" URL="../Graphical User Interface/SetOriginPanel.vi"/>
			<Item Name="Startup Panel.vi" Type="VI" URL="../Graphical User Interface/Startup Panel.vi"/>
			<Item Name="Stop VIs.vi" Type="VI" URL="../Graphical User Interface/Stop VIs.vi"/>
			<Item Name="StringToMatrix.vi" Type="VI" URL="../Library/Helping Routines/StringToMatrix.vi"/>
			<Item Name="ThrustPlot.vi" Type="VI" URL="../Graphical User Interface/ThrustPlot.vi"/>
			<Item Name="Tracking Options.vi" Type="VI" URL="../Graphical User Interface/Tracking Options.vi"/>
			<Item Name="Tracking Panel.vi" Type="VI" URL="../Graphical User Interface/Tracking Panel.vi"/>
			<Item Name="TrackingButtonsHelp.vi" Type="VI" URL="../Graphical User Interface/TrackingButtonsHelp.vi"/>
			<Item Name="TrackingHelp.vi" Type="VI" URL="../Graphical User Interface/TrackingHelp.vi"/>
			<Item Name="TrackingLawnMowerHelp.vi" Type="VI" URL="../Graphical User Interface/TrackingLawnMowerHelp.vi"/>
			<Item Name="TuningPanel.vi" Type="VI" URL="../Graphical User Interface/TuningPanel.vi"/>
			<Item Name="update KF tuning GUI.vi" Type="VI" URL="../Graphical User Interface/Tuning/update KF tuning GUI.vi"/>
			<Item Name="update PID tuning GUI.vi" Type="VI" URL="../Graphical User Interface/Tuning/update PID tuning GUI.vi"/>
			<Item Name="UpdateOOI List.vi" Type="VI" URL="../Graphical User Interface/Objects Of Interest/UpdateOOI List.vi"/>
			<Item Name="UserGuideMenu.rtm" Type="Document" URL="../Graphical User Interface/UserGuideMenu.rtm"/>
			<Item Name="VelocityPlots.vi" Type="VI" URL="../Graphical User Interface/VelocityPlots.vi"/>
			<Item Name="Vessel Visualization.vi" Type="VI" URL="../Graphical User Interface/Vessel Visualization.vi"/>
			<Item Name="VesselDHelp.vi" Type="VI" URL="../Graphical User Interface/VesselDHelp.vi"/>
			<Item Name="Waypoints Generator.vi" Type="VI" URL="../Graphical User Interface/Waypoints Generator.vi"/>
			<Item Name="OR_deadZone.vi" Type="VI" URL="../Graphical User Interface/Oculus Rift/OR_deadZone.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="mainVI5" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{1420DAB6-83E1-40E3-9D9F-9261E50DA45A}</Property>
				<Property Name="App_INI_GUID" Type="Str">{394DBF4D-93D0-4EAE-8A30-47F4E2D4DA16}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{B5662AA2-2645-4EC0-B429-A611C29F800B}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">mainVI5</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/ControlSystem</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{8E01FDDC-9D1C-498E-936F-7407FD64C06B}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">ControlSystem.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/ControlSystem/ControlSystem.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/ControlSystem/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref"></Property>
				<Property Name="Source[0].itemID" Type="Str">{7CF575EA-36EF-4026-A7FD-B9E75AD1E6DB}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Njord Control System.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_fileDescription" Type="Str">mainVI5</Property>
				<Property Name="TgtF_internalName" Type="Str">mainVI5</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">mainVI5</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{DEF167F0-933F-4F8D-B2A6-A5A6C4FB65A2}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">ControlSystem.exe</Property>
			</Item>
		</Item>
	</Item>
	<Item Name="AURLcRIO" Type="RT CompactRIO">
		<Property Name="alias.name" Type="Str">AURLcRIO</Property>
		<Property Name="alias.value" Type="Str">192.168.1.155</Property>
		<Property Name="CCSymbols" Type="Str">OS,VxWorks;CPU,PowerPC;TARGET_TYPE,RT;DeviceCode,729D;</Property>
		<Property Name="crio.ControllerPID" Type="Str">729D</Property>
		<Property Name="crio.family" Type="Str">901x</Property>
		<Property Name="host.ResponsivenessCheckEnabled" Type="Bool">true</Property>
		<Property Name="host.ResponsivenessCheckPingDelay" Type="UInt">5000</Property>
		<Property Name="host.ResponsivenessCheckPingTimeout" Type="UInt">1000</Property>
		<Property Name="host.TargetCPUID" Type="UInt">2</Property>
		<Property Name="host.TargetOSID" Type="UInt">14</Property>
		<Property Name="mathScriptPath" Type="Str">C:\Documents and Settings\Administrator\My Documents\LabVIEW Data</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="target.cleanupVisa" Type="Bool">false</Property>
		<Property Name="target.FPProtocolGlobals_ControlTimeLimit" Type="Int">300</Property>
		<Property Name="target.getDefault-&gt;WebServer.Port" Type="Int">80</Property>
		<Property Name="target.getDefault-&gt;WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.IOScan.Faults" Type="Str">1.0,0;</Property>
		<Property Name="target.IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="target.IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="target.IOScan.Period" Type="UInt">10000</Property>
		<Property Name="target.IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="target.IOScan.Priority" Type="UInt">0</Property>
		<Property Name="target.IOScan.ReportModeConflict" Type="Bool">false</Property>
		<Property Name="target.IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
		<Property Name="target.IsRemotePanelSupported" Type="Bool">true</Property>
		<Property Name="target.RTCPULoadMonitoringEnabled" Type="Bool">true</Property>
		<Property Name="target.RTDebugWebServerHTTPPort" Type="Int">8001</Property>
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
		<Property Name="target.server.tcp.serviceName" Type="Str"></Property>
		<Property Name="target.server.tcp.serviceName.default" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.vi.access" Type="Str">+*</Property>
		<Property Name="target.server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="target.server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.viscripting.showScriptingOperationsInContextHelp" Type="Bool">false</Property>
		<Property Name="target.server.viscripting.showScriptingOperationsInEditor" Type="Bool">false</Property>
		<Property Name="target.WebServer.Config" Type="Str"># Web server configuration file.
# Generated by LabVIEW 12.0.1f2
# 18.06.2013 15:46:36
#
# Global Directives
#
NI.AddLVRouteVars
TypesConfig "$LVSERVER_CONFIGROOT/mime.types"
LimitWorkers 10
LoadModulePath "$LVSERVER_MODULEPATHS"
LoadModule LVAuth lvauthmodule
LoadModule LVRFP lvrfpmodule
LoadModule esp libespModule
LoadModule LvExec ws_runtime
Listen 80
#
# Directives that apply to the default server
#
NI.ServerName LabVIEW
DocumentRoot "$LVSERVER_DOCROOT"
InactivityTimeout 60
SetConnector netConnector
AddHandler LVAuth
AddHandler LVRFP
AddHandler LvExec
AddHandler espHandler
AddHandler espHandler .esp
AddHandler fileHandler ""
AddOutputFilter chunkFilter
DirectoryIndex index.htm
</Property>
		<Property Name="target.WebServer.Enabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogEnabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogPath" Type="Path">/c/ni-rt/system/www/www.log</Property>
		<Property Name="target.WebServer.Port" Type="Int">80</Property>
		<Property Name="target.WebServer.RootPath" Type="Path">/c/ni-rt/system/www</Property>
		<Property Name="target.WebServer.TcpAccess" Type="Str">c+*</Property>
		<Property Name="target.WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.WebServer.ViAccess" Type="Str">+*</Property>
		<Property Name="target.webservices.SecurityAPIKey" Type="Str">PqVr/ifkAQh+lVrdPIykXlFvg12GhhQFR8H9cUhphgg=:pTe9HRlQuMfJxAG6QCGq7UvoUpJzAzWGKy5SbZ+roSU=</Property>
		<Property Name="target.webservices.ValidTimestampWindow" Type="UInt">15</Property>
		<Property Name="TargetOSID" Type="Str">VxWorks-PPC603</Property>
		<Item Name="Chassis" Type="cRIO Chassis">
			<Property Name="crio.ProgrammingMode" Type="Str">fpga</Property>
			<Property Name="crio.ResourceID" Type="Str">RIO0</Property>
			<Property Name="crio.Type" Type="Str">cRIO-9074</Property>
			<Item Name="FPGA Target" Type="FPGA Target">
				<Property Name="AutoRun" Type="Bool">false</Property>
				<Property Name="configString.guid" Type="Str">{21A573A4-B3FF-4A21-9CE0-20B9DA934000}cRIO Subresource{26C89342-D1E2-47AD-B82F-FFEBAA3E5728}resource=/Sleep;0;ReadMethodType=bool;WriteMethodType=bool{45F5465A-B68B-4169-843C-94C25DE7BF95}resource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool{468DE042-E525-4B8E-8C42-A1E9D5A3ED74}resource=/Chassis Temperature;0;ReadMethodType=i16{4FCCC9AA-0C18-4F96-96C5-841C274A7D04}resource=/Scan Clock;0;ReadMethodType=bool{6E89E5B2-1F22-4FBB-8A06-0B44A20B6066}cRIO Subresource{743BC95C-6644-4BD1-A235-D7E6BE3837D4}"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO2;DataType=100080000000000100094002000349313600010000000000000000;DisableOnOverflowUnderflow=FALSE"{8B9C92D0-4838-4ECC-9E6A-2B222316EE3A}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]{909712D0-5835-4EA1-B20E-33DF69902EB1}cRIO Subresource{918AEB55-7D5E-4F98-8B0D-01D5CB22AB68}"ControlLogic=0;NumberOfElements=1023;Type=2;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;READ_FIFO;DataType=100080000000000100094006000355313600010000000000000000;DisableOnOverflowUnderflow=FALSE"{B10FA560-6703-445D-ABF9-33ADCCF9D75B}cRIO Subresource{B95C7D0C-6493-4EFE-AFB7-129030FBB87B}cRIO Subresource{BACA50B1-8EA7-4B30-A13A-56BA162CA038}cRIO Subresource{C9EDF5F9-1079-48F7-AECB-41CEA0C12AF0}cRIO Subresource{CE2FA74D-47CB-4D74-8132-4402E34E5874}cRIO Subresource{D22172DE-BD44-42DF-A9DF-90D112D4363B}ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000.000000;MaxFreq=40000000.000000;VariableFreq=0;NomFreq=40000000.000000;PeakPeriodJitter=250.000000;MinDutyCycle=50.000000;MaxDutyCycle=50.000000;Accuracy=100.000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E{D4DF4CA5-DDD4-4B8D-9402-12BA3A713258}resource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=bool{E5E1CFE7-18DB-4585-9ABB-5E9019AEE5DB}"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO;DataType=1000800000000001000940050002553800000100000000000000;DisableOnOverflowUnderflow=FALSE"{EEA52D7E-DAD8-404D-A78A-B851BEAC08DE}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]cRIO-9074/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_CLASSCRIO_9074FPGA_TARGET_FAMILYSPARTAN3TARGET_TYPEFPGA/[rSeriesConfig.Begin][rSeriesConfig.End]</Property>
				<Property Name="configString.name" Type="Str">40 MHz Onboard ClockResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000.000000;MaxFreq=40000000.000000;VariableFreq=0;NomFreq=40000000.000000;PeakPeriodJitter=250.000000;MinDutyCycle=50.000000;MaxDutyCycle=50.000000;Accuracy=100.000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427EChassis Temperatureresource=/Chassis Temperature;0;ReadMethodType=i16cRIO-9074/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_CLASSCRIO_9074FPGA_TARGET_FAMILYSPARTAN3TARGET_TYPEFPGA/[rSeriesConfig.Begin][rSeriesConfig.End]FPGA LEDresource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=boolMod1[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]Mod2[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]Port1cRIO SubresourcePort1cRIO SubresourcePort2cRIO SubresourcePort2cRIO SubresourcePort3cRIO SubresourcePort3cRIO SubresourcePort4cRIO SubresourcePort4cRIO SubresourceREAD_FIFO"ControlLogic=0;NumberOfElements=1023;Type=2;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;READ_FIFO;DataType=100080000000000100094006000355313600010000000000000000;DisableOnOverflowUnderflow=FALSE"Scan Clockresource=/Scan Clock;0;ReadMethodType=boolSleepresource=/Sleep;0;ReadMethodType=bool;WriteMethodType=boolSystem Resetresource=/System Reset;0;ReadMethodType=bool;WriteMethodType=boolWRITE_FIFO"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO;DataType=1000800000000001000940050002553800000100000000000000;DisableOnOverflowUnderflow=FALSE"WRITE_FIFO2"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO2;DataType=100080000000000100094002000349313600010000000000000000;DisableOnOverflowUnderflow=FALSE"</Property>
				<Property Name="Mode" Type="Int">0</Property>
				<Property Name="NI.LV.FPGA.CLIPDeclarationsArraySize" Type="Int">0</Property>
				<Property Name="NI.LV.FPGA.CLIPDeclarationSet" Type="Xml">
<CLIPDeclarationSet>
</CLIPDeclarationSet></Property>
				<Property Name="NI.LV.FPGA.CompileConfigString" Type="Str">cRIO-9074/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_CLASSCRIO_9074FPGA_TARGET_FAMILYSPARTAN3TARGET_TYPEFPGA</Property>
				<Property Name="NI.LV.FPGA.Version" Type="Int">6</Property>
				<Property Name="NI.SortType" Type="Int">3</Property>
				<Property Name="Resource Name" Type="Str">RIO0</Property>
				<Property Name="SWEmulationSubMode" Type="UInt">0</Property>
				<Property Name="SWEmulationVIPath" Type="Path"></Property>
				<Property Name="Target Class" Type="Str">cRIO-9074</Property>
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
						<Property Name="FPGA.PersistentID" Type="Str">{468DE042-E525-4B8E-8C42-A1E9D5A3ED74}</Property>
					</Item>
					<Item Name="Sleep" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/Sleep</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{26C89342-D1E2-47AD-B82F-FFEBAA3E5728}</Property>
					</Item>
					<Item Name="System Reset" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/System Reset</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{45F5465A-B68B-4169-843C-94C25DE7BF95}</Property>
					</Item>
					<Item Name="FPGA LED" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/FPGA LED</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{D4DF4CA5-DDD4-4B8D-9402-12BA3A713258}</Property>
					</Item>
					<Item Name="Scan Clock" Type="Elemental IO">
						<Property Name="eioAttrBag" Type="Xml"><AttributeSet name="">
   <Attribute name="resource">
   <Value>/Scan Clock</Value>
   </Attribute>
</AttributeSet>
</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{4FCCC9AA-0C18-4F96-96C5-841C274A7D04}</Property>
					</Item>
				</Item>
				<Item Name="FIFOs" Type="Folder">
					<Item Name="READ_FIFO" Type="FPGA FIFO">
						<Property Name="Actual Number of Elements" Type="UInt">1023</Property>
						<Property Name="Arbitration for Read" Type="UInt">1</Property>
						<Property Name="Arbitration for Write" Type="UInt">1</Property>
						<Property Name="Control Logic" Type="UInt">0</Property>
						<Property Name="Data Type" Type="UInt">6</Property>
						<Property Name="Disable on Overflow/Underflow" Type="Bool">false</Property>
						<Property Name="fifo.configuration" Type="Str">"ControlLogic=0;NumberOfElements=1023;Type=2;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;READ_FIFO;DataType=100080000000000100094006000355313600010000000000000000;DisableOnOverflowUnderflow=FALSE"</Property>
						<Property Name="fifo.configured" Type="Bool">true</Property>
						<Property Name="fifo.projectItemValid" Type="Bool">true</Property>
						<Property Name="fifo.valid" Type="Bool">true</Property>
						<Property Name="fifo.version" Type="Int">12</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{918AEB55-7D5E-4F98-8B0D-01D5CB22AB68}</Property>
						<Property Name="Implementation" Type="UInt">2</Property>
						<Property Name="Local" Type="Bool">false</Property>
						<Property Name="Memory Type" Type="UInt">2</Property>
						<Property Name="Number of Elements" Type="UInt">1023</Property>
						<Property Name="Number Of Elements Per Read" Type="UInt">1</Property>
						<Property Name="Number Of Elements Per Write" Type="UInt">1</Property>
						<Property Name="Requested Number of Elements" Type="UInt">1023</Property>
						<Property Name="Type" Type="UInt">2</Property>
						<Property Name="Type Descriptor" Type="Str">100080000000000100094006000355313600010000000000000000</Property>
					</Item>
					<Item Name="WRITE_FIFO" Type="FPGA FIFO">
						<Property Name="Actual Number of Elements" Type="UInt">1029</Property>
						<Property Name="Arbitration for Read" Type="UInt">1</Property>
						<Property Name="Arbitration for Write" Type="UInt">1</Property>
						<Property Name="Control Logic" Type="UInt">0</Property>
						<Property Name="Data Type" Type="UInt">5</Property>
						<Property Name="Disable on Overflow/Underflow" Type="Bool">false</Property>
						<Property Name="fifo.configuration" Type="Str">"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO;DataType=1000800000000001000940050002553800000100000000000000;DisableOnOverflowUnderflow=FALSE"</Property>
						<Property Name="fifo.configured" Type="Bool">true</Property>
						<Property Name="fifo.projectItemValid" Type="Bool">true</Property>
						<Property Name="fifo.valid" Type="Bool">true</Property>
						<Property Name="fifo.version" Type="Int">12</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{E5E1CFE7-18DB-4585-9ABB-5E9019AEE5DB}</Property>
						<Property Name="Implementation" Type="UInt">2</Property>
						<Property Name="Local" Type="Bool">false</Property>
						<Property Name="Memory Type" Type="UInt">2</Property>
						<Property Name="Number of Elements" Type="UInt">1029</Property>
						<Property Name="Number Of Elements Per Read" Type="UInt">1</Property>
						<Property Name="Number Of Elements Per Write" Type="UInt">1</Property>
						<Property Name="Requested Number of Elements" Type="UInt">1029</Property>
						<Property Name="Type" Type="UInt">1</Property>
						<Property Name="Type Descriptor" Type="Str">1000800000000001000940050002553800000100000000000000</Property>
					</Item>
					<Item Name="WRITE_FIFO2" Type="FPGA FIFO">
						<Property Name="Actual Number of Elements" Type="UInt">1029</Property>
						<Property Name="Arbitration for Read" Type="UInt">1</Property>
						<Property Name="Arbitration for Write" Type="UInt">1</Property>
						<Property Name="Control Logic" Type="UInt">0</Property>
						<Property Name="Data Type" Type="UInt">2</Property>
						<Property Name="Disable on Overflow/Underflow" Type="Bool">false</Property>
						<Property Name="fifo.configuration" Type="Str">"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO2;DataType=100080000000000100094002000349313600010000000000000000;DisableOnOverflowUnderflow=FALSE"</Property>
						<Property Name="fifo.configured" Type="Bool">true</Property>
						<Property Name="fifo.projectItemValid" Type="Bool">true</Property>
						<Property Name="fifo.valid" Type="Bool">true</Property>
						<Property Name="fifo.version" Type="Int">12</Property>
						<Property Name="FPGA.PersistentID" Type="Str">{743BC95C-6644-4BD1-A235-D7E6BE3837D4}</Property>
						<Property Name="Local" Type="Bool">false</Property>
						<Property Name="Memory Type" Type="UInt">2</Property>
						<Property Name="Number Of Elements Per Read" Type="UInt">1</Property>
						<Property Name="Number Of Elements Per Write" Type="UInt">1</Property>
						<Property Name="Requested Number of Elements" Type="UInt">1023</Property>
						<Property Name="Type" Type="UInt">1</Property>
						<Property Name="Type Descriptor" Type="Str">100080000000000100094002000349313600010000000000000000</Property>
					</Item>
				</Item>
				<Item Name="Mod1" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 1</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9870</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.kBaudRateDivider1" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRateDivider2" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRateDivider3" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRateDivider4" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler1" Type="Str">1</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler2" Type="Str">1</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler3" Type="Str">1</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler4" Type="Str">1</Property>
					<Property Name="cRIOModule.kDataBits1" Type="Str">4</Property>
					<Property Name="cRIOModule.kDataBits2" Type="Str">4</Property>
					<Property Name="cRIOModule.kDataBits3" Type="Str">4</Property>
					<Property Name="cRIOModule.kDataBits4" Type="Str">4</Property>
					<Property Name="cRIOModule.kDesiredBaudRate1" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kDesiredBaudRate2" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kDesiredBaudRate3" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kDesiredBaudRate4" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kFlowControl1" Type="Str">1</Property>
					<Property Name="cRIOModule.kFlowControl2" Type="Str">1</Property>
					<Property Name="cRIOModule.kFlowControl3" Type="Str">1</Property>
					<Property Name="cRIOModule.kFlowControl4" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity1" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity2" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity3" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity4" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits1" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits2" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits3" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits4" Type="Str">1</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{8B9C92D0-4838-4ECC-9E6A-2B222316EE3A}</Property>
					<Item Name="Port1" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{21A573A4-B3FF-4A21-9CE0-20B9DA934000}</Property>
					</Item>
					<Item Name="Port2" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{909712D0-5835-4EA1-B20E-33DF69902EB1}</Property>
					</Item>
					<Item Name="Port3" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{B95C7D0C-6493-4EFE-AFB7-129030FBB87B}</Property>
					</Item>
					<Item Name="Port4" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{C9EDF5F9-1079-48F7-AECB-41CEA0C12AF0}</Property>
					</Item>
				</Item>
				<Item Name="Mod2" Type="RIO C Series Module">
					<Property Name="crio.Calibration" Type="Str">1</Property>
					<Property Name="crio.Location" Type="Str">Slot 2</Property>
					<Property Name="crio.RequiresValidation" Type="Bool">false</Property>
					<Property Name="crio.SupportsDynamicRes" Type="Bool">false</Property>
					<Property Name="crio.Type" Type="Str">NI 9870</Property>
					<Property Name="cRIOModule.EnableSpecialtyDigital" Type="Str">false</Property>
					<Property Name="cRIOModule.kBaudRateDivider1" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRateDivider2" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRateDivider3" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRateDivider4" Type="Str">384</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler1" Type="Str">1</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler2" Type="Str">1</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler3" Type="Str">1</Property>
					<Property Name="cRIOModule.kBaudRatePrescaler4" Type="Str">1</Property>
					<Property Name="cRIOModule.kDataBits1" Type="Str">4</Property>
					<Property Name="cRIOModule.kDataBits2" Type="Str">4</Property>
					<Property Name="cRIOModule.kDataBits3" Type="Str">4</Property>
					<Property Name="cRIOModule.kDataBits4" Type="Str">4</Property>
					<Property Name="cRIOModule.kDesiredBaudRate1" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kDesiredBaudRate2" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kDesiredBaudRate3" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kDesiredBaudRate4" Type="Str">9.600000E+3</Property>
					<Property Name="cRIOModule.kFlowControl1" Type="Str">1</Property>
					<Property Name="cRIOModule.kFlowControl2" Type="Str">1</Property>
					<Property Name="cRIOModule.kFlowControl3" Type="Str">1</Property>
					<Property Name="cRIOModule.kFlowControl4" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity1" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity2" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity3" Type="Str">1</Property>
					<Property Name="cRIOModule.kParity4" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits1" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits2" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits3" Type="Str">1</Property>
					<Property Name="cRIOModule.kStopBits4" Type="Str">1</Property>
					<Property Name="FPGA.PersistentID" Type="Str">{EEA52D7E-DAD8-404D-A78A-B851BEAC08DE}</Property>
					<Item Name="Port1" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{B10FA560-6703-445D-ABF9-33ADCCF9D75B}</Property>
					</Item>
					<Item Name="Port2" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{CE2FA74D-47CB-4D74-8132-4402E34E5874}</Property>
					</Item>
					<Item Name="Port3" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{BACA50B1-8EA7-4B30-A13A-56BA162CA038}</Property>
					</Item>
					<Item Name="Port4" Type="RIO Subresource">
						<Property Name="FPGA.PersistentID" Type="Str">{6E89E5B2-1F22-4FBB-8A06-0B44A20B6066}</Property>
					</Item>
				</Item>
				<Item Name="Serial Port Parameters.ctl" Type="VI" URL="../cRIO/FPGA/Serial Port Parameters.ctl">
					<Property Name="configString.guid" Type="Str">{21A573A4-B3FF-4A21-9CE0-20B9DA934000}cRIO Subresource{26C89342-D1E2-47AD-B82F-FFEBAA3E5728}resource=/Sleep;0;ReadMethodType=bool;WriteMethodType=bool{45F5465A-B68B-4169-843C-94C25DE7BF95}resource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool{468DE042-E525-4B8E-8C42-A1E9D5A3ED74}resource=/Chassis Temperature;0;ReadMethodType=i16{4FCCC9AA-0C18-4F96-96C5-841C274A7D04}resource=/Scan Clock;0;ReadMethodType=bool{6E89E5B2-1F22-4FBB-8A06-0B44A20B6066}cRIO Subresource{743BC95C-6644-4BD1-A235-D7E6BE3837D4}"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO2;DataType=100080000000000100094002000349313600010000000000000000;DisableOnOverflowUnderflow=FALSE"{8B9C92D0-4838-4ECC-9E6A-2B222316EE3A}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]{909712D0-5835-4EA1-B20E-33DF69902EB1}cRIO Subresource{918AEB55-7D5E-4F98-8B0D-01D5CB22AB68}"ControlLogic=0;NumberOfElements=1023;Type=2;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;READ_FIFO;DataType=100080000000000100094006000355313600010000000000000000;DisableOnOverflowUnderflow=FALSE"{B10FA560-6703-445D-ABF9-33ADCCF9D75B}cRIO Subresource{B95C7D0C-6493-4EFE-AFB7-129030FBB87B}cRIO Subresource{BACA50B1-8EA7-4B30-A13A-56BA162CA038}cRIO Subresource{C9EDF5F9-1079-48F7-AECB-41CEA0C12AF0}cRIO Subresource{CE2FA74D-47CB-4D74-8132-4402E34E5874}cRIO Subresource{D22172DE-BD44-42DF-A9DF-90D112D4363B}ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000.000000;MaxFreq=40000000.000000;VariableFreq=0;NomFreq=40000000.000000;PeakPeriodJitter=250.000000;MinDutyCycle=50.000000;MaxDutyCycle=50.000000;Accuracy=100.000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E{D4DF4CA5-DDD4-4B8D-9402-12BA3A713258}resource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=bool{E5E1CFE7-18DB-4585-9ABB-5E9019AEE5DB}"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO;DataType=1000800000000001000940050002553800000100000000000000;DisableOnOverflowUnderflow=FALSE"{EEA52D7E-DAD8-404D-A78A-B851BEAC08DE}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]cRIO-9074/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_CLASSCRIO_9074FPGA_TARGET_FAMILYSPARTAN3TARGET_TYPEFPGA/[rSeriesConfig.Begin][rSeriesConfig.End]</Property>
					<Property Name="configString.name" Type="Str">40 MHz Onboard ClockResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000.000000;MaxFreq=40000000.000000;VariableFreq=0;NomFreq=40000000.000000;PeakPeriodJitter=250.000000;MinDutyCycle=50.000000;MaxDutyCycle=50.000000;Accuracy=100.000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427EChassis Temperatureresource=/Chassis Temperature;0;ReadMethodType=i16cRIO-9074/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_CLASSCRIO_9074FPGA_TARGET_FAMILYSPARTAN3TARGET_TYPEFPGA/[rSeriesConfig.Begin][rSeriesConfig.End]FPGA LEDresource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=boolMod1[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]Mod2[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]Port1cRIO SubresourcePort1cRIO SubresourcePort2cRIO SubresourcePort2cRIO SubresourcePort3cRIO SubresourcePort3cRIO SubresourcePort4cRIO SubresourcePort4cRIO SubresourceREAD_FIFO"ControlLogic=0;NumberOfElements=1023;Type=2;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;READ_FIFO;DataType=100080000000000100094006000355313600010000000000000000;DisableOnOverflowUnderflow=FALSE"Scan Clockresource=/Scan Clock;0;ReadMethodType=boolSleepresource=/Sleep;0;ReadMethodType=bool;WriteMethodType=boolSystem Resetresource=/System Reset;0;ReadMethodType=bool;WriteMethodType=boolWRITE_FIFO"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO;DataType=1000800000000001000940050002553800000100000000000000;DisableOnOverflowUnderflow=FALSE"WRITE_FIFO2"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO2;DataType=100080000000000100094002000349313600010000000000000000;DisableOnOverflowUnderflow=FALSE"</Property>
				</Item>
				<Item Name="9870 Interface DMA (FPGA).vi" Type="VI" URL="../cRIO/FPGA/9870 Interface DMA (FPGA).vi">
					<Property Name="BuildSpec" Type="Str">{E54143C6-9291-404E-AF1E-F98D643D06A8}</Property>
					<Property Name="configString.guid" Type="Str">{21A573A4-B3FF-4A21-9CE0-20B9DA934000}cRIO Subresource{26C89342-D1E2-47AD-B82F-FFEBAA3E5728}resource=/Sleep;0;ReadMethodType=bool;WriteMethodType=bool{45F5465A-B68B-4169-843C-94C25DE7BF95}resource=/System Reset;0;ReadMethodType=bool;WriteMethodType=bool{468DE042-E525-4B8E-8C42-A1E9D5A3ED74}resource=/Chassis Temperature;0;ReadMethodType=i16{4FCCC9AA-0C18-4F96-96C5-841C274A7D04}resource=/Scan Clock;0;ReadMethodType=bool{6E89E5B2-1F22-4FBB-8A06-0B44A20B6066}cRIO Subresource{743BC95C-6644-4BD1-A235-D7E6BE3837D4}"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO2;DataType=100080000000000100094002000349313600010000000000000000;DisableOnOverflowUnderflow=FALSE"{8B9C92D0-4838-4ECC-9E6A-2B222316EE3A}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]{909712D0-5835-4EA1-B20E-33DF69902EB1}cRIO Subresource{918AEB55-7D5E-4F98-8B0D-01D5CB22AB68}"ControlLogic=0;NumberOfElements=1023;Type=2;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;READ_FIFO;DataType=100080000000000100094006000355313600010000000000000000;DisableOnOverflowUnderflow=FALSE"{B10FA560-6703-445D-ABF9-33ADCCF9D75B}cRIO Subresource{B95C7D0C-6493-4EFE-AFB7-129030FBB87B}cRIO Subresource{BACA50B1-8EA7-4B30-A13A-56BA162CA038}cRIO Subresource{C9EDF5F9-1079-48F7-AECB-41CEA0C12AF0}cRIO Subresource{CE2FA74D-47CB-4D74-8132-4402E34E5874}cRIO Subresource{D22172DE-BD44-42DF-A9DF-90D112D4363B}ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000.000000;MaxFreq=40000000.000000;VariableFreq=0;NomFreq=40000000.000000;PeakPeriodJitter=250.000000;MinDutyCycle=50.000000;MaxDutyCycle=50.000000;Accuracy=100.000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E{D4DF4CA5-DDD4-4B8D-9402-12BA3A713258}resource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=bool{E5E1CFE7-18DB-4585-9ABB-5E9019AEE5DB}"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO;DataType=1000800000000001000940050002553800000100000000000000;DisableOnOverflowUnderflow=FALSE"{EEA52D7E-DAD8-404D-A78A-B851BEAC08DE}[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]cRIO-9074/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_CLASSCRIO_9074FPGA_TARGET_FAMILYSPARTAN3TARGET_TYPEFPGA/[rSeriesConfig.Begin][rSeriesConfig.End]</Property>
					<Property Name="configString.name" Type="Str">40 MHz Onboard ClockResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000.000000;MaxFreq=40000000.000000;VariableFreq=0;NomFreq=40000000.000000;PeakPeriodJitter=250.000000;MinDutyCycle=50.000000;MaxDutyCycle=50.000000;Accuracy=100.000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427EChassis Temperatureresource=/Chassis Temperature;0;ReadMethodType=i16cRIO-9074/Clk40/falsefalseFPGA_EXECUTION_MODEFPGA_TARGETFPGA_TARGET_CLASSCRIO_9074FPGA_TARGET_FAMILYSPARTAN3TARGET_TYPEFPGA/[rSeriesConfig.Begin][rSeriesConfig.End]FPGA LEDresource=/FPGA LED;0;ReadMethodType=bool;WriteMethodType=boolMod1[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 1,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]Mod2[crioConfig.Begin]crio.Calibration=1,crio.Location=Slot 2,crio.Type=NI 9870,cRIOModule.EnableDECoM=false,cRIOModule.EnableInputFifo=false,cRIOModule.EnableOutputFifo=false,cRIOModule.kBaudRateDivider1=384,cRIOModule.kBaudRateDivider2=384,cRIOModule.kBaudRateDivider3=384,cRIOModule.kBaudRateDivider4=384,cRIOModule.kBaudRatePrescaler1=1,cRIOModule.kBaudRatePrescaler2=1,cRIOModule.kBaudRatePrescaler3=1,cRIOModule.kBaudRatePrescaler4=1,cRIOModule.kDataBits1=4,cRIOModule.kDataBits2=4,cRIOModule.kDataBits3=4,cRIOModule.kDataBits4=4,cRIOModule.kDesiredBaudRate1=9.600000E+3,cRIOModule.kDesiredBaudRate2=9.600000E+3,cRIOModule.kDesiredBaudRate3=9.600000E+3,cRIOModule.kDesiredBaudRate4=9.600000E+3,cRIOModule.kFlowControl1=1,cRIOModule.kFlowControl2=1,cRIOModule.kFlowControl3=1,cRIOModule.kFlowControl4=1,cRIOModule.kParity1=1,cRIOModule.kParity2=1,cRIOModule.kParity3=1,cRIOModule.kParity4=1,cRIOModule.kStopBits1=1,cRIOModule.kStopBits2=1,cRIOModule.kStopBits3=1,cRIOModule.kStopBits4=1,cRIOModule.RsiAttributes=[crioConfig.End]Port1cRIO SubresourcePort1cRIO SubresourcePort2cRIO SubresourcePort2cRIO SubresourcePort3cRIO SubresourcePort3cRIO SubresourcePort4cRIO SubresourcePort4cRIO SubresourceREAD_FIFO"ControlLogic=0;NumberOfElements=1023;Type=2;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;READ_FIFO;DataType=100080000000000100094006000355313600010000000000000000;DisableOnOverflowUnderflow=FALSE"Scan Clockresource=/Scan Clock;0;ReadMethodType=boolSleepresource=/Sleep;0;ReadMethodType=bool;WriteMethodType=boolSystem Resetresource=/System Reset;0;ReadMethodType=bool;WriteMethodType=boolWRITE_FIFO"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO;DataType=1000800000000001000940050002553800000100000000000000;DisableOnOverflowUnderflow=FALSE"WRITE_FIFO2"ControlLogic=0;NumberOfElements=1029;Type=1;ReadArbs=Arbitrate if Multiple Requestors Only;ElementsPerRead=1;WriteArbs=Arbitrate if Multiple Requestors Only;ElementsPerWrite=1;Implementation=2;WRITE_FIFO2;DataType=100080000000000100094002000349313600010000000000000000;DisableOnOverflowUnderflow=FALSE"</Property>
					<Property Name="NI.LV.FPGA.InterfaceBitfile" Type="Str">C:\Users\candelor\Documents\PhDwork\Control System WORK\Gunnerus Trials\FPGA Bitfiles\MinervaControlSy_FPGATarget_9870InterfaceDMA_4D1233B8.lvbitx</Property>
				</Item>
				<Item Name="40 MHz Onboard Clock" Type="FPGA Base Clock">
					<Property Name="FPGA.PersistentID" Type="Str">{D22172DE-BD44-42DF-A9DF-90D112D4363B}</Property>
					<Property Name="NI.LV.FPGA.BaseTSConfig" Type="Str">ResourceName=40 MHz Onboard Clock;TopSignalConnect=Clk40;ClockSignalName=Clk40;MinFreq=40000000.000000;MaxFreq=40000000.000000;VariableFreq=0;NomFreq=40000000.000000;PeakPeriodJitter=250.000000;MinDutyCycle=50.000000;MaxDutyCycle=50.000000;Accuracy=100.000000;RunTime=0;SpreadSpectrum=0;GenericDataHash=D41D8CD98F00B204E9800998ECF8427E</Property>
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
					<Property Name="NI.LV.FPGA.Version" Type="Int">5</Property>
				</Item>
				<Item Name="Dependencies" Type="Dependencies">
					<Item Name="vi.lib" Type="Folder">
						<Item Name="lvSimController.dll" Type="Document" URL="/&lt;vilib&gt;/rvi/Simulation/lvSimController.dll"/>
					</Item>
				</Item>
				<Item Name="Build Specifications" Type="Build">
					<Item Name="9870 Interface DMA (FPGA)" Type="{F4C5E96F-7410-48A5-BB87-3559BC9B167F}">
						<Property Name="AllowEnableRemoval" Type="Bool">false</Property>
						<Property Name="BuildSpecDecription" Type="Str"></Property>
						<Property Name="BuildSpecName" Type="Str">9870 Interface DMA (FPGA)</Property>
						<Property Name="Comp.BitfileName" Type="Str">MinervaControlSy_FPGATarget_9870InterfaceDMA_4D1233B8.lvbitx</Property>
						<Property Name="Comp.CustomXilinxParameters" Type="Str"></Property>
						<Property Name="Comp.MaxFanout" Type="Int">-1</Property>
						<Property Name="Comp.RandomSeed" Type="Bool">false</Property>
						<Property Name="Comp.RunWhenLoaded" Type="Bool">false</Property>
						<Property Name="Comp.Version.Build" Type="Int">0</Property>
						<Property Name="Comp.Version.Fix" Type="Int">0</Property>
						<Property Name="Comp.Version.Major" Type="Int">1</Property>
						<Property Name="Comp.Version.Minor" Type="Int">0</Property>
						<Property Name="Comp.VersionAutoIncrement" Type="Bool">false</Property>
						<Property Name="Comp.Vivado.EnableMultiThreading" Type="Bool">true</Property>
						<Property Name="Comp.Vivado.OptDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.PhysOptDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.PlaceDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.RouteDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.RunPowerOpt" Type="Bool">false</Property>
						<Property Name="Comp.Vivado.Strategy" Type="Str">Default</Property>
						<Property Name="Comp.Xilinx.DesignStrategy" Type="Str">balanced</Property>
						<Property Name="Comp.Xilinx.MapEffort" Type="Str">default(noTiming)</Property>
						<Property Name="Comp.Xilinx.ParEffort" Type="Str">standard</Property>
						<Property Name="Comp.Xilinx.SynthEffort" Type="Str">normal</Property>
						<Property Name="Comp.Xilinx.SynthGoal" Type="Str">speed</Property>
						<Property Name="Comp.Xilinx.UseRecommended" Type="Bool">true</Property>
						<Property Name="DefaultBuildSpec" Type="Bool">true</Property>
						<Property Name="DestinationDirectory" Type="Path">FPGA Bitfiles</Property>
						<Property Name="NI.LV.FPGA.LastCompiledBitfilePath" Type="Path">/C/Users/candelor/Documents/PhDwork/Control System WORK/Gunnerus Trials/FPGA Bitfiles/MinervaControlSy_FPGATarget_9870InterfaceDMA_4D1233B8.lvbitx</Property>
						<Property Name="NI.LV.FPGA.LastCompiledBitfilePathRelativeToProject" Type="Path">FPGA Bitfiles/MinervaControlSy_FPGATarget_9870InterfaceDMA_4D1233B8.lvbitx</Property>
						<Property Name="ProjectPath" Type="Path">/C/AUR-LAB/ROV control system/AURLab ROV Control System.lvproj</Property>
						<Property Name="RelativePath" Type="Bool">true</Property>
						<Property Name="RunWhenLoaded" Type="Bool">false</Property>
						<Property Name="SupportDownload" Type="Bool">true</Property>
						<Property Name="SupportResourceEstimation" Type="Bool">true</Property>
						<Property Name="TargetName" Type="Str">FPGA Target</Property>
						<Property Name="TopLevelVI" Type="Ref">/AURLcRIO/Chassis/FPGA Target/9870 Interface DMA (FPGA).vi</Property>
					</Item>
					<Item Name="Serial Port Parameters" Type="{F4C5E96F-7410-48A5-BB87-3559BC9B167F}">
						<Property Name="AllowEnableRemoval" Type="Bool">false</Property>
						<Property Name="BuildSpecDecription" Type="Str"></Property>
						<Property Name="BuildSpecName" Type="Str">Serial Port Parameters</Property>
						<Property Name="Comp.BitfileName" Type="Str">HILtest_FPGATarget_SerialPortParame_553CBBA8.lvbitx</Property>
						<Property Name="Comp.CustomXilinxParameters" Type="Str"></Property>
						<Property Name="Comp.MaxFanout" Type="Int">-1</Property>
						<Property Name="Comp.RandomSeed" Type="Bool">false</Property>
						<Property Name="Comp.RunWhenLoaded" Type="Bool">false</Property>
						<Property Name="Comp.Version.Build" Type="Int">0</Property>
						<Property Name="Comp.Version.Fix" Type="Int">0</Property>
						<Property Name="Comp.Version.Major" Type="Int">1</Property>
						<Property Name="Comp.Version.Minor" Type="Int">0</Property>
						<Property Name="Comp.VersionAutoIncrement" Type="Bool">false</Property>
						<Property Name="Comp.Vivado.EnableMultiThreading" Type="Bool">true</Property>
						<Property Name="Comp.Vivado.OptDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.PhysOptDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.PlaceDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.RouteDirective" Type="Str">Default</Property>
						<Property Name="Comp.Vivado.RunPowerOpt" Type="Bool">false</Property>
						<Property Name="Comp.Vivado.Strategy" Type="Str">Default</Property>
						<Property Name="Comp.Xilinx.DesignStrategy" Type="Str">balanced</Property>
						<Property Name="Comp.Xilinx.MapEffort" Type="Str">default(noTiming)</Property>
						<Property Name="Comp.Xilinx.ParEffort" Type="Str">standard</Property>
						<Property Name="Comp.Xilinx.SynthEffort" Type="Str">normal</Property>
						<Property Name="Comp.Xilinx.SynthGoal" Type="Str">speed</Property>
						<Property Name="Comp.Xilinx.UseRecommended" Type="Bool">true</Property>
						<Property Name="DefaultBuildSpec" Type="Bool">true</Property>
						<Property Name="DestinationDirectory" Type="Path">FPGA Bitfiles</Property>
						<Property Name="ProjectPath" Type="Path">/C/AUR-LAB/ROV control system/AURLab ROV Control System.lvproj</Property>
						<Property Name="RelativePath" Type="Bool">true</Property>
						<Property Name="RunWhenLoaded" Type="Bool">false</Property>
						<Property Name="SupportDownload" Type="Bool">true</Property>
						<Property Name="SupportResourceEstimation" Type="Bool">true</Property>
						<Property Name="TargetName" Type="Str">FPGA Target</Property>
						<Property Name="TopLevelVI" Type="Ref"></Property>
					</Item>
				</Item>
			</Item>
		</Item>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
