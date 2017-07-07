function [Sim, Surf] = Config_Servo(Sim, Surf)
% Define the Control Surface Model Parameters

hz2rps = 2*pi;
d2r = pi/180;
%

%% Servo Model Parameters
switch lower(Sim.servoType)
    case lower({'Hitec_HS-225BB', '225BB'}) % HiTec HS-225BB
        
        Surf.servoBw_rps = 8.0 * hz2rps; % FIXIT - Guess
        Surf.servoDamp_nd = 1.0; % FIXIT - Guess
        Surf.servoRateLim_rps = 150 * d2r; % FIXIT - Guess
        Surf.servoLimPos_rad = 90 * d2r; % FIXIT - Guess
        Surf.servoLimNeg_rad = -90 * d2r; % FIXIT - Guess
        
        Surf.servoTimeDelay_s = 1 * 1/50; % FIXIT - Guess
        Surf.servoFreeplay_rad = 0.5 * d2r; % FIXIT - Guess
        
    case lower({'Futaba_BLS471SV', 'BLS471SV'}) % Futaba BLS471SV
        % These are the Test Results using SBUS input
        
        Surf.servoBw_rps = 30 * hz2rps; % Servo Bandwidth @ 5 deg amplitude
        Surf.servoDamp_nd = 0.8; % FIXIT - Guess
        Surf.servoRateLim_rps = 1200 * d2r;
        Surf.servoLimPos_rad = 90 * d2r;
        Surf.servoLimNeg_rad = -90 * d2r;
        
        Surf.servoTimeDelay_s = 0.007;
        Surf.servoFreeplay_rad = 0.2 * d2r;
        
    otherwise
        
end


