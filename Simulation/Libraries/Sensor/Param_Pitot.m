function [Pitot] = Param_Pitot(Sim, Pitot)
% Define the Pitot Model Parameters

hz2rps = 2*pi;

if ~isfield(Pitot, 'errEnable'), Pitot.errEnable = 1; end

[Pitot] = Param_Pd(Sim.typePd, Pitot);
[Pitot] = Param_Ps(Sim.typePs, Pitot);

% Create Transfer Functions for the tube response
if ~isfield(Pitot, 'tubeLength_m'), Pitot.tubeLength_m = 0.5; end
if ~isfield(Pitot, 'vSound_mps'), Pitot.vSound_mps = 340; end % FIXME - Environment Driven
if ~isfield(Pitot, 'tubeDamp_nd'), Pitot.tubeDamp_nd = 0.3; end % Worst-case for resonable lengths

if ~isfield(Pitot, 'tubeBw_rps'), Pitot.tubeBw_rps = Pitot.vSound_mps / (4*Pitot.tubeLength_m) * hz2rps; end % Bandwidth

Pitot.tubeTF_num = [Pitot.tubeBw_rps^2];
Pitot.tubeTF_den = [1, 2*Pitot.tubeDamp_nd*Pitot.tubeBw_rps, Pitot.tubeBw_rps^2];

end

function [Pitot] = Param_Ps(Sim, Pitot)
% Static Pressure Transducer

hz2rps = 2*pi;

switch lower(Sim)
    case 'ams5915-1200-b' % (FIXME - Check all values!!)
        
        % Create Transfer Functions for the transducer response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % Static Pressure Transfer Function
        Pitot.PsBw_rps = (0.35 / 0.001) * hz2rps; % Bandwidth, Rise time is 0.5-1.0 ms
        Pitot.PsTF_num = Pitot.PsBw_rps;
        Pitot.PsTF_den = [1, Pitot.PsBw_rps];
        
        % Temperature Transfer Function
        Pitot.tempBw_rps = Pitot.PsBw_rps; % Bandwidth
        Pitot.tempTF_num = Pitot.PsTF_num;
        Pitot.tempTF_den = Pitot.PsTF_den;
        
        % Time delay, measurement to signal
        Pitot.PsTimeDelay_s = 1 / (1000); % Assume 1 frame at Specified "Reaction Time"
        Pitot.tempTimeDelay_s = Pitot.PsTimeDelay_s;
        
        % Time sample, used for Noise Generation only
        Pitot.timeSample_s = 1/1000;
        
        % Dynamic Pressure Error Model
        Pitot.PsScf = 1;
        Pitot.PsBias = 0; % Pa
        Pitot.PsSigma = 15.0 * 50; % Pa
        Pitot.PsSeed = randi([1, intmax('int16')], 1); % Noise Seed
        
        % Temperature Error Model
        Pitot.tempScf = 1;
        Pitot.tempBias = 0; % K
        Pitot.tempSigma = 0.5; % K
        Pitot.tempSeed = randi([1, intmax('int16')], 1); % Noise Seed
    otherwise
end
end

function [Pitot] = Param_Pd(Sim, Pitot)
% Dynamic Pressure Transducer

hz2rps = 2*pi;

switch lower(Sim)
    case 'ams5915-0020-d-b' % (FIXME - Check all values!!)
        
        % Create Transfer Functions for the transducer response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % Dynamic Pressure Transfer Function
        Pitot.PdBw_rps = (0.35 / 0.001) * hz2rps; % Bandwidth, Rise time is 0.5-1.0 ms
        Pitot.PdTF_num = Pitot.PdBw_rps;
        Pitot.PdTF_den = [1, Pitot.PdBw_rps];
        
        % Temperature Transfer Function
        Pitot.tempBw_rps = Pitot.PdBw_rps; % Bandwidth
        Pitot.tempTF_num = Pitot.PdTF_num;
        Pitot.tempTF_den = Pitot.PdTF_den;
        
        % Time delay, measurement to signal
        Pitot.PdTimeDelay_s = 1 / (1000); % Assume 1 frame at Specified "Reaction Time"
        Pitot.tempTimeDelay_s = Pitot.PdTimeDelay_s;
        
        % Time sample, used for Noise Generation only
        Pitot.timeSample_s = 1/1000;
        
        % Dynamic Pressure Error Model
        Pitot.PdScf = 1;
        Pitot.PdBias = 0; % Pa
        Pitot.PdSigma = 15.0 * 4; % Pa
        Pitot.PdSeed = randi([1, intmax('int16')], 1); % Noise Seed
        
        % Temperature Error Model
        Pitot.tempScf = 1;
        Pitot.tempBias = 0; % K
        Pitot.tempSigma = 0.5; % K
        Pitot.tempSeed = randi([1, intmax('int16')], 1); % Noise Seed
    otherwise
end
end

