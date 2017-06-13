function [Def, Surf] = ParamDef_Surf(Def, Surf)
% Define the Control Surface Model Parameters

hz2rps = 2*pi;
d2r = pi/180;
%

%% Servo Model Parameters
switch lower(Def.servoType)
    case lower({'Hitec_HS-225BB', '225BB'}) % HiTec HS-225BB
        
        Surf.servoBw_rps = 8.0 * hz2rps; % FIXIT - Guess
        Surf.servoDamp_nd = 1.0; % FIXIT - Guess
        Surf.servoRateLim_rps = 150 * d2r; % FIXIT - Guess
        Surf.servoPosLim_rad = 90 * d2r; % FIXIT - Guess
        Surf.servoNegLim_rad = -90 * d2r; % FIXIT - Guess
        
        Surf.servoTimeDelay_s = 1 * 1/50; % FIXIT - Guess
        Surf.servoFreeplay_rad = 0.5 * d2r; % FIXIT - Guess
        
    otherwise
        
end

%% Linkage Model Parameters
% Add parameters for the linkage, these are aircraft specific and hence populated with generic values
Surf.linkPosLim_rad = Surf.servoPosLim_rad;
Surf.linkNegLim_rad = -Surf.servoNegLim_rad;
Surf.linkFreeplay_rad = 0.0;

