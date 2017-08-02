function [Sim] = Config_UltraStick25e(Sim)
% Configures the Aircraft (UltraStick25e) for the Simulation.
%
%Usage:  [Sim] = Config_UltraStick25e(Sim);
%
%Inputs:
% Sim      - Simulation Configuration Structure []
%
%Outputs:
% Sim      - Simulation Configuration Structure
%
%Notes:
% 

% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.


%% Check I/O Arguments
narginchk(0, 1);
if nargin < 1
    Sim = [];
end
 
nargoutchk(0, 1);

%% Default Values and Constants
if isempty(Sim), Sim = []; end


%% Configuration of Core Sim Subsystems
[Sim.MassP] = Config_MassP(Sim.MassP); % Mass Properties
[Sim.Aero] = Config_Aero(Sim.Aero); % Aerodynamic
[Sim.Prop] = Config_Prop(Sim.Prop); % Propulsion


%% Effectors
% Control Surfaces (Servo and Linkage)
Sim.Surf = Config_Surf(Sim.Surf);

% Propulaion Motors
[Sim.Motor] = Config_Motor(Sim.Motor);

% Effectors bus
busNames = {'BusMotor', 'BusServo', 'BusSurf'};
busDataType = {'Bus: BusMotor', 'Bus: BusServo', 'Bus: BusSurf'};
Sim.BusEff = CreateBus(busNames, busDataType);

assignin('base', 'BusEff', Sim.BusEff);

%% Configure Sensor Models
[Sim.IMU] = Config_IMU(Sim.IMU);
[Sim.Pitot] = Config_Pitot(Sim.Pitot);
[Sim.GPS] = Config_GPS(Sim.GPS);

% Sensors bus
busNames = {'BusIMU', 'BusGPS', 'BusPitot'};
busDataType = {'Bus: BusIMU', 'Bus: BusGPS', 'Bus: BusPitot'};
Sim.BusSens = CreateBus(busNames, busDataType);

assignin('base', 'BusSens', Sim.BusSens);

%% Define Buses
% Bus Definitions need to be the base workspace for the Simulation

% Pilot Commands
% Sim.Pilot.elemNames = {'pltThrot_nd', 'pltRoll_nd', 'pltPitch_nd', 'pltYaw_nd', 'pltMode_nd'};
% Sim.Pilot.BusPilot = CreateBus(Sim.Pilot.elemNames);
% assignin('base', 'BusPilot', Sim.Pilot.BusPilot);

% Commands bus
Sim.Cmd.elemNames = ['throttle_nd', Sim.Surf.elemNames];
Sim.Cmd.BusCmd = CreateBus(Sim.Cmd.elemNames);
assignin('base', 'BusCmd', Sim.Cmd.BusCmd);

% Refs bus
% Sim.Guid.elemNames = {'lat_D_deg', 'long_D_deg'};
% Sim.Guid.BusGuid = CreateBus(Sim.Guid.elemNames);
% assignin('base', 'BusGuid', Sim.Guid.BusGuid);

