function Aero = Param_Aero_UltraStick120(Sim, T_S2SB)
% Remarks:
% ALL stability derivative units are radians.
% Forces are defined in the Wind frame, Moments in the Body frame

switch lower(Sim.type)
    case {'avl', 'avl_v1'}
        % Aero = Param_Aero_UltraStick120_AVL_v1();
    case {'faser'}
        Aero = Param_Aero_UltraStick120_FASER_v1(); % Established Aero PID derived from flight data with FASER using Goldy 1.
    otherwise
        
end

% Transform S frame to SB frame
Aero.rAero_SB_m = T_S2SB * Aero.rAero_S_m;

end

function Aero = Param_Aero_UltraStick120_FASER_v1()
%% Geometric Parameters
% Aerodynamic center is Origin of the Aero Frame (force application point)
Aero.rAero_S_m = [0.32; 0.0; 0.072]; % approximate AMM 10/29/11
Aero.T_Aero2W = [-1, 0, 0; 0, 1, 0; 0, 0, -1]; % Rotation Transform from Aero Frame to Wind Frame

% Mean aerodynamic chord [m]
Aero.c = 0.433578; % 0.4279 m (calculated MAC)

% Wing span [m]
Aero.b = 1.917192; % 1.92 m aft max

% Wing area [m^2]
Aero.S = 0.769237171; %.7732 from measurements

% Wing Aspect Ratio [m^2]
Aero.AR = Aero.b^2 / Aero.S;

%% Aero Model Coefficients
Aero = load('UltraStick120_Aero');
Aero.asymOn = 1; % set to 1 to turn on asymmetric aero model.

end

