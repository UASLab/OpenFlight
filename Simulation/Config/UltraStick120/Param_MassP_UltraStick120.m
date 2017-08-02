function MassP = Param_MassP_UltraStick120(Sim, T_S2SB)


% Load the Reference Mass Properties
switch lower(Sim.type)
    case {'avl'}
        MassP = Param_MassP_UltraStick120_avl_v1(Sim);
    case {'flight', 'old'}
        MassP = Param_MassP_UltraStick120_flight_v1(Sim); % Test derived mass properties
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

function MassP = Param_MassP_UltraStick120_flight_v1(MassP)
% Gross aircraft mass [kg]
MassP.massRef_kg  = 7.411; % AMM 10/29/11

% CG location [x y z], [m]
MassP.rCGRef_S_m = [0.315; 0.0; 0.072];

% Refernece Moments of Inertia [kg*m^2]
% AC.Inertia.Ixx = 0.672485702; 
% AC.Inertia.Iyy = 0.889416574; 
% AC.Inertia.Izz = 1.57817209;  
MassP.IxxRef_B_kgm2 = 0.8568; % 10/29/11
MassP.IyyRef_B_kgm2 = 1.0095; % 10/29/11
MassP.IzzRef_B_kgm2 = 1.7005; % 10/29/11

MassP.IxyRef_B_kgm2 = 0.0;
MassP.IxzRef_B_kgm2 = -0.759258051/4; % reduced to match flight data AMM 9/14/11
MassP.IyzRef_B_kgm2 = 0.0;

MassP.IRef_B_kgm2 = [MassP.IxxRef_B_kgm2, -MassP.IxyRef_B_kgm2, -MassP.IxzRef_B_kgm2;
    -MassP.IxyRef_B_kgm2, MassP.IyyRef_B_kgm2, -MassP.IyzRef_B_kgm2;
    -MassP.IxzRef_B_kgm2, -MassP.IyzRef_B_kgm2, MassP.IzzRef_B_kgm2];
end


function MassP = Param_MassP_UltraStick120_avl_v1(MassP)
% Gross aircraft mass [kg]
MassP.massRef_kg = NaN; % AVL Model
MassP.gravRef_mps2 = NaN;

% CG location [x y z], [m]
MassP.rCGRef_S_m = [NaN; 0; NaN];

% Refernece Moments of Inertia [kg*m^2]
MassP.IxxRef_B_kgm2 = NaN;
MassP.IyyRef_B_kgm2 = NaN;
MassP.IzzRef_B_kgm2 = NaN;

MassP.IxyRef_B_kgm2 = 0;
MassP.IxzRef_B_kgm2 = NaN;
MassP.IyzRef_B_kgm2 = 0;

MassP.IRef_B_kgm2 = [MassP.IxxRef_B_kgm2, -MassP.IxyRef_B_kgm2, -MassP.IxzRef_B_kgm2;
    -MassP.IxyRef_B_kgm2, MassP.IyyRef_B_kgm2, -MassP.IyzRef_B_kgm2;
    -MassP.IxzRef_B_kgm2, -MassP.IyzRef_B_kgm2, MassP.IzzRef_B_kgm2];
end