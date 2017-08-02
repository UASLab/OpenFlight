function [AirBird] = Param_AirBird(Sim, AirBird)
% Define the AirBird Model Parameters
% NASA "Bird" Null-Seeking Anemometers

hz2rps = 2*pi;

if ~isfield(AirBird, 'errEnable'), AirBird.errEnable = 1; end

% Create Transfer Functions for the transducer response
% Keep numerator and denominator seperate for entry into Simulink TF block
% Anemometer Transfer Function
AirBird.velBw_rps = 20 * hz2rps; % Bandwidth
AirBird.velTF_num = AirBird.velBw_rps;
AirBird.velTF_den = [1, AirBird.velBw_rps];

% Alpha Vane Transfer Function
AirBird.alphaBw_rps = 10 * hz2rps; % Bandwidth
AirBird.alphaTF_num = AirBird.alphaBw_rps;
AirBird.alphaTF_den = [1, AirBird.alphaBw_rps];

% Beta Vane Transfer Function
AirBird.betaBw_rps = 10 * hz2rps; % Bandwidth
AirBird.betaTF_num = AirBird.betaBw_rps;
AirBird.betaTF_den = [1, AirBird.betaBw_rps];

% Anemometer Error Model
AirBird.velScf = 1;
AirBird.velBias = 0; % m/s
AirBird.velSigma = 0.001; % m/s
AirBird.velSeed = randi([1, intmax('int16')], 1); % Noise Seed

% Alpha Vane Error Model
AirBird.alphaScf = 1;
AirBird.alphaBias = 0; % rad
AirBird.alphaSigma = 0.0000005; % rad
AirBird.alphaSeed = randi([1, intmax('int16')], 1); % Noise Seed

% Beta Vane Error Model
AirBird.betaScf = 1;
AirBird.betaBias = 0; % rad
AirBird.betaSigma = 0.0000005; % rad
AirBird.betaSeed = randi([1, intmax('int16')], 1); % Noise Seed

% Time delay, measurement to signal
AirBird.timeDelay_s = 0.001; % (FIXME - Check all values!!)

% Time sample, used for Noise Generation only
AirBird.timeSample_s = 1/100;


