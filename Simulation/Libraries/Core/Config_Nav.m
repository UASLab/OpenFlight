function [Nav] = Config_Nav(Nav)
% Configures the Aux Navigation Simulation Environment
%
%Usage:  [Nav] = Config_Nav(Nav);
%
%Inputs:
% Nav       - Simulation Configuration Structure []
%
%Outputs:
% Nav       - Simulation Configuration Structure
%
%Notes:
% 
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.


%% Check I/O Arguments
narginchk(0, 1);
if nargin < 1, Nav = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(Nav), Nav = []; end

% Set Default for VarSel
if ~isfield(Nav, 'VarSel'), Nav.VarSel = []; end
if isempty(Nav.VarSel),  Nav.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarNav_Simp', Simulink.Variant('VarNavSel == 1')); % Variant 1 - Simplified, Compatible with Local Level EOM


%% Select the Variant
switch Nav.VarSel
    case {1, 'Simp'}
        Nav.VarSel = 1;
        
        % Load the EGM-96 Data, FIXIT - Move to Param_Nav()
        load('egm96');
        Nav.lat_deg = Lat;
        Nav.lon_deg = Lon;
        Nav.altErr_m = Alterr;
        Nav.wgs84Corr = -0.53;

    case {2, 'AeroBlock'}
        Nav.VarSel = 2;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarNavSel', Nav.VarSel);


%% Model Bus
% Define the bus
busNames = {'altMsl_m', 'altAgl_m', 'vGrnd_mps', 'gamma_rad', 'course_rad'};
Nav.BusNav = CreateBus(busNames);

% Assign the bus to the base Workspace
assignin('base', 'BusNav', Nav.BusNav);

