function [longmod, spmod, latmod, linmodel] = LinearizeSim(simModel, OperatingPoint, AC)
% [longmod, spmod, latmod, linmodel = LinearizeSim(simModel, OperatingPoint, AC)
%
% Linearizes the UAV model about a given operating point.
% This function will use your workspace variables. 
% Requires the Control System Toolbox and Simulink Control Design.
%
% Inputs:
%   OperatingPoint - Operating point object of a trim condition
%   use_uvw        - boolean flag to use u,v,w as linear model outputs 
%                     instead of V, alpha, beta; defaults to "false"
%   verbose        - boolean flag to suppress output; default "true"
%
% Outputs:
%   longmod  - longitudinal linear model
%   spmod    - short period approximation
%   latmod   - lateral directional linear model
%   linmodel - full linear model
%
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2011 Regents of the University of Minnesota. 
% All rights reserved.
%

%% Load model into memory
isLoaded = bdIsLoaded(simModel); % check to see if model is loaded or open
if ~isLoaded
    load_system(simModel) % load model into system memory without opening diagram
end

%% LINEARIZE

% Set inputs
io(1) = linio('SimNL/Trim and Linearization Help/Actuator State Bus', 1, 'in');

% Set outputs
for k = 1:14 
    io(k+1)  = linio('SimNL/Aircraft States', k, 'out');
end

% Obtain lineariziation
linmodel = linearize(simModel, OperatingPoint.op_point, io);




% Longitudinal and lateral models are only generated for UltraSticks not
% miniMUTT (miniMUTT does not have a clear decoupling of both motions)
switch lower(AC.aircraft)
    case {'ultrastick120', 'ultrastick25e'} 
        
        set(linmodel, 'InputName', {'\delta_t';'\delta_e'; '\delta_r' ;'\delta_aL';'\delta_aR';'\delta_fL';'\delta_fR'});
        set(linmodel, 'OutputName',{'phi'; 'theta';'psi';'p';'q';'r';'ax';'ay';'az';'V'; 'beta'; 'alpha'; 'h'; 'gamma'});
        NewStateNames = {'phi';'theta';'psi';'p';'q';'r';'u';'v';'w';'Xe';'Ye';'Ze'};
        linmodel.StateName(1:length(NewStateNames)) = NewStateNames;
        
        %% GENERATE LONGITUDINAL LINEAR MODEL
        % Longitudinal dynamics
        % States: u(7)  w(9)  q(5) theta(2) Ze(12) omega(13)
        % Inputs: elevator(2) throttle(1)
        % Outputs: Vs(10) alpha(12) q(5) theta(2) h (13) ax(7) az(9)
        
        % Generate State-space matrices for Longitudinal Model
        % Indices for desired state, outputs, and inputs
        Xlon = [7 9 5 2 12 13];
        Ylon = [10 12 5 2 13 7 9];
        Ilon = [2 1];
        longmod = modred(linmodel(Ylon,Ilon),setdiff(1:13,Xlon),'Truncate');
        longmod = xperm(longmod,[3 4 2 1 5 6]); % reorder state
        fprintf('\n  Longitudinal Model\n------------------------\n');
        longmod
        fprintf('\n\nLongitudinal Poles:');
        damp(longmod)
        
        %% GENERATE SHORT PERIOD LINEAR MODEL
        % Short period dynamics
        % States:   w(9)  q(5)
        % Inputs: elevator(2)
        % Outputs:  alpha(12) q(5) az(9)
        
        % Generate State-space matrices for Longitudinal Model
        % Indices for desired state, outputs, and inputs
        Xlon = [9 5];
        Ylon = [12 5 9];
        Ilon = 2;
        spmod = modred(linmodel(Ylon,Ilon),setdiff(1:13,Xlon),'Truncate');
        fprintf('\n  Short Period Model\n------------------------\n');
        spmod
        fprintf('\n\nShort Period Poles:');
        damp(spmod)
        
        %% GENERATE LATERAL-DIRECTIONAL LINEAR MODEL
        % Lateral-directional dynamics
        % States: v(8) p(4) r(6) phi(1) psi(3)
        % Inputs: aileron(4) aileron(5) rudder(3)
        % Outputs: beta(11) p(4) r(6) phi(1) psi(3)
        
        % Generate State-space matrices for lateral-directional Model
        % Indices for desired state, outputs, and inputs
        Xlat = [8 4 6 1 3];
        Ylat = [11 4 6 1 3];
        Ilat = [4 5 3];
        latmod = modred(linmodel(Ylat,Ilat),setdiff(1:13,Xlat),'Truncate');
        latmod = xperm(latmod,[5 3 4 1 2]); % reorder state
        fprintf('\n\n  Lateral-Directional Model\n-----------------------------\n');
        latmod
        fprintf('\n\nLateral-Directional Poles:');
        damp(latmod)
            
    case 'minimutt'
        
        set(linmodel, 'InputName', {'\delta_t';'\delta_L1'; '\delta_L2' ;'\delta_L3';'\delta_L4';'\delta_R1';'\delta_R2';'\delta_R3';'\delta_R4'});
        set(linmodel, 'OutputName',{'phi'; 'theta';'psi';'p';'q';'r';'ax';'ay';'az';'V'; 'beta'; 'alpha'; 'h'; 'gamma'});
        NewStateNames = {'phi';'theta';'psi';'p';'q';'r';'u';'v';'w';'Xe';'Ye';'Ze'};
        linmodel.StateName(1:length(NewStateNames)) = NewStateNames;
        
        longmod = 'no longitudinal model for mini MUTT';
        latmod = 'no lateral model for mini MUTT';
        spmod = 'no short period model for mini MUTT';
end

%% Cleanup
if ~isLoaded
    bdclose(simModel) % clear model from system memory if we had to load it
end
