function [Prop] = Param_Prop(Sim, Prop)

% Constants
in2m = 0.0254;

%% Propulsion Data
switch lower(Sim.propType)
    case lower('apc_12x6e') % APC 12 x 6E propeller
        % EFlite Power 25, AEM wind tunnel test data Jan 2011
        % Castle Creations ICE Lite 50 used to collect motor data
        
        % Propeller radius %[m]
        Prop.radius_m = 12 / 2 * in2m;
        
        % Coefficient of Thrust, polynomial coefficients, advance ratio input
        Prop.CT = [-0.4314 1.08 -0.896 0.1089 0.0604 ];
        
        % Coefficient of Power, polynomial coefficients, advance ratio input
        Prop.CP = [0.5054 -0.5304 0.0412 0.01664 0.0223];
        
        % Electric motor and propeller combine moment of inertia
        Prop.Jmp_kgm2 = 0.00012991; % experimental measurement (not updated with Jan 2011 data)
        
    case lower('apc_14x9.5') % 14 x 9.5 prop on FASER 
        
        % Propeller diameter %[m]
        Prop.radius_m = 0.1778;

        % Coefficient of Thrust, polynomial coefficients, advance ratio input
        Prop.CT = [-0.4314 1.08 -0.896 0.1089 0.0604 ]; % FIXIT - Check source

        % Coefficient of Power, polynomial coefficients, advance ratio input
        Prop.CP = [0.5054 -0.5304 0.0412 0.01664 0.0223]; % FIXIT - Check source

        % Electric motor and propeller combine moment of inertia
        Prop.Jmp_kgm2 = 0.00041935; % estimated, AMM 9/12/11
        
    otherwise % Prop not defined
        error()
end


%% Limits, populate with generic values as placeholder
% Spin Direction
Prop.spinDir_nd = 1; % 1 - Normal, Positive about Body x-axis; -1 - Reversed

