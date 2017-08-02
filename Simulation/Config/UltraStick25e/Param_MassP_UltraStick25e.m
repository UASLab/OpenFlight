function MassP = Param_MassP_UltraStick25e(Sim, T_S2SB)


% Load the Reference Mass Properties
switch lower(Sim.type)
    case {'avl'}
        MassP = Param_MassP_UltraStick25e_avl_v1(Sim);
    case {'flight', 'old'}
        MassP = Param_MassP_UltraStick25e_flight_v1(Sim); % Test derived mass properties
    otherwise
        
end

% Compute the Specific Mass Properties
% Current Mass
if ~isfield(MassP, 'mass_kg')
    MassP.mass_kg = MassP.massRef_kg;
end

% Current CG location
if ~isfield(MassP, 'rCG_S_m')
    MassP.rCG_S_m = MassP.rCGRef_S_m;
end
MassP.rCG_SB_m = T_S2SB * MassP.rCG_S_m;

% Current Aircraft Inertia, B-frame
MassP.rCGRef_SB_m = T_S2SB * MassP.rCGRef_S_m;
MassP.rCGRef_B_m = MassP.rCG_SB_m - MassP.rCGRef_SB_m; % CG is origin of B frame, pos vector from CG to Ref frame
MassP.I_B_kgm2 = ...
    MassP.IRef_B_kgm2 + MassP.mass_kg * (dot(-MassP.rCGRef_B_m, -MassP.rCGRef_B_m)*eye(3) - (-MassP.rCGRef_B_m)*(-MassP.rCGRef_B_m)'); % I_CG = I_Ref + m(dot(r, r)*I + (r*r'), where r is from Ref to CG

end

function MassP = Param_MassP_UltraStick25e_flight_v1(MassP)
% Gross aircraft mass [kg]
switch lower(MassP.model)
    case 'loki'
        MassP.massRef_kg  = 1.9; % Loki
    case 'thor'
        MassP.massRef_kg  = 1.959; % Thor
    case 'frigg'
        MassP.massRef_kg  = 1.865; % Frigg
end

% CG location [x y z], [m]
MassP.rCGRef_S_m = [0.222; 0; 0.046];

% Refernece Moments of Inertia [kg*m^2]
MassP.IxxRef_B_kgm2 = 0.07151;
MassP.IyyRef_B_kgm2 = 0.08636;
MassP.IzzRef_B_kgm2 = 0.15364;

MassP.IxyRef_B_kgm2 = 0.0;
MassP.IxzRef_B_kgm2 = 0.014;
MassP.IyzRef_B_kgm2 = 0.0;

MassP.IRef_B_kgm2 = [MassP.IxxRef_B_kgm2, -MassP.IxyRef_B_kgm2, -MassP.IxzRef_B_kgm2;
    -MassP.IxyRef_B_kgm2, MassP.IyyRef_B_kgm2, -MassP.IyzRef_B_kgm2;
    -MassP.IxzRef_B_kgm2, -MassP.IyzRef_B_kgm2, MassP.IzzRef_B_kgm2];
end


function MassP = Param_MassP_UltraStick25e_avl_v1(MassP)
% Gross aircraft mass [kg]
MassP.massRef_kg = 1.793; % AVL Model
MassP.gravRef_mps2 = 9.81;

% CG location [x y z], [m]
MassP.rCGRef_S_m = [0.2223; 0; 0.02713];

% Refernece Moments of Inertia [kg*m^2]
MassP.IxxRef_B_kgm2 = 0.04382;
MassP.IyyRef_B_kgm2 = 0.08373;
MassP.IzzRef_B_kgm2 = 0.1193;

MassP.IxyRef_B_kgm2 = 0;
MassP.IxzRef_B_kgm2 = 0.00048;
MassP.IyzRef_B_kgm2 = 0;

MassP.IRef_B_kgm2 = [MassP.IxxRef_B_kgm2, -MassP.IxyRef_B_kgm2, -MassP.IxzRef_B_kgm2;
    -MassP.IxyRef_B_kgm2, MassP.IyyRef_B_kgm2, -MassP.IyzRef_B_kgm2;
    -MassP.IxzRef_B_kgm2, -MassP.IyzRef_B_kgm2, MassP.IzzRef_B_kgm2];
end